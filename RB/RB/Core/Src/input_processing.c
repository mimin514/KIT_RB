/*
 * input_processing.c
 *
 *  Created on: Sep 30, 2024
 *      Author: User
 */

 #include "main.h"
 #include "input_reading.h"
 #include "led_display.h"
#include "timer.h"

uint8_t modemode = 1;

void handle_mode(void) {
	switch (modemode) {
		case 1:
			normalstate();
			break;
		case 2:
			modify_red_duration();
			break;
		case 3:
			modify_yellow_duration();
			break;
		case 4:
			modify_green_duration();
			break;

	}

}

volatile uint8_t button1_flag = 0;
volatile uint8_t button2_flag = 0;
volatile uint8_t button3_flag = 0;
volatile uint8_t button4_flag = 0;


#define BUTTON_PRESSED GPIO_PIN_SET  // Define when the button is considered pressed
#define BUTTON_RELEASED GPIO_PIN_RESET

void getKeyInput(void) {
    static uint8_t prev_button_states[4] = {BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED};

    uint8_t button_states[4] = {
        HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin),
        HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin),
        HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin),
        HAL_GPIO_ReadPin(BUTTON_4_GPIO_Port, BUTTON_4_Pin)
    };

    for (uint8_t i = 0; i < 4; i++) {
        if (button_states[i] == BUTTON_PRESSED && prev_button_states[i] == BUTTON_RELEASED) {
            switch (i) {
                case 0: button1_flag = 1; break;  // Button 1
                case 1: button2_flag = 1; break;  // Button 2
                case 2: button3_flag = 1; break;  // Button 3
                case 3: button4_flag = 1; break;  // Button 4
            }
        }
        prev_button_states[i] = button_states[i];  // Update previous state
    }
}

void fsm_for_input_processing(void) {
    getKeyInput();

    if (button1_flag) {
        button1_flag = 0;
        modemode = (modemode % 4) + 1;
        updatemode(modemode);
    }

    if (button2_flag) {
        button2_flag = 0;
        switch (modemode) {
            case 2: but2_red(); break;
            case 3: but2_ye(); break;
            case 4: but2_gr(); break;
        }
    }

    if (button3_flag) {
        button3_flag = 0;
        switch (modemode) {
            case 2: but3_red(); break;
            case 3: but3_ye(); break;
            case 4: but3_gr(); break;
        }
    }

    if (button4_flag) {
        button4_flag = 0;
        modemode = 1;
        updatemode(modemode);
    }

    //update_handlemode();
}
