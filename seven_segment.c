#include "includes/seven_segment.h"
#include <stdio.h>
#include "pico/stdlib.h"

/**
 * Notice that we have eight pins, so we can represent the pins that
 * should be turned on as 8-bit values. The uint8_t type specifically
 * refers to an unsigned 8-bit integer. When individual bits are used
 * to represent data it's known as a bitfield.
 * 
 * We can then use bitwise operations and bitmasks to interpret these bitfields.
 * 
 * Additionally, placing these in an array allows us to define values
 * from 0 - 4 such that we can get the bitfield for a given number by
 * simply indexing the array! 
 * 
 * (These bitfields are defined in the ordering of the ALL_SEGMENTS array
 * in the header file, i.e., from A in the most-significant bit to G, then
 * DP in the least-significant bit.)
 * 
 * If it's not clear to you how these values work, check the diagram on Labsheet 6 or 
 * page 2 of the datasheet linked at the top of seven_segment.h.
 */
// You will need to extend the array to include more numbers.
uint8_t values[] = {
    0b11111100,         // 0
    0b01100000,         // 1
    0b11011010,         // 2 /z
    0b11110010,         // 3
    0b01100110,         // 4
    0b10110111,         //5
    0b10111110,         //6
    0b11100000,         //7
    0b11111111,         //8
    0b11100110,          //9
    0b00000010          //10 / MIDDLE
    0b11110110          //11 / A
    0b00011110          //12 /b
    0b10011100          //13 /c
    0b01111010          //14 /d
    0b10011110          // 15 /e
    0b10010110          // 16 /f
    0b11100110          //17 /g/q
    0b01110110          //18 /H/K/x
    0b01100000          //19 /i
    0b01111000          // 20 /j
    0b00011100          //21 /L
    0b10110000          //22 /m
    0b00110010          //23 /n
    0b11111100          //24 /o
    0b11010110          //25 /p
    0b00010010          //26 /r
    0b10110111          //27 /s
    0b00011110          //28 /t
    0b01111100          //29 /u
    0b00111000          //30 /v
    0b01001100          //31 /w
    0b01101110          //32 /y

};


//0b10000000 top
//0b01000000 top right
//0b00100000 bottom right
//0b0001000 bottom left
//0b0000100 bottom
//0b00000100 top left
//0b00000010 middle




// ------------------------------------------------------------------

void seven_segment_init() {
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_init(ALL_SEGMENTS[i]);
        gpio_set_dir(ALL_SEGMENTS[i], GPIO_OUT);
    }
}

void seven_segment_off() {
    // This display is common-anode, which means we need to turn a GPIO
    // pin ON for it to appear OFF on the display. 
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_put(ALL_SEGMENTS[i], true);
    }
}

void seven_segment_on() {
    for (unsigned int i = 0; i < ALL_SEGMENTS_COUNT; i++) {
        gpio_put(ALL_SEGMENTS[i], false);
    }
}
/*
 * @param number The number to display on the screen.
 * @return Zero if the number has been successfully displayed, otherwise a non-zero
 * value.
 */
unsigned int seven_segment_show(unsigned int number) {
    // the number is bigger than 4, the current program cannot display
    // you need to extend the program to display more numbers & alphabets
    if (number > 10) return 1;

    /** You don't need to edit the following code within the for-loop **/
	//this loop goes through the segments one by one and checks if that segment
	// should be on or off then it turns it on or off
    for (unsigned int i = 0; i < 7; i++) {
        // Create a mask to check the current bit.
        //
        // Our first segment (A) starts in the most-significant
        // bit of the bitfield, so we need to 7 - i to map i to
        // the bit for the relevant segment as follows:
        //
        // i = 0 -> 7 - i = 7 - 0 = 7
        // i = 1 -> 7 - i = 7 - 1 = 6
        // ...
        // i = 6 -> 7 - i = 7 - 6 = 1
        // i = 7 -> 7 - i = 7 - 7 =  0
        unsigned int segmentBit = 1 << (7 - i);

        // When the segmentBit is 1 << 7, it produces 0b1000_0000.
        // Where 1 is in the most significant bit and all the other
        // bits are 0.

        // Bitwise-and the segmentBit with the bitfield for the
        // current number. If we get zero, it means that segment
        // should turned off, otherwise the bit is turned on.
        bool illuminateSegment = (segmentBit & values[number]); // != 0;

        // Recall, however, that because the display is common-anode,
        // whenever we want to illuminate a segment, we actually need
        // to pull that pin low (i.e., put false).
        gpio_put(
            ALL_SEGMENTS[i],
            !illuminateSegment
        );
        
    }
    printf("%d \n", number);
    return 0;

}
