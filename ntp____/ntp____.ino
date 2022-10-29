#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>



WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com",60*60*8, 30*60*1000);


void smartConfig()
{
  WiFi.mode(WIFI_STA);
//  Serial.println("\r\nWait for Smartconfig");
  delay(2000);
  // 等待配网
  WiFi.beginSmartConfig();
 
 while (1)
  {
    Serial.print("正在配网\r");
    delay(500);
    if (WiFi.smartConfigDone())
    {
   //   Serial.println("SmartConfig Success");
   //   Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
  //    Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
      WiFi.setAutoConnect(true);  // 设置自动连接
      break;
    }
  }
 
 // Serial.println("");
 // Serial.println("WiFi connected");  
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
}


void setup(){
  Serial.begin(9600);
  pinMode(2, OUTPUT);
   WiFi.begin(WiFi.SSID().c_str(), WiFi.psk().c_str());
  delay(6800);//必须6000以上 不然连接不上
  while ( WiFi.status() != WL_CONNECTED ) {     
     smartConfig();
  }
  digitalWrite(LED_BUILTIN, HIGH); 
  timeClient.begin();
}

void loop() {
  timeClient.update();
 Serial.println(timeClient.getFormattedTime());
  delay(1000);
}
