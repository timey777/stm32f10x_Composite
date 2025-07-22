# STM32 Makefile
这是一个stm32f103c8tx的键盘鼠标和虚拟串口的复合设备,使用freeRTOS和stm32标准库。
### build project

```
$ make
```
```
$ openocd -f interface/cmsis-dap.cfg -c "program stm32f10x_makefile_freertos.bin verify reset exit 0x08000000"
```
