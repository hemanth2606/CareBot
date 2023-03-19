void setting_create_screen()
{
  setting_screen = lv_obj_create(app_screen);
  lv_obj_set_size(setting_screen,tft.width(),tft.height());

  lv_obj_t *setting_back_button = lv_btn_create(setting_screen);
  lv_obj_set_size(setting_back_button, 26, 26);
  lv_obj_align(setting_back_button,LV_ALIGN_TOP_LEFT,0,0);
  lv_obj_add_event_cb(setting_back_button, setting_back_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *setting_back_label = lv_label_create(setting_back_button);
  lv_label_set_text(setting_back_label, LV_SYMBOL_LEFT);
  lv_obj_align(setting_back_label, LV_ALIGN_CENTER, 0, 0);

  
  lv_obj_t *setting_label = lv_label_create(setting_screen);
  lv_label_set_text(setting_label, "Setting");
  lv_obj_align(setting_label, LV_ALIGN_TOP_MID, 0, 0);

}
void setting_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
     lv_obj_del(setting_screen);
    }
}