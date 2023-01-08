



void weather(){


    weather_setup();
    bool run1 = true;
    drawSdJpeg(screen[8],0,0);
   resetCountbtn();
    while(run1){

      getBtnCount();


      if(backStatus >= 1){

          drawSdJpeg(screen[0],0,0);
          delay(100);
          resetCountbtn();
          

        return;
      }
      
     if(Firebase.ready()){
      // actual temperature
     temp =   Firebase.RTDB.getFloat(&fbdo, "/weatherData/temp") ? String(fbdo.to<float>()).c_str() : "NA";
     
     tft.setCursor(10,62);
     tft.setTextSize(1);
     tft.setTextColor(TFT_WHITE,TFT_BLACK);
     tft.print(temp); 

      // feels like temperature
      
     feels_like =  Firebase.RTDB.getFloat(&fbdo, "/weatherData/feels_like") ? String(fbdo.to<float>()).c_str() : "NA";
     tft.setCursor(14,78);
     tft.setTextSize(1);
     tft.setTextColor(TFT_GREEN,TFT_BLACK);
     tft.println(feels_like);

         
     //humidity 
     
     humidity =  Firebase.RTDB.getFloat(&fbdo, "/weatherData/humidity") ? String(fbdo.to<float>()).c_str() : "NA";
     tft.setCursor(113,25);
     tft.setTextSize(1);
     tft.setTextColor(TFT_WHITE,TFT_BLACK);
     tft.println(humidity);

     // pressure
      pressure =  Firebase.RTDB.getFloat(&fbdo, "/weatherData/pressure") ? String(fbdo.to<float>()).c_str() : "NA";
      tft.setCursor(113,40);
      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE,TFT_BLACK);
      tft.println(pressure);

      // wind 
      wind =  Firebase.RTDB.getFloat(&fbdo, "/weatherData/wind") ? String(fbdo.to<float>()).c_str() : "NA";
      tft.setCursor(113,55);
      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE,TFT_BLACK);
      tft.println(wind);


      //visibilty 
      visibility =  Firebase.RTDB.getFloat(&fbdo, "/weatherData/visibility") ? String(fbdo.to<float>()).c_str() : "NA";
      tft.setCursor(113,70);
      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE,TFT_BLACK);
      tft.println(visibility);


      //temp min
      temp_min =  Firebase.RTDB.getFloat(&fbdo, "/weatherData/temp_min") ? String(fbdo.to<float>()).c_str() : "NA";
       tft.setCursor(113,100);
      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE,TFT_BLACK);
      tft.println(temp_min);

      // temp max
      temp_max =  Firebase.RTDB.getFloat(&fbdo, "/weatherData/temp_max") ? String(fbdo.to<float>()).c_str() : "NA";
       tft.setCursor(113,85);
      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE,TFT_BLACK);
      tft.println(temp_max);

     }
     
  
}

}
