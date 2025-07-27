#include "key_bsp.h"
#include "gpio.h"
#include "main.h"

#include "system_bsp.h"

tUniversalButton vf07_key1;
tUniversalButton vf07_key2;
tUniversalButton vf07_key3;

unsigned char GetKey1Gpio()
{
    return HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6);
}

unsigned char GetKey2Gpio()
{
    return HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_7);
}

unsigned char GetKey3Gpio()
{
    return HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8);
}

// 按键处理
void Key1Handler(eKeyState xKeyValue)
{

    switch (xKeyValue)
    {
    case eKeyO:
    {
        zzarc_vf07.oled_enter_key = 1;
    }
    break;
    case eKeyOO:
    {
        zzarc_vf07.oled_back_key = 1;
    }
    break;
    case eKeyOX:
    {
    }
    break;
    default:
    {
        // 其他按键
    }
    }
}

void Key2Handler(eKeyState xKeyValue)
{

    switch (xKeyValue)
    {
    case eKeyO:
    {
        zzarc_vf07.oled_down_key = 1;
    }
    break;
    case eKeyOO:
    {
    }
    break;
    case eKeyOX:
    {
    }
    break;
    default:
    {
        // 其他按键
    }
    }
}

void Key3Handler(eKeyState xKeyValue)
{

    switch (xKeyValue)
    {
    case eKeyO:
    {
        zzarc_vf07.oled_up_key = 1;
    }
    break;
    case eKeyOO:
    {
    }
    break;
    case eKeyOX:
    {
    }
    break;
    default:
    {
        // 其他按键
    }
    }
}

void BspKeyInit(tUniversalButton *xKey, unsigned char (*xGetGpio)())
{
    xKey->ReadGPIO = xGetGpio;
    xKey->GetTimeTampMs = HAL_GetTick;

    xKey->KeyStateTmp = 0;
    xKey->KeyDitherElimination = 0;
    xKey->PressTimePress = 0;
    xKey->PressTimeRepre = 0;
    xKey->KeyDelta = 0;
    xKey->KeyStateArr[0] = 0;
    xKey->KeyStateArr[1] = 0;
    xKey->KeyStateArr[2] = 0;
    xKey->i_index = 0;
    xKey->OutATime = 0;
    xKey->KeyDataOut = 0;

    xKey->InitFlg = 0x0A;
}

void BspKeyInstantiation(void)
{
    BspKeyInit(&vf07_key1, GetKey1Gpio);
    BspKeyInit(&vf07_key2, GetKey2Gpio);
    BspKeyInit(&vf07_key3, GetKey3Gpio);
}
