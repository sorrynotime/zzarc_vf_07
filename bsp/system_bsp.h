#ifndef SYSTEM_BSP_H
#define SYSTEM_BSP_H

#include "main.h"
#include "qthezg.h"

#include "key_bsp.h"

#include "OLED_UI.h"
#include "OLED_UI_MenuData.h"

#include "file_operate.h"

extern t_vf07 zzarc_vf07;

void system_bsp_init(void);
void system_bsp_test_loop(void);

#endif // SYSTEM_BSP_H
