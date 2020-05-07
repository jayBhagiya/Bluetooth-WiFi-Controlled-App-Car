#include <SoftwareSerial.h>

#define enA 5
#define enB 6
#define in1 8
#define in2 9
#define in3 10
#define in4 11

SoftwareSerial sw (3, 2);

boolean haveNewData = false;

int spd = 6;
int idx = 0;

char buff[10];
char termChar = '\n';
char data = ' ';

void setup() {
  Serial.begin(9600);
  sw.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  readSerial();
  if(haveNewData)
    processNewData(); 
  
  if(buff[0] == ':')
  {
    String data(buff);
    spd = data.substring(1).toInt();
  }
  
  run_car(buff[0], spd);
}

void readSerial()
{
  if(sw.available() > 0)
  {
    data = sw.read();
    if(data != termChar)
    {
      buff[idx++] = data;
    }
    else
    {
      buff[idx] = '\0';
      idx = 0;
      haveNewData = true;
    }
  }
}

void processNewData()
{
  Serial.print("Data : ");
  Serial.println(buff[0]);
  Serial.print("Speed : ");Serial.println(spd);
  haveNewData = false;
}

void run_car(char state, int setSpd)
{
  int mapSpd = map(setSpd, 0, 10, 0, 255);
  
  analogWrite(enA, mapSpd);
  analogWrite(enB, mapSpd);
 
    if(state == 'Q'){
      Soft_LF();
      Serial.println("Left Forward");
    }
    else if(state == 'F'){
      Forward();
      Serial.println("Forward");
    }
    else if(state == 'E'){
      Soft_RF();
     Serial.println("Right Forward");
    }
    else if(state == 'L'){
      Left();
      Serial.println("Left");
    }
    else if(state == 'R'){
      Right();
      Serial.println("Right");
    }
    else if(state == 'Z'){
      Soft_LB();
      Serial.println("Left Back");
    }
    else if(state == 'B'){
      Backward();
      Serial.println("Backward");
    }
    else if(state == 'C'){
      Soft_RB();
      Serial.println("Right Back");
    }
    else{
      Stop();
      Serial.println("Stop");
    }
}

void Forward()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void Backward()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

void Right()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void Left()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

void Stop()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void Soft_LF()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void Soft_RF()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void Soft_LB()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void Soft_RB()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
