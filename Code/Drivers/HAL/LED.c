/*
 * LED.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Mohamed
 */


#include "LED.h"
#include "gpio.h"
#include <avr/io.h>

// Initialize the LEDs
void LED_init(){

	/* Set the Blue & Red & Green PINS as OUTPUT pins */

	GPIO_setupPinDirection(LED_PORT_ID , RED_LED_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LED_PORT_ID , GREEN_LED_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LED_PORT_ID , BLUE_LED_PIN_ID , PIN_OUTPUT);


	/* Positive LOGIC */

#ifdef POSITIVE_LOGIC
	/* Turn off All LEDs*/
	GPIO_writePin(LED_PORT_ID , RED_LED_PIN_ID , LOGIC_LOW);
	GPIO_writePin(LED_PORT_ID , GREEN_LED_PIN_ID , LOGIC_LOW);
	GPIO_writePin(LED_PORT_ID , BLUE_LED_PIN_ID , LOGIC_LOW);

	/* Negative LOGIC */

#else
	/* Turn off All LEDs Negative LOGIC*/
	GPIO_writePin(LED_PORT_ID , RED_LED_PIN_ID , LOGIC_HIGH);
	GPIO_writePin(LED_PORT_ID , GREEN_LED_PIN_ID , LOGIC_HIGH);
	GPIO_writePin(LED_PORT_ID , BLUE_LED_PIN_ID , LOGIC_HIGH);

#endif

}


/* Turn on LED by ID */

void LED_on(uint8 LED_PIN_ID){

	switch(LED_PIN_ID){

	case RED_ID:

#ifdef POSITIVE_LOGIC
		GPIO_writePin(LED_PORT_ID , RED_LED_PIN_ID , LOGIC_HIGH);

#else
		GPIO_writePin(LED_PORT_ID , RED_LED_PIN_ID , LOGIC_LOW);
#endif

		break;

	case GREEN_ID:

#ifdef POSITIVE_LOGIC
		GPIO_writePin(LED_PORT_ID , GREEN_LED_PIN_ID , LOGIC_HIGH);

#else
		GPIO_writePin(LED_PORT_ID , GREEN_LED_PIN_ID , LOGIC_LOW);
#endif

		break;

	case BLUE_ID:

#ifdef POSITIVE_LOGIC
		GPIO_writePin(LED_PORT_ID , BLUE_LED_PIN_ID , LOGIC_HIGH);

#else
		GPIO_writePin(LED_PORT_ID , BLUE_LED_PIN_ID , LOGIC_LOW);

#endif

		break;
	}
}



/* Turn off LED by ID*/
/* Turn off LED by ID */
void LED_off(uint8 LED_PIN_ID) {

    switch(LED_PIN_ID) {

        case RED_ID:  // Use RED_ID instead of RED_LED_PIN_ID
#ifdef POSITIVE_LOGIC
            GPIO_writePin(LED_PORT_ID, RED_LED_PIN_ID, LOGIC_LOW);
#else
            GPIO_writePin(LED_PORT_ID, RED_LED_PIN_ID, LOGIC_HIGH);
#endif
            break;

        case GREEN_ID:  // Use GREEN_ID instead of GREEN_LED_PIN_ID
#ifdef POSITIVE_LOGIC
            GPIO_writePin(LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_LOW);
#else
            GPIO_writePin(LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_HIGH);
#endif
            break;

        case BLUE_ID:  // Use BLUE_ID instead of BLUE_LED_PIN_ID
#ifdef POSITIVE_LOGIC
            GPIO_writePin(LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_LOW);
#else
            GPIO_writePin(LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_HIGH);
#endif
            break;
    }
}


