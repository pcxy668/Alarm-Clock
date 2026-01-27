# 闹钟项目

### 1.目录结构

*   [Common](https://github.com/pcxy668/Alarm-Clock/tree/master/Common "Common")                        公共层
*   [Core](https://github.com/pcxy668/Alarm-Clock/tree/master/Core "Core")                              核心层
*   [Interface](https://github.com/pcxy668/Alarm-Clock/tree/master/Interface "Interface")               接口层
*   [Application](https://github.com/pcxy668/Alarm-Clock/tree/master/Application "Application")         应用层
*   [Others](https://github.com/pcxy668/Alarm-Clock/tree/master/Others "Others")                        原理图、PCB等设计文件
*   Drivers、MDK-ARM文件可由CubeMX统一生成，FreeRTOS文件可自行移植，故均未上传

### 2.部分改动

*   未采用LED灯板形式展示，改用0.96寸OLED屏幕展示
*   未采用语音驱动芯片，改用蜂鸣器发声
*   实时时钟采用STM32F103C8T6内部RTC模块
*   部分元件在不影响主体功能的前提下进行了型号替换

### 3.说明
* 经打板实测，各模块功能目前正常
* 可自行下载.eprj文件预览3d效果
