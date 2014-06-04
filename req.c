
#include <libusb.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
eprint(const char* msg, int err) {
	switch(err) {
	case LIBUSB_ERROR_IO:
		fprintf(stderr, "%s: I/O\n", msg);
		break;
	case LIBUSB_ERROR_NOT_FOUND:
		fprintf(stderr, "%s: not found\n", msg);
		break;
	case LIBUSB_ERROR_BUSY:
		fprintf(stderr, "%s: busy\n", msg);
		break;
	case LIBUSB_ERROR_NO_DEVICE:
		fprintf(stderr, "%s: no device\n", msg);
		break;
	case LIBUSB_ERROR_NOT_SUPPORTED:
		fprintf(stderr, "%s: not supported\n", msg);
		break;
	case LIBUSB_ERROR_PIPE:
		fprintf(stderr, "%s: pipe\n", msg);
		break;
	case LIBUSB_ERROR_TIMEOUT:
		fprintf(stderr, "%s: timeout\n", msg);
		break;
	default:
		fprintf(stderr, "%s: errno=%d\n", msg, err);
	}
}

unsigned char
c16tob(char c)
{
	if('0' <= c && c <= '9')
		return c - '0';
	return c - 'a' + 10;
}

int
main(int argc, char *argv[])
{
	unsigned char b;
	unsigned char bytes[9] = {0,};
	char *str = argv[1];
	int len;
	int i, j;

	libusb_device_handle *dev;
	int ret;

	if(argc != 2) {
		fprintf(stderr, "require one argument\n");
		return 1;
	}

	len = strlen(str);
	if(len > 18) {
		fprintf(stderr, "invalid input: too long\n");
		return 1;
	} else if(len % 2 != 0) {
		fprintf(stderr, "invalid input: odd length\n");
		return 1;
	}

	for(i = 0, j = 0; i < len; i +=2, j ++) {
		b = c16tob(str[i+1]);
		b += c16tob(str[i]) * 16;
		bytes[j] = b;
	}

	ret = libusb_init(NULL);
	if(ret != 0) {
		fprintf(stderr, "failed to initialize libusb\n");
		return 1;
	}

	// DEBUG
	libusb_set_debug(NULL, LIBUSB_LOG_LEVEL_ERROR);

	dev = libusb_open_device_with_vid_pid(NULL, 0x187c, 0x0525);
	if(dev == NULL) {
		fprintf(stderr, "failed to open usb device\n");
		goto bye_library;
	}

	{
		int cfg;
		ret = libusb_get_configuration(dev, &cfg);
		if(cfg != 1) {
			ret = libusb_detach_kernel_driver(dev, 0);
			if(ret != 0) {
				if(ret != LIBUSB_ERROR_NOT_FOUND) {
					eprint("failed to detach driver", ret);
					goto bye_device;
				}
			}

			ret = libusb_set_configuration(dev, 1);
			if(ret != 0) {
				eprint("failed to configure the device", ret);
				goto bye_device;
			}
		}
	}

	ret = libusb_claim_interface(dev, 0);
	if(ret != 0) {
		eprint("failed to claim the device", ret);
		goto bye_device;
	}

	ret = libusb_control_transfer(dev, 0x21, 9, 0x0202, 0, bytes, 9, 0);
	if(ret < 0) {
		eprint("(reset) control_transfer failed", ret);
	}

	libusb_release_interface(dev, 0);
bye_device:
	libusb_close(dev);
bye_library:
	libusb_exit(NULL);
	return 0;
}
