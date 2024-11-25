#include <stdio.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"

// the example code is to display a message when a button is pressed

#define BUTTON_PIN 16	

int main() {
	stdio_init_all();
	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_down(BUTTON_PIN); //pull down the button pin towards ground

	// Initialise the seven segment display.
	seven_segment_init();

	// setting variables
	unsigned long duration;
    static unsigned long button_pressed_timestamp;

	// Turn the seven segment display off when the program starts.
	seven_segment_off();
	printf("WELCOME TO THE MORSECODE INTERPRETOR \n");
	seven_segment_show(10);
	sleep_ms(100);
	seven_segment_off();
	while (true) {
		// pressed will be true if the button is currently being pressed
		
		bool pressed = gpio_get(BUTTON_PIN);
		if(pressed){
			button_pressed_timestamp = millis();
		}else {
			duration = millis() - button_pressed_timestamp;
			button_pressed_timestamp = millis();
		}

		if (400 > duration > 250){
			printf("-");
			seven_segment_show(28);

		}else if (duration > 100){
			printf(".");
			seven_segment_show(15);
		}else{
			printf("gap");
		}
		
	}
}
