### Exemplo Botões e LED RGB

```c
#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    // Configuração dos pinos dos botões como entrada com pull-up
    const uint BUTTON_A_PIN = 5;  // Botão A no GPIO 5
    const uint BUTTON_B_PIN = 6;  // Botão B no GPIO 6
    gpio_init(BUTTON_A_PIN);
    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
    gpio_pull_up(BUTTON_B_PIN);

    // Configuração dos LEDs RGB como saída
    const uint BLUE_LED_PIN= 12;   // LED azul no GPIO 12
    const uint RED_LED_PIN  = 13; // LED vermelho no GPIO 13
    const uint GREEN_LED_PIN = 11;  // LED verde no GPIO 11
    gpio_init(RED_LED_PIN);
    gpio_init(GREEN_LED_PIN);
    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    // Inicialmente, desligar o LED RGB
    gpio_put(RED_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
    gpio_put(BLUE_LED_PIN, 0);

    while (true) {
        // Se o botão A for pressionado
        if (gpio_get(BUTTON_A_PIN) == 0) {
            gpio_put(BLUE_LED_PIN, 0);   // Desliga o LED azul
            gpio_put(RED_LED_PIN, 1);   // Liga o LED vermelho
            gpio_put(GREEN_LED_PIN, 0);  // Desliga o LED verde
        }
        // Se o botão B for pressionado
        else if (gpio_get(BUTTON_B_PIN) == 0) {
            gpio_put(BLUE_LED_PIN, 0);   // Desliga o LED azul
            gpio_put(RED_LED_PIN, 0);   // Desliga o LED vermelho
            gpio_put(GREEN_LED_PIN, 1);  // Liga o LED verde
        }
        // Se nenhum botão estiver pressionado
        else {
            gpio_put(RED_LED_PIN, 0);   // Desliga o LED vermelho
            gpio_put(GREEN_LED_PIN, 0); // Desliga o LED verde
            gpio_put(BLUE_LED_PIN, 0);  // Desliga o LED azul
        }
        sleep_ms(10); // Pequeno atraso para evitar debounce
    }
    return 0; // O programa nunca alcança essa linha
}

```
#### CMakeLists
```c
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(botoes_led_rgb C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(botoes_led_rgb botoes_led_rgb.c )

pico_set_program_name(botoes_led_rgb "botoes_led_rgb")
pico_set_program_version(botoes_led_rgb "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(botoes_led_rgb 0)
pico_enable_stdio_usb(botoes_led_rgb 1)

# Add the standard library to the build
target_link_libraries(botoes_led_rgb
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(botoes_led_rgb PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(botoes_led_rgb)

pico_add_extra_outputs(botoes_led_rgb)


```

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
#### CMakeLists

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
