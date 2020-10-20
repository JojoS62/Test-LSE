#include "mbed.h"

constexpr uint32_t lse_drive_levels[] = {
    RCC_LSEDRIVE_LOW,
    RCC_LSEDRIVE_MEDIUMLOW,
    RCC_LSEDRIVE_MEDIUMHIGH,
    RCC_LSEDRIVE_HIGH
};


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

    // set LSE drive level
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(lse_drive_levels[level]);

    // drive level can only be changed when LSE is off
    enableLSE(true);
}

int main() {
    printf("\n\nTest STM32H743VI LSE\n");
    fflush(stdout);

    // enable MCO output (PA_8)
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_LSE, RCC_MCODIV_1);

    while (1) {
        char ch = getc(stdin);

        switch (ch)
        {
        case '0':
            enableLSE(false);
            break;
        case '9':
            enableLSE(true);
            break;

        default:
            if ((ch >= '1') && (ch <= '4')) {
                setLSE_DriveLoad(ch - '1');
            }
        }
   }
}

