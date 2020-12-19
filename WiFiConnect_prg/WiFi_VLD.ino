int intensidadeSinal = -9999;
//============================================================================
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
