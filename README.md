ImageProcessing

author:windgodvc

python

- 命令行 版 支持的功能 不算多 后续会加入 和 GUI一样的功能.
- python 批量裁剪 和 批量加圆四角。 (mask)

—help

- resizeImage /root 100 50 --demo
- CircleRectImage /root maskfile --demo

使用要求:

- python  pyQt4

Qt GUI C++

- 定位较高 能用于生成Application Icon 自动加入圆四角(mask) 其实这个是圆形还是什么都是来自于mask.png 的形态来决定的.可以说全部形态都支持.
- 可以用于游戏角色的头像裁剪加圆四角 (由于 自己ps 技术不好所以才写了这个软件.同时也是为了节省游戏内存的消耗 .在游戏中mask 花不少内存.)- - ...
- 原图不要求 一定是512 * 512 自己喜欢.
- 可以点击表格预览 处理后的效果.
- 支持输出不规则 透明图片,不会因为 mask 导致背景变黑.

来几张效果图

软件界面

       

效果图1

    

效果图2

  

原图1



原图2





The MIT License (MIT)

Copyright (c) 2016 windgod

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

	


