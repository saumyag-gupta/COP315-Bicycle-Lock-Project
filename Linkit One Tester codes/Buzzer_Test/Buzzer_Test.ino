#define buzzer 11

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(buzzer, HIGH);
  delay(5000);
  digitalWrite(buzzer,LOW);
  delay(5000);
}
