void weather_create_screen()
{
  weather_screen = lv_obj_create(app_screen);
  lv_obj_set_size(weather_screen,tft.width(),tft.height());
  lv_obj_clear_flag(weather_screen, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *weather_back_button = lv_btn_create(weather_screen);
  lv_obj_set_size(weather_back_button, 26, 26);
  lv_obj_align(weather_back_button,LV_ALIGN_TOP_LEFT,0,0);
  lv_obj_add_event_cb(weather_back_button, weather_back_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *weather_back_label = lv_label_create(weather_back_button);
  lv_label_set_text(weather_back_label, LV_SYMBOL_LEFT);
  lv_obj_align(weather_back_label, LV_ALIGN_CENTER, 0, 0);

  
  lv_obj_t *weather_label = lv_label_create(weather_screen);
  lv_label_set_text(weather_label, "weather");
  lv_obj_align(weather_label, LV_ALIGN_TOP_MID, 0, 0);

  // if(WiFi.status() == WL_CONNECTED){
  //   weather_cal();

  // }
  // else{

  // }

}
void weather_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
     lv_obj_del_async(weather_screen);
    }
}
// void weather_cal(){

//     HTTPClient http;
//     http.begin("https://api.openweathermap.org/data/2.5/weather?q=bengaluru&appid=73b8dbdabd44cd4c27a2c264beb435f0");
//     int httpcode = http.GET();
//     if(httpcode > 0 && httpcode == HTTP_CODE_OK ){
//         String payload = http.getString();
//         scrapWeatherData(payload);
//     }
//     else{

//     }
//     http.end();
  
// }

// void scrapWeatherData(String payload){
//   char jsonweatherfile[1000];
//   payload.toCharArray(jsonweatherfile , 1000);
//   StaticJsonDocument<1000> docs;
//   deserializeJson(docs , jsonweatherfile);
//   String clould = docs["weather"][0]["description"];
//   String temp = docs["main"]["temp"];
//   String temp_max = docs["main"]["temp_max"];
//   String temp_min = docs["main"]["temp_min"];
//   String humidity = docs["main"]["humidity"];
//   String pressure = docs["main"]["pressure"];
//   int  visibility = docs["visibility"];
// }
