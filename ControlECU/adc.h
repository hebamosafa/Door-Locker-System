/*
 * adc.h
 *
 *  Created on: Sep 18, 2019
 *      Author: future
 */

 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include"timer.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
typedef enum{AREF,AVCC,RES,INTERNAL}Ref_Bit;
typedef struct{
	Clock_Select clock;
	Ref_Bit ref_bit;
}config_adc;
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(config_adc *config_adc_ptr);
void ADC_init2(void);
/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
