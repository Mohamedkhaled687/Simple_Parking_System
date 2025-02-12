/*
 * ultrasoinc.c
 *
 *  Created on: Oct 13, 2024
 *      Author: Mohamed
 */


#include "ultrasoinc.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>
/* Global variable to store the pulse width */

uint16 g_highTime = 0;

/* Global variable to store the edge count and start time width */
 uint8 g_edgeCount = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description: Initialize the Ultrasonic sensor and ICU driver.
 */
void Ultrasonic_init(void)
{
    /* Set the trigger pin as output */
    GPIO_setupPinDirection(UltraSonic_TRIGGER_PORT,UltraSonic_TRIGGER_PIN,PIN_OUTPUT);

    /* ICU configuration: F_CPU/8, detect rising edge */
    ICU_ConfigType ICU_Config = {F_CPU_8,Rising};

    /* Call the initialization function */
    ICU_init(&ICU_Config);

    /* Set the ICU callback function to Ultrasonic_edgeProcessing */
    ICU_setCallBack(Ultrasonic_edgeProcessing);
}

/*
 * Description: Send the trigger pulse to the ultrasonic sensor.
 */
void Ultrasonic_Trigger(void)
{
    /* Send a HIGH pulse for 10 µs to trigger the ultrasonic sensor */
    GPIO_writePin(UltraSonic_TRIGGER_PORT,UltraSonic_TRIGGER_PIN,LOGIC_HIGH);
    _delay_us(TRIGGER_DELAY_VALUE);
    GPIO_writePin(UltraSonic_TRIGGER_PORT,UltraSonic_TRIGGER_PIN,LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void)
{
    /* Send the trigger pulse */
    Ultrasonic_Trigger();

    /* Wait until the echo pulse width is measured (stored in g_highTime) */
    while (g_highTime == 0);

    /*
    	 * Calculation details:
    	 * Sound velocity = 340.00 m/s = 34000 cm/s
    	 * The distance of Object (in cm) = (34000*echoTime)/2 = 17000 * echoTime
    	 * F_CPU/8 for timer frequency.
    	 * Then time to execute 1 instruction is 1 us.
    	 * Distance = 17000 x (echoTime) x 0.5 x 10^-6 cm = 0.017 x (echoTime) cm = (echoTime) / 117.6 cm
    */
    uint16 distance = g_highTime / 117.6;

    /* Reset the pulse width for the next measurement */
    g_highTime = 0;

    return distance;
}

/*
 * Description: ICU callback function to handle edge detection and measure the pulse width.
 */
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
    if (g_edgeCount == 1)
    {
        /* Rising edge detected, store the current timer value */
    	ICU_clearTimerValue();
        /* Switch to falling edge detection */
        ICU_setEdgeDetectionType(Falling);
    }
    else if (g_edgeCount == 2)
    {
        /* Falling edge detected, calculate pulse width (high time) */
        g_highTime = ICU_getInputCaptureValue();

        /* Clear the Timer */
        ICU_clearTimerValue();
        /* Switch back to rising edge detection for the next measurement */
        ICU_setEdgeDetectionType(Rising);
        g_edgeCount = 0;
    }
}
