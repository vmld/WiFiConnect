#include <Arduino.h>
#include "WiFi.h"
#include "SPI.h"          // for communication with the TFT LCD screen
#include "TFT_eSPI.h"     // for TFT LCD screen register
#include <NTPClient.h>    // for accessing NTP real time API data


void printText(int , int , String , uint8_t , uint8_t , uint8_t );
char* aSSID [] = {"VMLOD", "VitorinoLobato iPhone", "VMLDQUARTO", "ANTICOR-2.4"};
char* aSSPW [] = {"9917509533", "9917509533", "9917509533", "9917509533"};
//.................................................................
unsigned long secd_interval  =  1000; // one second in milliseconds
unsigned long secd_counter   = 0;     // for counting the seconds
unsigned long last_update_second = 0;
unsigned long time_T;                 // current time from millis()
int nnWiFi = -1;

TFT_eSPI dsply = TFT_eSPI(); // TFT LCD screen object
WiFiClient client;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

//============================================================================
//============================================================================
//============================================================================
void setup() {

    initializeLCD();

      
    Serial.begin(115200); // Instrução para inicializar o Serial, utilizaremos apenas para log no monitor.
    WiFi.mode(WIFI_STA);  // configurando o modo de operação do WiFi como estação
    WiFi.disconnect();    // desconecta do access point caso ele já esteja conectado
    WiFi_ScanConn();

//    if (WiFi_scanSS() == true){
//        WiFi.begin(aSSID[nnWiFi], aSSPW[nnWiFi]);
//        while (WiFi.status() != WL_CONNECTED) { delay(1000); Serial.println(F("Connecting to WiFi..")); }
//        Serial.print("ID >"+String(aSSID[nnWiFi])+"<  ");
//        Serial.println(WiFi.localIP());
//    }
}
//============================================================================
void loop() {
  time_T = millis();
  //..................................... Conta Segundos
  if (time_T - last_update_second > secd_interval) {
    // update time every second
    dsply.setTextColor(TFT_YELLOW);  //  set the text color
    updateTime();
    last_update_second = time_T;
    secd_counter++;
  }
  delay(1000);
}
