#define motor 4

void setup() {
  // put your setup code here, to run once:
  pinMode(motor,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motor, HIGH);
  delay(3000);
  digitalWrite(motor,LOW);
  delay(3000);
}
