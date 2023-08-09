cn.roger.animation
========

为了适应app inventor那诡异的语法，使用了工厂模式。<br>
[常数表在此](https://www.showdoc.cc/web/#/133680866739480)<br>

## ViewPropertyAnimatorUtil
所有文中的b的含义都是表示是否调用加by的方法，以下不再重复<br>
加by意味着叠加，如<br>
rotation(360f)，rotation(360f) = 0~360，360~360<br>
rotationBy(360f)，rotationBy(360f) = 0~360，360~720<br>
#### 方法
方法|注释
-|-
void scaleX(float f,boolean b)|设置x轴拉伸倍数
void scaleY(float f,boolean b)|设置y轴伸倍数
void alpha(float f,boolean b)|设置透明度
void translationX(float f,boolean b)|设置x轴位移
void translationY(float f,boolean b)|设置y轴位移
void translationZ(float f,boolean b)|设置z轴位移
void rotation(float f,boolean b)|旋转度数(°)
void rotationX(float f,boolean b)|绕x轴旋转度数(°)
void rotationY(float f,boolean b)|绕y轴旋转度数(°)
void x(float f,boolean b)|设置x轴坐标
void y(float f,boolean b)|设置y轴坐标
void z(float f,boolean b)|设置z轴坐标
---|---
void cancel()|取消动画
void withLayer()|取消动画
