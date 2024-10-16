/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
using namespace std::chrono;

// Blinking rate in milliseconds
#define BLINKING_RATE     250ms

Ticker flipper;
InterruptIn bouton(BUTTON1);
DigitalOut led(LED1);
float period=1;

void change_period()
{
    if(period <= 0.1){
        period = 1;
    }
    else{
        period-=0.1;
    }
}

void flip()
{
    led = !led;
    flipper.detach();
    flipper.attach(flip,period);
}

int main()
{
    led = 1;
    flipper.attach(&flip, period); // the address of the function to be attached (flip) and the interval (2 seconds)
    bouton.rise(&change_period);

    // spin in a main loop. flipper will interrupt it to call flip
    while (1) {
        ThisThread::sleep_for(BLINKING_RATE);
    }
}



// Timer t;
// InterruptIn bouton(BUTTON1);
// DigitalOut led(LED1);


// void flip()
// {
//     led = !led;
//     t.reset();
//     t.start();
// }

// void flop()
// {
//     led = !led;
//     t.stop();
// }

// int main()
// {
//     bouton.rise(&flip);
//     bouton.fall(&flop);
    
//     while (1)
//     {
//         printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());
//         ThisThread::sleep_for(BLINKING_RATE); 
//     }
// }


// InterruptIn bouton(BUTTON1);
// DigitalOut led(LED1);

// void flip()
// {
//     led = !led;
// }

// int main()
// {   
//     bouton.rise(&flip);
//     while(1) {
//         printf("bouton = %d\n\r", bouton.read());
//         ThisThread::sleep_for(BLINKING_RATE);        
//     }
// }


// DigitalIn bouton(BUTTON1);
// DigitalOut led(LED1);

// int main()
// {        
//     while(1) {
//         printf("bouton = %d\n\r", bouton.read());
//         led = bouton;
//         ThisThread::sleep_for(BLINKING_RATE);        
//     }
// }

