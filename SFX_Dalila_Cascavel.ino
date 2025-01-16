

#define PIRSENSOR 2
#define CHOCALHO 3

int unused[14] = {4, 5, 6, 7, 8, 9, 10, 11, 12, A1, A2, A3, A4, A5};

void setup() {
  Serial.begin (115200);
  delay (1000);
  Serial.println ("+++ Cascavel Cabaça +++");

  // Gerador de Aleatórios
  randomSeed(analogRead(0));
  
  pinMode (CHOCALHO, OUTPUT);
  pinMode (LED_BUILTIN, OUTPUT);

  // Led aceso in LOW
  digitalWrite (LED_BUILTIN, HIGH);

  // Chocalho inicia desligado
  digitalWrite (CHOCALHO, LOW);
  
  pinMode (PIRSENSOR, INPUT);
  
  // Evitando que os pinos fiquem flutuantes.
  for (int i = 0; i < 14; i++) {
    pinMode (unused[i], INPUT_PULLUP);
  }
}

void loop() {
  int = pirState = digitalRead (PIRSENSOR);

  if (pirState == HIGH) {
    digitalWrite (LED_BUILTIN, LOW);
    int numPulses = random (4,8);
    for (int i = 0; i< numPulses; i++) {
      digitalWrite (CHOCALHO, HIGH);
      
      // Esses delays foram importados do código original do Luciano
      delay(90);
      digitalWrite (CHOCALHO, LOW);
      delay (110);  
    }
   
    int waitTime = random (5,8);
    delay (waitTime * 1000);
  }
  // Apaga o Led
  digitalWrite (LED_BUILTIN, HIGH);
}

