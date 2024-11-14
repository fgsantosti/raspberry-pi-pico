#include "ws2812.h"
#include "hardware/pwm.h"

// Inicialização do controlador WS2812
void ws2812_init(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, 249);
    pwm_init(slice_num, &config, true);
}

// Função para enviar cor RGB para um LED WS2812
void ws2812_put_pixel(uint8_t r, uint8_t g, uint8_t b) {
    // Envia os bits para o controlador WS2812 usando PWM
    uint32_t pixel = ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;
    for (int i = 23; i >= 0; i--) {
        if ((pixel >> i) & 0x1) {
            pwm_set_gpio_level(PICO_DEFAULT_WS2812_PIN, 200);  // Envia 1
        } else {
            pwm_set_gpio_level(PICO_DEFAULT_WS2812_PIN, 50);   // Envia 0
        }
        sleep_us(1);  // Pequeno atraso para sincronização
    }
}

void ws2812_show(void) {
    // Atraso para garantir que o último bit seja enviado
    sleep_us(50);
}