
#define MAX_BRIGHTNESS 255


void heartMenu(){

  resetCountbtn();
  drawSdJpeg(screen[12],0,0);
  delay(100);
  showmax = true;
 
  while(1){  


  getBtnCount();


  if (backStatus >= 1) {
//    particleSensor.shutDown();
    drawSdJpeg(screen[0],0,0);
    delay(100);
    resetCountbtn();
//    showmax = false;
   
    return;
  }
  
  Serial.println("heartRate option");
//  Serial.println(count);
//  Serial.print(select_status);


  delay(10);

  switch (count){

      case 0:
          tft.drawRoundRect(12,26,101,25,5,TFT_GREEN);
          tft.drawRoundRect(12,64,100,25,5,TFT_BLACK);
          if( selectStatus >= 1) heartRate_loop();
          break;

      case 1:
          tft.drawRoundRect(12,64,100,25,5,TFT_GREEN);
          tft.drawRoundRect(12,26,101,25,5,TFT_BLACK);
          if(selectStatus >= 1) spo2Value() ; 
          break;

      default:
          buttonBtn.resetCount();
          break;
  }
   
}
}


void max_setup()
{
 

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

  
}

void heartRate_loop()
{
  
  resetCountbtn();
  drawSdJpeg(screen[9],0,0);
  delay(50);
  max_setup();
  bool runHeart = true;
 
//  
  DateTime now = rtc.now();
   
  int startTime = now.unixtime();
  
  while(runHeart){

    getBtnCount();


    DateTime now = rtc.now(); 
    int presentTime = now.unixtime();
   
    if( presentTime - startTime >= 45  ) 
    runHeart = false;


    // print count down message
    tft.setCursor(40,40);
    tft.setTextSize(1);
    tft.setTextColor(color1,sColor);
    tft.println("Count Down time");


    
    tft.setCursor(50,50);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(1);
    tft.println(45 - (presentTime - startTime));
//    tft.println(presentTime);
//    tft.println(now.unixtime() ) ;

    
    if(backStatus >= 1){
    drawSdJpeg(screen[12],0,0);
    delay(100);
    resetCountbtn();
    return;
   }
  long irValue = particleSensor.getIR();
  if(irValue <= 0){
    irValue = 100;
  }
  
  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);
    
    
    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  Serial.print("IR=");
 // tft.println(irValue);
  Serial.print(irValue);
  Serial.print(", BPM=");
//  tft.println(beatsPerMinute);
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
 // tft.println(beatAvg);
  Serial.print(beatAvg);
    String heartrate = String(beatAvg);
    if(beatAvg <= 99){
      heartrate = "0" + String(beatAvg);
    }
   
    
     tft.setCursor(72,109);
     tft.setTextSize(2);
     tft.setTextColor(TFT_WHITE,TFT_BLACK);
     tft.print(heartrate);

  if (irValue < 50000){

    tft.setCursor(36,88);
    tft.setTextSize(1);
    tft.setTextColor(TFT_RED,TFT_BLACK);
    tft.print("Not detected");
    DateTime now = rtc.now();
    startTime = now.unixtime();
//    
    
    Serial.print("Not detected");

  }
  

  else{
    tft.setCursor(36,88);
    tft.setTextSize(1);
     tft.setTextColor(TFT_GREEN,TFT_BLACK);
     tft.print("detected    ");
    
     
     
  }
  Serial.println();


  }




  while(1){
    
    getBtnCount();

    // vanish count down time 
    
      // print count down message
    tft.setCursor(40,40);
    tft.setTextSize(1);
    tft.setTextColor(color1,sColor);
    tft.println("               ");


    
    tft.setCursor(50,50);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(1);
    tft.println(" ");


    // vanish message regaring detected status 


    tft.setCursor(72,109);
    tft.setTextColor(color1,color1);
    tft.setTextSize(1);
    tft.println("           ");

    
      
    if(backStatus >= 1){
    drawSdJpeg(screen[12],0,0);
    delay(100);
    resetCountbtn();
    return;
   }


    
  }


  
  
}



void Spo2_setup(){


   if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println(F("MAX30105 was not found. Please check wiring/power."));
    while (1);
  }

  Serial.println(F("Attach sensor to finger with rubber band. Press any key to start conversion"));
//  while (Serial.available() == 0) ; //wait until user presses a key
//  Serial.read();

  byte ledBrightness = 60; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings


  
}


void spo2Value(){
    String spo2Modified;
   resetCountbtn();
   drawSdJpeg(screen[2],0,0);
   Spo2_setup();
   delay(10);
   while(1){


    getBtnCount();
  if(backStatus >= 1){
      drawSdJpeg(screen[12],0,0);
      delay(100);
      return;
}


     bufferLength = 100; //buffer length of 100 stores 4 seconds of samples running at 25sps
      for (byte i = 0 ; i < bufferLength ; i++)
  {
    while (particleSensor.available() == false) //do we have new data?
      particleSensor.check(); //Check the sensor for new data

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample(); //We're finished with this sample so move to next sample

  }

   maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
    
   while (1)
  {


     getBtnCount();
  if(backStatus >= 1){
      drawSdJpeg(screen[12],0,0);
       resetCountbtn();
      delay(100);
      return;
}
    //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
    for (byte i = 25; i < 100; i++)
    {
      redBuffer[i - 25] = redBuffer[i];
      irBuffer[i - 25] = irBuffer[i];
    }

    //take 25 sets of samples before calculating the heart rate.
    for (byte i = 75; i < 100; i++)
    {

          getBtnCount();
      if(backStatus >= 1){
          resetCountbtn();
      drawSdJpeg(screen[12],0,0);
      delay(100);
    
      return;
}
      while (particleSensor.available() == false) //do we have new data?
        particleSensor.check(); //Check the sensor for new data

//      digitalWrite(readLED, !digitalRead(readLED)); //Blink onboard LED with every data read

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample

      //send samples and calculation result to terminal program through UART
     if(spo2 <= 9){
       spo2Modified = "0" + String(spo2Modified); 
     }
     else spo2Modified = String(spo2);

     // tft.setCursor(28,94);
      
      if(spo2 == -999) {
        tft.setTextColor(TFT_WHITE , TFT_BLACK);
        tft.setTextSize(1);
        tft.setTextColor(TFT_RED,color1);
        tft.setCursor(80,115);
        String error = "data not found";
        tft.println(error);
      }
      else{
      tft.setCursor(80,115);
      tft.setTextColor(TFT_GREEN , color1);
      tft.setTextSize(1);
      tft.println("data found     ");
      tft.setCursor(107,105);
      tft.setTextColor(TFT_WHITE,color1);
      tft.print(spo2Modified);
      }
      Serial.print(F(", SPO2="));
      Serial.println(spo2, DEC);

    }

    //After gathering 25 new samples recalculate HR and SP02
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
  }
 
  
     
   }

}





void temperature(){
  max_setup();
  particleSensor.setup(0);
  particleSensor.enableDIETEMPRDY();
  resetCountbtn();
  drawSdJpeg(screen[6],0,0);

  showmax = true;
  while(1){
     
     getBtnCount();

  if( backStatus >= 1)
  {

      drawSdJpeg(screen[0],0,0);
      resetCountbtn();
      delay(100);
      return;
  }

    float temperature = particleSensor.readTemperature();

    tft.setCursor(65,100);
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLUE,TFT_BLACK);
    tft.print(temperature);

  }
}
