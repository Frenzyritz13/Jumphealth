#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>
#include <FirebaseFS.h>
#include <FirebaseJson.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#define FIREBASE_HOST "https://hackdartmouth2021-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5x7hbdqQLtzbxqxoGrriiEXGuEDMVozjPJMB3Aes"
#define WIFI_SSID "Mishra"
#define WIFI_PASSWORD "password7"
#define API_KEY "AIzaSyD9_17OYoVjG8NJaLVZ4WxpzLaMZuSO66s"

FirebaseData fbdo;
Adafruit_MPU6050 mpu;
int count =0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Init");
  WifiSetup();
  getAccelValues();
  dataCallibrate();
}

void loop()
{
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  String statusC;
  Firebase.getString(fbdo, "DeviceId1/Calibration/status", statusC);
  if(statusC=="3"){
    dataCallibrate();
  }
  printAccelValues();
 

}


void getAccelValues() {
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  mpu.begin();
  }

  
void printAccelValues() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  mpu.begin();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.setFloat(fbdo, "/Devices/DeviceId1/Accel/X", a.acceleration.x);
  Firebase.setFloat(fbdo, "/Devices/DeviceId1/Accel/Y", a.acceleration.y);
  Firebase.setFloat(fbdo, "/Devices/DeviceId1/Accel/Z", a.acceleration.z);

  delay(500);
}

void WifiSetup() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
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
}

void dataCallibrate() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  String statusC="2";
  int i=0;
  float highx=0.0f;
  float highy=0.0f;
  float highz=0.0f;
  float lowx=a.acceleration.x;
  float lowy=a.acceleration.y;
  float lowz=a.acceleration.z;
  
  for(i=0;i<50;i++) {
    if(a.acceleration.x>highx) highx=a.acceleration.x;
    if(a.acceleration.x<lowx) lowx=a.acceleration.x;
    if(a.acceleration.y>highy) highx=a.acceleration.y;
    if(a.acceleration.y<lowy) lowy=a.acceleration.y;
    if(a.acceleration.z>highz) highx=a.acceleration.z; 
    if(a.acceleration.z<lowz) lowz=a.acceleration.z;
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  Firebase.setFloat(fbdo, "/Calibration/DeviceId1/Accel/X/high", highx);
  Firebase.setFloat(fbdo, "/Calibration/DeviceId1/Accel/X/low", lowx);
  Firebase.setFloat(fbdo, "/Calibration/DeviceId1/Accel/Y/high", highy);
  Firebase.setFloat(fbdo, "/Calibration/DeviceId1/Accel/Y/low", lowy);
  Firebase.setFloat(fbdo, "/Calibration/DeviceId1/Accel/Z/high", highz);
  Firebase.setFloat(fbdo, "/Calibration/DeviceId1/Accel/Z/low", lowz);
  Firebase.setString(fbdo, "/Calibration/DeviceId1/status", statusC);
}
  


  
