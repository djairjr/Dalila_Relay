// Sistema de controle para as Cabaças
// Montei um sistema Asíncrono, com temporizações individuais para cada 
// cabaça. 
// São quatro e são definidas no escopo inicial.

// Estrutura para definir as temporizações de cada saída
struct Output {
  uint8_t pin;        // Pino no PCF8574 (0 a 7)
  unsigned long onTime;  // Tempo ligado em milissegundos
  unsigned long offTime; // Tempo desligado em milissegundos
  unsigned long previousMillis; // Último tempo registrado
  bool state;        // Estado atual (true = ligado, false = desligado)
};

// Define os tempos de ativação e desativação para cada saída
Output outputs[] = {
  {3, 1000, 500, 0, false},  // Saída 3: Liga 1s, Desliga 0.5s
  {4, 500, 1000, 0, false},   // Saída 4: Liga 0.5s, Desliga 1s
  {5, 1000, 1000, 0, false},  // Saída 5: Liga 1s, Desliga 1s
  {6, 500, 2000, 0, false}  // Saída 6: Liga 0.5s, Desliga 2s
};

const int numOutputs = sizeof(outputs) / sizeof(outputs[0]);

void setup() {
  Serial.begin(115200);    // Inicializa comunicação serial para debug
  // Inicializa os pinos indicados no STRUCT como saídas em Nível inicial baixo.
  for (int i = 0; i < numOutputs; i++) {
    pinMode (outputs[i].pin, OUTPUT);
    digitalWrite(outputs[i].pin, LOW);
  }
  // Para evitar ruídos nos pinos que não são usados.
  for (int i=7; i<20; i++) {
    pinMode (i, INPUT_PULLUP);
  }
}

void loop() {
  // Marca o inicio do loop e inicia um cronômetro
  // em currentMillis
  unsigned long currentMillis = millis();

  // Atualiza o estado de cada saída
  for (int i = 0; i < numOutputs; i++) {
    if (outputs[i].state) {
      // Se a saída está ligada, verifica se é hora de desligar
      if (currentMillis - outputs[i].previousMillis >= outputs[i].onTime) {
        outputs[i].state = false;  // Desliga a saída
        outputs[i].previousMillis = currentMillis; // Salva o tempo atual struct da saída
        digitalWrite(outputs[i].pin, LOW);
        /* Debug - Pode ser comentado 
        Serial.print("Saída ");
        Serial.print(outputs[i].pin);
        Serial.println(" DESLIGADA");
        */
      }
    } else {
      // Se a saída está desligada, verifica se é hora de ligar
      if (currentMillis - outputs[i].previousMillis >= outputs[i].offTime) {
        outputs[i].state = true;  // Liga a saída
        outputs[i].previousMillis = currentMillis;
        digitalWrite(outputs[i].pin, HIGH);
        /* Debug 
        Serial.print("Saída ");
        Serial.print(outputs[i].pin);
        Serial.println(" LIGADA");
        */
      }
    }
  }
}
