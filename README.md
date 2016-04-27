# Easy semihosting

A simple library for handling semihosting operations without std libs like a newlib.

Example builds with arm-none-eabi and requires qemu-system-arm to run

It’s possible to use openocd

```
openocd  -f board/st_nucleo_l1.cfg  -c "init"
```
