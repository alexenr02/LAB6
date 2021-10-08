/*
 * Lab6_SE.c
 *
 * Created: 3/26/2021 4:29:27 PM
 * Author : L03068681
 */ 


#include "sam.h"
#define PINCFG_CONFIG_VALUE 0b00000000

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();

	//PORT configuration for general-purpose PIN
		PORT->Group[0].PINCFG[14].reg = PINCFG_CONFIG_VALUE;
		PORT->Group[0].DIRSET.reg = PORT_PA14;
		
	//TIMER configuration
		//Configure the POWER MANAGER to enable the TC3 module
			PM->APBCMASK.reg |= PM_APBCMASK_TC3;
		//Configure the GENERIC CLOCK CONTROL used by the TC3 module
			GCLK->GENDIV.reg = 0x00;
			GCLK->GENCTRL.reg = 0x10600;
			GCLK->CLKCTRL.reg = 0x401B;
		//Determine the initial count
		//Time = Toscillator * (2^TIMERMODE - COUNT) * Prescaler
			TC3->COUNT16.COUNT.reg = 65307;
		//Configure the TC3 peripheral
			TC3->COUNT16.CTRLA.reg = 0X00;
			TC3->COUNT16.CTRLBSET.reg = 0X00;
			TC3->COUNT16.INTFLAG.reg = 0X01;
		//Enabling the TC3 peripheral
			TC3->COUNT16.CTRLA.reg |= 0x2;
		//Loop to sync the TC clock with the processor/main clock
			while ((TC3->COUNT16.STATUS.reg & 0x80) == 0x80){
				//not synchronize
			}
			
		/***************************************************************************/
          	//Loop to generate the square-wave signal
            //EXTRA cycles to ADD to the initial count---it will be still a 
            //polling-error of +/- 7 us in the period of the signal
            //LDRB(4) + ANDS(1) + BEQ(2) + LDRB(4) + ANDS(1) + BEQ(1) + STR(4) + 
            //STRB(4) + STRH(4) + B(2) = 27 cycles 

    /* Replace with your application code */
    while (1) 
    {
		while (TC3->COUNT16.INTFLAG.reg & 0x1 == 0x0){
			//loop
		}
		PORT->Group[0].OUTTGL.reg = 0x04000;
		TC3->COUNT16.INTFLAG.reg = 0X01;
		TC3->COUNT16.COUNT.reg = 65307;
    }
}