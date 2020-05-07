#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

SoftwareSerial sw(D7, D8);

char buff[5];

const char* ssid = "**Your WiFi**";
const char* password = "**Your Passward**";

void setup() {
  Serial.begin(9600);
  sw.begin(9600);

  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("Local IP is : ");
  Serial.print((WiFi.localIP()));

  server.begin();
}

void loop() 
{
  client = server.available();
  
  if (!client) 
    return; 
    
  String data = checkClient ();
  data.concat("\n");

  data.toCharArray(buff, 5);

  sw.write(buff);
  Serial.print(data);
}

//**************************** Checking Client ***********************************//

String checkClient (void)
{
  while(!client.available())
    delay(1); 
    
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  
  return request;
}
