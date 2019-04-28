#include <ESP8266WiFi.h>
#include <time.h>


const char* ssid = "Your-wifi-hotspot-name";
const char* password = "your-password";



//int timezone = GMTvalue * 3600;
int timezone = 5*3600;
int dst = 0;

void setup() {
  

  Serial.begin(115200);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }

  //digitalWrite( ledPin , HIGH);
  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );

  configTime(timezone, dst, "asia.pool.ntp.org");
  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
  Serial.println("\nTime response....OK");   
}

void loop() {
  
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  Serial.print(p_tm->tm_mday);
  Serial.print("/");
  Serial.print(p_tm->tm_mon + 1);
  Serial.print("/");
  Serial.print(p_tm->tm_year + 1900);
  
  Serial.print(" ");
  
int corrected_mm = p_tm->tm_min + 30;

if(corrected_mm > 60){
      Serial.print(p_tm->tm_hour + 1);
      Serial.print(":");
      Serial.print(corrected_mm - 60);
      Serial.print(":");
      Serial.println(p_tm->tm_sec);
}else{
      Serial.print(p_tm->tm_hour);
      Serial.print(":");
      Serial.print(corrected_mm);
      Serial.print(":");
      Serial.println(p_tm->tm_sec);
  }
  
  delay(1000);

}
