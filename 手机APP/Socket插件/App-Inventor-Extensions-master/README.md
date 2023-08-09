App-Inventor-Extensions
======
# 已整理测试项目 2019-08-06
以下都有测试图，可以到new_test目录下查看
 - socket
   - 就是socket通信的那个，补充了测试图
 - OpenGL_1
   - 立方体旋转测试
 - OpenGL_2
   - 旋转视角测试
 - OpenGL_3
   - 棋盘地图及移动测试
 - OpenGL_4
   - 移动控制杆的绘制
 - car
   - 我提交比赛的项目，没得奖，不用报太大期望

# PS 2019-07-31
MD博客CSDN要手机短信验证，所以博文不再更新，希望谅解<br>
总说着要上传测试文件，但我自己都编译不过我也。。。<br><br>
高三很忙，我就不再整理直接上传了，在new_tests目录下，不要笑话我的码风啊，我还没重构呢<br>
只有apk和aia和aix(其实可以从aia提取的)和java代码，只能看看效果和源码，编译就。。。<br>
部分项目由于使用了OpenGL所以兼容性堪忧，部分项目是测试文件所以只有apk<br><br>
网络问题可以试试下面的国内镜像<br>
https://gitee.com/aiw_prton/App-Inventor-Extensions

# 以下不变 2018-08-27
额这只是一个写博课时的代码合集，方便自己管理，也方便大家。<br>
可能博客上更新的还不如这里更的快。。。<br>
一个要开学的高二狗，轻喷<br>
可能导入有很大的冗余，见谅<br>
因为我英语很差，而且很懒，所以description的介绍都没写，全是复制粘贴的。。。<br>
顺便去我的csdn逛一圈呗<br>
https://blog.csdn.net/aiw_prton<br>
App Inventor插件开发(六)WIFI通信<br>
App Inventor插件开发(五)更美的UI<br>
App Inventor插件开发(四)OpenGL未完待续<br>
App Inventor插件开发(三)动画插件<br>
App Inventor插件开发(二)编译第一个AIX插件<br>
App Inventor插件开发(一)配置环境<br>

## shape
shapeUtil是一个形状创建工具，可以创建比如圆角矩形之类的形状，节省空间<br>
RippleUtil是水波纹动画。<br>

## ViewUtil
包名不小心大写了，懒得改。。。见谅<br>
封装了一遍控件类，按照标准继承，挑了些比较有用的方法<br>
不过改变了一些方法的组织顺序和调用方式，以适合App-Inventor的设计方式<br>
>AnyEventUtil用于事件处理，目前只有点击<br>
ButtonUtil用于创建按钮<br>
EditTextUtil用于创建输入框<br>
RelativeLayoutUtil用于创建相对布局<br>
TextViewUtil用于创建标签<br>

>ViewGroupUtil抽象类<br>
ViewUtil抽象类<br>

## Util
包名又不小心大写了，见谅<br>
>Util是一个杂七杂八的工具类，不好分类的方法都丢进去。<br>

## animation
终于记得小写了。。。<br>
动画，重写已完成。<br>

## OpenGL
包名又双叒叕不小心大写了。。。<br>
预计等这属于我单身狗的一年过去了上传。<br>

## Socket
包名又双叒叕不小心大写了。。。<br>
用于wifi下socket通信<br>
测试见csdn<br>
