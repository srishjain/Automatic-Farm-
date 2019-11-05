
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
const char* ssid="Le 2";
const char* password="37c7ttta";
WiFiServer server(80);
float moisture1;
float moisture2;
float ldr;
float pir;
float temp;
float humidity;
SoftwareSerial ArduinoUno(D2,D3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 
    Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  // Start the server
  server.begin();
  Serial.println("Server started");
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
   ArduinoUno.begin(4800);
  pinMode(D2,INPUT); //input or reciever
  pinMode(D3,OUTPUT); //output or transmitter
}

void loop() {
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  while(ArduinoUno.available()>0) //data recive from arduino
  {
   moisture1=ArduinoUno.parseFloat();//pass value to nodemcu and to val variable
   
      Serial.print("moisture in field 1 is: ");
      if(moisture1<300)
      { Serial.println(moisture1);
      Serial.println("HIGH");
      break;}
      else{
         Serial.println(moisture1);
      
      Serial.println("LOW");
      break;
      }
     
  }
  delay(20);
   while(ArduinoUno.available()>0) //data recive from arduino
  {
   moisture2=ArduinoUno.parseFloat();//pass value to nodemcu and to val variable
   
      Serial.print("moisture in field 2 is: ");
      if(moisture2<300)
      { Serial.println(moisture2);
      Serial.println("HIGH");
      break;}
      else{
         Serial.println(moisture2);
      
      Serial.println("LOW");
      break;
      }
     
  }
  delay(20);
     while(ArduinoUno.available()>0) //data recive from arduino
  {
   ldr=ArduinoUno.parseFloat();//pass value to nodemcu and to val variable
   
      Serial.print("Light condition: ");
      if(ldr<200)
      { Serial.println(ldr);
      Serial.println("ITS DARK");
      break;}
      else{
         Serial.println(ldr);
      
      Serial.println("ITS BRIGHT");
      break;
      }
     
  }
  delay(20);
     while(ArduinoUno.available()>0) //data recive from arduino
  {
   temp=ArduinoUno.parseFloat();//pass value to nodemcu and to val variable
   
      Serial.print("Temperature is: ");
      if(moisture2<300)
      { Serial.println(temp);
      
      break;}
      else{
         Serial.println(temp);
      
      
      break;
      }
     
  }
  delay(20);
     while(ArduinoUno.available()>0) //data recive from arduino
  {
   humidity=ArduinoUno.parseFloat();//pass value to nodemcu and to val variable
   
      Serial.print("Relative Humidity is: ");
      Serial.print(humidity);
        Serial.println("%");
      
      break;
     
  }
  delay(20);
     while(ArduinoUno.available()>0) //data recive from arduino
  {
   pir=ArduinoUno.parseFloat();//pass value to nodemcu and to val variable
   
      Serial.print("Intruder: ");
      if(pir<300)
      { Serial.println(pir);
      Serial.println("PRESENT");
      break;}
      else{
         Serial.println(pir);
      
      Serial.println("NOT PRESENT");
      break;
      }
     
  }
  delay(20);
   client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta http-equiv=\"refresh\" content=\"3\">");
  client.println("<h1>Getting Sensor values</h1>");
  client.println("<header>");
  client.println("</header>");
  client.println("<br />");
  client.println("<style>");
  client.println("h1{color: blue;}");
  client.println("</style>");
  client.println("<i>");
  client.print("<h3>");
  client.println("<i>");
  client.print("&nbsp &nbsp &nbsp &nbsp &nbsp");
  client.print(" Moisture in region 1 is ");
  client.println("</i>"); 
  if(moisture1<300.0)
  { 
    client.println("HIGH");
  }
  else if (moisture1>=300)
  { 
    client.println("LOW");
  }
  client.print("</h3>");
  client.print("<h3>");
  client.println("<i>");
  client.print("&nbsp &nbsp &nbsp &nbsp &nbsp");
  client.print(" Moisture in region 2 is ");
  client.println("</i>"); 
  if(moisture2<300.0)
  { 
    client.println("HIGH");
  }
  else if (moisture2>=300)
  { 
    client.println("LOW");
  }
  client.print("</h3>");
  client.print("<h3>");
  client.println("<i>");
  client.print("&nbsp &nbsp &nbsp &nbsp &nbsp");
  client.print(" Temperature is:  ");
  client.println("</i>"); 
  client.print(temp);
  client.println(" C");
  client.print("</h3>");
  client.print("<h3>");
  client.println("<i>");
  client.print("&nbsp &nbsp &nbsp &nbsp &nbsp");
  client.print(" Relative Humidity: ");
  client.println("</i>"); 
  client.print(humidity);
  client.println("%");
  client.print("</h3>");
    client.print("<h3>");
  client.println("<i>");
  client.print("&nbsp &nbsp &nbsp &nbsp &nbsp");
  client.print(" Intruder/Animal: ");
  client.println("</i>"); 
  if(pir<300.0)
  { 
    client.println("PRESENT");
  }
  else if (pir>=300)
  { 
    client.println("NOT PRESENT");
  }
  client.print("</h3>");
    client.print("<h3>");
  client.println("<i>");
  client.print("&nbsp &nbsp &nbsp &nbsp &nbsp");
  client.print(" Light condition ");
  client.println("</i>"); 
  if(ldr<300.0)
  { 
    client.println("ITS DARK");
  }
  else if (ldr>=300)
  { 
    client.println("ITS BRIGHT");
  }
  client.print("</h3>");
  client.println("</html>");
  delay(100);
  Serial.println("Client disconnected");
 
}

