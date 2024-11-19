#include "mbed.h"
#include "./mbed_zest-core-fmlr-72/TARGET_ZEST_CORE_FMLR-72/PinNames.h"
#include "./mbed_honeywell-hpma115-main/hpma115/hpma115.h"
// #include <iostream>
// #include <stdio.h>
// #include "rtos.h"
using namespace std::chrono;

namespace {
#define WAIT 1s
}
using namespace sixtron;
static DigitalOut led1(LED1);
static hpma115_data_t donnee;

static BufferedSerial uart(P1_UART_TX, P1_UART_RX, 9600);

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

int main()
{
    uint8_t coef;
    HPMA115::ErrorType err;

    HPMA115 sensor(P1_UART_TX, P1_UART_RX);

    printf("\n\n------------\nHPMA115 Example\n");

    // err = sensor.stop_measurement();
    // assert(err == HPMA115::ErrorType::Ok);

    // err = sensor.stop_autosend();
    // assert(err == HPMA115::ErrorType::Ok);

    // err = sensor.set_adjust_coef(200);
    // assert(err == HPMA115::ErrorType::Ok);

    // err = sensor.read_adjust_coef(&coef);
    // assert(err == HPMA115::ErrorType::Ok);
    // assert(coef == 200);

    // err = sensor.set_adjust_coef(100);
    // assert(err == HPMA115::ErrorType::Ok);

    // err = sensor.start_measurement();
    // assert(err == HPMA115::ErrorType::Ok);

    while(true){
        uint8_t* response;
        size_t len;
        readResponse(response, len);
        if(len)
            printf("Réponse: %d\n", response);
        else
            printf("Rien\n");
    }

    // while (true) {
    //     led1 = !led1;
        // err = sensor.read_measurement(&donnee);
        // if (err == HPMA115::ErrorType::Ok) {
        //     printf("donnee: \n");
        //     if (donnee.pm1_pm4_valid) {
        //         printf("PM1.0: %d\nPM4.0: %d\n", donnee.pm1_0, donnee.pm4_0);
        //     }
        //     printf("PM10: %d\nPM2.5: %d\n\n", donnee.pm10, donnee.pm2_5);
        // }

        // ThisThread::sleep_for(WAIT);
    // }
}




// DigitalOut led(LED1);
// Thread tPing(osPriorityNormal2, 1024);
// Thread tPong(osPriorityNormal, 1024);

// // Mutex pour synchroniser l'accès
// Mutex mtx;

// // Variable partagée pour contrôler l'alternance

// void ping(void)
// {
//     for (int i = 0; i < 100; i++) {
//         // Bloquer jusqu'à ce que ce soit le tour de ping
//         mtx.lock();
//         printf("ping\n");
//         mtx.unlock();
//     }
// }

// void pong(void)
// {
//     for (int i = 0; i < 100; i++) {
//         // Bloquer jusqu'à ce que ce soit le tour de pong
//         mtx.lock();
//         printf("pong\n");
//         mtx.unlock();
//     }
// }

// int main(void) 
// {
//     // Démarrer les threads
//     tPing.start(ping);
//     tPong.start(pong);

//     // Boucle principale
//     while (1) {
//         led = !led;
//         ThisThread::sleep_for(250ms);
//     }

//     return 0;
// }






// static BufferedSerial uart(P1_UART_TX, P1_UART_RX, 9600); // Configure UART avec TX et RX et un baud de 9600

// void sendCommand(const uint8_t* cmd, size_t len) {
//     uart.write(cmd, len);
// }

// bool readResponse(uint8_t* buffer, size_t len) {
//     size_t bytesRead = 0;
//     while (bytesRead < len) {
//         if (uart.readable()) {
//             uart.read(buffer + bytesRead, 1);
//             bytesRead++;
//         }
//     }
//     return bytesRead == len;
// }

// int main() {
//     // Commande pour démarrer la mesure
//     uint8_t startCmd[] = {0x68, 0x01, 0x01, 0x96};
//     uint8_t readCmd[] = {0x68, 0x01, 0x04, 0x93};
//     uint8_t response[32];

//     sendCommand(startCmd, sizeof(startCmd));
//     ThisThread::sleep_for(1000ms); // Attendre un peu pour que le capteur démarre

//     while (1)
//     {
//         // Commande pour lire les résultats de mesure
//         sendCommand(readCmd, sizeof(readCmd));

//         // Lecture de la réponse
//         if (readResponse(response, sizeof(response))) {
//             int pm1_0 = response[3] * 256 + response[4];
//             int pm2_5 = response[5] * 256 + response[6];
//             int pm4_0 = response[7] * 256 + response[8];
//             int pm10 = response[9] * 256 + response[10];
            
//             // int pm1_0 = response[3] * 256 + response[4];
//             // int pm2_5 = response[5] * 256 + response[6];
//             // int pm4_0 = response[7] * 256 + response[8];
//             // int pm10 = response[9] * 256 + response[10];

//             printf("Réponse : %x\n", response);
//             printf("PM1.0: %d µg/m3\n", pm1_0);
//             printf("PM2.5: %d µg/m3\n", pm2_5);
//             printf("PM4.0: %d µg/m3\n", pm4_0);
//             printf("PM10: %d µg/m3\n\n", pm10);
//         } else {
//             printf("Erreur lors de la lecture des données\n");
//         }
//         ThisThread::sleep_for(3000ms);
//     }

//     return 0;
// }




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

