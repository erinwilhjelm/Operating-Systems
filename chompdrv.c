#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <libusb-1.0/libusb.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/joystick.h>
#include <iostream>

using namespace std;


int fd;
struct libusb_device_handle *dev;

void emit(int fd, int type, int code, int val)

{

    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;
    write(fd, &ie, sizeof(ie));

}


int setup()
{

    int err = 0;
    struct uinput_setup usetup;

    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0)

    {
        printf("device not found");
        exit(-1);

    }


    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_EVBIT, EV_SYN);
    ioctl(fd, UI_SET_KEYBIT, BTN_A);
    ioctl(fd, UI_SET_EVBIT, EV_ABS);
    ioctl(fd, UI_SET_ABSBIT, ABS_X);
    ioctl(fd, UI_SET_ABSBIT, ABS_Y);

    memset(&usetup, 0, sizeof(usetup));

    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x9A7A;
    usetup.id.product = 0xBA17;

    strcpy(usetup.name, "chompdrv");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);

    libusb_init(NULL);
    dev = libusb_open_device_with_vid_pid(NULL, 39546, 47639);

    if (dev == NULL)
    {
        printf("device could not open");
        return -1;

    }

    libusb_claim_interface(dev, 0);
    libusb_set_interface_alt_setting(dev, 0, 0);

    return 1;

}



void input(int x, int y, int button)
{

    if (x == 1)
    {
        emit(fd, EV_ABS, ABS_X, -32767);
        emit(fd, EV_SYN, SYN_REPORT, 0);
    }

    else if (x == 2)
    {
        emit(fd, EV_ABS, ABS_X, 0);
        emit(fd, EV_SYN, SYN_REPORT, 0);
    }


    else if (x == 3)
    {
        emit(fd, EV_ABS, ABS_X, 32767);
        emit(fd, EV_SYN, SYN_REPORT, 0);
    }


    if (button == 1)
    {

        emit(fd, EV_KEY, BTN_A, 1);
        emit(fd, EV_SYN, SYN_REPORT, 0);

    }

    else if (button == 0)
    {

        emit(fd, EV_KEY, BTN_A, 0);
        emit(fd, EV_SYN, SYN_REPORT, 0);

    }

    if (y == 1)
    {

        emit(fd, EV_ABS, ABS_Y, 32767);
        emit(fd, EV_SYN, SYN_REPORT, 0);

    }

    else if (y == 2)
    {

        emit(fd, EV_ABS, ABS_Y, 0);
        emit(fd, EV_SYN, SYN_REPORT, 0);

    }

    else if (y == 3)
    {

      emit(fd, EV_ABS, ABS_Y, -32767);
      emit(fd, EV_SYN, SYN_REPORT, 0);

    }
}



int main()

{

    int i =  setup();
    if (i == -1)
    {
        printf("Error");
        return -1;
    }

    int size;
    unsigned char data[1];

    while (1)
    {

        libusb_interrupt_transfer(dev, 0x81, data, sizeof(data), &size, 1000);

        unsigned char bits[8];
        unsigned char byte = data[0];

    	for (i = 0; i < 8; i++) {

        	bits[i] = '0' + ((byte & (1 << i)) != NULL);
	}

        int x, y, button;
        button = bits[4] - '0';
        x = (bits[2] - '0') + 2 * (bits[3] - '0');
        y = (bits[0] - '0') + 2 * (bits[1] - '0');

        input(x, y, button);

    }

    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
    libusb_close(dev);
    libusb_exit(NULL);
    return (0);

}

