/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <mbed.h>
#include <PinNames.h>
using namespace std::chrono;

static BufferedSerial uart(P1_UART_TX, P1_UART_RX, 9600); // Configure UART avec TX et RX et un baud de 9600

void sendCommand(const uint8_t* cmd, size_t len) {
    uart.write(cmd, len);
}

bool readResponse(uint8_t* buffer, size_t len) {
    size_t bytesRead = 0;
    while (bytesRead < len) {
        if (uart.readable()) {
            uart.read(buffer + bytesRead, 1);
            bytesRead++;
        }
    }
    return bytesRead == len;
}

int main() {
    // Commande pour démarrer la mesure
    uint8_t startCmd[] = {0x68, 0x01, 0x01, 0x96};
    uint8_t readCmd[] = {0x68, 0x01, 0x04, 0x93};
    uint8_t response[32];

    sendCommand(startCmd, sizeof(startCmd));
    ThisThread::sleep_for(1000ms); // Attendre un peu pour que le capteur démarre

    while (1)
    {
        // Commande pour lire les résultats de mesure
        sendCommand(readCmd, sizeof(readCmd));

        // Lecture de la réponse
        if (readResponse(response, sizeof(response))) {
            int pm1_0 = response[3] * 256 + response[4];
            int pm2_5 = response[5] * 256 + response[6];
            int pm4_0 = response[7] * 256 + response[8];
            int pm10 = response[9] * 256 + response[10];
            
            // int pm1_0 = response[3] * 256 + response[4];
            // int pm2_5 = response[5] * 256 + response[6];
            // int pm4_0 = response[7] * 256 + response[8];
            // int pm10 = response[9] * 256 + response[10];

            printf("Réponse : %x\n", response);
            printf("PM1.0: %d µg/m3\n", pm1_0);
            printf("PM2.5: %d µg/m3\n", pm2_5);
            printf("PM4.0: %d µg/m3\n", pm4_0);
            printf("PM10: %d µg/m3\n\n", pm10);
        } else {
            printf("Erreur lors de la lecture des données\n");
        }
        ThisThread::sleep_for(3000ms);
    }

    return 0;
}




// // Blinking rate in milliseconds
// #define BLINKING_RATE     250ms

// Ticker flipper;
// InterruptIn bouton(BUTTON1);
// DigitalOut led(LED1);
// float period=1;

// void change_period()
// {
//     if(period <= 0.1){
//         period = 1;
//     }
//     else{
//         period-=0.1;
//     }
// }

// void flip()
// {
//     led = !led;
//     flipper.detach();
//     flipper.attach(flip,period);
// }

// int main()
// {
//     led = 1;
//     flipper.attach(&flip, period); // the address of the function to be attached (flip) and the interval (2 seconds)
//     bouton.rise(&change_period);

//     // spin in a main loop. flipper will interrupt it to call flip
//     while (1) {
//         ThisThread::sleep_for(BLINKING_RATE);
//     }
// }



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

