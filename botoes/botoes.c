#include <stdio.h>
#include "pico/stdlib.h"

// Configuração dos pinos para os botões
#define BUTTON_A 5
#define BUTTON_B 6

// Configuração dos pinos para o LED RGB
#define RED_LED 12
#define GREEN_LED 13
#define BLUE_LED 11

int main() {
    // Inicializa o sistema
    stdio_init_all();

    // Configuração dos botões como entradas com resistor de pull-up
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    // Configuração dos LEDs como saídas
    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);

    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);

    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, GPIO_OUT);

    // Desliga o LED RGB inicialmente
    gpio_put(RED_LED, 0);
    gpio_put(GREEN_LED, 0);
    gpio_put(BLUE_LED, 0);

    // Loop principal
    while (true) {
        // Verifica se o botão A foi pressionado
        if (gpio_get(BUTTON_A) == 0) {
            // Acende o LED vermelho
            gpio_put(RED_LED, 1);
            gpio_put(GREEN_LED, 0);
            gpio_put(BLUE_LED, 0);
        }
        // Verifica se o botão B foi pressionado
        else if (gpio_get(BUTTON_B) == 0) {
            // Acende o LED azul
            gpio_put(RED_LED, 0);
            gpio_put(GREEN_LED, 0);
            gpio_put(BLUE_LED, 1);
        }
        // Se nenhum botão estiver pressionado
        else {
            // Desliga todos os LEDs
            gpio_put(RED_LED, 0);
            gpio_put(GREEN_LED, 0);
            gpio_put(BLUE_LED, 0);
        }

        // Pequeno atraso para evitar leituras muito rápidas
        sleep_ms(10);
    }

    return 0;
}
