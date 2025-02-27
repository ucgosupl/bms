#include "stm32f4xx_hal.h"

extern void hal_init(void);

int main(void)
{
  hal_init();

  while (1)
  {
	  HAL_Delay(100);
  }
}

