#include <SoftwareSerial.h>
SoftwareSerial NodeMcu(3,2);

int moisture=A0;
int temp=A1;
int pir=A2;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 NodeMcu.begin(4800);
 pinMode(moisture,INPUT);
 pinMode(temp,INPUT);
 pinMode(pir,INPUT);
}

void loop() {
  
  long moisture1=analogRead(moisture);
  Serial.println(moisture1);
  long temp1=analogRead(temp);
  Serial.println(temp1);
  long pir1=analogRead(pir);
  Serial.println(pir);
   NodeMcu.print(moisture1);
   NodeMcu.println("\n");
   delay(10);
   /* NodeMcu.print(temp1);
   NodeMcu.println("\n");
   delay(10);
    NodeMcu.print(pir1);
   NodeMcu.println("\n");
   delay(10);*/
  
}
