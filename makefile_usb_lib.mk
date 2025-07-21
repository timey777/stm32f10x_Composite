# source director
STM32F1_USB_LIB     = $(STM32F10x_LIB_DIR)/STM32_USB-FS-Device_Driver
STM32F1_USB_SRC_DIR     = $(STM32F1_USB_LIB)/src
STM32F1_USB_INC_DIR     = $(STM32F1_USB_LIB)/inc

# use libraries, please add or remove when you use or remove it.
SRC  += $(STM32F1_USB_SRC_DIR)/usb_core.c
SRC  += $(STM32F1_USB_SRC_DIR)/usb_init.c
SRC  += $(STM32F1_USB_SRC_DIR)/usb_int.c
SRC  += $(STM32F1_USB_SRC_DIR)/usb_mem.c
SRC  += $(STM32F1_USB_SRC_DIR)/usb_regs.c
SRC  += $(STM32F1_USB_SRC_DIR)/usb_sil.c

# include directories
INCLUDE_DIRS += $(STM32F1_USB_INC_DIR)
