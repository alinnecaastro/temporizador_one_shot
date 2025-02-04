# Temporizador de um disparo (One Shot)

## Estrutura do Projeto  
- **build/** → Diretório de compilação gerado pelo CMake.  
- **diagram.json** → Simulação do Wokwi 
- **CMakeLists.txt** → Configuração do CMake para compilação.  
- **temporizador_one_shot.c** → Código principal do projeto.    
- **pico_sdk_import.cmake** → Importação do SDK do Raspberry Pi Pico.  
- **README.md** → Documentação do projeto.  


## Descrição Geral
 Este exercício tem como objetivo desenvolver um sistema de controle de LEDs utilizando o microcontrolador Raspberry Pi Pico W, com acionamento baseado em um botão (pushbutton). A lógica do sistema envolve o acionamento sequencial de três LEDs (azul, vermelho e verde), com intervalos de 3 segundos entre os estados dos LEDs.

 

## Video do funcionamento do projeto
https://drive.google.com/file/d/1hFp7RoonCgcqu9AKGjFybk2F3y6eqCJv/view?usp=sharing

## Video do funcionamento no simulador dentro do vscode 
https://drive.google.com/file/d/1-Tv3v2VtjqgrzVyx8CsMGfiXQHiEUawk/view?usp=sharing

## Funcionalidades do Projeto
° O sistema começa com os três LEDs acessos, quando o botão é pressionado.
° O temporizador é configurado com um atraso de 3 segundos. Cade vez que o temporizador dispara, ele chama uma função de callback para alternar o estado dos LEDs
°No primeiro estado: Todos os três estão acesos.
° No segundo estado após 3 segundos: Dois LEDs permanecem acesos, e o terceiro desligado.
° No terceiro estado após mais 3 segundos: Apenas um LED permanece aceso, enquanto os outros dois são desligados.
°O botão A inicia a sequência de LEDs, mas só pode fazer isso quando o último LED já estiver apagado, ou seja, a troca so pode ser feita quando a última transição (Desligado) for completada, quando o botão inicia ele proprio não poderá chamar uma nova chamada de função.

## Requisitos do Projeto
° Os LEDs devem ser controlados através de um botão (GPIO 05)
° Inicialmente, todos os LEDs devem estar apagados;
° Após o acionamento do botão, a sequência de LEDs deve ser controlada conforme os seguintes estados:
      Estado 1: Todos os LEDs acesos.
      Estado 2: Dois LEDs acesos, um LED apagado.
      Estado 3: Apenas um LED aceso, dois LEDs apagados.
° Cada mudança de estado deve ocorrer a cada 3 segundos (3.000ms), utilizando um temporizador.
° A mudança de estado dos LEDs deve ser feita dentro de funções de callback do temporizador (exemplo: turn_off_callback()).
° O botão (GPIO 05) deve ser capaz de iniciar a sequência de LEDs, mas somente quando o último LED for apagado. Ou seja, o botão não pode reiniciar a sequência enquanto o temporizador ainda estiver em execução ou enquanto algum LED não tiver sido apagado.

## Configuração do Ambiente
1. Instale o SDK do Raspberry Pi Pico:
2. Clone o repositório
    https://github.com/alinnecaastro/temporizador_one_shot.git

## **Compile o código:**

1. Certifique-se de que o SDK está instalado e funcionando corretamente no VSCode.

2. Usando a extensão do Raspberry Pi Pico Visual Studio Code extension, siga os passos:

3. Clean CMake: Para garantir que o projeto será compilado do zero.

4. Compile Project: Compilação dos binários.

5. Run Project [USB]: Compila e copia o firmware para a placa automaticamente.


## **Funcionamento do Código**

1. **Inicialização**
- Configuração dos 3 LEDs conectados aos pinos GPIO 11,12 e 13, que  serão controlados para mudar de estado.
- Configuração de um botão A que está conectado ao pino GPIO 05, e serve para iniciar o ciclo de LEDs.

2. **Sequência de LEDs**
- Inicialmente, todos os LEDs serão acesos (nível alto).
Após 3 segundos (tempo de atraso), dois LEDs serão desligados, deixando apenas um aceso.
- Após mais 3 segundos, o último LED será desligado, e o sistema voltará ao estado inicial (todos os LEDs acesos).

3. **Temporizador (Alarm Timer)**
- O temporizador é configurado com um atraso de 3.000ms (3 segundos), que acionará uma função de callback para alternar o estado dos LEDs.
- A mudança de estado dos LEDs será controlada por essa função de callback, como foi mencionado na aula síncrona (por exemplo, turn_off_callback()).

4. **Botão de Controle**
- O botão só pode iniciar a mudança de estado quando o último LED for apagado. Durante a execução do temporizador, o botão não pode iniciar a função callback, garantindo que a sequência de LEDs seja completada antes de permitir um novo ciclo.

4. **Loop Principal**
- Monitora se o botão foi pressionado e se a sequencia não está ativa
- Agenda a primeira mudança de estado após 3 segundos
- Incrementa o tempo decorrido a cada segundo



## **Como Usar**

1. Conecte os componentes conforme o diagrama de conexões.
2. Carregue o firmware no Raspberry Pi Pico W.
3. Interaja com o botão para acender os LEDs




## Conclusão
O código que você implementou serve para controlar três LEDs (vermelho, azul e verde) com base na interação de um botão, realizando uma sequência de acionamento e desligamento dos LEDs, e utilizando alarmes para temporização. A principal funcionalidade é permitir que os LEDs alterem seu estado de forma progressiva (todos acesos, dois acesos e um aceso), com intervalos de 3 segundos entre cada mudança de estado.

```