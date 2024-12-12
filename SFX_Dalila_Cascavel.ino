#define PIRSENSOR 2
#define CHOCALHO 3
#define SHAKETIME 250 // Tempo de ativação/desativaçao - quanto menor, mais rápido.

int state = LOW;
int val = 0;

void setup() {
  Serial.begin (115200);
  delay (1000);
  Serial.println ("Cascavel Cabaça");
  randomSeed(analogRead(0));
  pinMode (CHOCALHO, OUTPUT);
  pinMode (LED_BUILTIN, OUTPUT);
  pinMode (PIRSENSOR, INPUT);
}

void loop() {

  val = digitalRead(PIRSENSOR);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(LED_BUILTIN, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds

    if (state == LOW) {
      Serial.println("Motion detected!");
      state = HIGH;
      cascavel();
    }
  }
  else {
    digitalWrite(LED_BUILTIN, LOW); // turn LED OFF
    delay(200);             // delay 200 milliseconds

    if (state == HIGH) {
      Serial.println("Motion stopped!");
      state = LOW;
    }
  }
}


void cascavel() {
  # Vai fazer o movimento de 3 a 6 vezes aleatoriamente
  int interval = random(3, 6);

  for (int i = 0; i == interval; i++) {
    digitalWrite (CHOCALHO, HIGH);
    delay (SHAKETIME);
    digitalWrite (CHOCALHO, LOW);
    delay (SHAKETIME);
  }
}
