#include <lvgl.h>
#include <TFT_eSPI.h>
#include "WiFi.h"
#include <vector>

#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "ChatGPT.hpp"

#include "tinyexpr.h"

#include<HTTPClient.h>

#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "spo2_algorithm.h"
MAX30105 particleSensor;
#define MAX_BRIGHTNESS 255

#include <BleKeyboard.h>
BleKeyboard bleKeyboard("CareBot","Slealth",100);


const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 5.5 * 60 * 60;  // Set your timezone here
const int daylightOffset_sec = 0;

#include <EEPROM.h>
#define EEPROM_SIZE 128
#define EEPROM_ADDR_WIFI_FLAG 0
#define EEPROM_ADDR_WIFI_CREDENTIAL 4

static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

typedef enum {
  NONE,
  NETWORK_SEARCHING,
  NETWORK_CONNECTED_POPUP,
  NETWORK_CONNECTED,
  NETWORK_CONNECT_FAILED
} Network_Status_t;

Network_Status_t networkStatus = NONE;
static lv_obj_t *headerLabel;
static lv_style_t border_style;
static lv_style_t popupBox_style;
static lv_obj_t *timeLabel;
static lv_obj_t *settings;
static lv_obj_t *settingBtn;
static lv_obj_t *settingCloseBtn;
static lv_obj_t *settingWiFiSwitch;
static lv_obj_t *wfList;
static lv_obj_t *settinglabel;
static lv_obj_t *mboxConnect;
static lv_obj_t *mboxTitle;
static lv_obj_t *mboxPassword;
static lv_obj_t *mboxConnectBtn;
static lv_obj_t *mboxCloseBtn;
static lv_obj_t *keyboard;
static lv_obj_t *popupBox;
static lv_obj_t *popupBoxCloseBtn;
static lv_timer_t *timer;
static lv_timer_t *dict_timer;


static lv_obj_t *button;
lv_obj_t *Clock;
lv_obj_t *dayOfWeek;
lv_obj_t *date;
static lv_style_t style_Clock_text;
lv_obj_t *screen2 ;
lv_anim_t anim;

static lv_obj_t *bluetooth_Status_label;

lv_obj_t *home_screen;
lv_obj_t *tv;
lv_obj_t *activity_screen;
lv_obj_t *app_screen;
lv_obj_t *heart_rate_screen;
lv_obj_t *steps_screen;
lv_obj_t *spo2_screen;
lv_obj_t *skin_temp_screen;

lv_obj_t *light_control_screen;
lv_obj_t *calculator_screen;
lv_obj_t *setting_screen;
lv_obj_t *music_screen;

lv_obj_t *camera_screen;
lv_obj_t *timer_screen;
lv_obj_t *weather_screen;
lv_obj_t *chatGPT_screen;
lv_obj_t *dictionary_screen;


static int foundNetworks = 0;
unsigned long networkTimeout = 10 * 1000;
String ssidName, ssidPW;

TaskHandle_t ntScanTaskHandler, ntConnectTaskHandler,heartRateHandler=NULL,spo2Handler=NULL,stepHandler=NULL,skinTempHandler=NULL,stepsHandler=NULL,dictionaryHandler=NULL,chatGPTHandler=NULL,weatherHandler=NULL;
std::vector<String> foundWifiList;
void gfx_setup();

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 115200 );
  //bleKeyboard.begin();
  gfx_setup();
  loadingScreen();
  move_to_home_screen();
  //steps_cal_task();
}

void loop() {
  // put your main code here, to run repeatedly:
   lv_timer_handler(); /* let the GUI do its work */
    delay( 5 );
}
