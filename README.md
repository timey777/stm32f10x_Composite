# STM32 Makefile

### build project

```
$ make
```
```
$ openocd -f interface/cmsis-dap.cfg -c "program stm32f10x_makefile_freertos.bin verify reset exit 0x08000000"
```