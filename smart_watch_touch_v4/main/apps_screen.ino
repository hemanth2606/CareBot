void app_icon_create()
{
   
      LV_IMG_DECLARE(steps_icon);
      LV_IMG_DECLARE(heart_icon);
      LV_IMG_DECLARE(deep_sleep_icon);
      LV_IMG_DECLARE(spo2_icon);
      LV_IMG_DECLARE(skin_temp_icon);
      LV_IMG_DECLARE(calculator_icon);
      LV_IMG_DECLARE(light_control_icon);
      LV_IMG_DECLARE(music_icon);
      LV_IMG_DECLARE(setting_icon);
      LV_IMG_DECLARE(camera_icon);
      LV_IMG_DECLARE(timer_icon);
      LV_IMG_DECLARE(weather_icon);

        lv_img_dsc_t * const my_icons[] = {
        (lv_img_dsc_t *)&steps_icon,
        (lv_img_dsc_t *)&heart_icon,
        (lv_img_dsc_t *)&deep_sleep_icon,
        (lv_img_dsc_t *)&spo2_icon,
        (lv_img_dsc_t *)&skin_temp_icon,
        (lv_img_dsc_t *)&calculator_icon,
        (lv_img_dsc_t *)&light_control_icon,
        (lv_img_dsc_t *)&music_icon,
        (lv_img_dsc_t *)&setting_icon,
        (lv_img_dsc_t *)&camera_icon,
        (lv_img_dsc_t *)&timer_icon,
        (lv_img_dsc_t *)&weather_icon
        };
        
      lv_obj_t *app_flex = lv_obj_create(app_screen);
      lv_obj_set_style_base_dir(app_flex, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
      lv_obj_set_size(app_flex,tft.width(), tft.height());
      lv_obj_center(app_flex);
      lv_obj_set_flex_flow(app_flex, LV_FLEX_FLOW_ROW_WRAP);
      lv_obj_set_style_pad_column(app_flex, 36, 0);
      lv_obj_set_style_pad_row(app_flex, 20, 0);

      lv_obj_t *steps_button = lv_btn_create(app_flex);
      lv_obj_set_size(steps_button, 70, 70);
      lv_obj_t *steps_img = lv_img_create(steps_button);
      lv_img_set_src(steps_img, my_icons[0]);
      lv_obj_set_style_img_recolor_opa(steps_img, 255, 0);
      lv_obj_set_style_img_recolor(steps_img,lv_color_make(255,255,255),0);
      lv_obj_align(steps_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(steps_button,steps_event_cb, LV_EVENT_CLICKED, NULL);

      lv_obj_t *heart_rate_button = lv_btn_create(app_flex);
      lv_obj_set_size(heart_rate_button, 70, 70);
      lv_obj_t *heart_rate_img = lv_img_create(heart_rate_button);
      lv_img_set_src(heart_rate_img, my_icons[1]);
      lv_obj_set_style_img_recolor_opa(heart_rate_img, 255, 0);
      lv_obj_set_style_img_recolor(heart_rate_img,lv_color_make(255,255,255),0);
      lv_obj_align(heart_rate_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(heart_rate_button, heart_rate_event_cb, LV_EVENT_CLICKED, NULL);

      lv_obj_t *deep_sleep_button = lv_btn_create(app_flex);
      lv_obj_set_size(deep_sleep_button, 70, 70);
      lv_obj_t *deep_sleep_img = lv_img_create(deep_sleep_button);
      lv_img_set_src(deep_sleep_img, my_icons[2]);
      lv_obj_set_style_img_recolor_opa(deep_sleep_img, 255, 0);
      lv_obj_set_style_img_recolor(deep_sleep_img,lv_color_make(255,255,255),0);
      lv_obj_align(deep_sleep_img, LV_ALIGN_CENTER, 0, 0);
     // lv_obj_add_event_cb(deep_sleep_button, deep_sleep_event_cb, LV_EVENT_CLICKED, NULL);

      lv_obj_t *spo2_button = lv_btn_create(app_flex);
      lv_obj_set_size(spo2_button, 70, 70);
      lv_obj_t *spo2_img = lv_img_create(spo2_button);
      lv_img_set_src(spo2_img, my_icons[3]);
      lv_obj_set_style_img_recolor_opa(spo2_img, 255, 0);
      lv_obj_set_style_img_recolor(spo2_img,lv_color_make(255,255,255),0);
      lv_obj_align(spo2_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(spo2_button,spo2_event_cb, LV_EVENT_CLICKED, NULL);

      lv_obj_t *skin_temp_button = lv_btn_create(app_flex);
      lv_obj_set_size(skin_temp_button, 70, 70);
      lv_obj_t *skin_temp_img = lv_img_create(skin_temp_button);
      lv_img_set_src(skin_temp_img, my_icons[4]);
      lv_obj_set_style_img_recolor_opa(skin_temp_img, 255, 0);
      lv_obj_set_style_img_recolor(skin_temp_img,lv_color_make(255,255,255),0);
      lv_obj_align(skin_temp_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(skin_temp_button, skin_temp_event_cb, LV_EVENT_CLICKED, NULL);

      lv_obj_t *calculator_button = lv_btn_create(app_flex);
      lv_obj_set_size(calculator_button, 70, 70);
      lv_obj_t *calculator_img = lv_img_create(calculator_button);
      lv_img_set_src(calculator_img, my_icons[5]);
      lv_obj_set_style_img_recolor_opa(calculator_img, 255, 0);
      lv_obj_set_style_img_recolor(calculator_img,lv_color_make(255,255,255),0);
      lv_obj_align(calculator_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(calculator_button, calculator_event_cb, LV_EVENT_CLICKED, NULL);

      lv_obj_t *light_control_button = lv_btn_create(app_flex);
      lv_obj_set_size(light_control_button, 70, 70);
      lv_obj_t *light_control_img = lv_img_create(light_control_button);
      lv_img_set_src(light_control_img, my_icons[6]);
      lv_obj_set_style_img_recolor_opa(light_control_img, 255, 0);
      lv_obj_set_style_img_recolor(light_control_img,lv_color_make(255,255,255),0);
      lv_obj_align(light_control_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(light_control_button, light_control_event_cb, LV_EVENT_CLICKED, NULL);

      lv_obj_t *music_button = lv_btn_create(app_flex);
      lv_obj_set_size(music_button, 70, 70);
      lv_obj_t *music_img = lv_img_create(music_button);
      lv_img_set_src(music_img, my_icons[7]);
      lv_obj_set_style_img_recolor_opa(music_img, 255, 0);
      lv_obj_set_style_img_recolor(music_img,lv_color_make(255,255,255),0);
      lv_obj_align(music_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(music_button, music_event_cb, LV_EVENT_CLICKED, NULL);

      lv_obj_t *setting_button = lv_btn_create(app_flex);
      lv_obj_set_size(setting_button, 70, 70);
      lv_obj_t *setting_img = lv_img_create(setting_button);
      lv_img_set_src(setting_img, my_icons[8]);
      lv_obj_set_style_img_recolor_opa(setting_img, 255, 0);
      lv_obj_set_style_img_recolor(setting_img,lv_color_make(255,255,255),0);
      lv_obj_align(setting_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(setting_button, setting_event_cb, LV_EVENT_CLICKED, NULL);

       lv_obj_t *camera_button = lv_btn_create(app_flex);
      lv_obj_set_size(camera_button, 70, 70);
      lv_obj_t *camera_img = lv_img_create(camera_button);
      lv_img_set_src(camera_img, my_icons[9]);
      lv_obj_set_style_img_recolor_opa(camera_img, 255, 0);
      lv_obj_set_style_img_recolor(camera_img,lv_color_make(255,255,255),0);
      lv_obj_align(camera_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(camera_button, camera_event_cb, LV_EVENT_CLICKED, NULL);

       lv_obj_t *timer_button = lv_btn_create(app_flex);
      lv_obj_set_size(timer_button, 70, 70);
      lv_obj_t *timer_img = lv_img_create(timer_button);
      lv_img_set_src(timer_img, my_icons[10]);
      lv_obj_set_style_img_recolor_opa(timer_img, 255, 0);
      lv_obj_set_style_img_recolor(timer_img,lv_color_make(255,255,255),0);
      lv_obj_align(timer_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(timer_button, timer_event_cb, LV_EVENT_CLICKED, NULL);

       lv_obj_t *weather_button = lv_btn_create(app_flex);
      lv_obj_set_size(weather_button, 70, 70);
      lv_obj_t *weather_img = lv_img_create(weather_button);
      lv_img_set_src(weather_img, my_icons[11]);
      lv_obj_set_style_img_recolor_opa(weather_img, 255, 0);
      lv_obj_set_style_img_recolor(weather_img,lv_color_make(255,255,255),0);
      lv_obj_align(weather_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(weather_button, weather_event_cb, LV_EVENT_CLICKED, NULL);

       lv_obj_t *chatGPT_button = lv_btn_create(app_flex);
      lv_obj_set_size(chatGPT_button, 70, 70);
      lv_obj_t *chatGPT_img = lv_img_create(chatGPT_button);
      lv_img_set_src(chatGPT_img, my_icons[11]);
      lv_obj_set_style_img_recolor_opa(chatGPT_img, 255, 0);
      lv_obj_set_style_img_recolor(chatGPT_img,lv_color_make(255,255,255),0);
      lv_obj_align(chatGPT_img, LV_ALIGN_CENTER, 0, 0);
      lv_obj_add_event_cb(chatGPT_button, chatGPT_event_cb, LV_EVENT_CLICKED, NULL);

      
}
static void steps_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      steps_create_screen();
    }
}
static void heart_rate_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      heart_rate_create_screen();
    }
}
static void spo2_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      spo2_create_screen();
    }
}
static void skin_temp_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      skin_temp_create_screen();
    }
}
static void calculator_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      calculator_create_screen();
    }
}
static void light_control_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      light_control_create_screen();
    }
}
static void music_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      music_create_screen();
    }
}
static void setting_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      setting_create_screen();
    }
}
static void camera_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      camera_create_screen();
    }
}
static void timer_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      timer_create_screen();
    }
}
static void weather_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      weather_create_screen();
    }
}
static void chatGPT_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      chatGPT_create_screen();
    }
}


