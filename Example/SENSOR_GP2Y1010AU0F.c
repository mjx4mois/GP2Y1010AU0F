/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: GP2Y1010AU0F dust sensor (PM2.5)
     File Name		: SENSOR_GP2Y1010AU0F.h
     Function		: SENSOR_GP2Y1010AU0F
     Create Date	: 2017/12/31
---------------------------------------------------------------------- */

#ifndef __GP2Y1010AU0F_FUNCTION__
#define __GP2Y1010AU0F_FUNCTION__  

#include <stdio.h>
#include <math.h>
#include <delay.h>

#include "SENSOR_GP2Y1010AU0F.h"


#define GP2Y1010AU0F_DEBUG		0

/* read adc_data[0] -> ADC channel 0 -> PA_ 2 pin */
extern unsigned int adc_data[1];

//********************************************* SYSTEM *************************************************
/* --------------------------------------------------------------------------------------------------*/
/* set PORTD.4 as LED pin -> SET this pin as Output */
void GP2Y1010AU0F_SET_INITAIL(void)
{

			printf("GP2Y1010AU0F initial \r\n");
			DDRB = (1<<0);  	/* SET PORTB.0*/
			GP2Y1010AU0F_LED_OUT  = 1;	/* let  pin out =1, turn off */
			delay_ms(10);
			
}
/* --------------------------------------------------------------------------------------------------*/
/* --------------------------------------------------------------------------------------------------*/
/* get GP2Y1010AU0F raw data form ADC */
void GP2Y1010AU0F_GET_RAW_DATA(FLOAT*raw_data)
{
#if GP2Y1010AU0F_DEBUG	/* for debug*/
	INT32U data[3]={0};
#endif

	INT32U read_temp=0;
	FLOAT turn_voltage =0.0;

	/* read a dust data */

	/* step1. let GP2Y1010AU0F_LED_OUT turn low  280us ( active low )*/
	GP2Y1010AU0F_LED_OUT = 0;
	delay_us(275);						/* about 280 us*/
	read_temp = adc_data[0];			/* read ADC channel 0 data*/
	delay_us(40);							/* delay 40us*/
	GP2Y1010AU0F_LED_OUT = 1;		/* turn off  */
	
	turn_voltage = (FLOAT)read_temp /1023*5;  /*5->5v*/
	
#if GP2Y1010AU0F_DEBUG	/* for debug*/
	data[0]= (INT32U)(turn_voltage);
	data[1]= (INT32U)(turn_voltage*10) %10;   
	data[2]= (INT32U)(turn_voltage*100) %10;   	
	printf("adc_data[0] %d ,turn_voltage %f \r\n",adc_data[0],turn_voltage);		
	printf("voltage = %d.%d%d v \r\n",data[0],data[1],data[2]);			
#endif

	*raw_data = turn_voltage ;
			
}
/* --------------------------------------------------------------------------------------------------*/
/* --------------------------------------------------------------------------------------------------*/
/*  turn the ADC value to Dust Value  ; unit : ug/m^3*/
/* Point (dust , voltage) */
/* Zero area : dust_data = 0	*/
/* A area :A1(0,0.9) ; A2(0.05,1.1) ;		mA =	4 		; formula -> voltage_value -1.1 = mA*(dust_data -0.05)		*/
/* B area :B1(0.05,1.1) ; B2(0.4,3.25) ;	mB =	6.14285	; formula -> voltage_value -3.25 = mB*(dust_data -0.4)		*/
/* C area :C1(0.4,3.25) ; C2(0.45,3.5) ;	mC =	5		; formula -> voltage_value -3.5 = mC*(dust_data -0.45)		*/
/* D area :D1(0.45,3.5) ; D2(0.5,3.6) ;	mD =	2		; formula -> voltage_value -3.6 = mD*(dust_data -0.5)		*/
/* Sat area :	dust_data = 550 up	*/
void GP2Y1010AU0F_GET_DUST_VALUE(FLOAT *dust_data,FLOAT voltage_value)
{
	INT32U read_temp = 0;
	FLOAT dust_value = 0.0;

	
	/* check vlotage data */
	
	if(voltage_value <0.9)/* voltage_value <0.9V */ /* Zero area */
	{
		*dust_data =0;	/*unit : mg/m^3*/
	}
	else if((voltage_value >=0.9) && (voltage_value <1.1))/* voltage_value >=0.9V &&  voltage_value <1.1V  */ /* A area */
	{
		/* formula -> voltage_value -1.1 = mA*(dust_data -0.05)*/
		*dust_data = ((voltage_value -1.1) /DUST_A_AREA_M) + 0.05 ;/*unit : mg/m^3*/
	}
	else if((voltage_value >=1.1) && (voltage_value <3.25))/* voltage_value >=0.9V &&  voltage_value <1.1V  */ /* A area */
	{
		/* formula -> voltage_value -3.25 = mB*(dust_data -0.4)*/
		*dust_data = ((voltage_value -3.25) /DUST_B_AREA_M) + 0.4 ;/*unit : mg/m^3*/
	}
	else if((voltage_value >=3.25) && (voltage_value <3.5))/* voltage_value >=0.9V &&  voltage_value <1.1V  */ /* A area */
	{
		/* formula -> voltage_value -3.5 = mC*(dust_data -0.45)*/
		*dust_data = ((voltage_value -3.5) /DUST_C_AREA_M) + 0.45 ;/*unit : mg/m^3*/
	}
	else if((voltage_value >=3.5) && (voltage_value <3.6))/* voltage_value >=0.9V &&  voltage_value <1.1V  */ /* A area */
	{
		/* formula -> voltage_value -3.6 = mD*(dust_data -0.5)	*/
		*dust_data =  ((voltage_value -3.6) /DUST_D_AREA_M) + 0.5 ;/*unit : mg/m^3*/
	}
	else if(voltage_value >3.6)/* voltage >3.6V */ /* Sat area  */
	{
		*dust_data = 0.55;	/*unit : mg/m^3*/
	}
}
/* --------------------------------------------------------------------------------------------------*/
//********************************************* SYSTEM *************************************************


#endif //#ifndef __GP2Y1010AU0F_FUNCTION__ 
