// 本程序使用CGQ01甲醛模块，获取甲醛浓度，并重串口输出数据
// 本程序使用的是Serial
// 连接说明：
// CGQ01                     Atom
// 1.VCC                        +5.0V
// 2.GND                        GND
// 3.RX                         A3(TX)
// 4.TX                         A2(RX)

/*
测量范围：0-5ppm
输出信号：2000nA/pp
甲醛模块上电后需1分钟预热时间，1分钟后测的数据为有效数据。
*/

#include <CGQ01.h>

CGQ01 cgq01PPM; // 定义传感器变量

void setup()
{
    Serial.begin(115200);
    cgq01PPM.begin(); // 初始化
}

void loop()
{
    double ppm = cgq01PPM.getConcentrationPPM(); // 获取甲醛传感器的甲醛浓度
    if (ppm != -1)
    {
        Serial.print(ppm); // 串口输出甲醛浓度数据
    }
    delay(2000);  // 延迟2s
}
