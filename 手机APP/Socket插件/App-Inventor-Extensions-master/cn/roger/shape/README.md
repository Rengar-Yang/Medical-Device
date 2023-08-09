cn.roger.shape
========

为了适应app inventor那诡异的语法，采用了状态机的方式来组织语句。<br>
状态机的具体含义参见根目录的README.md<br>
颜色采用字符串形式，如红色#FF0000，大小写无所谓<br>
渐变颜色组采用列表字符串，就是用列表把字符串装起来<br>
[常数表在此](https://www.showdoc.cc/web/#/133680866739480)<br>

## GradientDrawableUtil
#### 状态
id
#### 方法
方法|注释
-|-
void NEW()|给View添加一个新GradientDrawable，即一个形状
void setCornerRadius(float radius)|设置圆角(px)
void setStroke(int width,String color)|设置边框宽度(px)和颜色
void setColor(String color|设置填充颜色
void setColors(YailList colors)|设置渐变颜色组
void setGradientType(int gradient)|设置渐变方式，参数见常数表
void setGradientRadius(float gradientRadius)|设置渐变半径，只有RADIAL_GRADIENT时有效
void setOrientation(int i)|设置渐变方向，参数见常数表
## RippleDrawableUtil
#### 状态
id
#### 方法
方法|注释
-|-
void newRippleDrawable(String color)|给View原先shape添加水波纹并设置颜色
