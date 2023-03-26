lv_obj_t *dictionary_keyboard;
lv_obj_t *dictionary_text_box_result;
lv_obj_t *dictionary_text_box;
void dictionary_create_screen()
{
  dictionary_screen = lv_obj_create(app_screen);
  lv_obj_set_size(dictionary_screen,tft.width(),tft.height());
  lv_obj_clear_flag(dictionary_screen, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *dictionary_back_button = lv_btn_create(dictionary_screen);
  lv_obj_set_size(dictionary_back_button, 26, 26);
  lv_obj_align(dictionary_back_button,LV_ALIGN_TOP_LEFT,0,0);
  lv_obj_add_event_cb(dictionary_back_button, dictionary_back_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *dictionary_back_label = lv_label_create(dictionary_back_button);
  lv_label_set_text(dictionary_back_label, LV_SYMBOL_LEFT);
  lv_obj_align(dictionary_back_label, LV_ALIGN_CENTER, 0, 0);

  
  lv_obj_t *dictionary_label = lv_label_create(dictionary_screen);
  lv_label_set_text(dictionary_label, "Dictionary");
  lv_obj_align(dictionary_label, LV_ALIGN_TOP_MID, 0, 0);

  dictionary_text_box = lv_textarea_create(dictionary_screen);
  lv_obj_set_size(dictionary_text_box, tft.width()-30 ,40);  
  lv_obj_align(dictionary_text_box, LV_ALIGN_TOP_MID, 0, 40);
  lv_textarea_set_placeholder_text(dictionary_text_box, "Enter word");
  lv_obj_add_event_cb(dictionary_text_box, dict_text_input_event_cb, LV_EVENT_ALL, dictionary_keyboard);

  dictionary_keyboard = lv_keyboard_create(dictionary_screen);
  lv_obj_set_size(dictionary_keyboard,  tft.width(), tft.height() / 2);
  lv_obj_add_flag(dictionary_keyboard, LV_OBJ_FLAG_HIDDEN);

  dictionary_text_box_result = lv_textarea_create(dictionary_screen);
  lv_obj_set_size(dictionary_text_box_result, tft.width()-30 ,tft.height() / 2);  
  lv_obj_align(dictionary_text_box_result, LV_ALIGN_BOTTOM_MID, 0, 0);


}
void dictionary_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED)
     {
       if (dictionary_screen != NULL)
       {
        lv_obj_del_async(dictionary_screen);
      }
 
    }
}
static void dict_text_input_event_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *ta = lv_event_get_target(e);

  if (code == LV_EVENT_FOCUSED) {
    lv_obj_move_foreground(dictionary_keyboard);
    lv_keyboard_set_textarea(dictionary_keyboard, ta);
    lv_obj_clear_flag(dictionary_keyboard, LV_OBJ_FLAG_HIDDEN);
  }
  if(code==LV_EVENT_READY)
  {
     lv_keyboard_set_textarea(dictionary_keyboard, NULL);
    lv_obj_add_flag(dictionary_keyboard, LV_OBJ_FLAG_HIDDEN);
    if(WiFi.status() == WL_CONNECTED)
    {
     dictionary_cal_task();
    }
    else{
      lv_textarea_set_text(dictionary_text_box_result, "wifi Not connected");
    }
     
  }

  if (code == LV_EVENT_DEFOCUSED) {
    lv_keyboard_set_textarea(dictionary_keyboard, NULL);
    lv_obj_add_flag(dictionary_keyboard, LV_OBJ_FLAG_HIDDEN);
  }
}

static void dictionary_cal_task() {
  xTaskCreatePinnedToCore(dictionary_cal,
              "dictionary_cal",
              8300,
              NULL,
              1,
              &dictionaryHandler,
              1);
}

void dictionary_cal(void *pvParameters)
{
  
       HTTPClient http;
      http.begin("enter u r api" + String(lv_textarea_get_text(dictionary_text_box)));
      int httpcode = http.GET();
      if(httpcode > 0 && httpcode == HTTP_CODE_OK)
      {
        String payload = http.getString();
        scrapDictionaryData(payload);
        //vTasksuspend(dictionaryHandler);
         
      }
      else
      {
          lv_textarea_set_text(dictionary_text_box_result, "fetching failed");
          //vTasksuspend(dictionaryHandler);
      }
      http.end();
        if (dictionaryHandler != NULL) 
        {
          //Serial.println("task deleted");
          vTaskDelete(dictionaryHandler);
          dictionaryHandler = NULL; 
        }
      
      
       
}

void scrapDictionaryData(String payload){
  char jsonfile[1000];
  payload.toCharArray(jsonfile , 1000); 

  StaticJsonDocument<1000> doc;

  deserializeJson(doc, jsonfile); 
  
  String dict_result = doc[0]["meanings"][0]["definitions"][0]["definition"];
  char buf[30];
  dict_result.toCharArray(buf , dict_result.length());
  lv_textarea_set_text(dictionary_text_box_result, buf);
  // doc.clear();
  // dict_result.clear();
  //Serial.println(dict_result);
}
