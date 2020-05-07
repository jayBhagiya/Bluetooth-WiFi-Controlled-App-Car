#include <SoftwareSerial.h>

#define enA 5
#define enB 6
#define in1 8
#define in2 9
#define in3 10
#define in4 11

int dataIn[4] = {0,0,0,0};
int in_data = 0;
int idx = 0;

SoftwareSerial sw(3, 2); //(Rx,Tx)

void setup() {
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  
  Serial.begin(115200);
  sw.begin(38400);
}

void loop() {
  if(sw.available())
  {
    in_data = sw.read();
    if(in_data == (255))
      idx = 0;

    dataIn[idx] = in_data;
    idx++;
  }

  //printData();
  run_car(dataIn[1], dataIn[2], dataIn[3]);
}

void run_car(int spd,int x_val,int y_val)
{ 
  int xAxis = map(x_val, 0, 200, 0, 1023);
  int yAxis = map(y_val, 0, 200, 0, 1023);
  
  analogWrite(enA,spd);
  analogWrite(enB,spd);
  
  if((xAxis>=0 && xAxis<=254)&&(yAxis>0 && yAxis<=256))
  {
    Soft_LF();
  }
  else if((xAxis>=0 && xAxis<=254)&&(yAxis>256 && yAxis<=767))
  {  
    Left();
  }
  else if((xAxis>=0 && xAxis<=254)&&(yAxis>767 && yAxis<=1023))
  {
    Soft_LB();
  }
  else if((xAxis>254 && xAxis<=765)&&(yAxis>=0 && yAxis<=256))
  {
    Forward();
  }
  else if((xAxis>254 && xAxis<=765)&&(yAxis>256 && yAxis<=767))
  { 
    Stop();
  }
  else if((xAxis>254 && xAxis<=765)&&(yAxis>767 && yAxis<=1023))
  {
    Backward();
  }
  else if((xAxis>765 && xAxis<=1023)&&(yAxis>=0 && yAxis<=256))
  {
    Soft_RF();
  }
  else if((xAxis>765 && xAxis<=1023)&&(yAxis>256 && yAxis<=767))
  {  
    Right();
  }
  else if((xAxis>765 && xAxis<=1023)&&(yAxis>767 && yAxis<=1023))
  {
    Soft_RB();
  }
  else
  {
    Stop();
  }
}

void printData()
{
  Serial.print(dataIn[0]);
  Serial.print(", Speed : ");
  Serial.print(dataIn[1]);
  Serial.print(", X_val : ");
  Serial.print(dataIn[2]);
  Serial.print(", Y_val : ");
  Serial.println(dataIn[3]);
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
