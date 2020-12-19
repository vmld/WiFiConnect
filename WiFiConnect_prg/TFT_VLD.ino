#include "SPI.h"          // for communication with the TFT LCD screen
#include "TFT_eSPI.h"     // for TFT LCD screen register
#include <TimeLib.h>      // for converting timestamps
#include <NTPClient.h>    // for accessing NTP real time API data


//..........................
String daysOfWeek[7] = {"Domingo", "2a.Feira", "3a.Feira", "4a.Feira", "5a.Feira", "6a.Feira", "Sabado"};
String monthNames[12] = {"Janeiro ", "Fevereiro ", "Março ", "Abril ", "Maio ", "Junho ", "Julho ", "Agosto ", "Setembro ", "Outubro ", "Novembro ", "Dezembro "};
bool Flag_Date = false;

void printText(int x, int y, String text, uint8_t textSize = 1, uint8_t textAllign = 1, uint8_t lineLength = 239) {
  /*  This function is used for displaying text on the screen
   *  Arguments:
   *    - X           position of the cursor
   *    - Y           position of the cursor
   *    - text        the actual text that will be displayed
   *    - textSize    text size can be one of these values 1, 2, 3, 4, 5
   *    - textAllign  text allign can be 1 - left align, 2 - center and 3 - right align
   *    - lineLenght  this should be used for line lenght of text, but does not works as shoud - TODO
   */
  
  uint8_t newTextSize = textSize;
  uint8_t real_x = 0;
  uint32_t stringLength = text.length();
  uint8_t characters = stringLength * 5 * newTextSize + stringLength * newTextSize;

  while ((characters + 10) > lineLength) {
    // make text smaller if it exceeds the screen
    // all text in this app is not (and it should not be) longer than line length
    newTextSize = newTextSize - 1;
    characters = stringLength * 5 * newTextSize + stringLength * newTextSize;
  }
  dsply.setTextSize(newTextSize);

  if ((stringLength > 16) && (newTextSize > 2)) {
    // there is an error with text that is 17 characters long with size of 2
    // so this IF statement is explicitly for that error, to make text size smaller
    newTextSize = newTextSize - 1;
    characters = stringLength * 5 * newTextSize + stringLength * newTextSize;
  }
  dsply.setTextSize(newTextSize);

  if (characters + 10 < lineLength) {
    if (textAllign == 1) { // left
      dsply.setCursor(x, y);
      dsply.println(text);
    }
    else if (textAllign == 2) { // centered
      if (textSize == 1) { // letter length = 5
        real_x = x + int((lineLength - characters) / 2);
        dsply.setCursor(real_x, y);
        dsply.println(text);
      }
      else if (textSize == 2) { // letter length = 10
        real_x = x + int((lineLength - characters) / 2);
        dsply.setCursor(real_x, y);
        dsply.println(text);
      }
      else if (textSize == 3) { // letter length = 15
        real_x = x + int((lineLength - characters) / 2);
        dsply.setCursor(real_x, y);
        dsply.println(text);
      }
      else if (textSize == 4) { // letter length = 20
        real_x = x + int((lineLength - characters) / 2);
        dsply.setCursor(real_x, y);
        dsply.println(text);
      }
      else if (textSize == 5) { // letter length = 25
        real_x = x + int((lineLength - characters) / 2);
        dsply.setCursor(real_x, y);
        dsply.println(text);
      }
      else {
        dsply.setTextSize(1);
        dsply.setCursor(x, y);
        dsply.println("ERROR! Text size is from 1 to 5!");
      }
    }
    else if (textAllign == 3) { // right
      if (textSize == 1) { // letter length = 5
        real_x = x + lineLength - characters;
        dsply.setCursor(real_x, y);
        dsply.println(text);
      }
      else if (textSize == 2) { // letter length = 10
        real_x = x + lineLength - characters;
        dsply.setCursor(real_x, y);
        dsply.println(text);
      }
      else if (textSize == 3) { // letter length = 15
        real_x = x + lineLength - characters;
        dsply.setCursor(real_x, y);
        dsply.println(text);
      }
      else if (textSize == 4) { // letter length = 20
        real_x = x + lineLength - characters;
        dsply.setCursor(real_x, y);
        dsply.println(text);
      }
      else if (textSize == 5) { // letter lenght = 25
        real_x = x + lineLength - characters;
        dsply.setCursor(real_x, y);
        dsply.println(text);
      }
      else {
        dsply.setTextSize(1);
        dsply.setCursor(x, y);
        dsply.println("ERROR! Text size is from 1 to 5!");
      }
    }
    else {
      dsply.setTextSize(1);
      dsply.setCursor(x, y);
      dsply.println("ERROR! TextAlign is 0, 1 and 2!");
    }
  }
  else {
    dsply.setCursor(x, y);
    dsply.println(text);
  }
}

//=============================================================================== checkZero
String checkZero(uint32_t number) {
  /*  This function is used to check if the unsigned integer number is a single digit, and to add zero before single digit number
   *  Argument:
   *  - number      unsigned ingeger number
   *  Returns:  String made from unsigned integer number
   */
   
  char buf[10];
  if (number < 10) {
    return "0" + String(number);
  }
  else {
    return String(number);
  }
}
//=====================================================================
void printTime(uint16_t x, uint16_t y, uint32_t dateTime, uint8_t textSize, uint8_t textAlign, uint8_t lineLenght = 239) {
  /*  This function is used to print Time from epoch timestamp
   *  Arguments:
   *  - X           positon of the cursor
   *  - Y           positon of the cursor
   *  - dateTime    epoch timestamp (unix timestamp)
   *  - textSize    text size can be one of these values 1, 2, 3, 4, 5
   *  - textAllign  text allign can be 1 - left align, 2 - center and 3 - right align
   *  - lineLenght  this should be used for line lenght of text, but does not works as shoud - TODO  
   */
   
  time_t tt = dateTime; // dateTime is epoch timestamp
  String mytime = String(checkZero(hour(tt))) + ":" + String(checkZero(minute(tt))) + ":" + String(checkZero(second(tt)));
  printText(x, y, mytime, textSize, textAlign, lineLenght);
}
//=====================================================================
void printDayAndDate(uint16_t x, uint16_t y, uint32_t dateTime, uint8_t textSize, uint8_t textAlign, uint8_t lineLenght = 239) {
  /*  This function is used to print date from epoch timestamp
   *  Arguments:
   *  - X           positon of the cursor
   *  - Y           positon of the cursor
   *  - dateTime    epoch timestamp (unix timestamp)
   *  - textSize    text size can be one of these values 1, 2, 3, 4, 5
   *  - textAllign  text allign can be 1 - left align, 2 - center and 3 - right align
   *  - lineLenght  this should be used for line lenght of text, but does not works as shoud - TODO  
   */
   
  
  time_t tt = dateTime; // dateTime is epoch timestamp
  if ( (Flag_Date==false) or (hour(tt)==0 and minute(tt)==0) ){
//String daysOfWeek[7] = {"Domingo", "2a.Feira", "3a.Feira", "4a.Feira", "5a.Feira", "6a.Feira", "Sabado"};
//String monthNames[12] = {"Janeiro ", "Fevereiro ", "Março ", "Abril ", "Maio ", "Junho ", "Julho ", "Agosto ", "Setembro ", "Outubro ", "Novembro ", "Dezembro "};
    String dayName = daysOfWeek[weekday(tt) - 1];
    String monthName = monthNames[month(tt) - 1];

    dsply.fillRect(0, 0, 240, 65, TFT_BLACK); 
    printText(x, y + 0, dayName, textSize , textAlign);
    String date = String(checkZero(day(tt))) + " " + monthName + String(year(tt));
    printText(x, y + 20, date, textSize, textAlign);
    Flag_Date = true;
  }
}
//================================================
void initializeLCD() {
  /*  This function is used to turn ON the LCD and to initialize dsply object */
   
  // turn ON the dispaly
  pinMode(15, OUTPUT);    // Backlight pin of the display is connecte to this pin of ESP32
  digitalWrite(15, LOW);  // we have to drive this pin LOW in order to turn ON the display
  delay(1);               // delay for 1ms

  dsply.init();

  dsply.fillScreen(TFT_BLACK);    //  clear the screen, fill the screen with black color
  dsply.setTextColor(TFT_YELLOW);  //  set the text color
  
  //dsply.setFreeFont(FSS9);      //  you can use some other font, 
                                  //  but you have to change positions of every element, 
                                  //  because for different font there are different text sizes
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
