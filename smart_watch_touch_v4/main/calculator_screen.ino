void calculator_create_screen()
{
  calculator_screen = lv_obj_create(app_screen);
  lv_obj_set_size(calculator_screen,tft.width(),tft.height());
  lv_obj_clear_flag(calculator_screen, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *calculator_back_button = lv_btn_create(calculator_screen);
  lv_obj_set_size(calculator_back_button, 26, 26);
  lv_obj_align(calculator_back_button,LV_ALIGN_TOP_LEFT,0,0);
  lv_obj_add_event_cb(calculator_back_button, calculator_back_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *calculator_back_label = lv_label_create(calculator_back_button);
  lv_label_set_text(calculator_back_label, LV_SYMBOL_LEFT);
  lv_obj_align(calculator_back_label, LV_ALIGN_CENTER, 0, 0);

  
  lv_obj_t *calculator_label = lv_label_create(calculator_screen);
  lv_label_set_text(calculator_label, "Calculator");
  lv_obj_align(calculator_label, LV_ALIGN_TOP_MID, 0, 0);

  calc_text_area();


}
void calculator_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
     lv_obj_del(calculator_screen);
    }
}

static void textarea_event_handler(lv_event_t * e)
{
    lv_obj_t * ta =(lv_obj_t*) lv_event_get_target(e);
    LV_UNUSED(ta);
    LV_LOG_USER("Enter was pressed. The current text is: %s", lv_textarea_get_text(ta));
}

static void btnm_event_handler(lv_event_t * e)
{

    lv_obj_t * obj =lv_event_get_target(e);
    lv_obj_t * ta = (lv_obj_t*)lv_event_get_user_data(e);
    const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

    if(strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) lv_textarea_del_char(ta);
    //else if(strcmp(txt, LV_SYMBOL_NEW_LINE) == 0) lv_event_send(ta, LV_EVENT_READY, NULL);
    else if(strcmp(txt, "AC") == 0) lv_textarea_set_text(ta,"");
    else if(strcmp(txt, "+/-") == 0) lv_textarea_add_char(ta,'-');
    else if(strcmp(txt, "=") == 0) {
      char buff[30];
      char res_buff[30];
      String res;
      String esp_result;
      esp_result = String(lv_textarea_get_text(ta));
      esp_result+='*';
      esp_result.toCharArray(buff,esp_result.length());    
      int error;
      double result = te_interp(buff, &error); 
      res = String(result);
      res.toCharArray(res_buff,res.length());
      lv_textarea_set_text(ta,res_buff);
      //Serial.println(result);

    }
    else lv_textarea_add_text(ta, txt);

}

void calc_text_area(void)
{
    lv_obj_t * ta = lv_textarea_create(calculator_screen);
    lv_textarea_set_one_line(ta, true);
    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 36);
    lv_obj_add_event_cb(ta, textarea_event_handler, LV_EVENT_READY, ta);
    lv_obj_add_state(ta, LV_STATE_FOCUSED); /*To be sure the cursor is visible*/

    static const char * btnm_map[] = {"AC", LV_SYMBOL_BACKSPACE, "+/-","/", "\n",
                                      "7", "8", "9","*", "\n",
                                      "4", "5", "6","-", "\n",
                                      "1", "2", "3", "+","\n",
                                      "%", "0", ".", "=",""
                                     };

    lv_obj_t * btnm = lv_btnmatrix_create(calculator_screen);
    lv_obj_set_size(btnm, tft.width()-10, 150);
    lv_obj_align(btnm, LV_ALIGN_BOTTOM_MID, 0, 20);
    lv_obj_add_event_cb(btnm, btnm_event_handler, LV_EVENT_VALUE_CHANGED, ta);
    lv_obj_clear_flag(btnm, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
    lv_btnmatrix_set_map(btnm, btnm_map);
}
