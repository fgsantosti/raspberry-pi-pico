
### **1. Introdução a Algoritmos e Programação**
#### O que é um Algoritmo?
Um **algoritmo** é uma sequência de passos lógicos para resolver um problema. Ele pode ser representado por pseudocódigo, fluxograma ou diretamente em uma linguagem de programação, como C.

#### Primeiro Programa em C
O famoso exemplo "Hello World":
```c
#include <stdio.h>  // Biblioteca padrão para entrada e saída

int main() {
    printf("Hello, World!\n");  // Exibe a mensagem na tela
    return 0;  // Indica que o programa terminou com sucesso
}
```

#### Simulação em Hardware
Imagine que estamos acendendo um LED para indicar "Hello World":

Para realizarmos os exemplos com a placa Raspberry Pi Pico W, inicialmente precisaremos criar o exemplo do [blink]((https://github.com/raspberrypi/pico-examples/tree/master/blink)). O professore irá fazer com vocês. 


```c
/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

// Dispositivos Pico W usam um GPIO no chip WIFI para o LED,
// então, ao compilar para Pico W, CYW43_WL_GPIO_LED_PIN será definido
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

// Realiza a inicialização
int pico_led_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Um dispositivo como o Pico que usa um GPIO para o LED definirá PICO_DEFAULT_LED_PIN
    // então podemos usar a funcionalidade GPIO normal para ligar e desligar o LED
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Para dispositivos Pico W, precisamos inicializar o driver, etc
    return cyw43_arch_init();
#endif
}

// Liga ou desliga o LED
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Basta definir o GPIO como ligado ou desligado
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Peça ao "driver" WIFI para definir o GPIO como ligado ou desligado
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

int main() {
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);
    while (true) {
        pico_set_led(true);
        sleep_ms(LED_DELAY_MS);
        pico_set_led(false);
        sleep_ms(LED_DELAY_MS);
    }
}
```

Para melhor compreesão de vocês vamos utilizar o botão da propria placa Raspberry Pi Pico W, ela pode ser acionada com o código que se encontra na documetação do [botao]((https://github.com/raspberrypi/pico-examples/tree/master/picoboard/button)).


Vamos transformar o código do botão em uma `biblioteca`. 

Uma biblioteca .h em C é um arquivo que contém declarações de funções, variáveis e macros que podem ser utilizadas em outros arquivos de código-fonte.
Pense em uma biblioteca .h como um catálogo de ferramentas que você pode usar em seu programa. Você não precisa saber como as ferramentas são feitas, apenas como usá-las.
Uma biblioteca .h geralmente contém:
- Declarações de funções: especificam o nome da função, os parâmetros que ela aceita e o tipo de valor que ela retorna.
- Declarações de variáveis: especificam o nome da variável e o seu tipo.
- Macros: são substituições de texto que podem ser usadas para simplificar o código.

Para usar uma biblioteca .h, você precisa:
1. Incluir a biblioteca no seu arquivo de código-fonte usando a diretiva #include.
1. Compilar o seu programa com a biblioteca incluída.

Exemplo:

```c
// meu_programa.c
#include "minha_biblioteca.h"

int main() {
    // Usa a função soma da biblioteca minha_biblioteca.h
    int resultado = soma(2, 3);
    printf("O resultado é: %d\n", resultado);
    return 0;
}
```

```c
// minha_biblioteca.h
#ifndef MINHA_BIBLIOTECA_H
#define MINHA_BIBLIOTECA_H

int soma(int a, int b);

#endif  // MINHA_BIBLIOTECA_H
```
```c
// minha_biblioteca.c
#include "minha_biblioteca.h"

int soma(int a, int b) {
    return a + b;
}
```

Nesse exemplo, o arquivo meu_programa.c inclui a biblioteca minha_biblioteca.h e usa a função soma da biblioteca. A biblioteca minha_biblioteca.h declara a função soma, que é definida no arquivo minha_biblioteca.c.

Vamos criar o bootsel.h uma biblioteca para utilizarmos o botão da propria placa. 

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

Agora vamos alterar um pouco a nossa funçao `main`:
```c
#include "pico/stdlib.h"
#include "bootsel.h"

//código omitido para LED do Pico piscar

// Loop infinito para verificar o estado do botão Bootsel
while (true) {
    // Verifica se o botão Bootsel está pressionado
    if (get_bootsel_button()) {
        // Se o botão estiver pressionado, liga o LED
        pico_set_led(true);
    } else {
        // Se o botão não estiver pressionado, desliga o LED
        pico_set_led(false);
    }
}

```

Vamos fazer mais um exemplo bem legal, vamos alterar um pouco a nossa funçao `main`:

```c
#include "pico/stdlib.h"
#include "bootsel.h"

//código omitido para LED do Pico piscar

int main() {
    // Inicializa o LED
    int rc = pico_led_init();
    
    // Verifica se a inicialização foi bem-sucedida
    hard_assert(rc == PICO_OK);

    // Loop infinito
    while (true) {
        // Verifica se o botão Bootsel está pressionado
        if (get_bootsel_button()) {
            // Se o botão estiver pressionado, ligamos o LED
            pico_set_led(true);
            
            // Aguardamos por um tempo antes de desligar o LED
            sleep_ms(LED_DELAY_MS);
            
            // Desligamos o LED
            pico_set_led(false);
            
            // Aguardamos por um tempo antes de verificar novamente o botão
            sleep_ms(LED_DELAY_MS);
            
            // Continuamos o loop
            continue;
        }
        
        // Se o botão não estiver pressionado, fazemos nada
    }
}
```

---

### **2. Operadores Aritméticos**
#### Explicação
Os operadores aritméticos em C incluem:
- `+` (adição), `-` (subtração), `*` (multiplicação), `/` (divisão), `%` (resto da divisão).

#### Exemplo: Cálculo de média
```c
#include <stdio.h>

int main() {
    float nota1 = 8.5, nota2 = 7.0, media;
    
    // Calcula a média
    media = (nota1 + nota2) / 2;
    
    printf("A média das notas é: %.2f\n", media);  // Exibe o resultado
    return 0;
}
```

#### Simulação em Hardware
Controlando a intensidade de um LED com um valor médio:
```c
#include <stdio.h>

int main() {
    int brilho1 = 50;  // Intensidade do LED 1 (0 a 100)
    int brilho2 = 80;  // Intensidade do LED 2
    int brilho_medio;
    
    brilho_medio = (brilho1 + brilho2) / 2;  // Calcula o brilho médio
    printf("Brilho médio do LED: %d\n", brilho_medio);
    return 0;
}
```

---

### **3. Operadores de Comparação**
#### Explicação
Comparam valores e retornam `1` (verdadeiro) ou `0` (falso):
- `==` (igual), `!=` (diferente), `<`, `>`, `<=`, `>=`.

#### Exemplo: Comparação de números
```c
#include <stdio.h>

int main() {
    int a = 5, b = 10;
    
    if (a < b) {
        printf("A é menor que B\n");
    } else {
        printf("A não é menor que B\n");
    }
    return 0;
}
```

#### Simulação em Hardware
Verificar se um botão foi pressionado:
```c
#include <stdio.h>

int main() {
    int botao_pressionado = 1;  // 1 significa que o botão foi pressionado
    
    if (botao_pressionado == 1) {
        printf("O botão foi pressionado, acendendo o LED!\n");
    } else {
        printf("O botão não foi pressionado.\n");
    }
    return 0;
}
```

---

### **4. Operadores Lógicos**
#### Explicação
Combinam expressões:
- `&&` (e lógico), `||` (ou lógico), `!` (não lógico).

#### Exemplo: Controle de acesso
```c
#include <stdio.h>

int main() {
    int senha_correta = 1234;  // Senha correta
    int senha_entrada;        // Senha digitada pelo usuário
    int botao_pressionado;    // Estado do botão: 1 = pressionado, 0 = não pressionado

    // Solicita a senha do usuário
    printf("Digite a senha: ");
    scanf("%d", &senha_entrada);

    // Solicita o estado do botão
    printf("O botão foi pressionado? (1 para Sim, 0 para Não): ");
    scanf("%d", &botao_pressionado);

    // Verifica as duas condições
    if (senha_entrada == senha_correta && botao_pressionado == 1) {
        printf("Acesso permitido! LED aceso.\n");
    } else {
        printf("Acesso negado. Verifique a senha ou pressione o botão.\n");
    }

    return 0;
}
```

#### Simulação em Hardware
Acender o LED apenas se dois botões forem pressionados:
```c
#include <stdio.h>

int main() {
    int botao1 = 1, botao2 = 0;  // 1 = pressionado, 0 = não pressionado
    
    if (botao1 == 1 && botao2 == 1) {
        printf("Ambos os botões foram pressionados. LED aceso!\n");
    } else {
        printf("Os dois botões não estão pressionados.\n");
    }
    return 0;
}
```

---

### **5. Estruturas Condicionais**
#### Explicação
Permitem executar partes diferentes do código com base em condições.

#### Exemplo: Verificar temperatura
```c
#include <stdio.h>

int main() {
    int temperatura = 30;

    if (temperatura > 25) {
        printf("Está quente!\n");
    } else {
        printf("Está frio!\n");
    }
    return 0;
}
```

#### Simulação em Hardware
Ligar ou desligar um ventilador com base na temperatura:
```c
#include <stdio.h>

int main() {
    int temperatura = 30;

    if (temperatura > 25) {
        printf("Temperatura alta! Ligando o ventilador.\n");
    } else {
        printf("Temperatura normal. Ventilador desligado.\n");
    }
    return 0;
}
```

---

### **6. Estruturas de Repetição**
#### Explicação
Executam um bloco de código repetidamente: `for`, `while`, `do-while`.

#### Exemplo: Contagem de 1 a 10
```c
#include <stdio.h>

int main() {
    for (int i = 1; i <= 10; i++) {
        printf("%d\n", i);
    }
    return 0;
}
```

#### Simulação em Hardware
Piscar um LED 5 vezes:
```c
#include <stdio.h>

int main() {
    for (int i = 1; i <= 5; i++) {
        printf("LED ligado!\n");
        printf("LED desligado!\n");
    }
    return 0;
}
```

---

### **7. Funções**
#### Explicação
Reutilizam blocos de código para facilitar o desenvolvimento.

#### Exemplo: Soma de dois números
```c
#include <stdio.h>

int soma(int a, int b) {
    return a + b;
}

int main() {
    int resultado = soma(3, 7);
    printf("A soma é: %d\n", resultado);
    return 0;
}
```

#### Simulação em Hardware
Função para controlar o LED:
```c
#include <stdio.h>

void ligar_led() {
    printf("LED ligado!\n");
}

void desligar_led() {
    printf("LED desligado!\n");
}

int main() {
    ligar_led();
    desligar_led();
    return 0;
}
```

#### Simulação em Hardware
Função para controlar o LED pelo usuário:
```c
#include <stdio.h>  // Biblioteca padrão para entrada e saída

// Definições para simular os pinos dos LEDs
#define LED1_PIN 2  // LED 1 conectado ao pino 2
#define LED2_PIN 3  // LED 2 conectado ao pino 3

int main() {
    int estado_led1 = 0;  // Estado do LED 1 (0 = desligado, 1 = ligado)
    int estado_led2 = 0;  // Estado do LED 2 (0 = desligado, 1 = ligado)
    int escolha;          // Variável para armazenar a escolha do usuário

    printf("Simulação de LEDs com estrutura condicional\n");
    printf("Os LEDs estão conectados aos pinos %d e %d\n", LED1_PIN, LED2_PIN);

    while (1) {  // Loop infinito para simular o controle dos LEDs
        printf("\nEscolha uma ação:\n");
        printf("1 - Ligar LED 1\n");
        printf("2 - Desligar LED 1\n");
        printf("3 - Ligar LED 2\n");
        printf("4 - Desligar LED 2\n");
        printf("5 - Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);

        // Estruturas condicionais para controlar os LEDs
        if (escolha == 1) {
            printf("Ligando LED 1...\n");
            estado_led1 = 1;  // Altera o estado do LED 1 para ligado
        } else if (escolha == 2) {
            printf("Desligando LED 1...\n");
            estado_led1 = 0;  // Altera o estado do LED 1 para desligado
        } else if (escolha == 3) {
            printf("Ligando LED 2...\n");
            estado_led2 = 1;  // Altera o estado do LED 2 para ligado
        } else if (escolha == 4) {
            printf("Desligando LED 2...\n");
            estado_led2 = 0;  // Altera o estado do LED 2 para desligado
        } else if (escolha == 5) {
            printf("Encerrando o programa...\n");
            break;  // Encerra o loop e o programa
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }

        // Exibe o estado atual dos LEDs
        printf("Estado atual: LED 1 = %s, LED 2 = %s\n",
               estado_led1 ? "Ligado" : "Desligado",
               estado_led2 ? "Ligado" : "Desligado");
    }

    return 0;
}
```

---

### **8. Vetores**
#### Explicação
Armazenam múltiplos valores de mesmo tipo.

#### Exemplo: Exibir números de um vetor
```c
#include <stdio.h>

int main() {
    int numeros[5] = {1, 2, 3, 4, 5};
    
    for (int i = 0; i < 5; i++) {
        printf("Número %d: %d\n", i + 1, numeros[i]);
    }
    return 0;
}
```

#### Simulação em Hardware
Controlar LEDs com base em um vetor:
```c
#include <stdio.h>

int main() {
    int estados[3] = {1, 0, 1};  // 1 = ligado, 0 = desligado
    
    for (int i = 0; i < 3; i++) {
        if (estados[i] == 1) {
            printf("LED %d ligado!\n", i + 1);
        } else {
            printf("LED %d desligado!\n", i + 1);
        }
    }
    return 0;
}
```

---

Esses exemplos práticos fornecem uma introdução sólida para iniciantes e integram conceitos teóricos com aplicações simuladas em hardware. Se precisar de ajustes ou mais detalhes, é só avisar! 😊
