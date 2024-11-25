
// Pinos para LEDs e botões
const int ledPins[] = {2, 3, 4, 5};       // LEDs: Vermelho, Amarelo, Verde, Azul
const int buttonPins[] = {6, 7, 8, 9};    // Botões correspondentes
const int buzzerPin = A5;                  // Pino do buzzer para feedback sonoro

// Pinos do display de 7 segmentos
const int segmentPins[] = {10, 11, 12, 13, A0, A1, A2}; // Pinos para cada segmento (a, b, c, d, e, f, g)

// Mapeamento de números para segmentos (a=0, b=1, ..., g=6)
const byte digitMap[10] = {
  0b0111111, // 0
  0b0000110, // 1
  0b1011011, // 2
  0b1001111, // 3
  0b1100110, // 4
  0b1101101, // 5
  0b1111101, // 6
  0b0000111, // 7
  0b1111111, // 8
  0b1101111  // 9
};

// Variáveis do jogo
int sequence[50];          // Sequência gerada pelo sistema (até 50 elementos)
int playerSequence[50];    // Sequência que o jogador tenta reproduzir
int sequenceLength = 1;    // Comprimento inicial da sequência (começa com 1)
bool isPlaying = false;     // Controle do estado do jogo (se está em andamento ou não)

// Função para gerar sequência aleatória
void generateSequence() {
    for (int i = 0; i < sequenceLength; i++) {
        sequence[i] = random(0, 4); // Gera números aleatórios entre 0 e 3 (correspondente aos LEDs)
    }
}

// Função para reproduzir sequência nos LEDs
void playSequence() {
    for (int i = 0; i < sequenceLength; i++) {
        int led = sequence[i]; // Pega o LED correspondente à posição da sequência
      
        tone(buzzerPin, 300); // Emitir som no buzzer enquanto o LED acende
        digitalWrite(ledPins[led], HIGH); // Acende o LED
        delay(500); // LED aceso por 500 ms
      
        noTone(buzzerPin); // Para o som no buzzer
        digitalWrite(ledPins[led], LOW); // Apaga o LED
        delay(250); // Pequeno intervalo antes do próximo LED
    }
}

// Função para verificar sequência do jogador
bool checkPlayerInput() {
    for (int i = 0; i < sequenceLength; i++) {
        if (playerSequence[i] != sequence[i]) { // Compara a sequência do jogador com a gerada
            return false; // Retorna falso se houver erro
        }
    }
    return true; // Retorna verdadeiro se a sequência estiver correta
}

// Função para atualizar o display de 7 segmentos
void updateDisplay(int number) {
    if (number > 9) number = 9; // Limita o número a 9 (máximo do display)
    byte segments = digitMap[number]; // Mapeia o número para os segmentos

    for (int i = 0; i < 7; i++) {
        digitalWrite(segmentPins[i], (segments >> i) & 0x01); // Acende os segmentos correspondentes
    }
}

// Função para tocar a música de início
void playStartMusic() {
    int melody[] = { 440, 494, 523, 494, 440 }; // Notas (A4, B4, C5 , B4, A4)
    int noteDurations[] = { 4, 4, 4, 4, 4 }; // Durações (quarte)
    
    for (int thisNote = 0; thisNote < 5; thisNote++) {
        int duration = 1000 / noteDurations[thisNote]; // Duração da nota em milissegundos
        tone(buzzerPin, melody[thisNote], duration); // Toca a nota
        delay(duration); // Espera a duração da nota
        noTone(buzzerPin); // Para o som
        delay(50); // Pequeno intervalo entre as notas
 }
}

// Função para tocar a música de game over
void playGameOverMusic() {
    int melody[] = { 262, 294, 330, 349, 392, 440, 494, 523 }; // Notas (C4, D4, E4, F4, G4, A4, B4, C5)
    int noteDurations[] = { 4, 4, 4, 4, 4, 4, 4, 4 }; // Durações (quarte)
    
    for (int thisNote = 0; thisNote < 8; thisNote++) {
        int duration = 1000 / noteDurations[thisNote]; // Duração da nota em milissegundos
        tone(buzzerPin, melody[thisNote], duration); // Toca a nota
        delay(duration); // Espera a duração da nota
        noTone(buzzerPin); // Para o som
        delay(50); // Pequeno intervalo entre as notas
    }
}

// Função para reiniciar o jogo
void resetGame() {
    sequenceLength = 1; // Reinicia a sequência para o tamanho inicial
    isPlaying = false;  // Para o jogo
    updateDisplay(sequenceLength); // Atualiza o display para mostrar o nível inicial
}

// Função de configuração inicial
void setup() {
    // Configurar LEDs e botões
    for (int i = 0; i < 4; i++) {
        pinMode(ledPins[i], OUTPUT); // Define os pinos dos LEDs como saída
        pinMode(buttonPins[i], INPUT); // Define os pinos dos botões como entrada
    }

    // Configurar pinos do display
    for (int i = 0; i < 7; i++) {
        pinMode(segmentPins[i], OUTPUT); // Define os pinos do display como saída
        digitalWrite(segmentPins[i], LOW); // Inicializa todos os segmentos apagados
    }
  
    pinMode(buzzerPin, OUTPUT); // Configura o pino do buzzer como saída

    // Iniciar semente para random()
    randomSeed(analogRead(0)); // Inicializa a semente do gerador de números aleatórios
  
    playStartMusic(); // Toca a música de início

    // Mostrar nível inicial no display
    updateDisplay(sequenceLength); // Atualiza o display para mostrar o nível inicial
}

// Loop principal
void loop() {
    if (!isPlaying) {
        // Iniciar um novo jogo ao pressionar o botão do primeiro LED
        if (digitalRead(buttonPins[0]) == LOW) { // Verifica se o botão do primeiro LED foi pressionado
            isPlaying = true; // Inicia o jogo
            updateDisplay(sequenceLength); // Atualiza o display para mostrar o nível atual
            delay(500); // Aguarda meio segundo
            generateSequence(); // Gera uma nova sequência aleatória
        }
    } else {
        playSequence(); // Reproduz a sequência gerada

        // Jogador insere sequência
        int playerIndex = 0; // Índice para a sequência do jogador
        while (playerIndex < sequenceLength) { // Enquanto o jogador não completar a sequência
            for (int i = 0; i < 4; i++) { // Verifica cada botão
                if (digitalRead(buttonPins[i]) == HIGH) { // Se o botão correspondente for pressionado
                    playerSequence[playerIndex++] = i; // Armazena a entrada do jogador

                    // Feedback visual
                    tone(buzzerPin, 600); // Emitir som no buzzer
                    digitalWrite(ledPins[i], HIGH); // Acende o LED correspondente
                    delay(300); // Mantém o LED aceso por 300 ms
                  
                    noTone(buzzerPin); // Para o som no buzzer
                    digitalWrite(ledPins[i], LOW); // Apaga o LED

                    while (digitalRead(buttonPins[i]) == HIGH); // Aguarda soltar o botão
                }
            }
        }

        // Verificar sequência do jogador
        if (checkPlayerInput()) { // Se a sequência do jogador estiver correta
            sequenceLength++; // Aumenta o comprimento da sequência
          	
            if (sequenceLength > 9) { // Se o comprimento da sequência exceder 9
                randomSeed(analogRead(0)); // Reinicia a semente para novos números aleatórios
                playStartMusic(); // Toca a música de início
                resetGame(); // Reinicia o jogo
            }
            
            updateDisplay(sequenceLength); // Atualiza o display com o novo nível
            delay(500); // Aguarda meio segundo antes de gerar uma nova sequência
          	generateSequence(); // Gera uma nova sequência aleatória
        } else {
            // Sequência errada - Reinicia o jogo
            resetGame(); // Reinicia o jogo
          	
          	byte segments = 0b0111111; // Mostra um 0
            for (int i = 0; i < 7; i++) {
                digitalWrite(segmentPins[i], (segments >> i) & 0x01);
            }
          	
          	playGameOverMusic(); // Toca a música de game over
          	delay(500);
        }
    }
}
