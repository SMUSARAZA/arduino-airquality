#define trigPin 10
#define echoPin 13

int measurePin = 5;
int ledPower = 12;
 
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
 
void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop(){
  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  
  if (distance >= 19){
    Serial.print("Distance = ");
    Serial.println("LAUNDRY BUCKET IS EMPTY. :)");
  }
  if (distance <=5){
    Serial.print("Distance = ");
    Serial.println("LAUNDRY BUCKET IS FULL.YOU NEED TO DO LAUNDRY. -_-");
  }
  if (distance < 19 && distance > 5){
    Serial.print("Distance = ");
    Serial.println("LAUNDRY BUCKET IS HALF FULL. :)");
  }

  delay(900);
  
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);
 
  voMeasured = analogRead(measurePin); // read the dust value
 
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
 
  
  calcVoltage = voMeasured * (5.0 / 1024);
 
  
  dustDensity = (0.17 * calcVoltage - 0.1)*1000;
 
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
 
  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);
 
  Serial.print(" - Dust Density [ug/m3]: ");
  Serial.println(dustDensity);

   if(dustDensity > 239){
    Serial.println("Dust level is rising.");
  }
  
 
  delay(1000);
}

