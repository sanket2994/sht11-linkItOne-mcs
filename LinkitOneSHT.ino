extern "C"{
  #include <sht11.h>    //since it is library written in C we include it in this block
}                     

#include "LWiFi.h"
#include "LWiFiClient.h"
//#include <LWiFiServer.h>
//#include <LWiFiUdp.h>
#include "HttpClient.h"

#define WIFI_AP "your_wifi_password"        //enter your ssid
#define WIFI_PWD "your_wifi_password"       //enter your wifi password
#define WIFI_AUTH LWIFI_WPA                 
#define DEVICEID DLiTLUMb                   //Device ID which created on Mediatek cloud Sandbox
#define DEVICEKEY o68PfXOeXYb0ff46          //Device key generated from mediatek cloud sandbox
#define SITE_URL "api.mediatek.com"

LWiFiClient content;
//HttpClient http(content);

  float getTemp;
  float getHumidity;


void setup() {
  Serial.begin(38400);
  Serial.println("Connecting to WiFi");
  int ret;
  while((ret=LWiFi.connectWPA(WIFI_AP,WIFI_PWD))<=0)
  {
    Serial.print(".");
  }
  Serial.println("connected to WIFI");
  
  Serial.print("Starting SHT11" );
  
}

void loop() {

  getTemp = readTemp();
  getHumidity=readHumidity();

  Serial.print("the temp is: ");
  Serial.println(getTemp,DEC);
  upload_to_cloud_temp(getTemp);
  Serial.print("The Humidity is: ");
  Serial.println(getHumidity,DEC);
  upload_to_cloud_hum(getHumidity);
  delay(5000);
}

//Function to upload temperature data on the cloud
void upload_to_cloud_temp(float temp)     
{
  while(!content.connect(SITE_URL,80));
  {
    Serial.println("connecting...");
    delay(500);
  }

  content.println("POST /mcs/v2/devices/DLiTLUMb/datapoints.csv HTTP/1.1");

  String data = "2,,"+ String(temp);

  int dataLength = data.length();

  content.println("Host: api.mediatek.com");
  content.println("deviceKey: o68PfXOeXYb0ff46");
  content.print("Content-Length: ");
  content.println(dataLength);
  content.println("Content-Type: text/csv");
  content.println("Connection: close");
  content.println();
  content.println(data);

}

//Function to upload humidity data on the cloud

void upload_to_cloud_hum(float hum)
{
  while(!content.connect(SITE_URL,80))
  {
    Serial.println("connecting..");
    delay(500);
  }

  content.println("POST /mcs/v2/devices/DLiTLUMb/datapoints.csv HTTP/1.1");

  String data = "3,,"+String(hum);

  int dataLength = data.length();

  content.println("Host: api.mediatek.com");
  content.println("deviceKey: o68PfXOeXYb0ff46");
  content.print("Content-Length: ");
  content.println(dataLength);
  content.println("Content-Type: text/csv");
  content.println("Connection: close");
  content.println();
  content.println(data);
}

