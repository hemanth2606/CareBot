uint32_t irBuffer[100]; //infrared LED sensor data
uint32_t redBuffer[100];  //red LED sensor data
int32_t bufferLength; //data length
int32_t spo2; //SPO2 value
int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
int32_t heartRate; //heart rate value
int8_t validHeartRate; //indicator to show if the heart rate calculation is valid

byte pulseLED = 11; //Must be on PWM pin
byte readLED = 13; //Blinks with each data read

lv_obj_t *spo2_arc_value;

void spo2_create_screen()
{
   LV_IMG_DECLARE(spo2_icon);
  spo2_screen = lv_obj_create(app_screen);
  lv_obj_set_size(spo2_screen,tft.width(),tft.height());

  lv_obj_t *spo2_back_button = lv_btn_create(spo2_screen);
  lv_obj_set_size(spo2_back_button, 26, 26);
  lv_obj_align(spo2_back_button,LV_ALIGN_TOP_LEFT,0,0);
  lv_obj_add_event_cb(spo2_back_button, spo2_back_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *spo2_back_label = lv_label_create(spo2_back_button);
  lv_label_set_text(spo2_back_label, LV_SYMBOL_LEFT);
  lv_obj_align(spo2_back_label, LV_ALIGN_CENTER, 0, 0);

  
  lv_obj_t *spo2_label = lv_label_create(spo2_screen);
  //lv_obj_set_size(step_label, 20, 30);
  lv_label_set_text(spo2_label, "SPO2");
  lv_obj_align(spo2_label, LV_ALIGN_TOP_MID, 0, 0);

   lv_obj_t *spo2_arc = lv_arc_create(spo2_screen);
  lv_obj_set_size(spo2_arc, 100, 100);
  lv_arc_set_rotation(spo2_arc, 270);
    lv_arc_set_bg_angles(spo2_arc, 0, 360);
  lv_obj_remove_style(spo2_arc, NULL, LV_PART_KNOB);
  lv_obj_clear_flag(spo2_arc, LV_OBJ_FLAG_CLICKABLE);
  lv_arc_set_value(spo2_arc, 100);
  lv_obj_align(spo2_arc,LV_ALIGN_CENTER,0,-20);

  lv_obj_t *spo2_img = lv_img_create(spo2_arc);
  lv_img_set_src(spo2_img, &spo2_icon);
  lv_obj_set_style_img_recolor_opa(spo2_img, 255, 0);
  lv_obj_set_style_img_recolor(spo2_img,lv_color_make(255,255,255),0);
  lv_obj_align(spo2_img, LV_ALIGN_CENTER, 0, 0);

  spo2_arc_value = lv_label_create(spo2_screen);
  lv_label_set_text(spo2_arc_value,"80 %");
  lv_obj_align(spo2_arc_value, LV_ALIGN_BOTTOM_MID, 0, -46);

  lv_obj_t *spo2_cal_button = lv_btn_create(spo2_screen);
  lv_obj_set_size(spo2_cal_button, 100, 40);
  lv_obj_align(spo2_cal_button,LV_ALIGN_BOTTOM_MID,0,0);
  lv_obj_add_event_cb(spo2_cal_button, spo2_cal_event_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *spo2_cal_label = lv_label_create(spo2_cal_button);
  lv_label_set_text(spo2_cal_label, "Calculate");
  lv_obj_align(spo2_cal_label, LV_ALIGN_CENTER, 0, 0);

}
void spo2_back_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
      if (spo2_screen != NULL) {
        if (spo2Handler != NULL) {
          vTaskDelete(spo2Handler);
          spo2Handler = NULL;
          particleSensor.shutDown();
        }
         lv_obj_del(spo2_screen);
       }
    }
}

void spo2_cal_event_cb(lv_event_t* e)
{
   lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        if (spo2Handler == NULL) {

            spo2_cal_task();

        }
     
    }
}

static void spo2_cal_task() {
  xTaskCreatePinnedToCore(spo2_cal,
              "spo2_cal",
              4096,
              NULL,
              2,
              &spo2Handler,
              1);
}

static void spo2_cal(void *pvParameters)
{
  pinMode(pulseLED, OUTPUT);
  pinMode(readLED, OUTPUT);

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    //error code

    while (1);
  }

  while (Serial.available() == 0) ; //wait until user presses a key
  Serial.read();

  byte ledBrightness = 60; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 4096; //Options: 2048, 4096, 8192, 16384
  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings


    bufferLength = 100; //buffer length of 100 stores 4 seconds of samples running at 25sps

  //read the first 100 samples, and determine the signal range
  for (byte i = 0 ; i < bufferLength ; i++)
  {
    while (particleSensor.available() == false) //do we have new data?
      particleSensor.check(); //Check the sensor for new data

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample(); //We're finished with this sample so move to next sample

    // Serial.print(F("red="));
    // Serial.print(redBuffer[i], DEC);
    // Serial.print(F(", ir="));
    // Serial.println(irBuffer[i], DEC);
  }

  //calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

  //Continuously taking samples from MAX30102.  Heart rate and SpO2 are calculated every 1 second
  while (1)
  {
    //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
    for (byte i = 25; i < 100; i++)
    {
      redBuffer[i - 25] = redBuffer[i];
      irBuffer[i - 25] = irBuffer[i];
    }

    //take 25 sets of samples before calculating the heart rate.
    for (byte i = 75; i < 100; i++)
    {
      while (particleSensor.available() == false) //do we have new data?
        particleSensor.check(); //Check the sensor for new data

      digitalWrite(readLED, !digitalRead(readLED)); //Blink onboard LED with every data read

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample

      //send samples and calculation result to terminal program through UART
      // Serial.print(F("red="));
      // Serial.print(redBuffer[i], DEC);
      // Serial.print(F(", ir="));
      // Serial.print(irBuffer[i], DEC);

      // Serial.print(F(", HR="));
      // Serial.print(heartRate, DEC);

      // Serial.print(F(", HRvalid="));
      // Serial.print(validHeartRate, DEC);

      // Serial.print(F(", SPO2="));
      // Serial.print(spo2, DEC);

      // Serial.print(F(", SPO2Valid="));
      //println(validSPO2, DEC);
      lv_label_set_text_fmt(spo2_arc_value, "%d",validSPO2);
    }
    //After gathering 25 new samples recalculate HR and SP02
     maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
  }
}