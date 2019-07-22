#pragma GCC optimize("O3")
//#include <ESP8266WiFi.h>  //Need for ESP8266
#include <WiFi.h>           //Need for ESP32 
#include<HardwareSerial.h>
#include "NTRIPServer.h"

const char* ssid     = "your_ssid";
const char* password = "your_password";

//Sample (use rtk2go.com(ntrip softwere test server))
char* host = "rtk2go.com";    //ntrip caster host address 
int httpPort = 2101;          //port 2101 is default port of NTRIP caster
char* mntpnt = "mountpoint";  //must change this string
char* psw   = "BETATEST";     //enter password of ntrip caster for subscribing
char* srcSTR   = "";          //source table infomation string reference software.rtcm-ntrip.org/wiki : NTRIP sourcetable contents (https://software.rtcm-ntrip.org/wiki/Sourcetable)
NTRIPServer ntrip_s;

void setup() {
  // put your setup code here, to run once:
// put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
  //Serial2.begin(115200, SERIAL_8N1, 17, 16);
  delay(10);
  
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Subscribing MountPoint");
  if (!ntrip_s.subStation(host, httpPort, mntpnt,psw,srcSTR)) {
    delay(15000);
    ESP.restart();
  }
  Serial.println("Subscribing MountPoint is OK");
}

char ch[512];
int readcount;
void loop() {
  // connect your ESP uart and GNSSreciver uart
  
  while (Serial2.available()) {
    if (ntrip_s.connected())
      ntrip_s.write(Serial2.read());
    else {
      ntrip_s.stop();
  
      // reconnect
      Serial.println("Subscribing MountPoint");
      if (!ntrip_s.subStation(host, httpPort, mntpnt,psw,srcSTR)) {
        delay(100);
      }
      else {
        Serial.println("Subscribing MountPoint is OK");
        delay(10);
      }
    }
  }

}
