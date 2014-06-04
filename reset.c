
#include <libusb.h>

#include <stdio.h>

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

	libusb_detach_kernel_driver(dev, 0);
	libusb_reset_device(dev);
	libusb_close(dev);

	libusb_exit(NULL);
	return 0;
}
