void music_create_screen()
{
  music_screen = lv_obj_create(app_screen);
  lv_obj_set_size(music_screen,tft.width(),tft.height());

  lv_obj_t *music_back_button = lv_btn_create(music_screen);
  lv_obj_set_size(music_back_button, 26, 26);
  lv_obj_align(music_back_button,LV_ALIGN_TOP_LEFT,0,0);
  lv_obj_add_event_cb(music_back_button, music_back_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *music_back_label = lv_label_create(music_back_button);
  lv_label_set_text(music_back_label, LV_SYMBOL_LEFT);
  lv_obj_align(music_back_label, LV_ALIGN_CENTER, 0, 0);

  
  lv_obj_t *music_label = lv_label_create(music_screen);
  lv_label_set_text(music_label, "Music");
  lv_obj_align(music_label, LV_ALIGN_TOP_MID, 0, 0);

}
void music_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      lv_obj_del(music_screen);
    }
}