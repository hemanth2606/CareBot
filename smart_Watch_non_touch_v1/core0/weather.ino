
//String openWeatherMapApiKey = "839f20e9c7b780adb3f5e21180e449a2";
//
//
//String city = "Bengaluru";
//String countryCode = "IN";
//// weather related variables
//
//JSONVar feels_like;
//JSONVar description;
//JSONVar humidity ;
//JSONVar pressure;
//JSONVar wind;
//JSONVar visibility;
//JSONVar temp_max;
//JSONVar temp_min;
//
//
//
//unsigned long lastTime = 0;
//// Timer set to 10 minutes (600000)
////unsigned long timerDelay = 600000;
//// Set timer to 10 seconds (10000)
//
//
//String jsonBuffer;
//
void weather_setup() {

  config.database_url = DATABASE_URL;

  
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  //Or use legacy authenticate method
  //config.database_url = DATABASE_URL;
  //config.signer.tokens.legacy_token = "<database secret>";

 
  Firebase.begin(&config, &auth);

  //Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);
  
  tft.fillScreen(TFT_BLACK);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  tft.setCursor(15,15);
  tft.setTextSize(1);
  tft.setTextColor(color2);
  tft.println("Connecting to wifi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    getBtnCount();
    if(backStatus >= 1){
      return;
      drawSdJpeg(screen[0],0,0);
    }
  }
  Serial.println("");
  tft.setCursor(15,30);
  tft.println("Connected to wifi network");
  tft.println(WiFi.localIP());
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}
//
//
//
//
//
//void weather_loop() {
//
//  
//  weather_setup();
//  drawSdJpeg(screen[8],0,0);
//
//  delay(100);
//  
//  while(1){
//     
//     getBtnCount();
////    Serial.print("back pin");
////    Serial.println(backStatus);
//    if(backStatus >= 1){
//      resetCountbtn();
//      drawSdJpeg(screen[0],0,0);
//      delay(100);
//    return;
//    }
//  // Send an HTTP GET request
//  if ((millis() - lastTime) > timerDelay) {
//    timerDelay = 300000;
//    // Check WiFi connection status
//    if(WiFi.status()== WL_CONNECTED){
//      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;
//      
//      jsonBuffer = httpGETRequest(serverPath.c_str());
//      Serial.println(jsonBuffer);
//      JSONVar myObject = JSON.parse(jsonBuffer);
//  
//      // JSON.typeof(jsonVar) can be used to get the type of the var
//      if (JSON.typeof(myObject) == "undefined") {
//        Serial.println("Parsing input failed!");
//        return;
//      }
//    
//     
////      Serial.print("Temperature: ");
////      Serial.println(myObject["main"]["temp"]);
////      Serial.print("Pressure: ");
////      Serial.println(myObject["main"]["pressure"]);
////      Serial.print("Humidity: ");
////      Serial.println(myObject["main"]["humidity"]);
////      
////      Serial.print("Clouds: ");
////    
////      Serial.println(myObject["weather"][0]["main"]);
//
//
//
//      //Actual temperature 
//
//     temp =  myObject["main"]["temp"];
//     tft.setCursor(10,62);
//     tft.setTextSize(1);
//     tft.setTextColor(TFT_WHITE,TFT_BLACK);
//     tft.print(temp);
//
//
//     // feels like temperature
//     feels_like = myObject["main"]["feels_like"];
//     tft.setCursor(14,78);
//     tft.setTextSize(1);
//     tft.setTextColor(TFT_GREEN,TFT_BLACK);
//     tft.println(feels_like);
//     
//
//    // description 
//    description = myObject["weather"][0]["description"];
//    tft.setCursor(12,110);
//    tft.setTextSize(1);
//    tft.setTextColor(TFT_WHITE,TFT_BLACK);
//    tft.println(description);
//     
//     //humidity 
//     humidity = myObject["main"]["humidity"];
//     tft.setCursor(113,25);
//     tft.setTextSize(1);
//     tft.setTextColor(TFT_WHITE,TFT_BLACK);
//     tft.println(humidity);
//
//     // pressure
//      pressure = myObject["main"]["pressure"];
//      tft.setCursor(113,40);
//      tft.setTextSize(1);
//      tft.setTextColor(TFT_WHITE,TFT_BLACK);
//      tft.println(pressure);
//
//      // wind 
//      wind = myObject["wind"]["speed"];
//      tft.setCursor(113,55);
//      tft.setTextSize(1);
//      tft.setTextColor(TFT_WHITE,TFT_BLACK);
//      tft.println(wind);
//
//
//      //visibilty 
//      visibility = myObject["visibility"];
//      tft.setCursor(113,70);
//      tft.setTextSize(1);
//      tft.setTextColor(TFT_WHITE,TFT_BLACK);
//      tft.println(visibility);
//
//
//      //temp min
//      temp_min = myObject["main"]["temp_min"];
//       tft.setCursor(113,100);
//      tft.setTextSize(1);
//      tft.setTextColor(TFT_WHITE,TFT_BLACK);
//      tft.println(temp_min);
//
//      // temp max
//      temp_max = myObject["main"]["temp_max"];
//       tft.setCursor(113,85);
//      tft.setTextSize(1);
//      tft.setTextColor(TFT_WHITE,TFT_BLACK);
//      tft.println(temp_max);
//
//
//      
//     
//      
//    }
//    
//    else {
//      timerDelay = 5000;
//     
//     if(backStatus >= 1){
//      resetCountbtn();
//      drawSdJpeg(screen[0],0,0);
//      delay(100);
//    return;
//    } 
//
//     // actual temperature
//     tft.setCursor(10,62);
//     tft.setTextSize(1);
//     tft.setTextColor(TFT_WHITE,TFT_BLACK);
//     tft.print(temp);
//
//
//     // feels like temperature
//    
//     tft.setCursor(14,78);
//     tft.setTextSize(1);
//     tft.setTextColor(TFT_GREEN,TFT_BLACK);
//     tft.println(feels_like);
//     
//
//    // description  
//    tft.setCursor(12,110);
//    tft.setTextSize(1);
//    tft.setTextColor(TFT_WHITE,TFT_BLACK);
//    tft.println(description);
//     
//     //humidity 
//    
//     tft.setCursor(113,25);
//     tft.setTextSize(1);
//     tft.setTextColor(TFT_WHITE,TFT_BLACK);
//     tft.println(humidity);
//
//     // pressure
//    
//      tft.setCursor(113,40);
//      tft.setTextSize(1);
//      tft.setTextColor(TFT_WHITE,TFT_BLACK);
//      tft.println(pressure);
//
//      // wind 
//     
//      tft.setCursor(113,55);
//      tft.setTextSize(1);
//      tft.setTextColor(TFT_WHITE,TFT_BLACK);
//      tft.println(wind);
//
//
//      //visibilty 
//     
//      tft.setCursor(113,70);
//      tft.setTextSize(1);
//      tft.setTextColor(TFT_WHITE,TFT_BLACK);
//      tft.println(visibility);
//
//
//      //temp min
//  
//       tft.setCursor(113,100);
//      tft.setTextSize(1);
//      tft.setTextColor(TFT_WHITE,TFT_BLACK);
//      tft.println(temp_min);
//
//      // temp max
//     
//       tft.setCursor(113,85);
//      tft.setTextSize(1);
//      tft.setTextColor(TFT_WHITE,TFT_BLACK);
//      tft.println(temp_max);
//    }
//    lastTime = millis();
//  }
//
//  }
//
// 
//}
//
//
//
//
//
//
//
//String httpGETRequest(const char* serverName) {
//  WiFiClient client;
//  HTTPClient http;
//    
//  // Your Domain name with URL path or IP address with path
//  http.begin(client, serverName);
//  
//  // Send HTTP POST request
//  int httpResponseCode = http.GET();
//  
//  String payload = "{}"; 
//  
//  if (httpResponseCode>0) {
//    Serial.print("HTTP Response code: ");
//    Serial.println(httpResponseCode);
//    payload = http.getString();
//  }
//  else {
//    Serial.print("Error code: ");
//    Serial.println(httpResponseCode);
//  }
//  // Free resources
//  http.end();
//
//  return payload;
//}
