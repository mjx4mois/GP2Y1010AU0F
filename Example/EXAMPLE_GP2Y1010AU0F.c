/*-----------------------------------------------------------------------
     Creator		: Morris chiou
     Sensor		: GP2Y1010AU0F dust sensor (PM2.5)
     File Name		: SENSOR_GP2Y1010AU0F.h
     Function		: SENSOR_GP2Y1010AU0F
     Create Date	: 2017/12/31
---------------------------------------------------------------------- */


#ifndef __GP2Y1010AU0F_EXAMPLE__
#define __GP2Y1010AU0F_EXAMPLE__

#include <mega32a.h>
#include <stdio.h>
#include <delay.h>
#include <math.h>
#include <alcd.h>
#include "SENSOR_GP2Y1010AU0F.h"


#define GP2Y1010AU0F_READ_BUFFER 10

void EXAMPLE_GP2Y1010AU0F(void);


void EXAMPLE_GP2Y1010AU0F(void)
{
		FLOAT read_voltage=0, read_dust_data=0.0;
		FLOAT get_raw_data=0.0,get_dust_data=0.0;
		FLOAT real_dust_data=0.0,total_data=0.0;
		FLOAT turn_mg_to_ug = 0;
		INT32U data[5]={0};         
		INT32U print_data[5]={0};      
		CHAR8U lcd_data[7]={0};		
		
		FLOAT temp_data[GP2Y1010AU0F_READ_BUFFER]={0.0};
		INT32U cnt=0; 
	
		/* initial trigger GP2Y1010AU0F LED IO */
   	   	GP2Y1010AU0F_SET_INITAIL();  
		
		printf("-------------------- GP2Y1010AU0F dust sensor (PM2.5) --------------------\r\n");
				
		/* read 5 data for first calculate */ 
		for(cnt=0;cnt<GP2Y1010AU0F_READ_BUFFER;cnt++)
		{
			/* Get The raw data from ADC */						
			GP2Y1010AU0F_GET_RAW_DATA(&get_raw_data);
			
			/* Calcuate the Dust value */	
			GP2Y1010AU0F_GET_DUST_VALUE(&get_dust_data,get_raw_data);

			get_dust_data=get_dust_data*1000;
					
			temp_data[cnt]= get_dust_data;
					 
			total_data+= get_dust_data;
					
			printf("reading data ...\r\n");					
		}
  			/* average the dust data */
			real_dust_data =  total_data / GP2Y1010AU0F_READ_BUFFER ;


		while(1)
		{
			/* Get The raw data from ADC */				
			GP2Y1010AU0F_GET_RAW_DATA(&get_raw_data);

			/* Get The raw data from ADC */			
			GP2Y1010AU0F_GET_DUST_VALUE(&get_dust_data,get_raw_data);

			get_dust_data=get_dust_data*1000;
			
			/* average the Dust Buffer */
			total_data = 0.0;
			/*read data & shift & add new data */
			for(cnt=0;cnt<GP2Y1010AU0F_READ_BUFFER;cnt++)
			{                   
				temp_data[cnt+1]=temp_data[cnt];    
				total_data+=temp_data[cnt+1]; 
				// printf("cnt %d\r\n",cnt);
				if(cnt==(GP2Y1010AU0F_READ_BUFFER-2))break;	
			}
			
			temp_data[0]= get_dust_data;
			total_data+= get_dust_data;
			real_dust_data=total_data/GP2Y1010AU0F_READ_BUFFER;
					
			
    			/* calculate the dust data for print */
			print_data[0]= (INT32U)(real_dust_data);
			print_data[1]= (INT32U)(real_dust_data*10)%10;   
			print_data[2]= (INT32U)(real_dust_data*100)%10;   	  
			
			print_data[3]= (INT32U)(real_dust_data*1000)%10; 
			print_data[4]= (INT32U)(real_dust_data*10000)%10;    		

			/* print the raw data */
			printf("dust data = %d.%d%d%d%d ug/m^3 \r\n",print_data[0],print_data[1],print_data[2],print_data[3],print_data[4]);	
	
					
			lcd_data[0]=(CHAR8U)((INT32U)real_dust_data/1000)%10;
			lcd_data[1]=(CHAR8U)((INT32U)real_dust_data/100)%10;
			lcd_data[2]=(CHAR8U)((INT32U)real_dust_data/10)%10;
			lcd_data[3]=(CHAR8U)((INT32U)real_dust_data)%10;

			lcd_data[4]=(CHAR8U)((INT32U)(real_dust_data*10)%10);
			lcd_data[5]=(CHAR8U)((INT32U)(real_dust_data*100)%10);
			lcd_data[6]=(CHAR8U)((INT32U)(real_dust_data*1000)%10);

			/* display the Dust value */	
			lcd_gotoxy(0,0);
			lcd_putsf("Dust:");
			lcd_putchar(48+lcd_data[0]);
			lcd_putchar(48+lcd_data[1]);
			lcd_putchar(48+lcd_data[2]); 
			lcd_putchar(48+lcd_data[3]);							
			lcd_putchar(46);    /* print "."  */ 
			lcd_putchar(48+lcd_data[4]);  
			lcd_putchar(48+lcd_data[5]); 							
			lcd_putchar(48+lcd_data[6]);                                           
			lcd_gotoxy(8,1);
			lcd_putsf("ug/m^3 ");

			/* delay 150ms */
			delay_ms(150);


		}

               printf("--------------------  GP2Y1010AU0F_READ_BUFFER dust sensor (PM2.5) --------------------\r\n");
}
#endif		//#ifndef __GP2Y1010AU0F_EXAMPLE__
