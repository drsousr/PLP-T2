# Calculadora com GUI em C e C++

Este repositório contém o desenvolvimento de uma calculadora simples com Interface Gráfica de Usuário (GUI) implementada em duas linguagens de programação distintas: C (linguagem procedural) e C++ (linguagem orientada à objetos). Este projeto foi criado para comparação dos paradigmas de programação procedural e orientado a objetos na disciplina de Paradigmas de Linguagem de Programação.


## Integrantes

* Beatriz Brito
* Geovanna Monteiro
* Pedro Henrique Sousa


## Tecnologias Utilizadas

* **C:**
    * GTK+ 3: Biblioteca para a criação de interfaces gráficas em C.
* **C++:**
    * gtkmm: Bindings C++ para a biblioteca GTK+.


## Funcionalidades da Calculadora

Ambas as versões da calculadora (em C e C++) implementam as seguintes funcionalidades:

* Entrada de números.
* Operações básicas: adição (+), subtração (-), multiplicação (*) e divisão (/).
* Limpeza do visor (botão "C" ou "Clear").
* Exibição do resultado.


## Como Executar as Calculadoras

### Calculadora em C

1.  **Pré-requisitos:** 
    ```bash
    sudo apt-get update
    sudo apt-get install libgtk-3-dev
    ```


2.  **Compilação:** 
    ```bash
    gcc main.c -o calculadora_c `pkg-config --cflags --libs gtk+-3.0`
    ```

3.  **Execução:** 
    ```bash
    ./calculadora_c
    ```


### Calculadora em C++

1.  **Pré-requisitos:**
    ```bash
    sudo apt-get update
    sudo apt-get install libgtkmm-3.0-dev
    ```


    ```bash
    g++ main.cpp -o calculadora_cpp `pkg-config --cflags --libs gtkmm-3.0`
    ```


    ```bash
    ./calculadora_cpp
    ```