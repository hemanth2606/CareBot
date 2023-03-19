
lv_obj_t *skin_temp_arc_value;

void skin_temp_create_screen()
{
   LV_IMG_DECLARE(skin_temp_icon);
  skin_temp_screen = lv_obj_create(app_screen);
  lv_obj_set_size(skin_temp_screen,tft.width(),tft.height());

  lv_obj_t *skin_temp_back_button = lv_btn_create(skin_temp_screen);
  lv_obj_set_size(skin_temp_back_button, 26, 26);
  lv_obj_align(skin_temp_back_button,LV_ALIGN_TOP_LEFT,0,0);
  lv_obj_add_event_cb(skin_temp_back_button, skin_temp_back_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *skin_temp_back_label = lv_label_create(skin_temp_back_button);
  lv_label_set_text(skin_temp_back_label, LV_SYMBOL_LEFT);
  lv_obj_align(skin_temp_back_label, LV_ALIGN_CENTER, 0, 0);

  
  lv_obj_t *skin_temp_label = lv_label_create(skin_temp_screen);
  lv_label_set_text(skin_temp_label, "Skin Temperature");
  lv_obj_align(skin_temp_label, LV_ALIGN_TOP_MID, 0, 0);

   lv_obj_t *skin_temp_arc = lv_arc_create(skin_temp_screen);
  lv_obj_set_size(skin_temp_arc, 100, 100);
  lv_arc_set_rotation(skin_temp_arc, 270);
  lv_arc_set_bg_angles(skin_temp_arc, 0, 360);
  lv_obj_remove_style(skin_temp_arc, NULL, LV_PART_KNOB);
  lv_obj_clear_flag(skin_temp_arc, LV_OBJ_FLAG_CLICKABLE);
  lv_arc_set_value(skin_temp_arc, 100);
  lv_obj_align(skin_temp_arc,LV_ALIGN_CENTER,0,-20);

  lv_obj_t *skin_temp_img = lv_img_create(skin_temp_arc);
  lv_img_set_src(skin_temp_img, &skin_temp_icon);
  lv_obj_set_style_img_recolor_opa(skin_temp_img, 255, 0);
  lv_obj_set_style_img_recolor(skin_temp_img,lv_color_make(255,255,255),0);
  lv_obj_align(skin_temp_img, LV_ALIGN_CENTER, 0, 0);

  skin_temp_arc_value = lv_label_create(skin_temp_screen);
  lv_label_set_text(skin_temp_arc_value,"30 °C");
  lv_obj_align(skin_temp_arc_value, LV_ALIGN_BOTTOM_MID, 0, -46);

  lv_obj_t *skin_temp_cal_button = lv_btn_create(skin_temp_screen);
  lv_obj_set_size(skin_temp_cal_button, 100, 40);
  lv_obj_align(skin_temp_cal_button,LV_ALIGN_BOTTOM_MID,0,0);
  lv_obj_add_event_cb(skin_temp_cal_button, skin_temp_cal_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *skin_temp_cal_label = lv_label_create(skin_temp_cal_button);
  lv_label_set_text(skin_temp_cal_label, "Calculate");
  lv_obj_align(skin_temp_cal_label, LV_ALIGN_CENTER, 0, 0);

}
void skin_temp_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      if (skin_temp_screen != NULL) {
        if (skinTempHandler != NULL) {
          vTaskDelete(skinTempHandler);
          skinTempHandler = NULL;
        }
         lv_obj_del(skin_temp_screen);
       }
    }
}

void skin_temp_cal_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        if (skinTempHandler == NULL) {

            skin_temp_cal_task();

        }
     
      
    }
}

static void skin_temp_cal_task() {
  xTaskCreatePinnedToCore(skin_temp_cal,
              "skin_temp_cal",
              4096,
              NULL,
              1,
              &skinTempHandler,
              tskNO_AFFINITY);
}

static void skin_temp_cal(void *pvParameters)
{
    if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false) //Use default I2C port, 400kHz speed
  {
    ///error code
    while (1);
  }

  //The LEDs are very low power and won't affect the temp reading much but
  //you may want to turn off the LEDs to avoid any local heating
  particleSensor.setup(0); //Configure sensor. Turn off LEDs
  //particleSensor.setup(); //Configure sensor. Use 25mA for LED drive

  particleSensor.enableDIETEMPRDY();
  while(1)
  {
  float Skin_temperature = particleSensor.readTemperature();
  int Skin_value =(int) (Skin_temperature*100);
  lv_label_set_text_fmt(skin_temp_arc_value, "%d.%2d °C",(int)(Skin_value/100),Skin_value%100);
  vTaskDelay(1500/portTICK_PERIOD_MS);
  }

}