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

#ifndef CGQ01_H
#define CGQ01_H

#include "Arduino.h"

class CGQ01
{
    public:
        CGQ01();
        // 初始化串口
        char begin();
        // 获取温度值
        double getConcentrationPPM();
        double getConcentrationMg();

    private:
        unsigned char Re_buf[11], counter;
        unsigned char sign;
        float ppm;
        float mg;
};

#endif
