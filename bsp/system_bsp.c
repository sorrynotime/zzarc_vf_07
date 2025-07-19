#include "system_bsp.h"


tTimeCounterCC systick_counter_20ms = { 0, 0 };

t_vf07 zzarc_vf07 = {0};

void system_bsp_init(void)
{
  // TODO: Initialize the system
  OLED_UI_Init(&MainMenuPage);
}

void system_bsp_test_loop(void)
{
  while (1)
  {
	zzarc_vf07.system_tick = HAL_GetTick();
    INTERMITTENT_SERVICE(systick_counter_20ms, HAL_GetTick(), 20)
    {
        // Perform periodic tasks here
        // For example, update the OLED display or check system status
        OLED_UI_MainLoop();
    }
  }
}
