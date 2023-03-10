
//#include "dictionary.h"
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI(); // tft display object

#include<WiFi.h>
#include<HTTPClient.h>
#include<ArduinoJson.h>

#include <JPEGDecoder.h>
#include <XPT2046_Touchscreen.h>
#include "TouchEvent.h"

// including max sensor library
#include "MAX30105.h"
#include "heartRate.h"
MAX30105 particleSensor; // max30105 object 
//
#include <Wire.h>
#include <ADXL345.h>


ADXL345 adxl; 

// start time
unsigned long startTime;
unsigned long presentTime;

const char* ssid = "ASUS_X00TD";
const char* password = "healsou1";
// including rtc library
#include "RTClib.h"
RTC_DS1307 rtc;
//
//bool Showtime = false;
//String presentTime = "";

#define TOUCH_CS 13      //touch screen chip select
#define TOUCH_IRQ 26     //touch screen interrupt


//// variables for spo2 
//uint32_t irBuffer[100]; //infrared LED sensor data
//uint32_t redBuffer[100];  //red LED sensor data
//int32_t bufferLength; //data length
//int32_t spo2; //SPO2 value
//int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
//int32_t heartRate; //heart rate value
//int8_t validHeartRate; //indicator to show if the heart rate calculation is valid

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

// Creating object of class XPT2046_Touchscreen
XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);


const char* screen[] = { "/new_ui/main_screen.jpg" ,
                         "/new_ui/main_screen_2.jpg", "/new_ui/steps.jpg" , "/new_ui/heart_rate.jpg" ,"/new_ui/spo2.jpg" , "/new_ui/temp.jpg", 
                         "/new_ui/photo_viewer.jpg", "/new_ui/Alarm.jpg" , "/new_ui/soil_moisture.jpg" , "/new_ui/calculator.jpg", 
                         "/new_ui/stocks.jpg" , "/new_ui/dictionary.jpg" , "/new_ui/settings.jpg" , "/new_ui/weather.jpg", 
                         "/new_ui/main_screen_4.jpg" , 
                         "/new_ui/temp.jpg" , "/new_ui/fill.jpg" , "/new_ui/music.jpg" , "/new_ui/camera_shutter.jpg" , 
                         "/new_ui/games/jpg" , "/new_ui/media.jpg" , "/new_ui/energy_saver.jpg" , "/new_ui/energy_saver.jpg" , 
                         "/new_ui/deep_sleep.jpg" ,
                         "/new_ui/wifi_connecting.jpg"
                      
                     }; 


int step_s =0 ;
float distance = 0;
int calories = 0;
float prevAcl = 0 , newAcl = 0;

int CurrentStatus = 0;

//init TouchEvent with pointer to the touch screen driver
TouchEvent tevent(touch);
TS_Point p;

TS_Point p_old;

int pos = 0;


// calculator 
const int LEN = 20;

// Size of the stack
const int MAX = 40;

class Stack {
private:
  // Stack: array of characters
  char st[MAX];

  // Number at top of the stack
  int top;

public:
  Stack()
  {
    top = 0;
  }

  // Function to put a character in stack
  void push(char var)
  {
    st[++top] = var;
  }

  // Function to return a character off stack
  char pop()
  {
    return st[top--];
  }

  // Function to get the top of the stack
  int gettop()
  {
    return top;
  }
};

// Expression class
class Express {
private:
  // Stack for analysis
  Stack s;

  // Pointer to input string
  char* pStr;

  // Length of the input string
  int len;

public:
  Express(char* ptr)
  {
    pStr = ptr;
    len = strlen(pStr);
  }

  // Parse the input string
  void parse();

  // Evaluate the stack
  int solve();
};

void Express::parse()
{

  // Character from the input string
  char ch;

  // Last value
  char lastval;

  // Last operator
  char lastop;

  // For each input character
  for (int j = 0; j < len; j++) {
    ch = pStr[j];

    // If it's a digit then save
    // the numerical value
    if (ch >= '0' && ch <= '9')
      s.push(ch - '0');

    // If it's an operator
    else if (ch == '+' || ch == '-'
        || ch == '*' || ch == '/') {

      // If it is the first operator
      // then put it in the stack
      if (s.gettop() == 1)

        s.push(ch);

      // Not the first operator
      else {
        lastval = s.pop();
        lastop = s.pop();

        // If it is either '*' or '/' and the
        // last operator was either '+' or '-'
        if ((ch == '*' || ch == '/')
          && (lastop == '+' || lastop == '-')) {

          // Restore the last two pops
          s.push(lastop);
          s.push(lastval);
        }

        // In all the other cases
        else {

          // Perform the last operation
          switch (lastop) {

          // Push the result in the stack
          case '+':
            s.push(s.pop() + lastval);
            break;
          case '-':
            s.push(s.pop() - lastval);
            break;
          case '*':
            s.push(s.pop() * lastval);
            break;
          case '/':
            s.push(s.pop() / lastval);
            break;
          default:
            Serial.println("\nUnknown oper");
            exit(1);
          }
        }
        s.push(ch);
      }
    }
    else {
      Serial.println("\nUnknown input character");
      exit(1);
    }
  }
}

int Express::solve()
{
  // Remove the items from stack
  char lastval;
  while (s.gettop() > 1) {
    lastval = s.pop();
    switch (s.pop()) {

    // Perform operation, push answer
    case '+':
      s.push(s.pop() + lastval);
      break;
    case '-':
      s.push(s.pop() - lastval);
      break;
    case '*':
      s.push(s.pop() * lastval);
      break;
    case '/':
      s.push(s.pop() / lastval);
      break;
    default:
      Serial.println("\nUnknown operator");
      exit(1);
    }
  }
  return int(s.pop());
}


// --------------------- setup ------------------------
void setup(){
  touch.begin();
  sd_setup();
  
//  xTaskCreatePinnedToCore( coreOneTask , "fucntion" , 100000 , NULL , 0,NULL , 0);
//  delay(100);
  drawSdJpeg(screen[0] , 0 , 0 ); 
//  rtc_setup();
  adlx_setup();
  delay(100);
  
}








    


void mainScreen(){
  drawSdJpeg(screen[CurrentStatus] , 0 , 0 );
  while(true){
      if(touch.touched() && !touch.bufferEmpty()){
            GetPoint();
          
          // <--------------------- health -------------------------->  
            if(p.x > 41 && p.x < 90 && p.y > 20 && p.y < 69){
                CurrentStatus = 2;
                steps();
       
            }
            else if(p.x > 102 && p.x <151 && p.y >20 && p.y < 69){
              CurrentStatus = 3;
              heartRate();
            }

            else if(p.x > 163 && p.x < 212 && p.y > 20 && p.y < 69){
              CurrentStatus =4;
              spo2();
            } 

            else if(p.x > 224 && p.x < 273 && p.y > 20 && p.y < 69){
              CurrentStatus = 5;
              temp();
          }

          // <---------------------- basic category       --------------------->

          else if(p.x > 41 && p.x < 90 && p.y > 77 && p.y < 126){
              CurrentStatus =6 ;
              gallery();
              
          }

          else if(p.x > 102 && p.x <151 && p.y >77 && p.y < 126){
              CurrentStatus  = 7;
              alarm_rtc();
          }


          else if(p.x > 163 && p.x < 212 && p.y > 77 && p.y < 126){
              CurrentStatus = 8;
              soil_moisture();
          }

          else if(p.x > 224 && p.x < 273 && p.y > 77 && p.y < 126){
              CurrentStatus = 9;
              calculator();
          }

          //-------------------- stocks ---------------// 

          else if(p.x > 41 && p.x < 90 && p.y > 134 && p.y < 183){
              CurrentStatus =10 ;
              stocks();
              
          }

          else if(p.x > 102 && p.x <151 && p.y >134 && p.y < 183){
              CurrentStatus  = 11;
              //dictionary();
          }


          else if(p.x > 163 && p.x < 212 && p.y > 134 && p.y < 183){
              CurrentStatus = 12;
              settings();
            
          }

          else if(p.x > 224 && p.x < 273 && p.y > 134 && p.y < 183){
              CurrentStatus = 13;
              weather();
          }
            
          
          // up arrow , home  , down arrow navigation
          else if(p.x > 41 && p.x < 119 && p.y > 202 && p.y < 230){
              CurrentStatus = 1;
//              drawSdJpeg(screen[CurrentStatus] , 0 , 0);
              
          }

          else if(p.x > 119 && p.x < 197 && p.y > 202 && p.y < 230){
            CurrentStatus = 0;
            drawSdJpeg(screen[CurrentStatus], 0 , 0); 
            return;
          }

          else if(p.x > 197 && p.x < 275 && p.y > 202 && p.y <230){
            CurrentStatus = 14;
            drawSdJpeg(screen[CurrentStatus] , 0 , 0);
            mainScreen1();
            
          }
          
    }
  }
}

void mainScreen1(){



  while(true){
      if(touch.touched() && !touch.bufferEmpty()){
            GetPoint();
          
          

         
            
          
          // up arrow , home  , down arrow navigation
           if(p.x > 41 && p.x < 119 && p.y > 202 && p.y < 230){
              CurrentStatus = 1;
              drawSdJpeg(screen[CurrentStatus] , 0 , 0);
              mainScreen();              
          }

          else if(p.x > 119 && p.x < 197 && p.y > 202 && p.y < 230){
            CurrentStatus = 0;
            drawSdJpeg(screen[CurrentStatus], 0 , 0); 
            initialScreen();
          }

          else if(p.x > 197 && p.x < 275 && p.y > 202 && p.y <230){
            CurrentStatus = 14;
            
            
            
          }
          
    }
  }
  
}


//void printTime(int x , int y){
//    DateTime now = rtc.now();
//   char buf[] = "hh:mm";
//   tft.setCursor(x, y);
//   tft.setTextSize(3);
//   tft.println(now.toString(buf));
//   delay(100);
//}
void loop(){
  initialScreen();
}



void initialScreen() {
    
    while(1){
      
      
      
          if(touch.touched() && !touch.bufferEmpty()){
                GetPoint();  
                if(p.x > 140 && p.x < 180 && p.y > 167 && p.y < 207){
                CurrentStatus = 1;
                mainScreen();   
            }
        }
    }       
}


void GetPoint(){
   p = touch.getPoint();
   p.x = map(p.x , 256 ,3860, 0 ,320);
   p.y = map(p.y , 300 , 3760 , 0 ,240);
   
}


bool isBackPressed(){
  GetPoint();
  if(p.x >0 && p.x < 30 && p.y >0 && p.y < 30)
    return true;
  
  return false;
}

bool isStartPressed(){
  GetPoint();
  if(p.x > 37 && p.x < 283 && p.y > 193 && p.y < 225 ){
    return 1;
  }
    return 0;  
}


void refreshScreen(int cor_x , int cor_y , int len){
  tft.setCursor(cor_x , cor_y);
  String x = " ";
  for(int i=0 ; i<len ; i++){
    x += " ";
  }
  tft.print(x);
  
}








void changeScreen(TS_Point p){

  int x = 0;
  
  while(true){
    
    p = touch.getPoint();
//     p.x = map(p.x, TS_LEFT, TS_RT, 0, 320);
//     p.y = map(p.y, TS_TOP, TS_BOT, 0, 240);
    Serial.print(" x: ");
    Serial.print(p.x);
    Serial.print(" y: ");
    Serial.print(p.y);
    Serial.println("");
    
    if(p.x > 145 && p.x < 180 && p.y > 200 && p.y > 230){
      mainScreen();
    }
   }
 }

void touchTest(){


  if(touch.touched()){

      if(!touch.bufferEmpty()){

       
//        p = touch.getPoint();
//        refreshScreen(0,0,18);
//        refreshScreen(0,20,18);

//        tft.setCursor(0,0);
//        tft.print("p.x :");
//        tft.print(p.x);
//        tft.print("p.y :");
//        tft.print(p.y);
        
//        tft.println(" ");
        
//        
//        p.x = map(p.x , 256 ,3860, 0 ,320);
//        p.y = map(p.y , 300 , 3760 , 0 ,240);
//        
//        tft.setCursor(0,20);
//
//        tft.print("P.x :");
//        tft.print(p.x);
//        tft.print("P.y :");
//        tft.print(p.y);
//        tft.println(" ");

        
        Serial.print("P.x :");
        Serial.print(p.x);
        Serial.print("P.y :");
        Serial.print(p.y);
        Serial.println(" ");
        

      }
   }
}


//        Serial.print("P.x :");
//        Serial.print(p.x);
//        Serial.print("P.y :");
//        Serial.print(p.y);
//        Serial.println(" ");

void testFontSize(){

    tft.setCursor(0,0);
    tft.setTextSize(1);
    tft.print("Neelesh");

    tft.setCursor(0,20);
    tft.setTextSize(2);
    tft.print("Neelesh");

    tft.setCursor(0,40);
    tft.setTextSize(3);
    tft.print("Neelesh");

    tft.setCursor(0,80);
    tft.setTextSize(4);
    tft.print("Neelesh");

    tft.setCursor(0,160);
    tft.setTextSize(5);
    tft.print("Neelesh");
}
