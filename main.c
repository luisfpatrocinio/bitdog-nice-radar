#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"

#include "ultrassonic.h"
#include "led.h"
#include "display.h"
#include "draw.h"
#include "text.h"
#include "buttons.h"
#include "approach.h"
#include "buzzer.h"

bool showingDistance = false;
int buttonCooldown = 0;

int ledIntensity = 0;
bool increasing = true;

struct repeating_timer timer;
struct repeating_timer changeForcedPersonTimer;

int forcedPerson = 2; // Forçar a pessoa a ser legal ou não (0 = legal, 1 = não legal, 2 = aleatório)
bool stopForcedPerson = false;

bool showingResults = false;

uint note_array[] = {
    261, // C4
    293, // D4
    329, // E4
    349, // F4
    392, // G4
    440, // A4
    493, // B4
    523  // C5
};

const int num_notes = sizeof(note_array) / sizeof(note_array[0]);

bool changeForcedPerson()
{
    if (stopForcedPerson) // Verifica se o timer deve ser interrompido
        return 1;         // Se sim, retorna 0
    forcedPerson++;
    forcedPerson = forcedPerson % 3; // Alterna entre 0, 1 e 2
    return 1;
}

bool repeatingTimerCallback(struct repeating_timer *t)
{
    if (increasing)
    {
        ledIntensity += 10;
        if (ledIntensity >= 255)
        {
            ledIntensity = 255;
            increasing = false;
        }
    }
    else
    {
        ledIntensity -= 10;
        if (ledIntensity <= 0)
        {
            ledIntensity = 0;
            increasing = true;
        }
    }

    return true; // Retorna true para continuar o timer
}

void handleButtonGpioEvent(uint gpio, uint32_t events)
{
    if (buttonCooldown > 0) // Verifica se o cooldown está ativo
        return;             // Se sim, não faz nada

    if (gpio == BTA) // Botão A
    {
        showingDistance = !showingDistance; // Alterna o estado de mostrar distância
        buttonCooldown = 10;                // Define o cooldown para 10 ciclos
    }
    else if (gpio = BTB)
    {
        // Botão B
        changeForcedPerson();
        buttonCooldown = 10; // Define o cooldown para 10 ciclos
    }
}

void showResults(int personStatus, int randomWordIndex, int textY)
{
    const char *positiveAdjectives[] = {
        "muito macho",
        "heterossexual",
        "homem de verdade",
        "nunca foi gay",
        "que cara bom"};

    const char *negativeAdjectives[] = {
        "bicha gladiadora",
        "homossexual",
        "LGBTQIAPN+",
        "curte uma brincadeira",
        "rebola lentinho"};

    setAllLedsBrightness(0); // Desliga todos os LEDs
    if (personStatus)
    {
        setLedBrightness(LED_GREEN_PIN, ledIntensity);                // Verde
        drawTextCentered(positiveAdjectives[randomWordIndex], textY); // Desenha no display
    }
    else
    {
        setLedBrightness(LED_RED_PIN, ledIntensity / 2);              // Vermelho
        setLedBrightness(LED_BLUE_PIN, ledIntensity);                 // Vermelho
        drawTextCentered(negativeAdjectives[randomWordIndex], textY); // Desenha no display
    }
}

void setup()
{
    stdio_init_all();
    initLeds();
    initUltrassonicSensor();
    initI2C();
    initDisplay();
    initializeButtons();
    initBuzzerPWM();                          // Inicializa o buzzer
    setButtonCallback(handleButtonGpioEvent); // Configura o callback para os botões

    add_repeating_timer_ms(12, repeatingTimerCallback, NULL, &timer);
    add_repeating_timer_ms(7500, changeForcedPerson, NULL, &changeForcedPersonTimer); // Inicia o timer para mudar a pessoa forçada a cada 5 segundos

    // startRepeatingTimer();                    // Inicia o timer repetitivo
}

int main()
{
    setup();

    absolute_time_t loadingTime = nil_time;
    absolute_time_t clearMessageTime = nil_time;

    bool scanning = false;
    bool nicePerson = false;
    static float sinSpeed = 0.25;     // Velocidade do movimento da onda
    static float sinAmplitude = 10.0; // Amplitude da onda
    static int textY = -8;            // Posição Y do texto
    int randomWordIndex = 0;

    while (true)
    {
        clearDisplay();
        float distance = measureDistance();
        absolute_time_t currentTime = get_absolute_time();
        int destTextY = 8; // Posição Y do texto

        // Interromper troca aleatória caso esteja escaneando.
        stopForcedPerson = (distance < 15.0f) ? true : false; // Interrompe a troca aleatória se a distância for menor que 15 cm

        // Decrementa o cooldown se estiver ativo
        buttonCooldown = buttonCooldown > 0 ? buttonCooldown - 1 : 0;

        // DEBUG
        if (showingDistance)
        {
            char buffer[20];                                                 // Buffer para armazenar a string formatada
            snprintf(buffer, sizeof(buffer), "Distance: %.2f cm", distance); // Formata a string com a distância
            drawTextCentered(buffer, 0);
            char _forcedPersonText[3];
            snprintf(_forcedPersonText, sizeof(_forcedPersonText), "%d", forcedPerson); // Formata a string com o valor de forcedPerso
            drawText(0, SCREEN_HEIGHT - 8, _forcedPersonText);                          // Desenha a distância no display
        }

        if (absolute_time_diff_us(currentTime, clearMessageTime) <= 0)
        {
            showingResults = false;
        }

        if (showingResults)
        {
            showResults(nicePerson, randomWordIndex, textY);
            sinAmplitude = approach(sinAmplitude, 0.0, 0.369); // Aproxima a amplitude da onda
            destTextY = SCREEN_HEIGHT / 2 - 10;                // Posição Y do texto
        }
        else
        {
            if (distance < 8.0f)
            {
                uint32_t ms = to_ms_since_boot(get_absolute_time());
                int index = (ms / 50) % num_notes;
                playTone(note_array[index], 100); // Toca um tom aleatório

                if (!scanning)
                {
                    if (forcedPerson == 2)
                        nicePerson = rand() % 2 == 0;
                    else if (forcedPerson == 1)
                        nicePerson = false;
                    else if (forcedPerson == 0)
                        nicePerson = true;
                    randomWordIndex = rand() % 5;
                    scanning = true;

                    int randomLoadingTime = 2 + rand() % 5;
                    loadingTime = make_timeout_time_ms(randomLoadingTime * 1000);
                }

                // Se ainda estiver carregando:
                if (absolute_time_diff_us(loadingTime, currentTime) <= 0)
                {
                    drawTextCentered("Mantenha...", textY);      // Desenha "Carregando..." no display
                    drawWave(SCREEN_HEIGHT / 2, sinSpeed, 10.0); // Desenha uma onda na parte inferior do display
                    setAllLedsBrightness(ledIntensity);          // Define o brilho dos LEDs
                    sinSpeed = approach(sinSpeed, 20, 0.369);    // Aproxima a velocidade da onda
                }
                else
                {
                    if (!showingResults)
                    {
                        showingResults = true;
                        clearMessageTime = make_timeout_time_ms(4500);
                    }
                }
            }
            else if (distance < 15.0f)
            {
                turnOffLeds();                                // Desliga os LEDs se a distância for maior que 50 cm
                setAllLedsBrightness(ledIntensity / 5);       // Desliga todos os LEDs
                drawTextCentered("Aproxime-se mais.", textY); // Desenha no display

                scanning = false;
                sinSpeed = approach(sinSpeed, 6.0, 2.0);
                sinAmplitude = approach(sinAmplitude, 8.0, 1.0); // Aproxima a amplitude da onda
            }
            else
            {
                turnOffLeds();                           // Desliga os LEDs se a distância for maior que 50 cm
                setAllLedsBrightness(0);                 // Desliga todos os LEDs
                drawTextCentered("Aproxime-se.", textY); // Desenha no display

                scanning = false;
                sinSpeed = approach(sinSpeed, 1.0, 2.0);
                float _fakeAmplitude = (forcedPerson == 0) ? 8.0 : (forcedPerson == 1) ? 12.0
                                                                                       : 10.0;
                sinAmplitude = approach(sinAmplitude, _fakeAmplitude, 0.25); // Aproxima a amplitude da onda
            }
        }

        textY = approach(textY, destTextY, 1);               // Aproxima a posição Y do texto
        drawWave(SCREEN_HEIGHT / 2, sinSpeed, sinAmplitude); // Desenha uma onda na parte inferior do display
        tight_loop_contents();                               // Mantém o loop apertado para evitar sobrecarga
        showDisplay();                                       // Atualiza o display com o conteúdo desenhado
    }

    return 0;
}
