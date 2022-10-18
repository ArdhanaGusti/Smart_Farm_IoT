#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include "DHT.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#define DHTPIN 4
#define USE_SERIAL Serial
#define relay 12
#define relay2 13
#define relay3 14
#define relay4 27
#define DHTTYPE DHT11
#define SensorPin 34
#define Offset 0.00
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40
#define TdsSensorPin 32 
int pHArray[ArrayLenth];
int pHArrayIndex=0;
#define VREF 3.3      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point
int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;
float hasiltds;
float persenjar;
const int trigPin = 5;
const int echoPin = 18;
const char* ssid     = "Student - Pradita Dirgantara";
const char* password = "kissdulu";
float y;
long duration;
int distance,neken=0;
bool adaan=HIGH;
bool toad=true,doat=false;
int pay;

const char* host = "sql308.epizy.com";
WiFiMulti wifiMulti;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
    Serial.begin(115200);
    lcd.init(); 
    lcd.backlight();
    delay(10);
    pinMode(relay, OUTPUT);
    pinMode(relay4, OUTPUT);
    pinMode(relay2, OUTPUT);
    pinMode(relay3, OUTPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);
    pinMode(echoPin, INPUT);
    pinMode(TdsSensorPin,INPUT);
    pinMode(SensorPin,INPUT);
    pinMode(26, INPUT); //Sensor multiplexer
    pinMode(25, INPUT); //Sensor multiplexer2
    pinMode(23, OUTPUT); //buzzer
    Wire.begin();
    dht.begin();
    digitalWrite(relay, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, HIGH);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, NULL);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    wifiMulti.addAP("Student - Pradita Dirgantara", NULL);
    lcd.clear();
}
int value = 0;

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}

int getMedianNum(int bArray[], int iFilterLen)
{
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++)
  {
    for (i = 0; i < iFilterLen - j - 1; i++)
    {
      if (bTab[i] > bTab[i + 1])
      {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}

void loop()
{   
    if((wifiMulti.run() == WL_CONNECTED)) {

       HTTPClient http3;
            
       USE_SERIAL.print("[HTTP] begin...\n");
       http3.begin("http://farm.sma.praditadirgantara.sch.id/pup.php?id=4"); //HTTP
            
       USE_SERIAL.print("[HTTP] GET...\n");
                    // start connection and send HTTP header
                    int httpCode3 = http3.GET();
            
                    // httpCode will be negative on error
                    if(httpCode3 > 0) {
                        // HTTP header has been send and Server response header has been handled
                        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode3);
                        
                        // file found at server
                        if(httpCode3 == HTTP_CODE_OK) {
                            String payload3 = http3.getString();
                            if(payload3 == "1"){
                  if((wifiMulti.run() == WL_CONNECTED)) {
                    neken+=100;
                    HTTPClient http4;
            
                    USE_SERIAL.print("[HTTP] begin...\n");
                    // configure traged server and url
                    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS

                    String url = "http://farm.sma.praditadirgantara.sch.id/vit.php?id=4&vit=";
                           url += neken;
                    http4.begin(url); //HTTP
            
                    USE_SERIAL.print("[HTTP] GET...\n");
                    // start connection and send HTTP header
                    int httpCode4 = http4.GET();
            
                    // httpCode will be negative on error
                    if(httpCode4 > 0) {
                        // HTTP header has been send and Server response header has been handled
                        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode4);
                        
                        // file found at server
                        if(httpCode4 == HTTP_CODE_OK) {
                            String payload4 = http4.getString();
                            USE_SERIAL.println(payload4);
                            USE_SERIAL.println(neken);
                        }
                    } else {
                        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http4.errorToString(httpCode4).c_str());
                    }
            
                    http4.end();
                }
                              digitalWrite(relay3, LOW);
                              digitalWrite(relay4, LOW);
                              delay(12000);
                              if((wifiMulti.run() == WL_CONNECTED)) {

       HTTPClient http2;
            
       USE_SERIAL.print("[HTTP] begin...\n");
       http2.begin("http://farm.sma.praditadirgantara.sch.id/pupuk.php?id=4&pupuk=0"); //HTTP
            
       USE_SERIAL.print("[HTTP] GET...\n");
                    // start connection and send HTTP header
                    int httpCode2 = http2.GET();
            
                    // httpCode will be negative on error
                    if(httpCode2 > 0) {
                        // HTTP header has been send and Server response header has been handled
                        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode2);
                        
                        // file found at server
                        if(httpCode2 == HTTP_CODE_OK) {
                            String payload2 = http2.getString();
                            USE_SERIAL.print(payload2);
                        }
                    } else {
                        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http2.errorToString(httpCode2).c_str());
                    }
            
                    http2.end();
                }
                            }
                            else{
                              digitalWrite(relay, HIGH);
                              digitalWrite(relay4, HIGH);
                            }
                        }
                    } else {
                        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http3.errorToString(httpCode3).c_str());
                    }
                    http3.end();
                }
    
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        http.begin("http://farm.sma.praditadirgantara.sch.id/mt.php?id=4"); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
                if(payload == "1"){
                  digitalWrite(relay, LOW);
                  delay(25000);
                  if((wifiMulti.run() == WL_CONNECTED)) {

                    HTTPClient http2;
            
                    USE_SERIAL.print("[HTTP] begin...\n");
                    // configure traged server and url
                    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
                    http2.begin("http://farm.sma.praditadirgantara.sch.id/mot.php?id=4&mot=0"); //HTTP
            
                    USE_SERIAL.print("[HTTP] GET...\n");
                    // start connection and send HTTP header
                    int httpCode2 = http2.GET();
            
                    // httpCode will be negative on error
                    if(httpCode2 > 0) {
                        // HTTP header has been send and Server response header has been handled
                        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode2);
            
                        // file found at server
                        if(httpCode2 == HTTP_CODE_OK) {
                            String payload = http2.getString();
                            USE_SERIAL.println(payload);
                        }
                    } else {
                        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http2.errorToString(httpCode).c_str());
                    }
            
                    http2.end();
                }
                }
                else{
                  digitalWrite(relay, HIGH);
                }
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        http.begin("http://farm.sma.praditadirgantara.sch.id/mp.php?id=4"); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
                if(payload == "1"){
                  digitalWrite(relay4, LOW);
                  delay(9000);
                  if((wifiMulti.run() == WL_CONNECTED)) {

                    HTTPClient http2;
            
                    USE_SERIAL.print("[HTTP] begin...\n");
                    // configure traged server and url
                    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
                    http2.begin("http://farm.sma.praditadirgantara.sch.id/mop.php?id=4&mop=0"); //HTTP
            
                    USE_SERIAL.print("[HTTP] GET...\n");
                    // start connection and send HTTP header
                    int httpCode2 = http2.GET();
            
                    // httpCode will be negative on error
                    if(httpCode2 > 0) {
                        // HTTP header has been send and Server response header has been handled
                        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode2);
            
                        // file found at server
                        if(httpCode2 == HTTP_CODE_OK) {
                            String payload = http2.getString();
                            USE_SERIAL.println(payload);
                        }
                    } else {
                        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http2.errorToString(httpCode).c_str());
                    }
            
                    http2.end();
                }
                }
                else{
                  digitalWrite(relay4, HIGH);
                }
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
    
    if(wifiMulti.run() == WL_CONNECTED) {

        HTTPClient http2;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http2.begin("http://farm.sma.praditadirgantara.sch.id/baca.php?id=4"); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode2 = http2.GET();

        // httpCode will be negative on error
        if(httpCode2 > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode2);
            
            // file found at server
            if(httpCode2 == HTTP_CODE_OK) {
                String payload2 = http2.getString();
                USE_SERIAL.println(payload2);
                if (payload2 == "1"){
                  digitalWrite(relay3, HIGH);
                }
                else {
                  digitalWrite(relay3, LOW);
                  delay(8000);
                                  if((wifiMulti.run() == WL_CONNECTED)) {

                    HTTPClient http3;
            
                    USE_SERIAL.print("[HTTP] begin...\n");
                    // configure traged server and url
                    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
                    http3.begin("http://farm.sma.praditadirgantara.sch.id/control.php?id=4&nilai=1"); //HTTP
            
                    USE_SERIAL.print("[HTTP] GET...\n");
                    // start connection and send HTTP header
                    int httpCode3 = http3.GET();
            
                    // httpCode will be negative on error
                    if(httpCode3 > 0) {
                        // HTTP header has been send and Server response header has been handled
                        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode3);
                        
                        // file found at server
                        if(httpCode3 == HTTP_CODE_OK) {
                            String payload3 = http3.getString();
                            USE_SERIAL.println(payload3);
                        }
                    } else {
                        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http3.errorToString(httpCode3).c_str());
                    }
            
                    http3.end();
                }
                }
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http2.errorToString(httpCode2).c_str());
        }

        http2.end();
    }
    
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http2;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http2.begin("http://farm.sma.praditadirgantara.sch.id/bac.php?id=4"); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode2 = http2.GET();

        // httpCode will be negative on error
        if(httpCode2 > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode2);
            
            // file found at server
            if(httpCode2 == HTTP_CODE_OK) {
                String payload2 = http2.getString();
                USE_SERIAL.println(payload2);
                if (payload2 == "1"){
                  neken = 0;
                  if((wifiMulti.run() == WL_CONNECTED)) {

                    HTTPClient http3;
            
                    USE_SERIAL.print("[HTTP] begin...\n");
                    // configure traged server and url
                    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
                    http3.begin("http://farm.sma.praditadirgantara.sch.id/vit.php?id=4&vit=0"); //HTTP
            
                    USE_SERIAL.print("[HTTP] GET...\n");
                    // start connection and send HTTP header
                    int httpCode3 = http3.GET();
            
                    // httpCode will be negative on error
                    if(httpCode3 > 0) {
                        // HTTP header has been send and Server response header has been handled
                        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode3);
                        
                        // file found at server
                        if(httpCode3 == HTTP_CODE_OK) {
                            String payload3 = http3.getString();
                            USE_SERIAL.println(payload3);
                            USE_SERIAL.println(neken);
                        }
                    } else {
                        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http3.errorToString(httpCode3).c_str());
                    }
            
                    http3.end();
                }
                if((wifiMulti.run() == WL_CONNECTED)) {

                    HTTPClient http3;
            
                    USE_SERIAL.print("[HTTP] begin...\n");
                    // configure traged server and url
                    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
                    http3.begin("http://farm.sma.praditadirgantara.sch.id/lang.php?id=4&lang=0"); //HTTP
            
                    USE_SERIAL.print("[HTTP] GET...\n");
                    // start connection and send HTTP header
                    int httpCode3 = http3.GET();
            
                    // httpCode will be negative on error
                    if(httpCode3 > 0) {
                        // HTTP header has been send and Server response header has been handled
                        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode3);
                        
                        // file found at server
                        if(httpCode3 == HTTP_CODE_OK) {
                            String payload3 = http3.getString();
                            USE_SERIAL.println(payload3);
                        }
                    } else {
                        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http3.errorToString(httpCode3).c_str());
                    }
            
                    http3.end();
                }
                }
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http2.errorToString(httpCode2).c_str());
        }

        http2.end();
    }
//    if((wifiMulti.run() == WL_CONNECTED)) {
//
//        HTTPClient http3;
//
//        USE_SERIAL.print("[HTTP] begin...\n");
//        // configure traged server and url
//        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
//        http3.begin("http://farm.sma.praditadirgantara.sch.id/baca.php?id=4"); //HTTP
//
//        USE_SERIAL.print("[HTTP] GET...\n");
//        // start connection and send HTTP header
//        int httpCode3 = http3.GET();
//
//        // httpCode will be negative on error
//        if(httpCode3 > 0) {
//            // HTTP header has been send and Server response header has been handled
//            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode3);
//            
//            // file found at server
//            if(httpCode3 == HTTP_CODE_OK) {
//                String payload3 = http3.getString();
//                USE_SERIAL.println(payload3);
//                if (payload3 == "1"){
//                  digitalWrite(relay4, HIGH);
//                }
//                else {
//                  digitalWrite(relay4, LOW);
//                }
//            }
//        } else {
//            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http3.errorToString(httpCode3).c_str());
//        }
//
//        http3.end();
//    }
    delay(100);
    ++value;

    //Sensor muktiplexer
    int val = digitalRead(26);
    Serial.print("Nilai = ");
    Serial.println(val);
    if (val == 1){
    digitalWrite(23, LOW);
    }
    else {
    digitalWrite(23, LOW);
    delay(500);
    digitalWrite(23, LOW);
    delay(500);
    }

    //Sensor muktiplexer2
    int val2 = digitalRead(25);
    Serial.print("Nilai2 = ");
    Serial.println(val2);
    if (val2 == 1){
    digitalWrite(23, LOW);
    }
    else {
    digitalWrite(23, LOW);
    delay(500);
    digitalWrite(23, LOW);
    delay(500);
    }

    //Sensor DHT
    int h = dht.readHumidity();
    int t = dht.readTemperature();
    Serial.print("Suhu = ");
    Serial.println(t);
    Serial.print("Kelembapan = ");
    Serial.println(h);

    //Ultrasonik
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    persenjar = 42-distance;
    int perjar = persenjar /42 * 100;
    Serial.print("connecting to ");
    Serial.println(host);
    Serial.print("Distance: ");
    Serial.println(distance);
    Serial.println(persenjar);
    
    //Sensor PH
    static unsigned long samplingTime = millis();
    static unsigned long printTime = millis();
    static float pHValue,voltage;

    pHArray[pHArrayIndex++]=analogRead(SensorPin);
    if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*2.5/4095;
      pHValue = 3*voltage+Offset;
    
//  pHValue = analogRead(SensorPin);
    //Serial.print("Voltage:");
    //Serial.print(voltage,2);
    Serial.print("    pH value: ");
    Serial.println(pHValue,2);
    delay(500);
   
  
  //Sensor TDS
//  static unsigned long analogSampleTimepoint = millis();
//  if (millis() - analogSampleTimepoint > 40U)  //every 40 milliseconds,read the analog value from the ADC
//  {
//    analogSampleTimepoint = millis();
//    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
//    analogBufferIndex++;
//    
//  }
//  static unsigned long printTimepoint = millis();
//  if (millis() - printTimepoint > 800U)
//  {
//    printTimepoint = millis();
//    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
//      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
//    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 4095.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
//    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0); //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
//    float compensationVolatge = averageVoltage / compensationCoefficient; //temperature compensation
//    tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) *0.5 ;
//    float nilaitds = tdsValue*2;
//    Serial.print("Nilai TDS = ");
//    Serial.print(tdsValue,0);
//    Serial.println("ppm");
//    int persentds = tdsValue/2000 *100;
//    }

    tdsValue = analogRead(TdsSensorPin);
    hasiltds = (1*pow(10, -7)*pow(tdsValue , 3))-(0.0004*pow(tdsValue , 2))+ 0.6677*tdsValue - 12.442;
    if(hasiltds >= 500 && hasiltds < 700){
    hasiltds+=60;
    }
    else if(hasiltds >= 700 && hasiltds < 800){
      hasiltds+=80;
    }
    else if(hasiltds >= 800){
      hasiltds+=160;
    }
    Serial.print("Nilai TDS : ");
    Serial.println(hasiltds);
    
//    if(tdsValue<=1700){
//    int y = map(tdsValue,0,1700,0,1000);
//    lcd.setCursor(0, 0); // Position of Cursor on LCD Screen
//    lcd.print("Tds = "); // Start Printing
//    lcd.print(y);
//    lcd.print("ppm");
//    }
//    if (tdsValue > 1700 && tdsValue <= 1900){
//    int y = map(tdsValue,1701,1900,1001,1600);
//    lcd.setCursor(0, 0); // Position of Cursor on LCD Screen
//    lcd.print("Tds = "); // Start Printing
//    lcd.print(y);
//    lcd.print("ppm");
//    }
//    if (tdsValue > 1900){
//    int y = map(tdsValue,1901,3000,1601,5000);
//    lcd.setCursor(0, 0); // Position of Cursor on LCD Screen
//    lcd.print("Tds = "); // Start Printing
//    lcd.print(y);
//    lcd.print("ppm");
//    }
//
    //TDS finish
//    lcd.setCursor(0, 0); // Position of Cursor on LCD Screen
//    lcd.print("Tds = "); // Start Printing
//    lcd.print(hasiltds);
//    lcd.print("ppm");
//    lcd.setCursor(0, 1);
//    lcd.print("Temp=");
//    lcd.print(t);
//    lcd.print("*C");
//    lcd.setCursor(10, 1);
//    lcd.print("Hum=");
//    lcd.print(h);
//    lcd.print("%");
//    lcd.setCursor(0, 2);
//    lcd.print("Nilai PH  = ");
//    lcd.setCursor(12, 2);
//    lcd.print(pHValue);
//    lcd.setCursor(0, 3);
//    lcd.print("Air = ");
//    lcd.setCursor(6, 3);
//    lcd.print(perjar,0);
//    lcd.print("%");
    
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http5;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        String url = "http://farm.sma.praditadirgantara.sch.id/kirdata.php?id=4&jarak=";
        url += perjar;
        url += "&tds=";
        url += hasiltds;
        url += "&ph=";
        url += pHValue;
        url += "&wph=";
        url += hasiltds;
        url += "&suhu=";
        url += t;
        url += "&kelembapan=";
        url += h;
        url += "&air=";
        url += val;
        url += "&air2=";
        url += val2;
        http5.begin(url); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode5 = http5.GET();

        // httpCode will be negative on error
        if(httpCode5 > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode5);
            
            // file found at server
            if(httpCode5 == HTTP_CODE_OK) {
                String payload = http5.getString();
                USE_SERIAL.println(payload);
            }
        } 
        else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http5.errorToString(httpCode5).c_str());
        }

        http5.end();
    }

    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http1;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http1.begin("http://farm.sma.praditadirgantara.sch.id/angka.php?id=4"); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode1 = http1.GET();

        // httpCode will be negative on error
        if(httpCode1 > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode1);
            
            // file found at server
            if(httpCode1 == HTTP_CODE_OK) {
                String payload1 = http1.getString();
                pay = payload1.toInt();                
                USE_SERIAL.println(pay);
                while(hasiltds <= pay-100){
                  digitalWrite(relay3, LOW);
                  digitalWrite(relay4, LOW);
                  tdsValue = analogRead(TdsSensorPin);
                  hasiltds = (1*pow(10, -7)*pow(tdsValue , 3))-(0.0004*pow(tdsValue , 2))+ 0.6677*tdsValue - 12.442;
                  if(hasiltds >= 500 && hasiltds < 700){
                  hasiltds+=60;
                  }
                  else if(hasiltds >= 700 && hasiltds < 800){
                    hasiltds+=80;
                  }
                  else if(hasiltds >= 800){
                    hasiltds+=160;
                  }
                  if((wifiMulti.run() == WL_CONNECTED)) {
                    HTTPClient http;
            
                    USE_SERIAL.print("[HTTP] begin...\n");
                    // configure traged server and url
                    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
                    http.begin("http://farm.sma.praditadirgantara.sch.id/angka.php?id=4"); //HTTP
            
                    USE_SERIAL.print("[HTTP] GET...\n");
                    // start connection and send HTTP header
                    int httpCode = http.GET();
            
                    // httpCode will be negative on error
                    if(httpCode > 0) {
                        // HTTP header has been send and Server response header has been handled
                        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
            
                        // file found at server
                        if(httpCode == HTTP_CODE_OK) {
                            String payload = http.getString();
                            pay = payload.toInt();
                            USE_SERIAL.println(payload);
                        }
                    } else {
                        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
                    }
            
                    http.end();
                  }
                 }
                 if(hasiltds >= pay-100){
                  digitalWrite(relay, HIGH);
                  digitalWrite(relay4, HIGH);
                 }
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http1.errorToString(httpCode1).c_str());
        }

        http1.end();
    }
    
    // Use WiFiClient class to create TCP connections
//    WiFiClient client;
//    const int httpPort = 80;
//    if (!client.connect(host, httpPort)) {
//        Serial.println("connection failed");
//        return;
//    }
//    
//    // We now create a URI for the request
//    String url = "http://smartfarm.epizy.com/kirdata.php?id=4&jarak=";
//    url += perjar;
//    url += "&tds=";
//    url += tdsValue;
//    url += "&ph=";
//    url += pHValue;
//    url += "&wph=";
//    url += tdsValue;
//    url += "&suhu=";
//    url += t;
//    url += "&kelembapan=";
//    url += h;
//    url += "&air=";
//    url += val;
//
//    Serial.print("Requesting URL: ");
//    Serial.println(url);
//
//    // This will send the request to the server
//    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//                 "Host: " + host + "\r\n" +
//                 "Connection: close\r\n\r\n");
//    unsigned long timeout = millis();
//    while (client.available() == 0) {
//        if (millis() - timeout > 5000) {
//            Serial.println(">>> Client Timeout !");
//            client.stop();
//            return;
//        }
//    }
//
//    // Read all the lines of the reply from server and print them to Serial
//    while(client.available()) {
//        String line = client.readStringUntil('\r');
//        Serial.print(line);
//    }

    Serial.println();
    Serial.println("closing connection");
}
