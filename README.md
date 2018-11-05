# ssd1306-GIF-from-spiffs-esp8266
Playing long animation files on ssd1306 with esp8266 spiffs

I found a way to play extremely long animations on oled. It works by reading mono image file from spiffs byte by byte.

example starwars (1009 frames)



Tutorial

So first you resize or/and crop your gif so it fits oled. Then you turn it to sprite one long stack up of your frames. Then online
mono converter turn it to black and white one bit to one pixel format.
It is important to calculate frame size in bytes precisely. you do that by dividing mono file's size with frame amount

1) Gif resize

2) GIF to one column sprite. Only on column and all frames downward!!

3) Mono converter

4) Variables. Calculate framesize and tell hight and width in the code

3) Data upload and code upload!!

enjoy

