#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#include <WiFi.h>
#include <HTTPClient.h>

#include "time.h"

/////////////////// VARIABLES TO FILL /////////////////

String macAddress = ""; // bluetooth MAC address of key device

const char* ssid = ""; // ESP32 Wifi SSID (your Wifi network name)
const char* password = ""; // ESP32 WIFI Password (your Wifi password)

String eventNAME = "Light_Toggle_ESP32"; // Your IFTTT webhooks url
String webhooksKEY = ""; // Your IFTTT webhooks url

// IFTTT website root certificate. 
const char* ca_cert = \
"-----BEGIN CERTIFICATE-----\n" \ 
"MIIFaTCCBFGgAwIBAgIQAm5h7bYD2v8sd86dSn2WETANBgkqhkiG9w0BAQsFADBG\n" \ 
"MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRUwEwYDVQQLEwxTZXJ2ZXIg\n" \ 
"Q0EgMUIxDzANBgNVBAMTBkFtYXpvbjAeFw0yMDA0MjkwMDAwMDBaFw0yMTA1Mjkx\n" \ 
"MjAwMDBaMBQxEjAQBgNVBAMTCWlmdHR0LmNvbTCCASIwDQYJKoZIhvcNAQEBBQAD\n" \ 
"ggEPADCCAQoCggEBAMQP1a+aBKLeIvXq5AM+DbPKQMuurrTjFhkl50WPeJftwSR0\n" \ 
"BA5zOaTMx9tUENmDvC/XVyMydf72fa/8ChD7Q65LlWitaAZQ1xAJjszlqlc0/fmN\n" \ 
"zbUkSf2TvH68nCIzWNmb6YfrySTVp82wUeYX0FB+ra3evVJg+sGs4pEv25N0kkiq\n" \ 
"x1f5mOrlQ9mUGNok2Ttn4CVpVah4S53D0Ja/2ihgOs2VVeKa9OL57Xj28I0kWHzO\n" \ 
"GCVOJuAvij51SQeVCfX4wRWZrumoWFMuIN0ZJlOkiLHAvkBIeFp64bLa4G277WVQ\n" \ 
"HKTM4bNO22nQbyEU5/pbSZpHM3NYGoZJ343/Zm8CAwEAAaOCAoMwggJ/MB8GA1Ud\n" \ 
"IwQYMBaAFFmkZgZSoHuVkjyjlAcnlnRb+T3QMB0GA1UdDgQWBBSWDbLpfk6eIzTL\n" \ 
"9MClcG+nIgTROzAhBgNVHREEGjAYgglpZnR0dC5jb22CCyouaWZ0dHQuY29tMA4G\n" \ 
"A1UdDwEB/wQEAwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwOwYD\n" \ 
"VR0fBDQwMjAwoC6gLIYqaHR0cDovL2NybC5zY2ExYi5hbWF6b250cnVzdC5jb20v\n" \ 
"c2NhMWIuY3JsMCAGA1UdIAQZMBcwCwYJYIZIAYb9bAECMAgGBmeBDAECATB1Bggr\n" \ 
"BgEFBQcBAQRpMGcwLQYIKwYBBQUHMAGGIWh0dHA6Ly9vY3NwLnNjYTFiLmFtYXpv\n" \ 
"bnRydXN0LmNvbTA2BggrBgEFBQcwAoYqaHR0cDovL2NydC5zY2ExYi5hbWF6b250\n" \ 
"cnVzdC5jb20vc2NhMWIuY3J0MAwGA1UdEwEB/wQCMAAwggEFBgorBgEEAdZ5AgQC\n" \ 
"BIH2BIHzAPEAdwD2XJQv0XcwIhRUGAgwlFaO400TGTO/3wwvIAvMTvFk4wAAAXHH\n" \ 
"MyL2AAAEAwBIMEYCIQDNt22r4JoGNGXZTa/XDm5pxdt4TToMSw7P8Jt2MHHUNgIh\n" \ 
"AJUxNtK1CwYIV2moEl85XTFi8vj3ipml/pYPjPuyFoPiAHYA7sCV7o1yZA+S48O5\n" \ 
"G8cSo2lqCXtLahoUOOZHssvtxfkAAAFxxzMjZAAABAMARzBFAiEA3PFOPVkHRqn+\n" \ 
"M9egc7MBlLDTcwmkAfG3l+8CcYgrMh0CIHYkGPnxDJrYAdzLcz3HnH5Km5/IGvo0\n" \ 
"zKwqdPjcSfotMA0GCSqGSIb3DQEBCwUAA4IBAQBZzHe34OI5hXRiLHQaW5jDb9A5\n" \ 
"yDE5yBjWYTlsELmM24a0G92K6cJ6H48RAHxiArJGVBQ8C4QvieFdwtiLTDMj6YIh\n" \ 
"OxrQHmEgN3Q7YJBAKWadQLfkLyrUHdrgFqPynKnY/aJjGEuEGCfNBNh1KXk3TMam\n" \ 
"B9SzV9jHv3B9jko/iLYnp7LUYf0M+jetvY/JcJkiMqEbdgSDqW9b+cqDgnKLkz/u\n" \ 
"Diti105In2iVkyVJrMneSsKITnVlPaBRKrZOKVlPim6Ox5v5M5/Fccm6RFWWNvWW\n" \ 
"zf5CMEKKwaPYD2RW/UUdSInu62lllMdgfSx8WcvCO48pbFBM3dlJMCykuy3n\n" \ 
"-----END CERTIFICATE-----\n";

/////////////////// PROGRAM /////////////////

int scanTime = 2; //In seconds, increase if your device needs more time to be discovered
int initScanTime = 25;
BLEScan* pBLEScan;
time_t lastTimeDetected = 0;
bool isHere = NULL;

const int httpsPort = 443;
String url = "https://maker.ifttt.com/trigger/" + eventNAME + "/with/key/" + webhooksKEY;

// time constants

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 0;

void connectToWIFI(){
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nWiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void postWebhooks(int state = 2){
  /*
    state determines if you want to force the lights in a state:
      0 is off
      1 is on
      2 is toggle
    
    currently only toggle is implemented
  */

  // WIFI setup
  connectToWIFI();

  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;   
    
    http.begin(url);  //Specify destination for HTTP request
    int httpResponseCode = http.POST("");   //Send the actual POST request
    
    if(httpResponseCode>0){
    
      String response = http.getString();                       //Get the response to the request
    
      Serial.println(httpResponseCode);   //Print return code
      Serial.println(response);           //Print request answer
    
    }else{
    
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    
    }
    
    http.end();  //Free resources
    
  }else{
      Serial.println("Error in WiFi connection");   
  }
}

time_t getUnixTime()
{
  connectToWIFI();
  time_t now;
  time(&now);
  return now;
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      if(String(macAddress.c_str()) == String(advertisedDevice.getAddress().toString().c_str())){
        lastTimeDetected = getUnixTime();
        Serial.println("test True : " + String(lastTimeDetected));
      }
    }
};

void scanBLE(){
  pBLEScan->clearResults(); // delete results fromBLEScan buffer to release memory
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
}

int scanID = 0;
void setup() {
  Serial.begin(115200);

  // WIFI setup
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  connectToWIFI();

  // time setup
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getUnixTime(); // init time with ntp

  // Bluetooth setup
  Serial.println("Scanning...");
  BLEDevice::init(""); 
  BLEDevice::setPower(ESP_PWR_LVL_N0, ESP_BLE_PWR_TYPE_SCAN); // set low classic bluetooth power and scan power for BLE
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(false); //active scan uses more power, but get results faster
  pBLEScan->setInterval(1000);
  pBLEScan->setWindow(999);  // less or equal setInterval value

  BLEScanResults initFoundDevices = pBLEScan->start(initScanTime, false);
  Serial.println("scan ended");
  isHere = difftime(getUnixTime(), lastTimeDetected) <= initScanTime + 1; // if detected during setup
  pBLEScan->clearResults();
  Serial.println("isHere setup : " + String(isHere));
}

int leftTimeInterval = 20; // choose a somewhat big interval if you don't want false negative

void loop() {
  scanBLE();
  double interval = difftime( getUnixTime(), lastTimeDetected);
  if(!isHere && interval <= leftTimeInterval){ // user arrived
    isHere = 1;
    Serial.println("User arrived");
    postWebhooks();
  }
  if(interval >= leftTimeInterval){ // user left
    if(isHere){
      Serial.println("User left");
      postWebhooks();
    }
    isHere = 0;
  }
}
