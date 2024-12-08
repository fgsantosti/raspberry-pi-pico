
## Conteúdo Aula EmbarcaTech sobre a Configuração Visual Code e a placa Raspberry Pi Pico W

## 1. Apresentacao marcelino
## 2. Apresentacao jivago e felipe
## 3. Jivago exemplo debug
## 4. Felipe exemplos C bootsel
    ### botao com condicional (pressionando
    ### segundo com um contador
    ### terceiro entrada de dados
    ### laço de repeticao
    ### funcao
## 5. Placa bitdoglab botao e led RGB
## 6. Placa bitdoglab botao e buzzer
## 7. Despedida


## 1. Jivago exemplo debug
## 2. Felipe exemplos C bootsel
    ### botao com condicional (pressionando
```c
/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/sync.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"

// Este exemplo faz o LED do Pico piscar quando o botão BOOTSEL é pressionado.
//
// O Picoboard tem um botão conectado ao pino CS do flash, que o bootrom
// verifica e pula diretamente para o código de inicialização do USB se o botão
// estiver pressionado (puxando o CS do flash para baixo). Podemos verificar
// esse pino pulando para algum código na SRAM (para que a interface XIP não seja
// necessária), deixando o pino CS do flash flutuando e observando se ele é
// puxado para baixo.
//
// Isso não funciona se outros estiverem tentando acessar o flash ao mesmo tempo,
// por exemplo, o transmissor XIP ou a outra core.

bool __no_inline_not_in_flash_func(get_bootsel_button)() {
    const uint CS_PIN_INDEX = 1;

    // É necessário desabilitar as interrupções, pois os manipuladores de interrupção
    // podem estar no flash e estamos prestes a desabilitar temporariamente o acesso ao
    // flash!
    uint32_t flags = save_and_disable_interrupts();

    // Define o chip select como Hi-Z
    hw_write_masked(&ioqspi_hw->io[CS_PIN_INDEX].ctrl,
                    GPIO_OVERRIDE_LOW << IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_LSB,
                    IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

    // Note que não podemos chamar funções de sleep no flash agora
    for (volatile int i = 0; i < 1000; ++i);

    // Os registros HI GPIO em SIO podem observar e controlar os 6 pinos QSPI.
    // Note que o botão puxa o pino *baixo* quando pressionado.
#if PICO_RP2040
    #define CS_BIT (1u << 1)
#else
    #define CS_BIT SIO_GPIO_HI_IN_QSPI_CSN_BITS
#endif
    bool button_state = !(sio_hw->gpio_hi_in & CS_BIT);

    // É necessário restaurar o estado do chip select, senão teremos um problema
    // quando voltarmos ao código no flash!
    hw_write_masked(&ioqspi_hw->io[CS_PIN_INDEX].ctrl,
                    GPIO_OVERRIDE_NORMAL << IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_LSB,
                    IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

    restore_interrupts(flags);

    return button_state;
}
```

    _ segundo com um contador

```c
#include <stdio.h>
#include "pico/stdlib.h"

#include "bootsel.h"

int main() {
    stdio_init_all();
    if (get_bootsel_button()) {
        contador++;
        printf("Bootsel button is pressed  - %d\n", contador);
        sleep_ms(1000);
    }
}

```
    _ terceiro entrada de dados

```c
#include <stdio.h>
#include "pico/stdlib.h"

#include "bootsel.h"

int main() {
    stdio_init_all();
    int contador=0;
    char x = '0';
    while (true) {
        scanf("%c", &x);
        switch(x){
            case '1':
                printf("x eh 1\n");
                break;
            case '2':
                printf("x eh 2\n");
                break;
            default:
                printf("x nao eh 1 nem 2\n");
        }
}

```
    _ laço de repeticao
    _ funcao
## 3. Placa bitdoglab botao e led RGB
## 4. Placa bitdoglab botao e buzzer

