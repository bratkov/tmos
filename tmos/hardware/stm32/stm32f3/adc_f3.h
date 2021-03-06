/*
 * adc_f3.h
 *
 *  Created on: Feb 22, 2013
 *      Author: miro
 */

#ifndef ADC_F3_H_
#define ADC_F3_H_


#include <mcu_inc.h>
#include <tmos_types.h>

/*******************************************************************************
 *  Analog to Digital Converter
 ******************************************************************************/
typedef struct
{
  __IO uint32_t ADC_SR;			//!< (adc Offset: 0x000) ADC Status Register
  __IO uint32_t ADC_CR1;        //!< (adc Offset: 0x004) ADC Control Register 1
  __IO uint32_t ADC_CR2;        //!< (adc Offset: 0x008) ADC Control Register 2
  __IO uint32_t ADC_SMPR1;      //!< (adc Offset: 0x00C) ADC Sample time register 1
  __IO uint32_t ADC_SMPR2;      //!< (adc Offset: 0x010) ADC Sample time register 2
  __IO uint32_t ADC_JOFRx[4];   //!< (adc Offset: 0x014) ADC injected channel data offset register x
  __IO uint32_t ADC_HTR;        //!< (adc Offset: 0x024) ADC watchdog high threshold register
  __IO uint32_t ADC_LTR;        //!< (adc Offset: 0x028) ADC watchdog low threshold register
  __IO uint32_t ADC_SQR1;       //!< (adc Offset: 0x02C) ADC regular sequence register 1
  __IO uint32_t ADC_SQR2;       //!< (adc Offset: 0x030) ADC regular sequence register 2
  __IO uint32_t ADC_SQR3;       //!< (adc Offset: 0x034) ADC regular sequence register 3
  __IO uint32_t ADC_JSQR;		//!< (adc Offset: 0x038) ADC injected sequence register
  __IO uint32_t ADC_JDRx[4];	//!< (adc Offset: 0x03C) ADC injected data register x
  __IO uint32_t ADC_DR;         //!< (adc Offset: 0x04C) ADC data register
  __IO uint32_t reserved[44];   //!< (adc Offset: 0x050) reserved
} ADC_TypeDef;

/*******************************************************************************
 * @defgroup ADC_regs_define
 * @{
 ******************************************************************************/

/** @defgroup ADC_SR:		(adc Offset: 0x000) ADC Status Register			  */
#define ADC_SR_STRT                 0x00000010 //!< Regular channel Start flag
#define ADC_SR_JSTRT                0x00000008 //!< Injected channel Start flag
#define ADC_SR_JEOC                 0x00000004 //!< Injected channel end of conversion
#define ADC_SR_EOC                  0x00000002 //!< End of conversion
#define ADC_SR_AWD                  0x00000001 //!< Analog watchdog flag
/** @} */

/** @defgroup ADC_CR1:      (adc Offset: 0x004) ADC Control Register 1		  */
#define ADC_CR1_AWDEN               0x00800000 //!< Analog watchdog enable on regular channels
#define ADC_CR1_JAWDEN              0x00400000 //!< Analog watchdog enable on injected channels
#define ADC_CR1_DISCNUM             0x0000E000 //!< DISCNUM[2:0] bits (Discontinuous mode channel count)
#define ADC_CR1_JDISCEN             0x00001000 //!< Discontinuous mode on injected channels
#define ADC_CR1_DISCEN              0x00000800 //!< Discontinuous mode on regular channels
#define ADC_CR1_JAUTO               0x00000400 //!< Automatic injected group conversion
#define ADC_CR1_AWDSGL              0x00000200 //!< Enable the watchdog on a single channel in scan mode
#define ADC_CR1_SCAN                0x00000100 //!< Scan mode
#define ADC_CR1_JEOCIE              0x00000080 //!< Interrupt enable for injected channels
#define ADC_CR1_AWDIE               0x00000040 //!< AAnalog Watchdog interrupt enable
#define ADC_CR1_EOCIE               0x00000020 //!< Interrupt enable for EOC
#define ADC_CR1_AWDCH               0x0000001F //!< AWDCH[4:0] bits (Analog watchdog channel select bits)
/** @} */

/** @defgroup ADC_CR2:      (adc Offset: 0x008) ADC Control Register 2		  */
#define ADC_CR2_TSVREFE             0x00800000 //!< Temperature Sensor and VREFINT Enable
#define ADC_CR2_SWSTART             0x00400000 //!< Start Conversion of regular channels
#define ADC_CR2_JSWSTART            0x00200000 //!< Start Conversion of injected channels
#define ADC_CR2_EXTTRIG             0x00100000 //!< External Trigger Conversion mode for regular channels
#define ADC_CR2_EXTSEL              0x000E0000 //!< EXTSEL[2:0] bits (External Event Select for regular group)
#define ADC_CR2_JEXTTRIG            0x00008000 //!< External Trigger Conversion mode for injected channels
#define ADC_CR2_JEXTSEL             0x00070000 //!< JEXTSEL[2:0] bits (External event select for injected group)
#define ADC_CR2_ALIGN               0x00000800 //!< Data Alignment
#define ADC_CR2_DMA                 0x00000100 //!< Direct Memory access mode
#define ADC_CR2_RSTCAL              0x00000008 //!< Reset Calibration
#define ADC_CR2_CAL                 0x00000004 //!< A/D Calibration
#define ADC_CR2_CONT                0x00000002 //!< Continuous Conversion
#define ADC_CR2_ADON                0x00000001 //!< A/D Converter ON / OFF
/** @} */

/** @defgroup ADC_SMPR1:    (adc Offset: 0x00C) ADC Sample time register 1	  */
#define ADC_SMPR1_SMP17             0x00E00000 //!< SMP17[2:0] bits (Channel 17 Sample time selection)
#define ADC_SMPR1_SMP16             0x001C0000 //!< SMP16[2:0] bits (Channel 16 Sample time selection)
#define ADC_SMPR1_SMP15             0x00038000 //!< SMP15[2:0] bits (Channel 15 Sample time selection)
#define ADC_SMPR1_SMP14             0x00007000 //!< SMP14[2:0] bits (Channel 14 Sample time selection)
#define ADC_SMPR1_SMP13             0x00000E00 //!< SMP13[2:0] bits (Channel 13 Sample time selection)
#define ADC_SMPR1_SMP12             0x000001C0 //!< SMP12[2:0] bits (Channel 12 Sample time selection)
#define ADC_SMPR1_SMP11             0x00000038 //!< SMP11[2:0] bits (Channel 11 Sample time selection)
#define ADC_SMPR1_SMP10             0x00000007 //!< SMP10[2:0] bits (Channel 10 Sample time selection)
/** @} */

/** @defgroup ADC_SMPR2:    (adc Offset: 0x010) ADC Sample time register 2	  */
#define ADC_SMPR2_SMP9              0x38000000 //!< SMP9[2:0] bits (Channel 9 Sample time selection)
#define ADC_SMPR2_SMP8              0x07000000 //!< SMP8[2:0] bits (Channel 8 Sample time selection)
#define ADC_SMPR2_SMP7              0x00E00000 //!< SMP7[2:0] bits (Channel 7 Sample time selection)
#define ADC_SMPR2_SMP6              0x001C0000 //!< SMP6[2:0] bits (Channel 6 Sample time selection)
#define ADC_SMPR2_SMP5              0x00038000 //!< SMP5[2:0] bits (Channel 5 Sample time selection)
#define ADC_SMPR2_SMP4              0x00007000 //!< SMP4[2:0] bits (Channel 4 Sample time selection)
#define ADC_SMPR2_SMP3              0x00000E00 //!< SMP3[2:0] bits (Channel 3 Sample time selection)
#define ADC_SMPR2_SMP2              0x000001C0 //!< SMP2[2:0] bits (Channel 2 Sample time selection)
#define ADC_SMPR2_SMP1              0x00000038 //!< SMP1[2:0] bits (Channel 1 Sample time selection)
#define ADC_SMPR2_SMP0              0x00000007 //!< SMP0[2:0] bits (Channel 0 Sample time selection)
/** @} */

/** @defgroup ADC_JOFRx[4]: (adc Offset: 0x014) ADC injected channel data offset register x */
#define ADC_JOFR1_JOFFSETx          0x00000FFF //!< Data offset for injected channel x
/** @} */

/** @defgroup ADC_HTR:      (adc Offset: 0x024) ADC watchdog high threshold register */
#define ADC_HTR_HT                  0x00000FFF //!< Analog watchdog high threshold
/** @} */

/** @defgroup ADC_LTR:      (adc Offset: 0x028) ADC watchdog low threshold register */
#define ADC_LTR_LT                  0x00000FFF //!< Analog watchdog low threshold
/** @} */

/** @defgroup ADC_SQR1:     (adc Offset: 0x02C) ADC regular sequence register 1 */
#define ADC_SQR1_L                  0x00F00000 //!< L[3:0] bits (Regular channel sequence length)
#define ADC_SQR1_SQ16               0x000F8000 //!< SQ16[4:0] bits (16th conversion in regular sequence)
#define ADC_SQR1_SQ15               0x00007C00 //!< SQ15[4:0] bits (15th conversion in regular sequence)
#define ADC_SQR1_SQ14               0x000003E0 //!< SQ14[4:0] bits (14th conversion in regular sequence)
#define ADC_SQR1_SQ13               0x0000001F //!< SQ13[4:0] bits (13th conversion in regular sequence)
/** @} */

/** @defgroup ADC_SQR2:     (adc Offset: 0x030) ADC regular sequence register 2 */
#define ADC_SQR2_SQ12               0x3E000000 //!< SQ12[4:0] bits (12th conversion in regular sequence)
#define ADC_SQR2_SQ11               0x01F00000 //!< SQ11[4:0] bits (11th conversion in regular sequence)
#define ADC_SQR2_SQ10               0x000F8000 //!< SQ10[4:0] bits (10th conversion in regular sequence)
#define ADC_SQR2_SQ9                0x00007C00 //!< SQ9[4:0] bits (9th conversion in regular sequence)
#define ADC_SQR2_SQ8                0x000003E0 //!< SQ8[4:0] bits (8th conversion in regular sequence)
#define ADC_SQR2_SQ7                0x0000001F //!< SQ7[4:0] bits (7th conversion in regular sequence)
/** @} */

/** @defgroup ADC_SQR3:     (adc Offset: 0x034) ADC regular sequence register 3 */
#define ADC_SQR3_SQ6                0x3E000000 //!< SQ6[4:0] bits (6th conversion in regular sequence)
#define ADC_SQR3_SQ5                0x01F00000 //!< SQ5[4:0] bits (5th conversion in regular sequence)
#define ADC_SQR3_SQ4                0x000F8000 //!< SQ4[4:0] bits (4th conversion in regular sequence)
#define ADC_SQR3_SQ3                0x00007C00 //!< SQ3[4:0] bits (3rd conversion in regular sequence)
#define ADC_SQR3_SQ2                0x000003E0 //!< SQ2[4:0] bits (2nd conversion in regular sequence)
#define ADC_SQR3_SQ1                0x0000001F //!< SQ1[4:0] bits (1st conversion in regular sequence)
/** @} */

/** @defgroup ADC_JSQR:		(adc Offset: 0x038) ADC injected sequence register */
#define ADC_JSQR_JL                 0x00300000 //!< JL[1:0] bits (Injected Sequence length)
#define ADC_JSQR_JSQ4               0x000F8000 //!< JSQ4[4:0] bits (4th conversion in injected sequence)
#define ADC_JSQR_JSQ3               0x00007C00 //!< JSQ3[4:0] bits (3rd conversion in injected sequence)
#define ADC_JSQR_JSQ2               0x000003E0 //!< JSQ2[4:0] bits (2nd conversion in injected sequence)
#define ADC_JSQR_JSQ1               0x0000001F //!< JSQ1[4:0] bits (1st conversion in injected sequence)
/** @} */

/** @defgroup ADC_JDRx[4]:	(adc Offset: 0x03C) ADC injected data register x  */
#define ADC_JDRx_JDATA              0x0000FFFF //!< Injected data
/** @} */

/** @defgroup ADC_DR:       (adc Offset: 0x04C) ADC data register			  */
#define ADC_DR_ADC2DATA             0xFFFF0000 //!< ADC2 data
#define ADC_DR_DATA                 0x0000FFFF //!< Regular data
/** @} */


/** @} */ // @defgroup ADC_regs_define


#endif /* ADC_F3_H_ */
