void timer_create_screen()
{
  timer_screen = lv_obj_create(app_screen);
  lv_obj_set_size(timer_screen,tft.width(),tft.height());

  lv_obj_t *timer_back_button = lv_btn_create(timer_screen);
  lv_obj_set_size(timer_back_button, 26, 26);
  lv_obj_align(timer_back_button,LV_ALIGN_TOP_LEFT,0,0);
  lv_obj_add_event_cb(timer_back_button, timer_back_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *timer_back_label = lv_label_create(timer_back_button);
  lv_label_set_text(timer_back_label, LV_SYMBOL_LEFT);
  lv_obj_align(timer_back_label, LV_ALIGN_CENTER, 0, 0);

  
  lv_obj_t *timer_label = lv_label_create(timer_screen);
  lv_label_set_text(timer_label, "Clock");
  lv_obj_align(timer_label, LV_ALIGN_TOP_MID, 0, 0);

}
void timer_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
     lv_obj_del(timer_screen);
    }
}