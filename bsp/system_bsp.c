#include "system_bsp.h"

tTimeCounterCC systick_counter_8ms = { 0, 0 };
tTimeCounterCC systick_counter_20ms = { 0, 0 };

t_vf07 zzarc_vf07 = {0};

void system_bsp_init(void)
{
	BspKeyInstantiation();
	OLED_UI_Init(&MainMenuPage);
}

void system_bsp_test_loop(void)
{
  while (1)
  {
//	zzarc_vf07.system_tick = HAL_GetTick();
  
    INTERMITTENT_SERVICE(systick_counter_8ms, HAL_GetTick(), 8)
    {
       zzarc_vf07.key1_state = KeyLoop(&vf07_key1);
       zzarc_vf07.key2_state = KeyLoop(&vf07_key2);
       zzarc_vf07.key3_state = KeyLoop(&vf07_key3);
	   
       Key1Handler(zzarc_vf07.key1_state);
       Key2Handler(zzarc_vf07.key2_state);
       Key3Handler(zzarc_vf07.key3_state);
	   
    }
	
    INTERMITTENT_SERVICE(systick_counter_20ms, HAL_GetTick(), 20)
    {
        OLED_UI_MainLoop();
    }
  }
}
