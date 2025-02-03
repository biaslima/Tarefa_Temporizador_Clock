#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/watchdog.h"

#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define BOTAO 5

volatile bool alarme_ativo = false;

int64_t desligar_led_azul_callback(alarm_id_t id, void *user_data);
int64_t desligar_led_verde_callback(alarm_id_t id, void *user_data);

int64_t desligar_led_vermelho_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, false);
    add_alarm_in_ms(3000, desligar_led_azul_callback, NULL, false);
    return 0; 
}

int64_t desligar_led_azul_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, false);
    add_alarm_in_ms(3000, desligar_led_verde_callback, NULL, false);
    return 0; 
}

int64_t desligar_led_verde_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, false);
    alarme_ativo = false;
    return 0; 
}


int main() {

    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);

    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);

    while (true) {
        if (!gpio_get(BOTAO) && !alarme_ativo) {
            alarme_ativo = true;

            gpio_put(LED_VERMELHO, 1);
            gpio_put(LED_VERDE, 1);
            gpio_put(LED_AZUL, 1);

            
            add_alarm_in_ms(3000, desligar_led_vermelho_callback, NULL, false);
            alarme_ativo = false;  
        }

        printf("Aguardando botão ser pressionado\n");
        sleep_ms(200);
    }
}
