int intensidadeSinal = -9999;
//============================================================================
void WiFi_ScanConn(){
    if (WiFi_scanSS() == true){
        WiFi.begin(aSSID[nnWiFi], aSSPW[nnWiFi]);
        while (WiFi.status() != WL_CONNECTED) { delay(1000); Serial.println(F("Connecting to WiFi..")); }
        Serial.print("ID >"+String(aSSID[nnWiFi])+"<  ");
        Serial.println(WiFi.localIP());
    }
}
bool WiFi_scanSS(){
    int n = WiFi.scanNetworks();
    bool zBool = false;

    //verifica se encontrou alguma rede
    if (n == 0) {
        Serial.println("Nenhuma rede encontrada");
    } else {
        intensidadeSinal= -9999;
        Serial.println("\nRedes encontradas");
        for (int i = 0; i < n; ++i) {
          Serial.println(String(i) +"  > "+WiFi.SSID(i) +" ("+WiFi.RSSI(i)+")" ); //nome da rede
          printText(0, i*20, String(WiFi.RSSI(i)), 1 );
          printText(21, i*20, WiFi.SSID(i), 1);
          if ( WiFi_chkSS(WiFi.SSID(i),WiFi.RSSI(i))  == true){
            zBool = true;
          }
          delay(500);
        }
    }
    if(zBool){
      dsply.fillScreen(TFT_BLACK);    //  clear the screen, fill the screen with black color
      printText(0, 300, aSSID[nnWiFi], 2); 
    }
    return zBool;
}
//============================================================================ Procura na Lista ID Definidos em aSSID
bool WiFi_chkSS(String xID,int xSI ){
    bool xBool = false;
    for (byte ii = 0; ii < 3; ii = ii + 1) {
        if (xID == aSSID[ii]){
//        Serial.print(" Redes Aceites ");
//        Serial.println(xID);
          if(abs(xSI) < abs(intensidadeSinal)){
//            Serial.print(" (xSI)Melhor Sinal ");
//            Serial.println(xSI);
              nnWiFi = ii;
              intensidadeSinal = xSI;
              xBool = true;
          }                        
          break;
        }
    }
    return xBool;
}
//=====================================================================
uint32_t readTimeDate() {
  /*  This function is used to read the time form NTP API
   *  Arguments:
   *  none
   *  Returns: epoch timestamp from NTP API
   */
   
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  return timeClient.getEpochTime();
}
//=====================================================================
void updateTime() {
  /*  This function is used to dusplay time on the screen */
  uint32_t dateTime = readTimeDate();
 
  dsply.fillRect(0, 72, 240, 40, TFT_BLACK); 
  printDayAndDate(0, 20, dateTime, 2, 2); // day name and long date
  printTime(0, 72, dateTime, 4, 2);

}