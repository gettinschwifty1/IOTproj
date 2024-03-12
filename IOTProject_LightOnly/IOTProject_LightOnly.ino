


//  code for reading sensor comes from https://sensorkit.arduino.cc/sensorkit/module/lessons/lesson/05-the-light-sensor
 
int light_sensor = A3; 
bool timer = false;
int lightLevel = 5;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); //begin Serial Communication
}

void loop() 
{
  // put your main code here, to run repeatedly:
  int raw_light = analogRead(light_sensor); // read the raw value from light_sensor pin (A3)
  int light = map(raw_light, 0, 1023, 0, 100); // map the value from 0, 1023 to 0, 100
  int ledPin = 5;

  Serial.print("Light level: "); 
  Serial.println(light); // print the light value in Serial Monitor
 
  delay(100); // add a delay to only read and print every 100 miliseconds or tenth of a second
  
  
  if(light < lightLevel )
  {
   //digitalWrite(5, LOW);
   timer = true;
  } 
  
  else 
  {
    // turn LED off:
    digitalWrite(5, LOW);
    timer = false;
  }    
  Serial.print("Timer: "); 
  Serial.print(timer);
          // deivydosser is dossing again 06.03.2024// 
  int cnt = 0; // counter that is set to go up by one every second
  while(timer == true && light < lightLevel)// while light is less then 10 
  {
    delay(1000);
    cnt++;
    if (cnt >= 10) 
    {
      digitalWrite(5, HIGH);
      timer = false;
      
    }
    raw_light = analogRead(light_sensor); // read the raw value from light_sensor pin (A3)
     light = map(raw_light, 0, 1023, 0, 100);
    
    Serial.print("Counter: "); 
    Serial.print(cnt);
  }
}
