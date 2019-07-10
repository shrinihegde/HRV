#include <Blynk.h>

/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 #include <SoftwareSerial.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
 SoftwareSerial zIGBEE(14, 12);
 WidgetTerminal terminal(V1);
char auth[] = "2400a95682ac475aa84f79f41608ef4f";
// Your WiFi credentials.
// Set password to 000"" for open networks.
char ssid[] = "abstergo";
char pass[] = "Phoenix123";
int Realy = D0;
//BLYNK_WRITE(V1)
void setup()
{
  // Debug console
  Serial.begin(9600);
zIGBEE.begin(9600);
pinMode(Realy,OUTPUT);
digitalWrite(Realy,LOW);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  while(zIGBEE.available()>0)
{
char ch = zIGBEE.read(); 
 Serial.println(ch);
 if(ch == 'H')
 {
  terminal.println(F("low BP AND shock genrator on"));
  terminal.flush();
  digitalWrite(Realy,HIGH);
  delay(1000);
    digitalWrite(Realy,LOW);
  delay(1000);

 }
 if(ch == 'G')
 {
  terminal.println(F("critical condition"));
terminal.flush();
 }
 // terminal.flush();
}
}
