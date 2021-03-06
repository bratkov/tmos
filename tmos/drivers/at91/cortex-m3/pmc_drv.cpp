/**************************************************************************//**
 * @file     pmc_drv.cpp
 * @ingroup  DRV_AT91_PMC
 * @brief    PMC driver implementation
 * @version  V3.00
 * @date     28. November 2010
 * @author	 Miroslav Kostadinov
 *
 ******************************************************************************/

#include <tmos.h>
#include "pmc_drv.h"
#include <mcu_cpp.h>
#include <eefc.h>

/**
 * Set the main clock source (RC or XT oscillator)
 * @param pPMC
 * @param val - CKGR_MOR value
 */
void sys_SetMainClock(Pmc* pPMC, unsigned int val)
{
	unsigned int old, temp;

	//enable XT or SC oscillator
	old = pPMC->CKGR_MOR;
	if((old ^ val)& CKGR_MOR_MOSCSEL)
	{

		if(old & CKGR_MOR_MOSCSEL)
		{
			//switch XT -> RC, so first enable RC
			temp = val & (CKGR_MOR_MOSCRCF_Msk | CKGR_MOR_MOSCRCEN | CKGR_MOR_KEY_Msk);
			temp |= (old & ~CKGR_MOR_MOSCRCF_Msk) ;
			old = PMC_SR_MOSCRCS;
		} else
		{
			//switch RC -> XT, so enable XT
			temp = val & ~CKGR_MOR_MOSCSEL;
			temp |= old & (CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCRCF_Msk);
			old = PMC_SR_MOSCXTS;
		}

		pPMC->CKGR_MOR = temp;

		//check the osc is already stable
		while(!(pPMC->PMC_SR & old));

		pPMC->CKGR_MOR = temp ^ CKGR_MOR_MOSCSEL;

		//wait for the switch
		while(!(pPMC->PMC_SR & PMC_SR_MOSCSELS));

	}

	pPMC->CKGR_MOR = val;

	//wait for master clock
	while(!(pPMC->PMC_SR & PMC_SR_MCKRDY));
}

/**
 * Set new system clock
 *
 * @param drv_info - PMC driver info
 * @param new_clk - clock, encodded as follow:
 *  - bit [1:0] - clock source (MCKR_CSS)
 *
 * Details:
 *
 * Switching from one clock source and prescaler to another cannot be done in a
 * single step. And when we change only the source or only the prescaler we must
 * ensure that the intermediate combination is allowed.\n
 * Also this function is run from the flash, so we should avoid forbidden
 * frequencies. For example SAM7S64 series have a bug and they can't work in the
 * 3-19MHz range. \n
 *
 * Algorithm:
 * - STEP 1. If we have to change the clock source, we switch first to a known
 * good slow clock.	The slow clock can be embedded oscillator (RC, fast RC or
 * main) and the selection is defined from the application in the PMC_INFO.
 *
 */
void sys_SetNewClock(PMC_INFO drv_info, unsigned int new_clk)
{
	unsigned int	temp;
	Pmc* pPMC = drv_info->hw_base;

	pPMC->PMC_WPMR = PMC_WPMR_WPKEY(0x504D43);

// STEP 1: If new source != old source => switch to slow clock

	//prepare main clock
	sys_SetMainClock(pPMC, drv_info->CFG_CKGR_MOR);

	temp = pPMC->PMC_MCKR;
	if((new_clk ^ temp) & PMC_MCKR_CSS_Msk)
	{
		temp &= ~ PMC_MCKR_CSS_Msk;
		if(new_clk & PMC_MCKR_CSS_Msk)
		{
			//switch to main clock
			temp |= PMC_MCKR_CSS_MAIN_CLK;
		} else
		{
			//switch to slow clock
			//JTAG can get lost if current prescaler is too high

		}
		pPMC->PMC_MCKR = temp;


		//wait for  clock switch
		while(!(pPMC->PMC_SR & PMC_SR_MCKRDY));

		// we are now using main/slow source, so we can set the prescaler
		temp &= ~PMC_MCKR_PRES_Msk;
		temp |= new_clk & PMC_MCKR_PRES_Msk;
		pPMC->PMC_MCKR = temp;
		//JTAG can get lost now...

		//prescaller change may not be completed
	} else
	{
		// the source is OK, only the prescaller is about to change..
		// If the new clock is lower, we will change the divisor here
		// before we calculate and change the flash wait states.
		if(new_clk > temp)
		{
			pPMC->PMC_MCKR = new_clk;
		}
	}

	//wait until main clock is stable....
	while(!(pPMC->PMC_SR & PMC_SR_MCKRDY));

// STEP 2: We are now running in slow clock or we have reduced the clock
// 		   From now on, we will only increase the clock, but before that
//		   we must prepare the hardware (wait states and osc/pll)

	//calculate the flash wait states <20MHz=0 >30MHz=2
	if((new_clk & PMC_MCKR_CSS_Msk) > PMC_MCKR_CSS_MAIN_CLK)
		temp = EEFC_FMR_FWS(2);
	else
		temp = EEFC_FMR_FWS(0);

	EFC->EEFC_FMR = (EFC->EEFC_FMR & ~EEFC_FMR_FWS_Msk) | temp;



	//check the source
	if((new_clk ^ pPMC->PMC_MCKR ) & PMC_MCKR_CSS_Msk)
	{
		// start pll if required
		if((new_clk & PMC_MCKR_CSS_Msk) == PMC_MCKR_CSS_PLLA_CLK)
		{
			// Start PLL
			pPMC->CKGR_PLLAR = drv_info->CFG_CKGR_PLLAR;
			// Wait PLL
			while(!(pPMC->PMC_SR & PMC_SR_LOCKA));
		}

	}

//STEP 3: set the desired clock and divider if it is not done by now.
	// here the new source is ok...
	// and we know that either the prescaler, either the source is OK (or both)
	pPMC->PMC_MCKR = new_clk;
	//wait until main clock is stable....
	while(!(pPMC->PMC_SR & PMC_SR_MCKRDY));


    //some cleanup...
    temp = sizeof(pPMC->PMC_PCK)/4;
    while(temp--)
    {
    	new_clk |= pPMC->PMC_PCK[temp];
    }

    new_clk &= PMC_MCKR_CSS_Msk;
    //turn off PLL A
    if(new_clk != PMC_MCKR_CSS_PLLA_CLK)
		pPMC->CKGR_PLLAR = drv_info->CFG_CKGR_PLLAR & ~CKGR_PLLAR_MULA_Msk;

    if(new_clk == PMC_MCKR_CSS_SLOW_CLK)
			pPMC->CKGR_MOR = 0;			//turn off oscillator

    new_clk=pPMC->PMC_MCKR;
	temp = drv_info->CFG_FREQUENCIES[new_clk & PMC_MCKR_CSS_Msk];
	temp >>= (new_clk & PMC_MCKR_PRES_Msk) >> 2;
    system_clock_frequency = temp;

}

/** Disables the interrupt for a given driver
 *
 * @param drv_info
 */
void drv_isr_disable(DRIVER_INFO drv_info)
{
	NVIC_DisableIRQ(drv_info->drv_index);
}

/** Enables the pmc/clock for a given driver
 *
 * @param drv_info
 */
void drv_pmc_enable(DRIVER_INFO drv_info)
{
	PMC_EnablePeripheral(drv_info->peripheral_indx);
}

/** Disables the pmc/clock for a given driver
 *
 * @param drv_info
 */
void drv_pmc_disable(DRIVER_INFO drv_info)
{
	PMC_DisablePeripheral(drv_info->peripheral_indx);
}


/**
 * DCR
 * @param drv_info
 * @param reason
 * @param hnd
 */
void PMC_DCR(PMC_INFO drv_info, unsigned int reason, HANDLE hnd)
{

}

/**
 * PMC Driver DSR
 * @param drv_info
 * @param hnd
 */
void PMC_DSR(PMC_INFO drv_info, HANDLE hnd)
{
	ASSERT(0);
}

/**
 * PMC Driver ISR
 * @param drv_info
 */
void PMC_ISR(PMC_INFO drv_info )
{
	ASSERT(0);
}
