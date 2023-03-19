void chatGPT_create_screen()
{
  chatGPT_screen = lv_obj_create(app_screen);
  lv_obj_set_size(chatGPT_screen,tft.width(),tft.height());

  lv_obj_t *chatGPT_back_button = lv_btn_create(chatGPT_screen);
  lv_obj_set_size(chatGPT_back_button, 26, 26);
  lv_obj_align(chatGPT_back_button,LV_ALIGN_TOP_LEFT,0,0);
  lv_obj_add_event_cb(chatGPT_back_button, chatGPT_back_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *chatGPT_back_label = lv_label_create(chatGPT_back_button);
  lv_label_set_text(chatGPT_back_label, LV_SYMBOL_LEFT);
  lv_obj_align(chatGPT_back_label, LV_ALIGN_CENTER, 0, 0);

  
  lv_obj_t *chatGPT_label = lv_label_create(chatGPT_screen);
  lv_label_set_text(chatGPT_label, "Chat GPT");
  lv_obj_align(chatGPT_label, LV_ALIGN_TOP_MID, 0, 0);

}
void chatGPT_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
     lv_obj_del(chatGPT_screen);
    }
}