#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>







// from pushingbox setup 
//-------------------------------------------------------
  /////////////////
 // MODIFY HERE //
/////////////////
char wifissid[] = "WIFI_SSID";   //  your network SSID (name)
char wifipass[] = "doghunter";    // your WPA network password

char DEVID1[] = "v519BB414074997D";        //Scenario : "The mailbox is open"

//Numeric Pin where you connect your switch
uint8_t pinDevid1 = 3; // Example : the mailbox switch is connect to the Pin 3

// Debug mode
boolean DEBUG = true;
  //////////////
 //   End    //
//////////////

char serverName[] = "api.pushingbox.com";
boolean pinDevid1State = false;                // Save the last state of the Pin for DEVID1
boolean lastConnected = false;  
int status = WL_IDLE_STATUS;     // the Wifi radio's status

WiFiClient client;
//--------------------------------------------------------// 

//  code for reading sensor comes from https://sensorkit.arduino.cc/sensorkit/module/lessons/lesson/05-the-light-sensor
 
int light_sensor = A3; 
bool timer = false;

void setup() 
{
  Serial.begin(9600); //begin Serial Communication
  
  // set up for pushingbox notifactions
  //---------------------------------------------------------------------------------------------------------------------------------
  // initialize serial:
  Serial.begin(9600);
  pinMode(pinDevid1, INPUT);
 
  // attempt to connect using WPA2 encryption:
  Serial.println("Attempting to connect to WPA network...");
  status = WiFi.begin(wifissid, wifipass);
 
  // if you're not connected, stop here:
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // if you are connected, print out info about the connection:
  else {
    Serial.println("Connected to network");
  }
  //----------------------------------------------------------------------------------------------------------------------------------
}
 
void loop() 
{
  int raw_light = analogRead(light_sensor); // read the raw value from light_sensor pin (A3)
  int light = map(raw_light, 0, 1023, 0, 100); // map the value from 0, 1023 to 0, 100
  int ledPin = 5;

  Serial.print("Light level: "); 
  Serial.println(light); // print the light value in Serial Monitor
 
  delay(100); // add a delay to only read and print every 100 miliseconds or tenth of a second
  
  
  if(light < 10 )
  {
   //digitalWrite(5, LOW);
   timer = true;
  } 
  
  else 
  {
    // turn LED off:
    digitalWrite(5, LOW);
    timer == false;
  }    
  Serial.print("Timer: "); 
  Serial.print(timer);
        // deivydosser is dossing again 06.03.2024, 19.03.2024, 16.04.2024, 23.04.2024,  
  int cnt = 0; // counter that is set to go up by one every second
  while(timer == true && light < 10)// while light is less then 10 
  {
    delay(1000);
    cnt++;
    if (cnt >= 10) 
    {
      digitalWrite(5, HIGH);
      timer = false;
      sendToPushingBox(DEVID1);
    }
    raw_light = analogRead(light_sensor); // read the raw value from light_sensor pin (A3)
    light = map(raw_light, 0, 1023, 0, 100);
    
    Serial.print("Counter: "); 
    Serial.print(cnt);
  }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void loopWifiSetup() //taken from pushingbox code for setting up
{
   ////
   // Listening for the pinDevid1 state
   ////
  if (digitalRead(pinDevid1) == HIGH && pinDevid1State == false) // switch on pinDevid1 is ON
  {
    if(DEBUG){Serial.println("pinDevid1 is HIGH");}
    pinDevid1State = true;
    //Sending request to PushingBox when the pin is HIGHT
    sendToPushingBox(DEVID1);
  }
   if (digitalRead(pinDevid1) == LOW && pinDevid1State == true) // switch on pinDevid1 is OFF
  {
    if(DEBUG){Serial.println("pinDevid1 is LOW");}
    pinDevid1State = false;
    //Sending request to PushingBox when the pin is LOW
    //sendToPushingBox(DEVID1);    //Here you can run an other scenario by creating a DEVID2 variable
  }
 
  //DEBUG part
  // this write the respons from PushingBox Server.
  // You should see a "200 OK"
  if (client.available()) {
    char c = client.read();
    if(DEBUG){Serial.print(c);}
  }
 
  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    if(DEBUG){Serial.println();}
    if(DEBUG){Serial.println("disconnecting.");}
    client.stop();
  }
  lastConnected = client.connected();
}
//Function for sending the request to PushingBox
void sendToPushingBox(char devid[]){
  client.stop(); if(DEBUG){Serial.println("connecting...");}
  if(client.connect(serverName, 80)) { 
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
}


