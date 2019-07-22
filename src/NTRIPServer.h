#ifndef NTRIPSERVER_H_
#define NTRIPSERVER_H_

#include <Arduino.h>

#include <WiFiClient.h>
#include<base64.h>

#define NTRIP_MAXSTR 256

class NTRIPServer : public WiFiClient{
  public :
  bool subStation(char* host,int &port,char* mntpnt,char* psw, char* info);      //request RAW data from Caster 
  //String makeOptionalSTR(char* dataFormat, char* details, char* carrier, char* navSys, char* network, country,char* lat,char*lon,char* nmea,char sol,char gen,comEnc,char* auth,fee,bitrate);
};

#endif //NTRIPSERVER_H_
