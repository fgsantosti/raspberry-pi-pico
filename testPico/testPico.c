#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

// Core 0 Main Code
int main(void){
    stdio_init_all();

    // Configure ADC
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    // Primary Core 0 Loop
    while(1){
        uint16_t raw = adc_read();
        const float conversion_factor = 3.3f / (1<<12);
        float result = raw * conversion_factor;
        float temp = 27 - (result -0.706)/0.001721;
        printf("Temp = %f C\n", temp);
        sleep_ms(1000);
    }
}