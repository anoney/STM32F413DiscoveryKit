#include "mbed.h"
#include "BSP_DISCO_F413ZH\\Drivers\\BSP\\STM32F413H-Discovery\\stm32f413h_discovery.h"
#include "BSP_DISCO_F413ZH\\Drivers\\BSP\\STM32F413H-Discovery\\stm32f413h_discovery_ts.h"
#include "BSP_DISCO_F413ZH\\Drivers\\BSP\\STM32F413H-Discovery\\stm32f413h_discovery_lcd.h"

TS_StateTypeDef  TS_State = {0};

int main()
{
    uint16_t x1, y1;

    BSP_LCD_Init();

    /* Touchscreen initialization */
    if (BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize()) == TS_ERROR) {
        printf("BSP_TS_Init error\n");
    }

    /* Clear the LCD */
    BSP_LCD_Clear(LCD_COLOR_WHITE);

    /* Set Touchscreen Demo1 description */
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 40);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DisplayStringAt(0, 15, (uint8_t *)"Touch the screen", CENTER_MODE);

    while (1) {
        BSP_TS_GetState(&TS_State);
        if(TS_State.touchDetected) {
            /* One or dual touch have been detected          */

            /* Get X and Y position of the first touch post calibrated */
            x1 = TS_State.touchX[0];
            y1 = TS_State.touchY[0];
            printf("Touch Detected x=%d y=%d\n", x1, y1);

            BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
            BSP_LCD_FillCircle(x1, y1, 20);

            thread_sleep_for(10);
        }
    }
}
