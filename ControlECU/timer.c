/*
 * timer.c
 *
 *  Created on: Sep 18, 2019
 *      Author: future
 */


#include "timer.h"



static volatile void (*g_callBackPtr)(void) = NULL_PTR;
#ifdef TIMER1
void timer1_Init(const config* config_ptr,bool CHANNAL_A,bool CHANNAL_B){
	if(CHANNAL_A)
		CONTROL_REGA=(CONTROL_REGA&0xB7)|((config_ptr->waveform)<<6);
	if(CHANNAL_B)
		CONTROL_REGA=(CONTROL_REGA&0xB7)|((config_ptr->waveform)<<4);
	CONTROL_REGA=(CONTROL_REGA&0xFC)|(config_ptr->control1);
	CONTROL_REGB=(CONTROL_REGB&0xE7)|((config_ptr->control2)<<3);
	CONTROL_REGB=(CONTROL_REGB&0xF8)|(config_ptr->clock);
	COUNT_REG=0;
	if(CHANNAL_A)
		COMPARE_REGA=config_ptr->compare_value;
	if(CHANNAL_B)
		COMPARE_REGB=config_ptr->compare_value;
	SET_BIT(TIMSK,config_ptr->interrupt_mode1);
}
#else
void timer02_Init( config* config_ptr){

	CONTROL_REG=(CONTROL_REG&0xB7)|((config_ptr->waveform)<<3);
	CONTROL_REG=(CONTROL_REG&0xCF)|((config_ptr->compare) <<4);
	CONTROL_REG=(CONTROL_REG&0xF8)|(config_ptr->clock);
	COUNT_REG=0;
	COMPARE_REG=config_ptr->compare_value;
	#ifdef TIMER0
		SET_BIT(TIMSK,config_ptr->interrupt_mode02);
	#else
		TIMSK|=((1<<config_ptr->interrupt_mode_02)<<6);

	#endif

}
#endif
/*
*/
void set_compare_value(uint8 value){
	COMPARE_REG=value;
}
void Timer_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

#ifdef TIMER0
	ISR (TIMER0_OVF_vect){if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}}
	ISR (TIMER0_COMP_vect){

	if(g_callBackPtr != NULL_PTR){	(*g_callBackPtr)(); }}
#else
	#ifdef TIMER1
	ISR (TIMER1_OVF_vect){if(g_callBackPtr != NULL_PTR){	(*g_callBackPtr)(); }}
	ISR (TIMER1_COMP_vect){if(g_callBackPtr != NULL_PTR){	(*g_callBackPtr)(); }}
	#else
		ISR (TIMER2_OVF_vect){if(g_callBackPtr != NULL_PTR){	(*g_callBackPtr)(); }}
		ISR (TIMER2_COMP_vect){if(g_callBackPtr != NULL_PTR){	(*g_callBackPtr)(); }}
	#endif

#endif

