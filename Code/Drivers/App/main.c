/*
 * main.c
 *
 *  Created on: Oct 13, 2024
 *      Author: Mohamed
 */

#include "lcd.h"
#include "BUZZER.h"
#include "LED.h"
#include "ultrasoinc.h"
#include "common_macros.h"
#include <avr/io.h>
#include <util/delay.h>

int main(){

	/* Enable GLOBAL interrupt */
	SET_BIT(SREG , 7);
	/* Initialize the Peripherals */
	LCD_init();
	LED_init();
	Ultrasonic_init();
	Buzzer_init();


	uint16 distance = 0;
	LCD_displayString("Distance=    cm");

	while(1){

		distance = Ultrasonic_readDistance() + 1;
		LCD_moveCursor(0, 10);

		/* Display the distance on the LCD screen */
		LCD_intgerToString(distance);

		/* Clear extra characters for distances less than 100 cm */
		if (distance < 100) {
			LCD_displayCharacter(' ');
		} else if (distance < 10) {
			LCD_displayString("  ");
			}

		if(distance <= 5) {
			Buzzer_on();
			LCD_moveCursor(1, 0);
			LCD_displayString("      STOP!    ");

			while(distance <= 5) {
				for(uint8 LED_ID = RED_ID; LED_ID <= BLUE_ID; LED_ID++) {
					LED_on(LED_ID);
					_delay_ms(200);
					LED_off(LED_ID);
				}
				distance = Ultrasonic_readDistance() + 1;
				LCD_moveCursor(0, 10);
				/* Display the distance on the LCD screen */
				LCD_intgerToString(distance);

			}

			Buzzer_off();
			LCD_clearScreen();
			LCD_displayString("Distance=    cm");
			LCD_moveCursor(0, 10);  // Move cursor back to display the distance
		}
		else if(distance >= 6 && distance <= 10) {
			LED_on(RED_ID);
			LED_on(BLUE_ID);
			LED_on(GREEN_ID);
		}
		else if(distance >= 11 && distance <= 15) {
			LED_on(RED_ID);
			LED_on(GREEN_ID);
			LED_off(BLUE_ID);
		}
		else if(distance >= 16 && distance <= 20) {  // Corrected condition
			LED_on(RED_ID);
			LED_off(BLUE_ID);
			LED_off(GREEN_ID);
		}
		else {
			LED_off(RED_ID);
			LED_off(GREEN_ID);
			LED_off(BLUE_ID);  // Corrected function name for BLUE_ID
		}

		_delay_ms(100);
	}
}
