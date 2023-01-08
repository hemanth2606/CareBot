void setting(){

    drawSdJpeg(screen[3],0,0);

    resetCountbtn();
    delay(10);
    

    while(1){
      
    
    getBtnCount();

    if (backStatus >= 1){
        resetCountbtn();
        drawSdJpeg(screen[0],0,0);
        delay(10);
        return; 
    }
    
    switch(count){

      case 0:
            tft.drawRoundRect(14,34,105,12,5,color2);
            tft.drawRoundRect(14,49,105,12,5,color1);
            tft.drawRoundRect(14,64,105,12,5,color1);
            tft.drawRoundRect(14,79,105,12,5,color1);
            tft.drawRoundRect(14,94,105,12,5,color1);
            tft.drawRoundRect(14,109,105,12,5,color1);
            if(selectStatus >= 1) settingWifi()  ;
            delay(50);
      
              break;
              
      case 1:
            tft.drawRoundRect(14,34,105,12,5,color1);
            tft.drawRoundRect(14,49,105,12,5,color2);
            tft.drawRoundRect(14,64,105,12,5,color1);
            tft.drawRoundRect(14,79,105,12,5,color1);
            tft.drawRoundRect(14,94,105,12,5,color1);
            tft.drawRoundRect(14,109,105,12,5,color1);
            if(selectStatus >= 1) settingTwilio(twilioStatus , 94 , 45);
            delay(50);
      
              break;
      case 2:
            tft.drawRoundRect(14,34,105,12,5,color1);
            tft.drawRoundRect(14,49,105,12,5,color1);
            tft.drawRoundRect(14,64,105,12,5,color2);
            tft.drawRoundRect(14,79,105,12,5,color1);
            tft.drawRoundRect(14,94,105,12,5,color1);
            tft.drawRoundRect(14,109,105,12,5,color1);
//            if(selectStatus >= 1) settingTorch()  ;

            delay(50);

              break;
              
      case 3:
            tft.drawRoundRect(14,34,105,12,5,color1);
            tft.drawRoundRect(14,49,105,12,5,color1);
            tft.drawRoundRect(14,64,105,12,5,color1);
            tft.drawRoundRect(14,79,105,12,5,color2);
            tft.drawRoundRect(14,94,105,12,5,color1);
            tft.drawRoundRect(14,109,105,12,5,color1);
            if(selectStatus >= 1);
            delay(50);
              break;
         
      case 4:
            tft.drawRoundRect(14,34,105,12,5,color1);
            tft.drawRoundRect(14,49,105,12,5,color1);
            tft.drawRoundRect(14,64,105,12,5,color1);
            tft.drawRoundRect(14,79,105,12,5,color1);
            tft.drawRoundRect(14,94,105,12,5,color2);
            tft.drawRoundRect(14,109,105,12,5,color1);
            if(selectStatus >= 1);
            delay(50);
            break;
      case 5:
            tft.drawRoundRect(14,34,105,12,5,color1);
            tft.drawRoundRect(14,49,105,12,5,color1);
            tft.drawRoundRect(14,64,105,12,5,color1);
            tft.drawRoundRect(14,79,105,12,5,color1);
            tft.drawRoundRect(14,94,105,12,5,color1);
            tft.drawRoundRect(14,109,105,12,5,color2);
            if(selectStatus >= 1);
            delay(50);
              break;
      default:
            count = 0;
              break;          
      
    }
    if(count >= 6) count = 0;
      delay(100);
    }
}




void settingWifi(){


    

     if(wifiStatus == true){
        wifiStatus == false;
        WiFi.disconnect();
        drawSdJpeg(icon[0],94,30);
        delay(200);
     }
     else{ 
        wifiStatus = true;
        wifi_on();
        drawSdJpeg(screen[3],0,0);
        drawSdJpeg(icon[1],94,30);
        delay(100);
     } 
      
}


void  settingTwilio(bool &value , int x , int y ){

  selectBtn.resetCount();
    if(value == true){
      value = false;
      drawSdJpeg(icon[0],x,y);
      delay(50);
    }
    else{
      value = true;
      WiFi.disconnect();
      startTwilioSetup();
      
      drawSdJpeg(icon[1],x,y);
      drawSdJpeg(screen[3],0,0);
      delay(50);
    }
    Serial.println("after ");
    Serial.println(value);
    delay(100);

}
  








void startTwilioSetup(){
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(15,15);
  tft.setTextSize(1);
  tft.setTextColor(color2);
  tft.println("Connecting to wifi");
  
  thing.SetWiFi("ASUS_X00TD", "healsou1");
  thing.initDevice();
  Serial.println("Connecting");
  
  
  Serial.println("");
  tft.setCursor(15,30);
  tft.println("Connected to wifi network");
  tft.println(WiFi.localIP());
  
}


void settingTorch(){

  
}

void wifi_on(){
     tft.fillScreen(color1);
     WiFi.begin(ssid, password);
     tft.setCursor(30,30);
     tft.println("Connecting.....");
     while(WiFi.status() != WL_CONNECTED){
        if(backStatus >= 1){
          return;
        }
                     

     }
     tft.fillScreen(color1);
     tft.println("Connected");
     tft.println(WiFi.localIP());
     delay(2000); 
}
