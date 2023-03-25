void camera_create_screen()
{
  camera_screen = lv_obj_create(app_screen);
  lv_obj_set_size(camera_screen,tft.width(),tft.height());

  lv_obj_t *camera_back_button = lv_btn_create(camera_screen);
  lv_obj_set_size(camera_back_button, 26, 26);
  lv_obj_align(camera_back_button,LV_ALIGN_TOP_LEFT,0,0);
  lv_obj_add_event_cb(camera_back_button, camera_back_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *camera_back_label = lv_label_create(camera_back_button);
  lv_label_set_text(camera_back_label, LV_SYMBOL_LEFT);
  lv_obj_align(camera_back_label, LV_ALIGN_CENTER, 0, 0);

  
  lv_obj_t *camera_label = lv_label_create(camera_screen);
  lv_label_set_text(camera_label, "Camera");
  lv_obj_align(camera_label, LV_ALIGN_TOP_MID, 0, 0);

  lv_obj_t *camera_click_button = lv_btn_create(camera_screen);
  lv_obj_set_size(camera_click_button, 26, 26);
  lv_obj_align(camera_click_button,LV_ALIGN_CENTER,0,0);
  lv_obj_add_event_cb(camera_click_button, camera_Click_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *camera_click_label = lv_label_create(camera_click_button);
  lv_label_set_text(camera_click_label, "Camera");
  lv_obj_align(camera_click_label, LV_ALIGN_TOP_MID, 0, 0);

}
void camera_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
     lv_obj_del(camera_screen);
    }
}
void camera_Click_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      camera_click_cal();
    }
}
void camera_click_cal()
{
  
}