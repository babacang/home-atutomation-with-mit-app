#include <ESP8266WiFi.h>
#include <Servo.h>
 
const char* ssid = "hah";
const char* password = "hahhahhah";
#define lampu D0 
#define kipas D1 

Servo servo;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200); //Default Baud Rate for NodeMCU
  delay(10);
 
  pinMode(lampu, OUTPUT);  // Connect Relay to NodeMCU's D4 Pin
  pinMode(kipas, OUTPUT); 
  servo.attach(D2);
  digitalWrite(lampu, 0);
  digitalWrite(kipas, 0);
  servo.write(0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.println(WiFi.localIP());
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  if (req.indexOf("/lampu/0") != -1)
    {digitalWrite(lampu,0);}
  if (req.indexOf("/lampu/1") != -1)
    {digitalWrite(lampu,1);}
  if (req.indexOf("/kipas/0") != -1)
    {digitalWrite(kipas,0);}
  if (req.indexOf("/kipas/1") != -1)
    {digitalWrite(kipas,1);}
  if (req.indexOf("/pintu/0") != -1)
    {servo.write(180);}
  if (req.indexOf("/pintu/1") != -1)
    {servo.write(0);}  
  
}
