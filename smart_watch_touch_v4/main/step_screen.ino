lv_obj_t *step_arc_value;
lv_obj_t *calories_arc_value;
lv_obj_t *distance_arc_value;

int step_s =0 ;
float distance = 0;
int calories = 0;
float prevAcl = 0 , newAcl = 0;

void steps_create_screen()
{
   LV_IMG_DECLARE(steps_icon);
  LV_IMG_DECLARE(calories_icon);
  LV_IMG_DECLARE(distance_icon);

  steps_screen = lv_obj_create(app_screen);
  lv_obj_set_size(steps_screen,tft.width(),tft.height());

  lv_obj_t *step_back_button = lv_btn_create(steps_screen);
  lv_obj_set_size(step_back_button, 26, 26);
  lv_obj_align(step_back_button,LV_ALIGN_TOP_LEFT,0,0);
  lv_obj_add_event_cb(step_back_button, steps_back_event_cb, LV_EVENT_CLICKED, NULL);

   lv_obj_t *step_back_label = lv_label_create(step_back_button);
  lv_label_set_text(step_back_label, LV_SYMBOL_LEFT);
  lv_obj_align(step_back_label, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *step_label = lv_label_create(steps_screen);
  //lv_obj_set_size(step_label, 20, 30);
  lv_label_set_text(step_label, "Pedometer");
  lv_obj_align(step_label, LV_ALIGN_TOP_MID, 0, 0);

  //lv_obj_t *steps_part = lv_arc_create(steps_screen);
  lv_obj_t *steps_arc = lv_arc_create(steps_screen);
  lv_obj_set_size(steps_arc, 120, 120);
  lv_arc_set_rotation(steps_arc, 135);
  lv_arc_set_bg_angles(steps_arc, 0, 270);
  lv_obj_remove_style(steps_arc, NULL, LV_PART_KNOB);
  lv_obj_clear_flag(steps_arc, LV_OBJ_FLAG_CLICKABLE);
  lv_arc_set_value(steps_arc, 30);
  lv_obj_align(steps_arc,LV_ALIGN_CENTER,0,-10);

  lv_obj_t *steps_img = lv_img_create(steps_arc);
  lv_img_set_src(steps_img, &steps_icon);
  lv_obj_set_style_img_recolor_opa(steps_img, 255, 0);
  lv_obj_set_style_img_recolor(steps_img,lv_color_make(255,255,255),0);
  lv_obj_align(steps_img, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *step_arc_label = lv_label_create(steps_arc);
  //lv_obj_set_size(step_arc_label, 20, 30);
  lv_label_set_text(step_arc_label,"steps");
  lv_obj_align(step_arc_label, LV_ALIGN_BOTTOM_MID, 0, -20);

  step_arc_value = lv_label_create(steps_arc);
  //lv_obj_set_size(step_arc_label, 20, 30);
  lv_label_set_text(step_arc_value,"1000");
  lv_obj_align(step_arc_value, LV_ALIGN_BOTTOM_MID, 0, 0);

  lv_obj_t *calories_arc = lv_arc_create(steps_screen);
  lv_obj_set_size(calories_arc, 100, 100);
  lv_arc_set_rotation(calories_arc, 135);
  lv_arc_set_bg_angles(calories_arc, 0, 270);
  lv_obj_remove_style(calories_arc, NULL, LV_PART_KNOB);
  lv_obj_clear_flag(calories_arc, LV_OBJ_FLAG_CLICKABLE);
  lv_arc_set_value(calories_arc, 30);
  lv_obj_align(calories_arc,LV_ALIGN_BOTTOM_LEFT,10,40);

  lv_obj_t *calories_img = lv_img_create(calories_arc);
  lv_img_set_src(calories_img, &calories_icon);
  lv_obj_set_style_img_recolor_opa(calories_img, 255, 0);
  lv_obj_set_style_img_recolor(calories_img,lv_color_make(255,255,255),0);
  lv_obj_align(calories_img, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *calories_arc_label = lv_label_create(calories_arc);
  lv_label_set_text(calories_arc_label,"cal");
  lv_obj_align(calories_arc_label, LV_ALIGN_BOTTOM_MID, 0, -30);

  calories_arc_value = lv_label_create(calories_arc);
  lv_label_set_text(calories_arc_value,"200");
  lv_obj_align(calories_arc_value, LV_ALIGN_BOTTOM_MID, 0, -10);

  lv_obj_t *distance_arc = lv_arc_create(steps_screen);
  lv_obj_set_size(distance_arc, 100, 100);
  lv_arc_set_rotation(distance_arc, 135);
  lv_arc_set_bg_angles(distance_arc, 0, 270);
  lv_obj_remove_style(distance_arc, NULL, LV_PART_KNOB);
  lv_obj_clear_flag(distance_arc, LV_OBJ_FLAG_CLICKABLE);
  lv_arc_set_value(distance_arc, 30);
  lv_obj_align(distance_arc,LV_ALIGN_BOTTOM_RIGHT,-10,40);

  lv_obj_t *distance_img = lv_img_create(distance_arc);
  lv_img_set_src(distance_img, &distance_icon);
  lv_obj_set_style_img_recolor_opa(distance_img, 255, 0);
  lv_obj_set_style_img_recolor(distance_img,lv_color_make(255,255,255),0);
  lv_obj_align(distance_img, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *distance_arc_label = lv_label_create(distance_arc);
  lv_label_set_text(distance_arc_label,"dist");
  lv_obj_align(distance_arc_label, LV_ALIGN_BOTTOM_MID, 0, -30);

  distance_arc_value = lv_label_create(distance_arc);
  lv_label_set_text(distance_arc_value,"100 KM");
  lv_obj_align(distance_arc_value, LV_ALIGN_BOTTOM_MID, 0, -10);

  
}
void steps_back_event_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      if (steps_screen != NULL) {
         lv_obj_del(steps_screen);
       }
    }
}
// static void steps_cal_task() {
//   xTaskCreatePinnedToCore(steps_cal,
//               "steps_cal",
//               4096,
//               NULL,
//               1,
//               &stepsHandler,
//               0);
// }
// void adlx_setup(){

//   adxl.powerOn();
//   //set activity/ inactivity thresholds (0-255)
//   adxl.setActivityThreshold(75); //62.5mg per increment
//   adxl.setInactivityThreshold(75); //62.5mg per increment
//   adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
 
//   //look of activity movement on this axes - 1 == on; 0 == off 
//   adxl.setActivityX(1);
//   adxl.setActivityY(1);
//   adxl.setActivityZ(1);
 
//   //look of inactivity movement on this axes - 1 == on; 0 == off
//   adxl.setInactivityX(1);
//   adxl.setInactivityY(1);
//   adxl.setInactivityZ(1);
 
//   //look of tap movement on this axes - 1 == on; 0 == off
//   adxl.setTapDetectionOnX(0);
//   adxl.setTapDetectionOnY(0);
//   adxl.setTapDetectionOnZ(1);
 
//   //set values for what is a tap, and what is a double tap (0-255)
//   adxl.setTapThreshold(50); //62.5mg per increment
//   adxl.setTapDuration(15); //625us per increment
//   adxl.setDoubleTapLatency(80); //1.25ms per increment
//   adxl.setDoubleTapWindow(200); //1.25ms per increment
 
//   //set values for what is considered freefall (0-255)
//   adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
//   adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
//   //setting all interrupts to take place on int pin 1
//   //I had issues with int pin 2, was unable to reset it
//   adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
//   adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
//   adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
//   adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
//   adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
//   //register interrupt actions - 1 == on; 0 == off  
//   adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
//   adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
//   adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
//   adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
//   adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);

// }


// void steps_cal(void *pvParameters)
// {
//   while(1)
//   {  adlx_setup();
//   int x,y,z;  
//   adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z

//   double xyz[3];
//   double ax,ay,az;
//   adxl.getAcceleration(xyz);
//   ax = xyz[0];
//   ay = xyz[1];
//   az = xyz[2];
//   prevAcl = newAcl;
//   newAcl = sqrt(ax*ax+ay*ay+az*az);
//   float change = newAcl - prevAcl;
//   if (change > .1) step_s++;
//   distance = step_s*.000762;
//   calories = step_s*0.04;
//   Serial.println(step_s);
//    lv_label_set_text_fmt(step_arc_value, "%d", step_s);
//   lv_label_set_text_fmt(calories_arc_value, "%d", calories);
//   lv_label_set_text_fmt(distance_arc_value, "%d", distance);
//   vTaskDelay( 100 / portTICK_PERIOD_MS);
//   }

// }
