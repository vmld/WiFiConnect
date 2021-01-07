#include <time.h>
#include "WiFi.h"
#include <NTPClient.h>    // for accessing NTP real time API data


void printText(int , int , String , uint8_t , uint8_t , uint8_t );
struct tm data;//Cria a estrutura que contem as informacoes da data.
char ftDataTime[64];
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

//..........................
//https://portal.vidadesilicio.com.br/esp32-utilizando-o-rtc-interno-para-datas/
bool Flag_Date = false;
String monthNames[12] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
String daysOfWeek[9] = {"Domingo", "2a.Feira", "3a.Feira", "4a.Feira", "5a.Feira", "6a.Feira", "Sabado"};
//http://www.cplusplus.com/reference/ctime/strftime/
//========================================================
//............................. 
void iniLocalTime()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
//............................. 
void readTimeDate() {
  /*  This function is used to local clock
   */
  time_t tt = time(NULL);//Obtem o tempo atual em segundos. Utilize isso sempre que precisar obter o tempo atual
  data = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura

  //............................. Display TFT - Hora
  dsply.fillRect(0, 72, 240, 40, TFT_BLACK); 
  strftime(ftDataTime, 64, "%H:%M:%S", &data);//Cria uma String formatada da estrutura "Hora"
  printText(0, 72, ftDataTime, 4, 2, 239);

  //Display Dia da Semana e data, Só na inicialização com Flag_Data==false OU ás 00:00:00 atá 00:00:09 
  if ( (Flag_Date==false) or (data.tm_min==0 && data.tm_hour ==0 && data.tm_sec < 10) ){

    dsply.fillRect(0, 0, 240, 65, TFT_BLACK); 
    dsply.setTextColor(TFT_YELLOW);  //  set the text color
    
    //............................. Display TFT - Dia Semana
    char xDSem[10];
    sprintf(xDSem,"%s", daysOfWeek[data.tm_wday]);
    printText(0, 20, xDSem, 2, 2, 239); 
    
    //............................. Display TFT - Data
    char xDate[20];
    sprintf(xDate,"%2d %s %2d", data.tm_mday, monthNames[data.tm_mon],data.tm_year+1900);
    printText(0, 40, xDate, 2, 2, 239); 

    Serial.print( xDSem );
    Serial.print( ", " );
    Serial.println( xDate );

    Flag_Date = true;
  }
}
