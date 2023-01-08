

void coreOneTask(void *parameter){
    rtc_setup();
    adlx_setup();
    while(1){
//    Serial.println(" core0");
    
  if(twilioStatus){
      thing.Handle(); 
  }
    

    
    if(!showtimings){
    char buf2[] = "hh:mm";
    DateTime z = rtc.now();
    checkalarm(z.toString(buf2));
    }                 
    if(!showmax){
    pedometer_loop();
                 
    } 



    
}
}

void Status(){

      resetCountbtn();
      drawSdJpeg(screen[5],0,0);
     while(1){

      getBtnCount();

      
      if(backStatus >= 1){
        resetCountbtn();  
        drawSdJpeg(screen[0],0,0);
        delay(10);
        return;
        
        }

      // print steps 
      tft.setCursor(101,10);
      tft.setTextColor(TFT_WHITE,TFT_BLACK);
      tft.setTextSize(1);
      tft.println(steps);



      



      //print distance 
        tft.setCursor(101,58);
      tft.setTextColor(TFT_WHITE,TFT_BLACK);
      tft.setTextSize(1);
      tft.println(distance);




      // print  calories 
        tft.setCursor(101,102);
      tft.setTextColor(TFT_WHITE,TFT_BLACK);
      tft.setTextSize(1);
      tft.println(calories);

      
        
      
     }



  
}

void adlx_setup(){



    adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
 
  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
 
  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625us per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
  //setting all interrupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  //register interrupt actions - 1 == on; 0 == off  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);

}





void pedometer_loop(){



  int x,y,z;  
  adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z


  
  double xyz[3];
  double ax,ay,az;
  adxl.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];

  Serial.print(ax);
  Serial.print(" ");
  Serial.print(ay);
  Serial.print(" ");
  Serial.println(az);
  prevAcl = newAcl;
  newAcl = sqrt(ax*ax+ay*ay+az*az);
  Serial.print("acceleration");

  float change = newAcl - prevAcl;
  

  if (change > .1) steps++;

  distance = steps*.000762;
  calories = steps*0.04;

  Serial.print("steps");
  Serial.println(steps);
  delay(500);
}



// netwroking 


// whatsapp 


void whatsapp(){

    resetCountbtn();
    drawSdJpeg(screen[7],0,0);

    while(1){
        getBtnCount();
    if (backStatus >= 1) {
          
    drawSdJpeg(screen[0],0,0);
    delay(100);
    resetCountbtn(); 
    return;
  }


  switch(count){

      case 0: 
       if(selectStatus >= 1) setalarm(twilioStatus , 100 , 100); 
      break ;

      default:
            selectBtn.resetCount();   
  }

  
  if(selectStatus >= 1){   
  } 
    }  
}








String HandleResponse(String query)
{

    if(query == "send report "){
      String message = "Heart rate is " + String(beatAvg) + "\n" + "oxygen level : " + String(spo2) + "\n" + "Number of steps :" + String(steps) + "\n" + "Number of distance :" + String(distance) + "\n" + "Number of calories " + String(calories) + "\n" ;  
      return message ;
      
    }
    
    else if(query == "start process"){
      
      return "processing";
    }

    else if(query == "test"){
      return "test";
    }

    else if(query.toInt() == 1){
    
      delay(10);
      return  "hello";
    }
   
    else
        return "Your query was invalid..";
}
