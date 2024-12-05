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
```c
#include <stdio.h>

int main() {
    printf("Acendendo um LED para dizer Hello World!\n");
    // Simulação: LED ligado
    printf("LED está ligado!\n");
    return 0;
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
