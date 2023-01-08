






void rtc_setup(){



#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
   
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  }

  
}

  
void rtc_loop(){

    
  
    
    resetCountbtn();
    showmax = true;
    
    
     drawSdJpeg(screen[11],0,0);
    while(1){ 
      DateTime now = rtc.now();
   char buf1[] = "hh:mm:ss";

   char date[] = "DD/MM/YYYY";
    getBtnCount();
//  checkalarm(now.toString(buf1));






    if(backStatus >= 1){
      showmax = false;
      
      resetCountbtn();
    drawSdJpeg(screen[0],0,0);
    delay(50);
    return;  
    }
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE,TFT_BLACK);
    tft.setCursor(62,82);
    tft.println(now.toString(buf1));

    tft.setTextColor(TFT_WHITE,TFT_BLACK);
    tft.setCursor(62,32);
    tft.println(now.toString(date));

    
     
    }
}



void alarm(){   
  resetCountbtn();
  drawSdJpeg(screen[10],0,0); 
  delay(100);
  count = 0;

  alarmStatus();
  
    
  while(1){

    getBtnCount();
    

    if (backStatus >= 1){
      
        drawSdJpeg(screen[0],0,0);
        delay(10);
        resetCountbtn();
        return; 
    }
//    Serial.println("alarm");
//    Serial.println(alarm1);
//    Serial.println(select_status);
    

  
   
    switch(count){

      case 0:
              tft.drawRoundRect(13,44,134,20,5,TFT_GREEN);
              tft.drawRoundRect(13,69,134,20,5,TFT_BLACK);
              tft.drawRoundRect(13,94,134,20,5,TFT_BLACK);
              if (selectStatus >= 1) setalarm(alarm1,125,44);
              delay(50);
              
      
              break;
              
      case 1:
              tft.drawRoundRect(13,44,134,20,5,TFT_BLACK);
              tft.drawRoundRect(13,69,134,20,5,TFT_GREEN);
              tft.drawRoundRect(13,94,134,20,5,TFT_BLACK);
              if (selectStatus >= 1) setalarm(alarm2,125,69);
              delay(50);
             
      
      
              break;
      case 2:

              tft.drawRoundRect(13,44,134,20,5,TFT_BLACK);
              tft.drawRoundRect(13,69,134,20,5,TFT_BLACK);
              tft.drawRoundRect(13,94,134,20,5,TFT_GREEN);
              if (selectStatus >= 1) setalarm(alarm3, 125,94);
              delay(50);

      

              break;
      default:
            buttonBtn.resetCount();
            break;
    
 
    
  }
 


  if(count >= 3) resetCountbtn();
   

  
}
}
















void setalarm(bool &value ,int x , int y){
//    Serial.println("inside loop");
//    Serial.println(value);
  selectBtn.resetCount();
    if(value == true){
      value = false;
      drawSdJpeg(icon[0],x,y);
      delay(50);
    }
    else{
      value = true;
     
      drawSdJpeg(icon[1],x,y);
      delay(50);
    }
    Serial.println("after ");
    Serial.println(value);
    delay(100);

}



void alarmStatus(){    // set status based icons 

  alarm1 == true ? drawSdJpeg(icon[1],125,44) : drawSdJpeg(icon[0],125,44);
  alarm2 == true ? drawSdJpeg(icon[1],125,69) : drawSdJpeg(icon[0],125,69);
  alarm3 == true ? drawSdJpeg(icon[1], 125 ,94): drawSdJpeg(icon[0],125,94);
  
}






void checkalarm(String  presentTime){
      Serial.println(presentTime);
 

    if((presentTime == alarm1_time && alarm1 == true) || (presentTime == alarm2_time && alarm2 == true ) || (presentTime == alarm3_time && alarm3 == true)){
        tone(buzzer ,1000);
        delay(100);
        noTone(buzzer);
        delay(100);
           
    }   
}
