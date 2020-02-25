/*
 * timer.h
 *
 *  Created on: Sep 18, 2019
 *      Author: future
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

#define TIMER0
#ifdef TIMER0
	#define CONTROL_REG TCCR0
#else
	#ifdef TIMER1
		#define CONTROL_REGA TCCR1A
		#define CONTROL_REGB TCCR1B
	#else
		#define CONTROL_REG TCCR2
	#endif
#endif

#ifdef TIMER0
	#define COUNT_REG TCNT0
#else
	#ifdef TIMER1
		#define COUNT_REG TCNT1
	#else
		#define COUNT_REG TCNT2
	#endif
#endif


#ifdef TIMER0
	#define COMPARE_REG OCR0
#else
	#ifdef TIMER1
		#define COMPARE_REGA 0CR1A
		#define COMPARE_REGB 0CR1B
	#else
		#define COMPARE_REG OCR2
	#endif
#endif

typedef enum {NORMAL_MODE,PWM_PHASE,CTC=8,PWM_FAST=9}Waveform_Generation_Mode;
typedef enum {NORMAL_COMPARE,TOGGLE,CLEAR,SET}Compare_Output_Mode;
typedef enum{NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024}Clock_Select;
typedef enum{OVERFLOW_INT02,OUTPUT_COMPARE}Interrupt_mode_02;
typedef enum{OVERFLOW_INT1=2,OUTPUT_COMPAREB,OUTPUT_COMPAREA}Interrupt_mode_1;

typedef enum{CTC1=0}CONTROL1;
typedef enum{CTC2=3}CONTROL2;

	typedef struct{
		Waveform_Generation_Mode waveform;
		Compare_Output_Mode compare;
		Clock_Select clock;
		uint8 compare_value;
		Interrupt_mode_02 interrupt_mode02;
		Interrupt_mode_1 interrupt_mode1;
		CONTROL1 control1;
		CONTROL2 control2;

		}config;


		void Timer_setCallBack(void(*a_ptr)(void));
		void set_compare_value(uint8 value);
		void timer02_Init( config* config_ptr);
		void timer1_Init(const config* config_ptr,bool CHANNAL_A,bool CHANNAL_B);
#endif /* TIMER_H_ */
