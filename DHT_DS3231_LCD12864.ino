#include "DHT.h"//使用DHT库
DHT dht;
float Temperature, Humidity;
unsigned int Counter = 0;


#include "U8glib.h"
U8GLIB_ST7920_128X64_1X u8g(7, 9, 8); //EN ,RW,RS



#include "DS3231.h"
#include <Wire.h>//I2C库

DS3231 Clock;
bool Century = false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;

int second, minute, hour, date, month, year, dow; //temperature,


#include "utility/u8g.h"
const u8g_fntpgm_uint8_t chinese_test_xing[51] U8G_FONT_SECTION("chinese_test_xing") = {
  0, 16, 16, 0, 254, 0, 0, 0, 0, 0, 177, 177, 0, 13, 255, 0,
  0, 13, 14, 28, 16, 1, 255, 63, 224, 32, 32, 63, 224, 32, 32, 63,
  224, 2, 0, 34, 0, 63, 240, 66, 0, 130, 0, 63, 224, 2, 0, 2,
  0, 255, 248
};//星/b1
const u8g_fntpgm_uint8_t chinese_test_qi[55] U8G_FONT_SECTION("chinese_test_qi") = {
  0, 16, 16, 0, 254, 0, 0, 0, 0, 0, 178, 178, 0, 14, 254, 0,
  0, 14, 16, 32, 16, 0, 254, 34, 0, 34, 124, 127, 68, 34, 68, 34,
  68, 62, 124, 34, 68, 34, 68, 62, 68, 34, 124, 34, 68, 255, 68, 4,
  132, 34, 132, 65, 20, 130, 8
};//期/b2
const u8g_fntpgm_uint8_t chinese_test_wen[45] U8G_FONT_SECTION("chinese_test_wen") = {
  0, 12, 12, 0, 0, 0, 0, 0, 0, 0, 179, 179, 0, 10, 255, 0,
  0, 11, 11, 22, 12, 0, 255, 71, 192, 36, 64, 7, 192, 148, 64, 87,
  192, 32, 0, 47, 224, 202, 160, 74, 160, 74, 160, 95, 224
};//温/b3
const u8g_fntpgm_uint8_t chinese_test_du[45] U8G_FONT_SECTION("chinese_test_du") = {
  0, 12, 12, 0, 0, 0, 0, 0, 0, 0, 180, 180, 0, 10, 255, 0,
  0, 11, 11, 22, 12, 0, 255, 2, 0, 127, 224, 72, 128, 127, 224, 72,
  128, 79, 128, 64, 0, 95, 192, 72, 128, 135, 0, 184, 224
};//度/b4
const u8g_fntpgm_uint8_t chinese_test_shi[45] U8G_FONT_SECTION("chinese_test_shi") = {
  0, 12, 12, 0, 0, 0, 0, 0, 0, 0, 181, 181, 0, 10, 255, 0,
  0, 11, 11, 22, 12, 0, 255, 71, 192, 36, 64, 7, 192, 148, 64, 87,
  192, 36, 64, 34, 128, 202, 160, 70, 192, 66, 128, 79, 224
};//湿/b5
const u8g_fntpgm_uint8_t chinese_test_yi[27] U8G_FONT_SECTION("chinese_test_yi") = {
  0, 16, 16, 0, 0, 0, 0, 0, 0, 0, 161, 161, 0, 11, 0, 0,
  0, 16, 2, 4, 16, 0, 9, 255, 255, 255, 255
};//一/a1
const u8g_fntpgm_uint8_t chinese_test_er[43] U8G_FONT_SECTION("chinese_test_er") = {
  0, 16, 16, 0, 254, 0, 0, 0, 0, 0, 162, 162, 0, 11, 0, 0,
  0, 15, 10, 20, 16, 0, 1, 63, 248, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 254
};//二/a2
const u8g_fntpgm_uint8_t chinese_test_san[47] U8G_FONT_SECTION("chinese_test_san") = {
  0, 16, 16, 0, 254, 0, 0, 0, 0, 0, 163, 163, 0, 12, 0, 0,
  0, 15, 12, 24, 16, 0, 0, 127, 252, 0, 0, 0, 0, 0, 0, 0,
  0, 63, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 254
};//三/a3
const u8g_fntpgm_uint8_t chinese_test_si[49] U8G_FONT_SECTION("chinese_test_si") = {
  0, 16, 16, 0, 254, 0, 0, 0, 0, 0, 164, 164, 0, 12, 255, 0,
  0, 13, 13, 26, 16, 1, 255, 255, 248, 136, 136, 136, 136, 136, 136, 136,
  136, 136, 136, 144, 136, 144, 120, 160, 8, 192, 8, 128, 8, 255, 248, 128,
  8
}; //四/a4
const u8g_fntpgm_uint8_t chinese_test_wu[51] U8G_FONT_SECTION("chinese_test_wu") = {
  0, 16, 16, 0, 254, 0, 0, 0, 0, 0, 165, 165, 0, 13, 255, 0,
  0, 15, 14, 28, 16, 0, 255, 127, 252, 2, 0, 2, 0, 2, 0, 2,
  0, 63, 240, 4, 16, 4, 16, 4, 16, 4, 16, 8, 16, 8, 16, 8,
  16, 255, 254
};//五/a5
const u8g_fntpgm_uint8_t chinese_test_liu[53] U8G_FONT_SECTION("chinese_test_liu") = {
  0, 16, 16, 0, 254, 0, 0, 0, 0, 0, 166, 166, 0, 14, 255, 0,
  0, 15, 15, 30, 16, 0, 255, 2, 0, 1, 0, 0, 128, 0, 128, 0,
  0, 255, 254, 0, 0, 0, 0, 4, 64, 4, 32, 8, 16, 8, 8, 16,
  8, 32, 4, 64, 4
};//六/a6
const u8g_fntpgm_uint8_t chinese_test_ri[45] U8G_FONT_SECTION("chinese_test9_ri") = {
  0, 12, 12, 0, 0, 0, 0, 0, 0, 0, 167, 167, 0, 10, 255, 0,
  0, 9, 11, 22, 12, 1, 255, 129, 0, 255, 128, 129, 0, 129, 0, 129,
  0, 255, 0, 129, 0, 129, 0, 129, 0, 255, 0, 129, 0
};//日/a7

void setup(void) {

  //Serial.begin(9600);
  //int MinimumSamplingPeriod=dht.getMinimumSamplingPeriod();
  dht.setup(2); // data pin 2
  Clock.setClockMode(false);  //设置时钟模式，12/24, h12：标志位，true时为12-h, false为24-h。
  //ClocksetA1Time(byte A1Day, byte A1Hour, byte A1Minute, byte A1Second, byte AlarmBits, bool A1Dy, bool A1h12, bool A1PM)
  //TCs.AddFunc(0, loop, 1000);
  //TCs.AddFunc(1, TemperatureHumidity, /*dht.getMinimumSamplingPeriod()*/5000);
  //TCs.AddFunc(1, Tim, 500);
}

void loop(void) {
  getTemperatureHumidity();                         //调用温湿度函数
  Tim(); //调用显示时间的函数
  // ClockA1();                                        //调用闹钟函数
}

void getTemperatureHumidity(void) {
  Counter++;                                        
  //long Time = millis();                            
  //Serial.print("Time:");
  //Serial.println(T);
  if (Counter == 1) {                                 //程序第一次执行延迟2S（AM2302传感器）
    int MinimumSamplingPeriod = dht.getMinimumSamplingPeriod();//获取温湿度传感器读取数据的时间间隔
   
    delay(MinimumSamplingPeriod);                     //延迟2S
    //Serial.println("YanChi:");
    //Serial.println(MinimumSamplingPeriod);
  }
  int i;                                               //从上面的millis()函数可以大概判断程序执行一次需要多长时间
  //i =( (Counter * 165) % 2145);
  i = Counter % 6;                                //整个程序每执行13次读取一次温湿度（AM2302传感器）
  //Serial.println("jishu:");
  //Serial.println(Counter);
  if (i == 0) {                                        //整个程序每执行13次读取一次温湿度（AM2302传感器）
    //Serial.println("shijian:");
    //Serial.println(i);
    Temperature = dht.getTemperature();                 //获取温度
    Humidity = dht.getHumidity();                      //获取湿度
  }
}

void Tim(void) {
  //=======读取时钟的各种中值，存入对应变量========
  second = Clock.getSecond();               //秒
  minute = Clock.getMinute();               //分
  hour = Clock.getHour(h12, PM);            //小时
  date = Clock.getDate();                   //日
  dow = Clock.getDoW();                     //星期
  month = Clock.getMonth(Century);          //月
  year = Clock.getYear();                   //年（仅2位）
  //Temperature = Clock.getTemperature();     //温度  （正负2-3摄氏度误差，温度仅供参考）

  //======开始显示==========
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
}

//======定义的显示模式======
void draw(void)
{
  u8g.setPrintPos(0, 16);                               //定义显示位置 横向起始位置0 纵向16
  u8g.setFont(u8g_font_freedoomr10r);                   //设置字体
  u8g.print("20");
  u8g.print(year);                                      //显示年
  u8g.print('-');
  u8g.print(month);                                     //显示月
  u8g.print('-');
  u8g.print(date);                                      //显示日
  //u8g.setPrintPos(106,16);
  //u8g.print(dow);

  //u8g.setPrintPos(60,16);
  //u8g.print('-');
  u8g.setFont(chinese_test_xing);//
  u8g.drawStr(80, 16, "\xb1");                          //显示汉字“星”
  u8g.setFont(chinese_test_qi);
  u8g.drawStr(96, 16, "\xb2");                          //显示汉字“期”

  switch (dow) {                                        //判断现在是星期几，显示对应的汉字
    case 1 : {
        u8g.setFont(chinese_test_yi);
        u8g.drawStr(112, 20, "\xa1");//一
      }
      break;
    case 2 : {
        u8g.setFont(chinese_test_er);
        u8g.drawStr(112, 16, "\xa2");//二
      }
      break;
    case 3 : {
        u8g.setFont(chinese_test_san);
        u8g.drawStr(112, 16, "\xa3");//三
      }
      break;
    case 4 : {
        u8g.setFont(chinese_test_si);
        u8g.drawStr(112, 16, "\xa4");//四
      }
      break;
    case 5 : {
        u8g.setFont(chinese_test_wu);
        u8g.drawStr(112, 16, "\xa5");//五
      }
      break;
    case 6 : {
        u8g.setFont(chinese_test_liu);
        u8g.drawStr(112, 16, "\xa6");//六
      }
      break;
    case 7 : {
        u8g.setFont(chinese_test_ri);
        u8g.drawStr(112, 16, "\xa7");//日
      }
      break;
  }

  u8g.setPrintPos(8, 48);                //定义显示位置 横向起始位置8 纵向48
  u8g.setFont(u8g_font_freedoomr25n);    //设定字体（具体请参看 U8GLIB google code页面，大量字体可选）
  if (hour >= 10) {
    u8g.print(hour);                     //输出小时的值
  }
  else {
    u8g.print('0');                      //如果时间是个位数前面补一个0
    u8g.print(hour);
  }
  u8g.print(':');                        //显示一个冒号
  if (minute >= 10) {
    u8g.print(minute);                     //显示分钟的值
  }
  else {
    u8g.print('0');
    u8g.print(minute);
  }
  u8g.setFont(u8g_font_freedoomr10r);    //调整显示字体
  u8g.print(':');                        //再显示冒号
  if (second >= 10) {
    u8g.print(second);                     //显示秒
  }
  else {
    u8g.print('0');
    u8g.print(second);
  }

  //u8g.setFont(u8g_font_osb18);
  //u8g.drawBitmapP(0,48, 1, 12, chinese_test);
  //u8g.setFont(u8g_font_osb21);

  //u8g.setFont(u8g_font_freedoomr10r);
  //u8g.setFont(u8g_font_osb18);
  //delay(100);
  u8g.setFont(chinese_test_wen);
  u8g.drawStr(0, 62, "\xb3");                              //显示汉字“温”
  u8g.setFont(chinese_test_du);
  u8g.drawStr(13, 62, "\xb4");                             //显示汉字“度”
  u8g.setFont(chinese_test_shi);
  u8g.drawStr(68, 62, "\xb5");                             //湿
  u8g.setFont(chinese_test_du);
  u8g.drawStr(81, 62, "\xb4");                             //度
  u8g.setPrintPos(25, 65);                                 //调整显示坐标
  u8g.setFont(u8g_font_freedoomr10r);                      //调整字体
  u8g.print(':');
  u8g.print(Temperature , 1);                              //显示温度，保留一位小数
  u8g.print("C");
  u8g.setPrintPos(94, 65);
  u8g.print(":");
  u8g.print(Humidity, 0);                                 //显示湿度
  //  delay(3);
  //  u8g.setPrintPos(110, 65);
  u8g.print("%");
  //  delay(3);
}


