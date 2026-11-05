#define TRIG_PIN 27
#define ECHO_PIN 14
#define RELAY_PIN 26

// Change to HIGH if your relay is active-HIGH
#define RELAY_ON LOW
#define RELAY_OFF HIGH

long duration;
float distance;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(RELAY_PIN, RELAY_OFF);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    distance = -1;
  } else {
    distance = duration * 0.0343 / 2;
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Turn pump ON when a hand is detected
  if (distance > 0 && distance <= 10) {
    digitalWrite(RELAY_PIN, RELAY_ON);
    Serial.println("Hand detected - Water ON");
  } else {
    digitalWrite(RELAY_PIN, RELAY_OFF);
    Serial.println("No hand detected - Water OFF");
  }

  delay(200);
}
