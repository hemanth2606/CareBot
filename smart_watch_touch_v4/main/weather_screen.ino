void weather_create_screen()
{
  weather_screen = lv_obj_create(app_screen);
  lv_obj_set_size(weather_screen,tft.width(),tft.height());

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

}
void weather_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
     lv_obj_del(weather_screen);
    }
}