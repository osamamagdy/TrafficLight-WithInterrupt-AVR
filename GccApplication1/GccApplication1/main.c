/*
 * GccApplication1.c
 *
 * Created: 7/12/2020 5:40:20 PM
 * Author : Osama Magdy
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define RED 0
#define YELLOW 1
#define GREEN 2

int state;
int my_time;


void blink_red()
{
	while(my_time<15)
	{
		PORTC=0x01;
		_delay_ms(500);
		PORTC=0x00;
		_delay_ms(500);
		my_time++;
	}
}


void blink_green()
{
	while(my_time<7)
	{
		PORTC=0x04;
		_delay_ms(500);
		PORTC=0x00;
		_delay_ms(500);
		my_time++;
	}
}



void blink_yellow()
{
	while(my_time<3)
	{
		PORTC=0x02;
		_delay_ms(500);
		PORTC=0x00;
		_delay_ms(500);
		my_time++;
	}
}


//External Interrupt 0 Service Routine
ISR (INT0_vect)
{
	//char my_time_rem = 15 - my_time;
	
	if (state==GREEN)
	{
		while (my_time<15)
		{
			PORTC=0x04;
			_delay_ms(500);
			PORTC=0x00;
			_delay_ms(500);
			my_time++;
		}
		
	}
	
	
	
}





int main(void)
{	
	DDRC= 0x07;
	PORTC=0x00;
	
	sei();
	
	
	
	GICR |= 0x40;  // we used "|" to not miss up the register
	MCUCR = 0x03;
	MCUCSR = 0x00; //As you enabled the global interrupt
	GIFR = 0x40;
	
	state = 0;
	my_time=0;
	
	/* Replace with your application code */
	
	while (1)
	{
		
		switch(state)
		{
			case RED :
			blink_red();
			my_time = 0 ;
			state = GREEN;
			break;
			
			case GREEN :
			blink_green();
			my_time = 0 ;
			state = YELLOW;
			break;
			
			case YELLOW :
			blink_yellow();
			my_time = 0;
			state = RED;
			break;
			
		}
	}
	
	
	
	
    
}

