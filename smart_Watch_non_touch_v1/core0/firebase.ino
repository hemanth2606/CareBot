





void firebaseSetup()
{

  Serial.begin(115200);

  WiFi.begin(ssid,password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h



  Firebase.begin(&config, &auth);

  
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);


}


void soil(){
  resetCountbtn();
  drawSdJpeg(screen[4],0,0);
  String x;

  showmax = true;
  firebaseSetup();

while(1){
  

   if (Firebase.ready())
  {
     x = Firebase.RTDB.getFloat(&fbdo, "/commonData/soil/") ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str();
     tft.setCursor(93,93);
     tft.setTextColor(TFT_WHITE,TFT_BLACK);
     tft.setTextSize(1);
     tft.println(x);
     
     
     Serial.println(x); 
      
}

    
  
   getBtnCount();
    if(backStatus >= 1){
        resetCountbtn();
        drawSdJpeg(screen[0],0,0);
        delay(100);
        return;
      }
  
}
  
}









void updateValuesToFirebase(){

      
  
   
    // update haert rate 
   Firebase.RTDB.setInt(&fbdo, "/commonData/heartRate", beatAvg) ;

   // update spo2
   Firebase.RTDB.setInt(&fbdo,"/commonData/spo2", spo2) ; 

  // update steps
   Firebase.RTDB.setInt(&fbdo, "/commonData/steps", steps);

   // update distance
   Firebase.RTDB.setFloat(&fbdo , "/commonData/distance" , distance);

   // update calories
   Firebase.RTDB.setFloat(&fbdo , "/commonData/calories" , calories);

}
