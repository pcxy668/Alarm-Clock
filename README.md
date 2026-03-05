# 闹钟项目

### 1.目录结构

* [Common](https://github.com/pcxy668/Alarm-Clock/tree/master/Common "Common")                        公共层
* [Core](https://github.com/pcxy668/Alarm-Clock/tree/master/Core "Core")                              核心层
* [Drivers](https://github.com/pcxy668/Alarm-Clock/tree/master/Drivers "Drivers")                     驱动层             
* [Interface](https://github.com/pcxy668/Alarm-Clock/tree/master/Interface "Interface")               接口层
* [Application](https://github.com/pcxy668/Alarm-Clock/tree/master/Application "Application")         应用层
* [FreeRTOS](https://github.com/pcxy668/Alarm-Clock/tree/master/FreeRTOS "FreeRTOS")                  FreeRTOS
* [MDK-ARM](https://github.com/pcxy668/Alarm-Clock/tree/master/MDK-ARM "MDK-ARM")                     MDK工具链
* [Others](https://github.com/pcxy668/Alarm-Clock/tree/master/Others "Others")                        原理图、PCB等设计文件
### 2.硬件组成
* 主控芯片 STM32F103C8T6
* 显示部分采用0.96寸OLED屏幕，未使用LED灯板形式展示
* 使用蜂鸣器发声，未采用语音驱动芯片
* 实时时钟采用主控芯片内部RTC模块
* 温湿度模块接口提供了DHT11及DS18B20（无湿度功能）两种芯片实现
* RH6015C 触摸芯片
* 18650 1500mAh 可充电锂电池
* TC4056A 充电管理芯片
* XB5306A 电池保护芯片
* 拨动开关、轻触开关模块
* 声音传感器模块
### 3.主要功能
* 支持实时时间（年、月、日、星期、时、分）、温度、湿度、自定义文字显示
* 支持2个自定义闹钟，3种模式：5天工作日、每天、关闭
* 可通过按键设置时间及闹钟
* 屏幕可设置常亮、常关、自息屏模式
* 息屏后可通过触摸模块或声控模块唤醒
* 闹铃使用蜂鸣器发声
### 4.说明
* 经打板实测，各模块功能目前正常
* 可自行下载.eprj文件预览3d效果
* pcb尺寸进行调整
* 部分元件在不影响主体功能的前提下进行了型号替换
