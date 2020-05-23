/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: GP2Y1010AU0F dust sensor (PM2.5)
     File Name		: SENSOR_GP2Y1010AU0F.h
     Function		: SENSOR_GP2Y1010AU0F
     Create Date	: 2017/12/31
---------------------------------------------------------------------- */

#ifndef __GP2Y1010AU0F_HEADER__
#define __GP2Y1010AU0F_HEADER__  

/***** sepc suggest -> read a dust data  period = 10mS å */

/*--------------------------------- Define GP2Y1010AU0F pin I/O -------------------------------------*/
#define GP2Y1010AU0F_LED_OUT			PORTB.0			/*GP2Y1010AU0F Pin 3 need to drive.*/
/* Point (dust , voltage) */
/* Zero area : dust_data = 0	*/
/* A area :A1(0,0.9) ; A2(0.05,1.1) ;		mA =	4 		; formula -> voltage_value / 4 = dust_data			*/
/* B area :B1(0.05,1.1) ; B2(0.4,3.25) ;	mB =	6.14285	; formula -> voltage_value / 6.14285 = dust_data		*/
/* C area :C1(0.4,3.25) ; C2(0.45,3.5) ;	mC =	5		; formula -> voltage_value / 5 = dust_data			*/
/* D area :D1(0.45,3.5) ; D2(0.5,3.6) ;	mD =	2		; formula -> voltage_value / 2 = dust_data			*/
/* Sat area :	dust_data = 550 up	*/
#define DUST_A_AREA_M				(4)
#define DUST_B_AREA_M				(6.14285)
#define DUST_C_AREA_M				(5)
#define DUST_D_AREA_M				(2)
/*--------------------------------- Define GP2Y1010AU0F pin I/O -------------------------------------*/


/********************************************** SYSTEM **************************************************/
/*--------------------------------------------------------------------------------------------------*/
/*set PORTD.4 as LED pin -> SET this pin as Output*/
void GP2Y1010AU0F_SET_INITAIL(void);
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/*get GP2Y1010AU0F raw data form ADC*/
void GP2Y1010AU0F_GET_RAW_DATA(FLOAT *raw_data);
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
/* turn the ADC value to Dust Value  ; unit : ug/m^3*/
void GP2Y1010AU0F_GET_DUST_VALUE(FLOAT *dust_data,FLOAT raw_data);
/*--------------------------------------------------------------------------------------------------*/
/********************************************** SYSTEM **************************************************/
#endif	/*#ifndef __GP2Y1010AU0F_HEADER__ */