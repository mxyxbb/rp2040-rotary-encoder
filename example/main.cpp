#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <pico/stdlib.h>

#include "quadrature_encoder.pio.h"
#include "button.pio.h"

quadrature_t quadratures1;

// setting pin1 to actual pin will successfully enable the read funtion
// setting pin1 to -1 will disable the read funtion
// please use pin1, pin2, pin3 and pin4 in order, such as 2,14,9,-1. don't: -1,2,14,9

void quad_init(quadrature_t* q, PIO pio, int pin1, int pin2, int pin3, int pin4, int max_step_rate){

    q->pio = pio;
    uint numbers = 0;
    if(pin1 >= 0) {numbers++;printf("encoder1 is used in pin %d,%d\n", pin1,pin1+1);}
    if(pin2 >= 0) {numbers++;printf("encoder2 is used in pin %d,%d\n", pin2,pin2+1);}
    if(pin3 >= 0) {numbers++;printf("encoder3 is used in pin %d,%d\n", pin3,pin3+1);}
    if(pin4 >= 0) {numbers++;printf("encoder4 is used in pin %d,%d\n", pin4,pin4+1);}
    q->number_of_qua = numbers;
    q->pins[0] = pin1;
    q->pins[1] = pin2;
    q->pins[2] = pin3;
    q->pins[3] = pin4;
    for (uint i = 0; i < 4; i++)
    {
        q->count_new[i] = 0;
        q->count_old[i] = 0;
    }
    
    (void)pio_add_program_at_offset(pio, &quadrature_encoder_program, 0);
    quadrature_encoder_program_init(*q, max_step_rate);
}

int main() {
    stdio_init_all();
    sleep_ms(3*1000);
    printf("booted\n");

    // encoder1 is connected to pin 20,21
    // encoder1 is connected to pin 17,18
    quad_init(&quadratures1, pio0, 20, 17, -1, -1, 0);


    uint button_offset = pio_add_program(pio1, &button_program);

    uint const button_gpio = 2;
    button_init(pio1, button_offset, button_gpio);


    for (;;) {
        int delta[2];
        // note: thanks to two's complement arithmetic delta will always
        // be correct even when new_value wraps around MAXINT / MININT
        quadrature_encoder_get_count(&quadratures1);
        delta[0] = quadratures1.count_new[0] - quadratures1.count_old[0];
        quadratures1.count_old[0] = quadratures1.count_new[0];
        delta[1] = quadratures1.count_new[1] - quadratures1.count_old[1];
        quadratures1.count_old[1] = quadratures1.count_new[1];
        if (delta[0] != 0) {
            printf("position0 %8d, delta %6d\n", quadratures1.count_new[0], delta[0]);
        }
        if (delta[1] != 0) {
            printf("position1 %8d, delta %6d\n", quadratures1.count_new[1], delta[1]);
        }

        uint32_t button_state;
        if (button_get_state(&button_state)) {
            printf("got a button edge: 0x%08lx\n", button_state);
        }
    }
}
