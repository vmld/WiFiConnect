#include <Arduino.h>
#include "SPI.h"          // for communication with the TFT LCD screen
#include "TFT_eSPI.h"     // for TFT LCD screen register

char* aSSID [] = {"VMLOD", "VitorinoLobato iPhone", "VMLDQUARTO", "ANTICOR-2.4"};
char* aSSPW [] = {"9917509533", "9917509533", "9917509533", "9917509533"};
//.................................................................
unsigned long secd_interval  =  1000; // one second in milliseconds
unsigned long secd_counter   = 0;     // for counting the seconds
unsigned long last_update_second = 0;
unsigned long time_T;                 // current time from millis()

//TFT_eSPI dsply = TFT_eSPI(); // TFT LCD screen object
//WiFiClient client;
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP);
//........................
TFT_eSPI dsply = TFT_eSPI(); // TFT LCD screen object

//============================================================================
//============================================================================
//============================================================================
//=====================================================
void setup() {

    initializeLCD();
      
    Serial.begin(115200); // Instrução para inicializar o Serial, utilizaremos apenas para log no monitor.
    WiFi_ScanConn();

    iniLocalTime();       //init and get the time
 
}
//============================================================================
void loop() {
  time_T = millis();
  //..................................... Conta Segundos
  if (time_T - last_update_second > secd_interval) {
    // update time every second
    readTimeDate();
    last_update_second = time_T;
    secd_counter++;
  }
  delay(1000);
}
