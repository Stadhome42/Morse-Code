#include <stdio.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"
#include <math.h>

// the example code is to display a message when a button is pressed

#define BUTTON_PIN 16	

int main() {
	stdio_init_all();
	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_down(BUTTON_PIN); //pull down the button pin towards ground
	unsigned long start_time = 0;
    unsigned long end_time = 0;
	unsigned long duration;
    static unsigned long button_pressed_timestamp;

	// Initialise the seven segment display.
	seven_segment_init();

	// setting variables
	

	// Turn the seven segment display off when the program starts.
	seven_segment_off();
	printf("WELCOME TO THE MORSECOsDE INTERPRETOR \n");
	seven_segment_show(10);
	sleep_ms(100);
	seven_segment_off();
    while (true){
		bool pressed = gpio_get(BUTTON_PIN);
		if (pressed){
			
			start_time == round(time_us_64() / 1000);
			while(pressed){
				seven_segment_off();
			}
			duration = round(time_us_64() / 1000) - start_time;
		}else{
			
		}
        if (gpio_get(BUTTON_PIN) == 0){
			// Button is pressed
			if (start_time == 0){
				// Record the start time when the button is first pressed
				start_time = time_us_32();
			}
		}else{
			// Button is not pressed
			if (start_time != 0){
				// Record the end time when the button is released
				end_time = time_us_32();
				uint64_t duration = end_time - start_time; // Print the duration in microseconds
				printf("Button pressed for %llu microseconds\n", duration);
				// Reset the start time
				start_time = 0;
			}
		}
    }
}
