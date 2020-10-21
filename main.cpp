#include "mbed.h"

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
constexpr uint32_t lse_drive_levels[] = {
    RCC_LSE_LOWPOWER_MODE,
    RCC_LSE_HIGHDRIVE_MODE
};
#else
constexpr uint32_t lse_drive_levels[] = {
    RCC_LSEDRIVE_LOW,
    RCC_LSEDRIVE_MEDIUMLOW,
    RCC_LSEDRIVE_MEDIUMHIGH,
    RCC_LSEDRIVE_HIGH
};
#endif


DigitalOut  led1(LED1, 1);

void enableLSE(bool enable)
{
    printf("LSE enabled: %s\n", enable ? "true" : "false");

    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.LSEState = enable ? RCC_LSE_ON : RCC_LSE_OFF;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        printf("*** failed to %s LSE\n", enable ? "enable" : "disable");
    }
}

void setLSE_DriveLoad(uint level)
{
    printf("set LSE drive load: %d\n", level);

    if (level >= sizeof(lse_drive_levels)/sizeof(lse_drive_levels[0])) {
        printf("   LSE drive load level out of range\n");
        return;
    }

    // drive level can only be changed when LSE is off
    enableLSE(false);

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
    HAL_RCCEx_SelectLSEMode(lse_drive_levels[level]);
#else
    // set LSE drive level
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(lse_drive_levels[level]);
#endif

    // drive level can only be changed when LSE is off
    enableLSE(true);
}

int main() {
    printf("\n\nTest LSE drive load level configuration\n");
    fflush(stdout);

    // enable MCO output (PA_8)
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_LSE, RCC_MCODIV_1);

    while (1) {
        char ch = getc(stdin);

        switch (toupper(ch))
        {
        case '0':
            enableLSE(false);
            break;
        case '9':
            enableLSE(true);
            break;

        case 'L':
            // this enables LSE when called the first time
            ThisThread::sleep_for(100ms);
            led1 = !led1;
            ThisThread::sleep_for(100ms);
            break;

        default:
            if ((ch >= '1') && (ch <  '1' + sizeof(lse_drive_levels)/sizeof(lse_drive_levels[0]))) {
                setLSE_DriveLoad(ch - '1');
            }
        }
   }
}

