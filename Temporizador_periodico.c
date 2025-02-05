#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"


// definição das constantes 
const uint led_pin_vermelho = 13; 
const uint led_pin_amarelo = 12;
const uint led_pin_verde= 11;

bool repeating_timer_callback(struct repeating_timer *t) {
    static int estado = 0;
    
    // Desliga todos os LEDs antes de acender o próximo
    gpio_put(led_pin_vermelho, 0);
    gpio_put(led_pin_amarelo, 0);
    gpio_put(led_pin_verde, 0);
    
    // Liga o LED correspondente ao estado atual
    switch (estado) {
        case 0:
            gpio_put(led_pin_verde, 1);
            printf("Sinal vermelho ligado\n");
            break;
        case 1:
            gpio_put(led_pin_amarelo, 1);
            printf("Sinal amarelo ligado\n");
            break;
        case 2:
            gpio_put(led_pin_vermelho, 1);
            printf("Sinal verde ligado\n");
            break;
    }
    
    estado = (estado + 1) % 3;
    
    return true;
}



int main()
{
    stdio_init_all(); // inicializa todos os códigos stdio
    
    //inicializa e define os pinos GPIO como saída.
    gpio_init(led_pin_vermelho);
    gpio_set_dir(led_pin_vermelho,GPIO_OUT);
    gpio_init(led_pin_amarelo);
    gpio_set_dir(led_pin_amarelo,GPIO_OUT);
    gpio_init(led_pin_verde);
    gpio_set_dir(led_pin_verde,GPIO_OUT);
     
    struct repeating_timer timer;
    // Temporizador 3 segundos
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer); 

    while (true) {
        printf("Ligando o sinal!\n");
        sleep_ms(1000);
    }
}
