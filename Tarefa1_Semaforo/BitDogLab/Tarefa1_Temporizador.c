#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define led_pin_red 13
#define led_pin_green 11

int next_led = 0; 

bool repeating_timer_callback (struct repeating_timer *t){

    printf("3 segundos se passaram\n");

    if (next_led == 0){
        gpio_put(led_pin_red, 1);
        gpio_put(led_pin_green, 0);
        next_led = 1;
    }
    else if (next_led == 1){
        gpio_put(led_pin_red, 1);
        gpio_put(led_pin_green, 1);
        next_led = 2;
    }

    else if (next_led == 2){
        gpio_put(led_pin_red, 0);
        gpio_put(led_pin_green, 1);
        next_led = 0;
    }
    return true; 
}

int main()
{
    stdio_init_all();

    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);

    struct repeating_timer timer;


    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        printf("Código rodando\n");
        sleep_ms(1000);
    }
}
