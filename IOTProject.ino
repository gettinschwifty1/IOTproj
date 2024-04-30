#include <Bridge.h>
#include <HttpClient.h>
//#include <PushingBox-for-Arduino-WiFi-shield.ino>






// from pushingbox setup 
//-------------------------------------------------------
  /////////////////
 // MODIFY HERE //
/////////////////


char devid = "v519BB414074997D";        //Scenario : "The mailbox is open"

//Numeric Pin where you connect your switch


// Debug mode

  //////////////
 //   End    //
//////////////

char serverName[] = "api.pushingbox.com";


//--------------------------------------------------------// */
bool DEBUG = true;
//  code for reading sensor originates from https://sensorkit.arduino.cc/sensorkit/module/lessons/lesson/05-the-light-sensor , but is modified
int lightLevel = 7; 
int light_sensor = A3; 
bool timer = false;

void setup() 
{
  Serial.begin(9600); //begin Serial Communication
  
  
  // set up for pushingbox notifactions
  //---------------------------------------------------------------------------------------------------------------------------------
  //initialize serial:
  //Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  while (!Serial); // wait for a serial connection
 
 
}
void loop() 
{
  // put your main code here, to run repeatedly:
  int raw_light = analogRead(light_sensor); // read the raw value from light_sensor pin (A3)
  int light = map(raw_light, 0, 1023, 0, 100); // map the value from 0, 1023 to 0, 100
  int ledPin = 5;

  HttpClient client;

  Serial.print("Light level: "); 
  Serial.println(light); // print the light value in Serial Monitor
 
  delay(100); // add a delay to only read and print every 100 miliseconds or tenth of a second
  
  //Serial.flush();
  //String UploadMessage;
  //Serial.print("\n Uploaded temp value: ");
 // Serial.print(light);
  //delay(5000);
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
  // printing if the timer is activated - 0 is no, 1 is yes
  Serial.print("Timer: "); 
  Serial.print(timer );

  // deivydosser is dossing again 06.03.2024, 19.03.2024, 16.04.2024, 23.04.2024, 

  int count = 0; // counter that is set to go up by one every second
  while(timer == true && light < lightLevel)// while light is less then specified level
  {
    delay(1000);
    count++;
    if (count >= 3) 
    {
      digitalWrite(5, HIGH);
      //timer = false;
      //Serial.print("");
     // sendToPushingBox(DEVID1);
      String APIRequest;
      APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=10000&TimeStamp=50&TempC="+light;
      client.get (APIRequest);
      while (client.available()) {
    char c = client.read();

  }
      //loopWifiSetup();
        Serial.flush();
      String UploadMessage;
      
    }
    
    
      
    
    raw_light = analogRead(light_sensor); // read the raw value from light_sensor pin (A3)
    light = map(raw_light, 0, 1023, 0, 100);
    
    Serial.print("\nCounter: "); // printing the amount of time the light sensor has been covered in seconds
    Serial.print(count);
    
  }
}

/*/Function for sending the request to PushingBox
void sendToPushingBox(char devid[]){
  client.stop();
  if(DEBUG){Serial.println("connecting...");}
  if(client.connect(serverName, pinDevid1)) { 
    if(DEBUG){Serial.println("connected");}
    if(DEBUG){Serial.println("sendind request");}
    client.print("GET /pushingbox?devid=");
    client.print(devid);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(serverName);
    client.println("User-Agent: Arduino");
    client.println();
  } 
  else { 
    if(DEBUG){Serial.println("connection failed");} 
  } 
  return;
}*/
