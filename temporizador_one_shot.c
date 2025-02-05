#include <stdio.h>
#include "pico/time.h"
#include "pico/stdlib.h"

#define BUTTON_A 5      // Pino do botão
#define LED_GREEN 11   // Pino do LED verde
#define LED_AZUL 12     // Pino do LED azul
#define LED_RED 13    // Pino do LED vermelho

bool led_red_active = false;
bool led_azul_active = false;
bool led_green_active = false;
bool sequence_active = false; // Flag para indicar se a sequência está ativa
int elapsed_time = 1; 

uint32_t last_button_press_time = 0;  // Tempo do último evento de botão
#define DEBOUNCE_DELAY_MS 200  // Delay de debounce em milissegundos

// Função de callback para mudar o estado dos LEDs
int64_t change_led_state_callback(alarm_id_t id, void *user_data) {
    if (led_red_active && led_azul_active && led_green_active) {
        // Desliga o LED vermelho após 3 segundos
        gpio_put(LED_AZUL, false);
        led_red_active = false;
        printf("Tempo: %d segundos | Dois LEDs ligados (Vermelho e Verde,)\n",elapsed_time);
    } else if (!led_red_active && led_azul_active && led_green_active) {
        // Desliga o LED azul após mais 3 segundos
        gpio_put(LED_RED, false);
        led_azul_active = false;
        printf("Tempo: %d segundos | Apenas um LED ligado (Verde)\n",elapsed_time);
    } else if (!led_red_active && !led_azul_active && led_green_active) {
        // Desliga o LED verde após mais 3 segundos
        gpio_put(LED_GREEN, false);
        led_green_active = false;
        sequence_active = false; // Finaliza a sequência
        printf("Tempo: %d segundos |Todos os LEDs desligados\n",elapsed_time);
    }
    return 0; // Retorna 0 para indicar que o alarme não deve ser repetido
}
bool debounce_button() {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());  // Tempo atual em milissegundos
    if ((current_time - last_button_press_time) > DEBOUNCE_DELAY_MS) {
        last_button_press_time = current_time;
        return true;  // O botão foi pressionado e o debounce foi superado
    }
    return false;  // O botão foi pressionado muito recentemente, ignora
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial (USB)

    // Configura os pinos dos LEDs como saída
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Configura o pino do botão como entrada com pull-up
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    while (1) {
        // Verifica se o botão foi pressionado e se a sequência não está ativa
if (gpio_get(BUTTON_A) == 0 && debounce_button() && !sequence_active) {            sleep_ms(50); // Debounce do botão
            if (gpio_get(BUTTON_A) == 0) {
                // Liga todos os LEDs
                gpio_put(LED_AZUL, true);
                gpio_put(LED_RED, true);
                gpio_put(LED_GREEN, true);
                led_red_active = true;
                led_azul_active = true;
                led_green_active = true;
                sequence_active = true; // Indica que a sequência está ativa
                elapsed_time = 1;
                printf("Tempo: %d segundos |Todos os LEDs ligados\n",elapsed_time);

                // Agenda a primeira mudança de estado após 3 segundos
                add_alarm_in_ms(3000, change_led_state_callback, NULL, false);
                // Agenda a segunda mudança de estado após 6 segundos
                add_alarm_in_ms(6000, change_led_state_callback, NULL, false);
                // Agenda a terceira mudança de estado após 9 segundos
                add_alarm_in_ms(9000, change_led_state_callback, NULL, false);
            }
        }
 // Incrementa o tempo decorrido a cada segundo
        if (sequence_active) {
            sleep_ms(1000); // Espera 1 segundo
            elapsed_time++; // Incrementa o tempo decorrido
        } else {
            sleep_ms(10); // Pequeno atraso para evitar leitura múltipla do botão
        }
     // Pequeno atraso para evitar leitura múltipla do botão
    }

    return 0;
}