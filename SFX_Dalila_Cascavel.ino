#define PIRSENSOR 2
#define CHOCALHO 3
#define SHAKETIME 250

int state = LOW;
int val = 0;

void setup() {
  Serial.begin (115200);
  delay (1000);
  Serial.println ("+++ Cascavel Cabaça +++");
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
      Serial.println("Movimento Detectado");
      state = HIGH;
      cascavel();
    }
  }
  else {
    digitalWrite(LED_BUILTIN, LOW); // turn LED OFF
    delay(200);             // delay 200 milliseconds

    if (state == HIGH) {
      Serial.println("Sem Movimento");
      state = LOW;
    }
  }
}


void cascavel() {
  int interval = random(3, 6);
  
  for (int i = 0; i < interval; i++) {
    Serial.println (">> Chacoalha <<");
    digitalWrite (CHOCALHO, HIGH);
    delay (SHAKETIME);
    digitalWrite (CHOCALHO, LOW);
    delay (SHAKETIME);
  }
}
