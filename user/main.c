#include "hw_config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "uart_log.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "string.h"
__IO uint8_t bCompleteState = 0;

extern QueueHandle_t xUartQueue;
/////////////////////////////////
extern __IO uint8_t Receive_Buffer[64];
extern __IO uint32_t Receive_length;
extern __IO uint32_t length;
uint8_t Send_Buffer[64];
uint32_t packet_sent = 1;
uint32_t packet_receive = 1;

uint8_t Keyboard_Buffer[9] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t bKeyboardDirty = 0;
uint8_t Mouse_Buffer[5] = {2, 0, 0, 0, 0};
uint8_t bMouseDirty = 0;

void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--)
        ;
}

void RCC_Configuration(void)
{
    /* GPIOA, GPIOB clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    /* USB clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOB Pin 11 configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* USB D+ and D- configuration (GPIOA Pin 11 and Pin 12) */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void CDCSend(unsigned char *buf)
{
    if (packet_sent == 1)
        CDC_Send_DATA((unsigned char *)buf, strlen(buf));
}
void CDCSendByLength(unsigned char *buf, int len)
{
    if (packet_sent == 1)
        CDC_Send_DATA((unsigned char *)buf, len);
}
void Send_Keyboard_Report(uint8_t Keyboard_Buffer[9])
{
    if (!bCompleteState)
    {
        /* Reset the control token to inform upper layer that a transfer is ongoing */
        bCompleteState = 2;

        /* Copy keyboard report info in ENDP1 Tx Packet Memory Area */
        USB_SIL_Write(EP4_IN, Keyboard_Buffer, 9);

        /* Enable endpoint for transmission */
        SetEPTxValid(ENDP4); // Mark endpoint as ready for transmission
    }
    else
    {
        // debug("Previous transfer not complete\r\n");
    }
}
void Send_Mouse_Report(uint8_t Mouse_Buffer[5])
{
    if (!bCompleteState)
    {
        /* Reset the control token to inform upper layer that a transfer is ongoing */
        bCompleteState = 1;

        /* Copy mouse position info in ENDP1 Tx Packet Memory Area */
        USB_SIL_Write(EP4_IN, Mouse_Buffer, 5);

        /* Enable endpoint for transmission */
        SetEPTxValid(ENDP4); // Mark endpoint as ready for transmission
    }
    else
    {
        // debug("Previous transfer not complete\r\n");
    }
}
bool IsBufferAllZero(uint8_t *buf, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        if (buf[i] != 0)
        {
            return 0;
        }
    }
    return 1;
}
bool ApplyBuffer(uint8_t *buf, uint32_t len)
{
    if (buf[0] == 0x01 && len == 10)
    {
        bKeyboardDirty = 2;
        if (buf[1] == 1 || IsBufferAllZero(buf + 2, 8))
        {
            // If the buffer is all zero, set the dirty flag to 1
            bKeyboardDirty = 1;
        }
        // Process keyboard report
        memcpy(Keyboard_Buffer + 1, buf + 2, 8);
        //CDCSend("OK\r\n");
    }
    else if (buf[0] == 0x02 && len == 6)
    {
        bMouseDirty = 2;
        if (buf[1] == 1 || IsBufferAllZero(buf + 2, 4))
        {
            // If the buffer is all zero, set the dirty flag to 1
            bMouseDirty = 1;
        }
        // Process mouse report
        memcpy(Mouse_Buffer + 1, buf + 2, 4);
        //CDCSend("OK\r\n");
    }
    else
    {
        return 0;
    }
    return 1;
}
void vTaskFunction(void *pvParameters)
{
    while (1)
    {
        if (bDeviceState == CONFIGURED)
        {
            CDC_Receive_DATA();
            /*Check to see if we have data yet */
            if (Receive_length != 0)
            {
                if (ApplyBuffer(Receive_Buffer, Receive_length))
                {
                    //CDCSend("OK\r\n");
                }
                else
                {
                    //CDCSendByLength(Receive_Buffer, Receive_length);
                    CDCSend("ERROR\r\n");
                }
                Receive_length = 0;
            }
        }
    }
}

// New task for UART echo
void vUartEchoTask(void *pvParameters)
{
    uint8_t received_char;
    while (1)
    {
        if (xQueueReceive(xUartQueue, &received_char, portMAX_DELAY) == pdPASS)
        {
            printchar(NULL, (unsigned int)received_char); // Echo the received character
        }
    }
}

// New task for UART echo
void vKeyboardMouseTask(void *pvParameters)
{
    uint8_t sendKeyboard = 1; // Flag to alternate between keyboard and mouse

    while (1)
    {
        if (bDeviceState == CONFIGURED)
        {
            if (sendKeyboard)
            {
                if (bKeyboardDirty)
                {
                    if (bKeyboardDirty == 1)
                    {
                        bKeyboardDirty = 0;
                    }
                    Send_Keyboard_Report(Keyboard_Buffer);
                }
            }
            else
            {
                if (bMouseDirty)
                {
                    if (bMouseDirty == 1)
                    {
                        bMouseDirty = 0;
                    }
                    //CDCSend("Mouse\r\n");
                    Send_Mouse_Report(Mouse_Buffer);
                }
            }

            sendKeyboard = !sendKeyboard; // Toggle between keyboard and mouse
        }
        vTaskDelay(1); // Delay to prevent busy waiting
    }
}

int main()
{
    // init uart log
    uart_log_init();

    RCC_Configuration();
    GPIO_Configuration();

    debug("start main\r\n");
    /* Initialize USB HID */
    Set_USBClock();
    USB_Interrupts_Config();
    USB_Init();

    const char *pcTextForTask1 = "Task1 is running\r\n";

    BaseType_t xReturn = xTaskCreate(vTaskFunction, "Task 1", 128, (void *)pcTextForTask1, 1, NULL);
    if (xReturn != pdPASS)
    {
        debug("Task create failed!\r\n");
        while (1)
            ;
    }

    // Create UART echo task
    xReturn = xTaskCreate(vKeyboardMouseTask, "UART Echo Task", 128, NULL, 1, NULL);
    if (xReturn != pdPASS)
    {
        debug("UART Echo Task create failed!\r\n");
        while (1)
            ;
    }

    vTaskStartScheduler();

    while (1)
        ;

    return 0;
}