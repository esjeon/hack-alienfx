
#include <libusb.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int
main() {
	libusb_device_handle *dev;
	int ret;

	ret = libusb_init(NULL);
	if(ret != 0) {
		fprintf(stderr, "failed to initialize libusb\n");
		return 1;
	}

	// DEBUG
	libusb_set_debug(NULL, LIBUSB_LOG_LEVEL_DEBUG);

	dev = libusb_open_device_with_vid_pid(NULL, 0x187c, 0x0525);
	if(dev == NULL) {
		fprintf(stderr, "failed to open usb device\n");
		return 1;
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
		goto bye_kernel;
	}

	// CLEAR_FEATURE REMOTE_WAKEUP
	// --> Unsupported. We get -EPIPE
	//ret = libusb_control_transfer(dev,
	//		LIBUSB_REQUEST_TYPE_STANDARD,
	//		LIBUSB_REQUEST_CLEAR_FEATURE,
	//		1, // USE_DEVICE_REMOTE_WAKEUP, in linux/usb/ch9.h
	//		0, buf, 0, 0
	//);

	// UNKOWN
	//{
	//	unsigned char buf[10] = {0, };
	//	ret = libusb_control_transfer(dev, 0x21, 10, 0, 0, buf, 0, 0);
	//	if(ret < 0) {
	//		eprint("control_transfer failed", ret);
	//	}
	//}

	//{ // reset all
	//	unsigned char buf[9] = { 0x02, 0x07, 0x04, 0, };
	//	ret = libusb_control_transfer(dev, 0x21, 9, 0x0202, 0, buf, 9, 0);
	//	if(ret < 0) {
	//		eprint("(reset) control_transfer failed", ret);
	//	}
	//}

	//{ // reset touchpad
	//	unsigned char buf[9] = { 0x02, 0x07, 0x01, 0, };
	//	ret = libusb_control_transfer(dev, 0x21, 9, 0x0202, 0, buf, 9, 0);
	//	if(ret < 0) {
	//		eprint("(reset) control_transfer failed", ret);
	//	}
	//}

	//{
	//	//unsigned char buf[10] = {0, };
	//	// set touchpad color to purple ... 02030600020030f000
	//	unsigned char buf[9] = { 0x02, 0x03, 0x06, 0x00, 0x02, 0x00, 0x30, 0xf0, 0x00 };
	//	// set touchpad color to orange ... 020306000200f80000
	//	//unsigned char buf[9] = { 0x02, 0x03, 0x06, 0x00, 0x02, 0x00, 0xf8, 0x00, 0x00 };
	//	// set color to purple ... 02030200000230f000
	//	//unsigned char buf[9] = { 0x02, 0x03, 0x06, 0x00, 0x00, 0x02, 0x30, 0xf0, 0x00 };

	//	libusb_control_transfer(dev, 0x21, 9, 0x0202, 0, buf, 9, 0);
	//	if(ret < 0) {
	//		eprint("(color) control_transfer failed", ret);
	//	}
	//}

	//{
	//	unsigned char buf[9] = { 0x02, 0x04, 0, };
	//	ret = libusb_control_transfer(dev, 0x21, 9, 0x0202, 0, buf, 9, 0);
	//	if(ret < 0) {
	//		eprint("control_transfer failed", ret);
	//	}
	//}

	//sleep(5);

bye_interface:
	libusb_release_interface(dev, 0);
bye_kernel:
	//libusb_reset_device(dev);
	(void)ret;//libusb_attach_kernel_driver(dev, 0);
bye_device:
	libusb_close(dev);
	libusb_exit(NULL);
	return 0;
}

