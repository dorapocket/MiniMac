# 代码

## 直接使用
使用Arduino IDE烧录，烧录前配置：

1、按照 https://blog.csdn.net/qq_42771439/article/details/105326095 构建ESP32环境

2、（如果你买了8M Flash的ESP32-Wroom）安装好后，把本文件夹下minimac_8M复制到 文档/Arduino/hardware/espressif/esp32/tools/partitions目录下，并打开 文档/Arduino/hardware/espressif/esp32/boards.txt 加入下列语句（不然会报错程序大小太大）
```
esp32.menu.PartitionScheme.minimac=MiniMac(8MB No OTA)
esp32.menu.PartitionScheme.minimac.build.partitions=minimac_8M
esp32.menu.PartitionScheme.minimac.upload.maximum_size=6094848
```

3、复制本文件夹下Arduino/libraries到你电脑上文档/Arduino/libraries

4、用Arduino IDE打开MiniMac.ino
- 工具->开发板->ESP32 Dev Module
- (如果你买了4M Flash)工具->Partaition Scheme-> Huge App(4MB No OTA)
- (如果你买了8M Flash)工具->Partaition Scheme-> MiniMac(8MB No OTA)

5、验证并上传

## 自定义
图片采用Adobe Animate制作，具体文件已放在MiniMac-pics文件夹内，导出时选择导出影片-JPEG序列，再用main_gif.py设置好即可自动生成图片库文件，引用即可。生成后的使用方法可以摸索一下MiniMac.ino文件。

## 参考代码
基础代码：Xutoubee https://space.bilibili.com/243597062

Python脚本：韩同学 https://space.bilibili.com/30356692

Respect！