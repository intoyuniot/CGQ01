/*
 ******************************************************************************

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation, either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, see <http://www.gnu.org/licenses/>.

 This library is CGQ01 formaldehyde sensor module

 ******************************************************************************
 */


#include "CGQ01.h"


CGQ01::CGQ01()
{

}

char CGQ01::begin()
{
    Serial.begin(9600);
    while(!Serial)
    {
    }

    // 校零协议
    Serial.write(0XA5);
    Serial.write(0X5A);
    Serial.write(0X02);
    Serial.write(0X85);
    Serial.write(0XAA);
    counter = 0;
    sign = 0;
}


double CGQ01::getConcentrationPPM()
{
    unsigned char i=0,sum=0;

    Serial.flush();
    Serial.write(0XA5);	//获取甲醛浓度信息数据，读取协议模式
    Serial.write(0X5A);
    Serial.write(0X02);
    Serial.write(0X80);
    Serial.write(0XAA);
    delay(50);

    while (Serial.available())
    {
        Re_buf[counter]=(unsigned char)Serial.read();
        if(counter==1 && Re_buf[0]!=0xA5 && Re_buf[1]!=0x5A)
        {
            counter = 0;
            return -1;			//检查帧头
        }

        if(counter==8&&Re_buf[8]!=0xAA)
        {
            counter = 0;
            return -1;			//检查帧尾
        }

        counter++;
        if(counter==9)          //接收到数据
        {
            counter=0;			//重新赋值，准备下一帧数据的接收
            sign=1;
        }
    }

    if(sign)
    {
        sign=0;
        ppm = (float)(Re_buf[6]<<8|Re_buf[7])/100;  // 甲醛 ppm
        return ppm;
    }
    return -1;
}

double CGQ01::getConcentrationMg()
{
    unsigned char i=0,sum=0;

    Serial.flush();
    Serial.write(0XA5);	//获取甲醛浓度信息数据，读取协议模式
    Serial.write(0X5A);
    Serial.write(0X02);
    Serial.write(0X80);
    Serial.write(0XAA);
    delay(50);

    while (Serial.available())
    {
        Re_buf[counter]=(unsigned char)Serial.read();
        if(counter==1 && Re_buf[0]!=0xA5 && Re_buf[1]!=0x5A)
        {
            counter = 0;
            return -1;			//检查帧头
        }

        if(counter==8&&Re_buf[8]!=0xAA)
        {
            counter = 0;
            return -1;			//检查帧尾
        }

        counter++;
        if(counter==9)          //接收到数据
        {
            counter=0;			//重新赋值，准备下一帧数据的接收
            sign=1;
        }
    }

    if(sign)
    {
        sign=0;
        mg = (float)(Re_buf[4]<<8|Re_buf[5])/100;  // 甲醛 mg
        return ppm;
    }
    return -1;
}
