 #include <Servo.h>. //舵机库文件
int beep = 8;//定义蜂鸣器接口为数字8 接口
int red =10;
int green=11;
int flameVal = 0; //存储火焰传感器数据

const int trigPin = 5;//定义一个常量
const int echoPin = 6;//定义一个常量

long duration;//舵机旋转角度
int distance;//超声波距离
Servo myServo; //初始化实例对象

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()
{
  Serial.begin(9600);
  pinMode(beep, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);//定义beep 为输出接口
  pinMode(trigPin, OUTPUT); //引脚的定义输出
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);//设置串口波特率
  myServo. attach(9); //舵机的引脚连接arduino的9号引脚
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
//while(Serial.available())
//{
  distance = calculateDistance();//计算路程
  flameVal = analogRead(A0); //读取火焰传感器的模拟值
  //Serial.println(flameVal); 
// Serial.println(distance); 
  char c=Serial.read();

  if(c=='A')
    {
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.println("OPENING...");
      display.display();
      delay(3000);
      for(int i=0;i<=90;i=i+10){  //最大旋转角度为180度
      myServo.write(i);//往舵机写旋转角度
      delay(15);//延时
      }
    }
    else if(c=='B'){
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.println("CLOSING...");
      display.display();
      for(int i=90;i>=0;i=i-1){  
      myServo.write(i);
      delay(15);
      }
      Serial.println("Hello I am working");
    }
    else if(distance<=5){
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.println("OPENING...");
      display.display();
      for(int i=0;i<=90;i=i+10){  //最大旋转角度为180度
      myServo.write(i);//往舵机写旋转角度
      delay(15);//延时
      }
      delay(3000);
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.println("CLOSING...");
      display.display();
      for(int i=90;i>=0;i=i-1){  
      myServo.write(i);
      delay(15);
      }
      Serial.println("Hello I am working");
    }
//}
if (flameVal >= 100) //当模拟值大于200时蜂鸣器鸣响，阈值根据实际测试进行修改
  { 
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(4);
    display.println("FIRE!");
    display.display();
    digitalWrite(beep, HIGH);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    delay(100);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    delay(100);
  }
  else {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(4);
    display.println("SWJTU");
    display.display();
    digitalWrite(beep, LOW);
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
  }
}

int calculateDistance() { //调用子程序
    
    digitalWrite(trigPin, LOW); //给一个低电平
    delayMicroseconds(2);//延时2微妙
    digitalWrite(trigPin, HIGH); //给一个高电平
    delayMicroseconds(10);//延时10微妙
    digitalWrite(trigPin, LOW);//给一个低电平
    distance= float( pulseIn(echoPin, HIGH) * 17 ) / 1000; //计算距离;
    return distance;//返回距离
  } 
