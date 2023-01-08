#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <HTTPClient.h>

//#include <Arduino_JSON.h>
#include <Wire.h>
#include <ADXL345.h>
#include<RTClib.h>
#include <TFT_eSPI.h>
#include <JPEGDecoder.h>
#include<ESP32Servo.h>
#include "MAX30105.h"
#include "heartRate.h"
#include<ezButton.h>
#include "spo2_algorithm.h"

#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#include <WiFi.h>
#include <ThingESP.h>


ThingESP32 thing("user109", "ESP8266", "888555222");


String temp , temp_max , temp_min , feels_like;
String humidity , pressure , visibility , wind ;
String description;




void sdCardSetup();
void drawSdJpeg(const char *filename, int xpos, int ypos);
void heartRate_loop();
void Spo2_setup();
void spo2Value();
void temperature();
void coreOneTask(void *parameter);
void adlx_setup();
void rtc_setup();
void checkalarm(String  presentTime);
void heartMenu();
void pedometer_loop();
void alarm();
void weather_loop();
void soil();
void wifi_on();



ezButton buttonBtn(17);       // pin No 17 
ezButton selectBtn(13);       // pin No 13
ezButton backBtn(26);         // pin NO 26


int count = 0 , backStatus = 0 , selectStatus = 0;
#define buzzer  27
#define radius 14

// colors
#define color2 TFT_GREEN
#define color1 TFT_BLACK
#define sColor TFT_WHITE


bool alarm1 = true;
bool alarm2 = true;
bool alarm3 = true;


String alarm1_time = "05:00";
String alarm2_time = "06:00";
String alarm3_time = "07:00";


bool showtimings = true;
bool showmax = false;

bool wifiStatus = false;
bool bluetoothStatus = false;
bool maxStatus = false;   // max30100  status 
bool pedometerStatus = false;
bool twilioStatus = false;  //  twilio status




const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];    //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;        //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

int startTime ; 
const char* ssid = "BVQY";
const char* password = "rdark1111";

// variables to calculate steps ,  distance , calories burned
int steps =0 ;
float distance = 0;
int calories = 0;
float prevAcl = 0 , newAcl = 0;

ADXL345 adxl; 
RTC_DS1307 rtc;
TFT_eSPI tft = TFT_eSPI();
MAX30105 particleSensor;
// JPEG decoder library

#define API_KEY "AIzaSyBTe53cZo6gqNY4vRLXX5liBKJIvWn9_Dg"
#define DATABASE_URL "https://carebot-3b945-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

#define USER_EMAIL "hemanthgowda2406@gmail.com"
#define USER_PASSWORD "#Hemanth@123"


//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

//JSONVar temp;
unsigned long timerDelay = 5000;  // weather report


uint32_t irBuffer[100]; //infrared LED sensor data
uint32_t redBuffer[100];  //red LED sensor data
int32_t bufferLength; //data length
int32_t spo2; //SPO2 value
int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
int32_t heartRate; //heart rate value
int8_t validHeartRate; //indicator to show if the heart rate calculation is valid


const char *icon[] = {"/toggle_off.jpg","/toggle_on.jpg"};
const char *screen[] = {"/menu.jpg","/main_screen.jpg" , "/oxygen_level.jpg","/settings.jpg","/Soil_moisture.jpg","/Status.jpg","/temperature.jpg","/twilio.jpg","/weather.jpg","/heart_beat.jpg","/alarm.jpg", "/clock.jpg","/heartMenu.jpg"};



/********************************** setup ******************************/
void setup() {
  Serial.begin(115200);




  // twilio setup 
  


  // ezbutton btns setup 
  buttonBtn.setDebounceTime(100);                // set debounce time to 50 milliseconds
  buttonBtn.setCountMode(COUNT_FALLING);
  selectBtn.setDebounceTime(100);                // set debounce time to 50 milliseconds
  selectBtn.setCountMode(COUNT_FALLING);
  backBtn.setDebounceTime(100);                  // set debounce time to 50 milliseconds
  backBtn.setCountMode(COUNT_FALLING);
  pinMode(buzzer, OUTPUT);
  digitalWrite(15, HIGH);                       // TFT screen chip select
  digitalWrite( 5, HIGH);                       // SD card chips select, must use GPIO 5 (ESP32 SS)
 
  tft.begin();
  tft.setRotation(1);                           // portrait
  tft.fillScreen(color1); 
  sdCardSetup();                               // sd card setup 
  xTaskCreatePinnedToCore( coreOneTask , "fucntion" , 100000 , NULL , 0 ,NULL , 0);
  delay(100);
  drawSdJpeg(screen[1], 0, 0);  
  delay(10);
  rtc_setup();
  
  
}


/********************************* main loop **********************************************/


void loop(){

 btnloop();

  
    
      
    
//rtc
 
//     Alarm checker 
   
//  delay(100);
  // print time on screen 
  DateTime now = rtc.now();
  char buf1[] = "hh:mm";
  
  
  checkalarm(now.toString(buf1));


  
  
  
  
//  Serial.println(now.second());

  
  char buf[] = "hh:mm:ss"; 
  tft.setCursor(50,50);
  tft.setTextSize(1);
  tft.setTextColor(sColor , color1); 
  tft.println(now.toString(buf)); 



  //tft print date
  char buf2[] = "DD:MM:YYYY";
  tft.setCursor(50,70);  // need to change co-ordinates
  tft.setTextColor(sColor , color1);
  tft.setTextSize(1);
  tft.println(now.toString(buf2));
  
  

  // tft print temperature
  
  tft.setCursor(100,100);
  tft.setTextColor(sColor , color1);
  tft.setTextSize(1);
  tft.println("0");



  // wifi status based drawing icon 



  // bluetooth status based drawing icon 




  // torch status based drawing icon 




  // battery percentage based drawing icon 




  // print number steps taken 
  tft.setCursor(128,94);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE , TFT_BLACK);
  tft.println(steps);

  


  count = buttonBtn.getCount();
  selectStatus = selectBtn.getCount();

  Serial.println(count);
  Serial.println(selectStatus);
  
  switch (count){
      case 0 : 
            tft.drawCircle(80,104,16,TFT_GREEN);
            if( selectStatus >= 1){
              resetCountbtn();
              showtimings = true;
              menu_loop();
            }
            break;
      case 1:
            tft.drawCircle(80,104,16,TFT_BLACK);
            break; 
      default: 
            tft.drawCircle(80,14,16,TFT_BLACK);
            Serial.println("default case");
            break;
  }

  if (count >= 2) buttonBtn.resetCount();
  delay(50);
  
}









void menu_loop() {

 

  resetCountbtn();
  drawSdJpeg(screen[0],0,0);
  delay(100);
  
  while(1){   // infinite loop       
  

  getBtnCount();
  delay(10);
  Serial.println(count);
  Serial.println(selectStatus);
  Serial.println(backStatus);
  

  if(backStatus >= 1){
    count = 0;
    resetCountbtn();
    drawSdJpeg(screen[1],0,0);
    delay(10);
    return ;
    
  }

    Serial.print("outer count");
    Serial.println(count);
 
  switch (count){

    case 1:
         //heart menu
          tft.drawCircle(80,24,radius,sColor);
          tft.drawCircle(119,37,radius,color1);
          tft.drawCircle(131,67,radius,color1);
          tft.drawCircle(121,97,radius,color1);
          tft.drawCircle(80,104,radius,color1);
          tft.drawCircle(39,97,radius,color1);
          tft.drawCircle(30,67,radius,color1);
          tft.drawCircle(41,37,radius,color1);
          tft.drawCircle(81,67,radius,color1);
          if(selectStatus >= 1) heartMenu();
          
          delay(50);
          break;
    case 2:
          // temperature
          tft.drawCircle(80,24,radius,color1);
          tft.drawCircle(119,37,radius,sColor);
          tft.drawCircle(131,67,radius,color1);
          tft.drawCircle(121,97,radius,color1);
          tft.drawCircle(80,104,radius,color1);
          tft.drawCircle(39,97,radius,color1);
          tft.drawCircle(30,67,radius,color1);
          tft.drawCircle(41,37,radius,color1);
          tft.drawCircle(81,67,radius,color1);
          if ( selectStatus >= 1) temperature();
          
          delay(50);
          
          break;
    case 3:

        //alarm
         tft.drawCircle(80,24,radius,color1);
          tft.drawCircle(119,37,radius,color1);
          tft.drawCircle(131,67,radius,sColor);
          tft.drawCircle(121,97,radius,color1);
          tft.drawCircle(80,104,radius,color1);
          tft.drawCircle(39,97,radius,color1);
          tft.drawCircle(30,67,radius,color1);
          tft.drawCircle(41,37,radius,color1);
          tft.drawCircle(81,67,radius,color1);
          if (selectStatus >= 1) alarm() ; 
         delay(50);
          break;
    case 4:

          //weather report
           tft.drawCircle(80,24,radius,color1);
          tft.drawCircle(119,37,radius,color1);
          tft.drawCircle(131,67,radius,color1);
          tft.drawCircle(121,97,radius,sColor);
          tft.drawCircle(80,104,radius,color1);
          tft.drawCircle(39,97,radius,color1);
          tft.drawCircle(30,67,radius,color1);
          tft.drawCircle(41,37,radius,color1);
          tft.drawCircle(81,67,radius,color1);
          if(selectStatus >= 1) weather();
          delay(50);
          break;

    case 5:

          //soil monitoring
          tft.drawCircle(80,24,radius,color1);
          tft.drawCircle(119,37,radius,color1);
          tft.drawCircle(131,67,radius,color1);
          tft.drawCircle(121,97,radius,color1);
          tft.drawCircle(80,104,radius,sColor);
          tft.drawCircle(39,97,radius,color1);
          tft.drawCircle(30,67,radius,color1);
          tft.drawCircle(41,37,radius,color1);
          tft.drawCircle(81,67,radius,color1);
          if(selectStatus >= 1) soil() ;
          delay(50);
          break;
     
    case 6:

          //settings
          tft.drawCircle(80,24,radius,color1);
          tft.drawCircle(119,37,radius,color1);
          tft.drawCircle(131,67,radius,color1);
          tft.drawCircle(121,97,radius,color1);
          tft.drawCircle(80,104,radius,color1);
          tft.drawCircle(39,97,radius,sColor);
          tft.drawCircle(30,67,radius,color1);
          tft.drawCircle(41,37,radius,color1);
          tft.drawCircle(81,67,radius,color1);
          if(selectStatus >= 1) setting();
          delay(50);
          break;

    case 7:

          // clock
          tft.drawCircle(80,24,radius,color1);
          tft.drawCircle(119,37,radius,color1);
          tft.drawCircle(131,67,radius,color1);
          tft.drawCircle(121,97,radius,color1);
          tft.drawCircle(80,104,radius,color1);
          tft.drawCircle(39,97,radius,color1);
          tft.drawCircle(30,67,radius,sColor);
          tft.drawCircle(41,37,radius,color1);
          tft.drawCircle(81,67,radius,color1);
          if( selectStatus >= 1) rtc_loop();
        delay(50);
        break;
    case 8:

          // accelerometer
          tft.drawCircle(80,24,radius,color1);
          tft.drawCircle(119,37,radius,color1);
          tft.drawCircle(131,67,radius,color1);
          tft.drawCircle(121,97,radius,color1);
          tft.drawCircle(80,104,radius,color1);
          tft.drawCircle(39,97,radius,color1);
          tft.drawCircle(30,67,radius,color1);
          tft.drawCircle(41,37,radius,sColor);
          tft.drawCircle(81,67,radius,color1);
          if (selectStatus >= 1) Status() ;
        delay(50);
        break;
    case 9:

          // twilio 
          tft.drawCircle(80,24,radius,color1);
          tft.drawCircle(119,37,radius,color1);
          tft.drawCircle(131,67,radius,color1);
          tft.drawCircle(121,97,radius,color1);
          tft.drawCircle(80,104,radius,color1);
          tft.drawCircle(39,97,radius,color1);
          tft.drawCircle(30,67,radius,color1);
          tft.drawCircle(41,37,radius,color1);
          tft.drawCircle(81,67,radius,sColor);
          if (selectStatus >= 1) whatsapp() ;
        delay(50);
        break;

    default:
         
          break;
    
  }
    
      
 
    if(count >= 10) buttonBtn.resetCount();
     delay(100);
  }
   
}






void resetCountbtn(){    // This fuunction reset Count value of all btn 

  buttonBtn.loop();                         // MUST call the loop() function first
  selectBtn.loop(); 
  backBtn.loop(); 
  buttonBtn.resetCount();
  selectBtn.resetCount();
  backBtn.resetCount(); 
}




void btnloop(){   //  function used check btn status using loop()
  
  buttonBtn.loop();                         // MUST call the loop() function first
  selectBtn.loop(); 
  backBtn.loop(); 
 
}


void getBtnCount(){    // function to get each btn count 
  buttonBtn.loop();                         // MUST call the loop() function first
  selectBtn.loop(); 
  backBtn.loop(); 
  count = buttonBtn.getCount();
  selectStatus = selectBtn.getCount();
  backStatus = backBtn.getCount();
}
