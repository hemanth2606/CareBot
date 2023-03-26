lv_obj_t *chatGPT_keyboard;
lv_obj_t *chatGPT_text_box_result;
lv_obj_t *chatGPT_text_box;

const char *test_root_ca =
  "-----BEGIN CERTIFICATE-----\n"
  "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\n"
  "-----END CERTIFICATE-----\n";

WiFiClientSecure chatGPT_client;
ChatGPT<WiFiClientSecure> chat_gpt(&chatGPT_client, "v1", "enter your API key");

void chatGPT_create_screen()
{
  chatGPT_screen = lv_obj_create(app_screen);
  lv_obj_set_size(chatGPT_screen,tft.width(),tft.height());
  lv_obj_clear_flag(chatGPT_screen, LV_OBJ_FLAG_SCROLLABLE);

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

  chatGPT_text_box = lv_textarea_create(chatGPT_screen);
  lv_obj_set_size(chatGPT_text_box, tft.width()-30 ,40);  
  lv_obj_align(chatGPT_text_box, LV_ALIGN_TOP_MID, 0, 40);
  lv_textarea_set_placeholder_text(chatGPT_text_box, "Enter word");
  lv_obj_add_event_cb(chatGPT_text_box, chatGPT_text_input_event_cb, LV_EVENT_ALL, chatGPT_keyboard);

  chatGPT_keyboard = lv_keyboard_create(chatGPT_screen);
  lv_obj_set_size(chatGPT_keyboard,  tft.width(), tft.height() / 2);
  lv_obj_add_flag(chatGPT_keyboard, LV_OBJ_FLAG_HIDDEN);

  chatGPT_text_box_result = lv_textarea_create(chatGPT_screen);
  lv_obj_set_size(chatGPT_text_box_result, tft.width()-30 ,tft.height() / 2);  
  lv_obj_align(chatGPT_text_box_result, LV_ALIGN_BOTTOM_MID, 0, 0);


}

static void chatGPT_text_input_event_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *ta = lv_event_get_target(e);

  if (code == LV_EVENT_FOCUSED) {
    lv_obj_move_foreground(chatGPT_keyboard);
    lv_keyboard_set_textarea(chatGPT_keyboard, ta);
    lv_obj_clear_flag(chatGPT_keyboard, LV_OBJ_FLAG_HIDDEN);
  }
  if(code==LV_EVENT_READY)
  {
     lv_keyboard_set_textarea(chatGPT_keyboard, NULL);
    lv_obj_add_flag(chatGPT_keyboard, LV_OBJ_FLAG_HIDDEN);
     if(WiFi.status() == WL_CONNECTED)
     {
          chatGPT_cal_task();
     }
     else
    { 
        lv_textarea_set_text(chatGPT_text_box_result, "WIfi not connected");
    }
     
  }

  if (code == LV_EVENT_DEFOCUSED) {
    lv_keyboard_set_textarea(chatGPT_keyboard, NULL);
    lv_obj_add_flag(chatGPT_keyboard, LV_OBJ_FLAG_HIDDEN);
  }
}


void chatGPT_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
       if (chatGPT_screen != NULL)
       {
         lv_obj_del_async(chatGPT_screen);
       }
     
    }
}

static void chatGPT_cal_task() {
  xTaskCreatePinnedToCore(chatGPT_cal,
              "chatGPT_cal",
              8060,
              NULL,
              1,
              &chatGPTHandler,
              1);
}
void chatGPT_cal(void *pvParameters)
{
      chatGPT_client.setCACert(test_root_ca);
      char buf[1000];
      String chatGPT_result;
      if (chat_gpt.simple_message("gpt-3.5-turbo-0301", "user",String(lv_textarea_get_text(chatGPT_text_box)), chatGPT_result)) 
      {
        chatGPT_result.toCharArray(buf , chatGPT_result.length());
        lv_textarea_set_text(chatGPT_text_box_result, buf);
     } 
     else 
     {
        chatGPT_result.toCharArray(buf , chatGPT_result.length());
        lv_textarea_set_text(chatGPT_text_box_result, buf);
     }
      if (chatGPTHandler != NULL) 
        {
          //Serial.println("task deleted");
          vTaskDelete(chatGPTHandler);
          chatGPTHandler = NULL; 
        }
  
}
  

