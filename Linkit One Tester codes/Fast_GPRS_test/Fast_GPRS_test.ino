
void setup()
{
  Serial.begin(9600);
  uint32_t curr = millis();
      while((millis()-curr)<30000)  
      {
        
      Serial.println("Inside On Lock");
      Serial.println(millis());
      }
}

void loop()
{
      
}
