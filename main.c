#include <stdio.h>
#include <msp430.h> 
#include "WD3703.h"
#include "LCD12864.h"
#include "UCS_INIT.h"
/**
 * hello.c
 */

float temp=0;
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Lcd12864_Init();
	 UCS_init();
	while(1)

	{

	    temp= WD3703_Read_Temperature();
	    sprintf(tab_SPI3,"%.2f ", temp);
	    lcd12864_disp_str(1,1, tab_SPI3);
  
  
	}
	
	
}
