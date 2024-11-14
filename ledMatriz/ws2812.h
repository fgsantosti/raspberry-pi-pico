#ifndef WS2812_H
#define WS2812_H

#include "pico/stdlib.h"

// Define o pino para o WS2812
#define PICO_DEFAULT_WS2812_PIN 7  // Pino para os dados da matriz LED

// Inicializa o controlador WS2812
void ws2812_init(uint gpio);

// Envia um pixel colorido RGB
void ws2812_put_pixel(uint8_t r, uint8_t g, uint8_t b);

void ws2812_show(void);

#endif
