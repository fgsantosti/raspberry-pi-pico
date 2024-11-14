#include <stdio.h>
#include "pico/stdlib.h"
#include "ws2812.h"

#define NUM_LEDS 25
#define GPIO_PIN 7

// Função auxiliar para converter RGB em um valor de 24 bits
uint32_t rgb_to_color(uint8_t red, uint8_t green, uint8_t blue) {
    return ((uint32_t)red << 16) | ((uint32_t)green << 8) | (uint32_t)blue;
}

int main() {
    stdio_init_all();
    ws2812_init(GPIO_PIN);

    // Acende todos os LEDs na cor vermelha para teste
    uint32_t color = rgb_to_color(255, 0, 0);  // Cor vermelha
    for (int i = 0; i < NUM_LEDS; i++) {
        ws2812_put_pixel(color, i, NUM_LEDS);
    }

    while (1) {
        // Mantém a cor acesa indefinidamente
    }

    return 0;
}
