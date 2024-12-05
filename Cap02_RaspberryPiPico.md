### Exemplo Botão e Buzzer
```c 
#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    // Configuração do GPIO para o botão como entrada com pull-up
    const uint BUTTON_PIN = 5;  // Pino do botão
    const uint BUZZER_PIN = 21; // Pino do buzzer
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Configuração do GPIO para o buzzer como saída
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    while (true) {
        // Verifica o estado do botão
        if (gpio_get(BUTTON_PIN) == 0) {  // Botão pressionado (nível lógico baixo)
            printf("Button pressed\n");
            gpio_put(BUZZER_PIN, 1);     // Liga o buzzer
            sleep_ms(1000);             // Aguarda 1 segundo
        } else {
            gpio_put(BUZZER_PIN, 0);     // Desliga o buzzer
        }
    }

    return 0;
}

```

```c
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(botao_buzzer C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(botao_buzzer botao_buzzer.c )

pico_set_program_name(botao_buzzer "botao_buzzer")
pico_set_program_version(botao_buzzer "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(botao_buzzer 0)
pico_enable_stdio_usb(botao_buzzer 1)

# Add the standard library to the build
target_link_libraries(botao_buzzer
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(botao_buzzer PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(botao_buzzer)

pico_add_extra_outputs(botao_buzzer)
```
