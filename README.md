# 图形学入门记录
[TOC]

</font>

<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

# 前言

<font color=#999AAA >记录图形学入门阶段的学习记录</font>

<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

<font color=#999AAA >提示：以下是本篇文章正文内容

# 一、基础
<font color=#999AAA >包括c++基础和图形学基础
## 1.1  C++基础
### 1.1.0 使用const 的作用：
```cpp
//1.函数前面使用const 表示返回值为const
const int getValue();
//2.函数后面加 const表示函数不可以修改class的成员
int getValue2() const;
//3. const的对象，不能引用非const的成员函数
const A; 
//4.用const修饰函数参数，表示函数不可以修改该值
//如果函数体内的语句试图改动strSource的内容，编译器将指出错误。
void StringCopy (char*strDestination, const char *strSource);
```
[对于第二类的补充](https://blog.csdn.net/qinhan728/article/details/49823667?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-4-49823667-blog-83341222.pc_relevant_multi_platform_whitelistv3&spm=1001.2101.3001.4242.3&utm_relevant_index=7)

**highlight!!!!**

C++中，const类型对象只能调用const成员函数，但非const类型对象对于重载了const和非const的函数，会优先调用非const函数。这也提醒我们对于确定不想改变的变量，一定要定义为const类型，防止调用了某个非const的成员函数改变了对象数据却没有发现！
### 1.1.1 运算符重载
- **原理：**
当您调用一个重载函数或重载运算符时，编译器通过把您所使用的参数类型与定义中的参数类型进行比较，决定选用最合适的定义。选择最合适的重载函数或重载运算符的过程，称为重载决策
```
例如，operator+() 重载+运算符
   operator*()重载*运算符
```

运算符重载可被定义为普通非成员函数或类成员函数
- 普通非成员函数：(两个box对象相加)
```cpp
Box operator+(const Box&, const Box&);
```
- 类成员函数：
```cpp
 // 重载 + 运算符，用于把两个 Box 对象相加
      Box operator+(const Box& b)
      {
         Box box;
         box.length = this->length + b.length;
         box.breadth = this->breadth + b.breadth;
         box.height = this->height + b.height;
         return box;
      }
```
在main函数调用+即可
```cpp
 // 把两个对象相加，得到 Box3
   Box3 = Box1 + Box2;
```
- 函数重载
[link](https://www.runoob.com/cplusplus/cpp-overloading.html)
重载声明是指一个与之前已经在该作用域内声明过的函数或方法具有相同名称的声明，但是它们的参数列表和定义（实现）不相同
### 1.1.2 inline内联函数 
[link](https://www.bilibili.com/read/cv6292203/)


**类中成员函数与内联**：
定义在类中的成员函数缺省都是内联的
如果在类定义时就在类内给出函数定义，那当然最好。
如果在类中未给出成员函数定义，而又想内联该函数的话，那在类外要加上inline，否则就认为不是内联的。 

## 1.2 CG相关基础
### 1.2.1 向量叉积&点乘
[向量叉积&点乘参考](https://blog.csdn.net/jgj123321/article/details/96474456?spm=1001.2101.3001.6650.9&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-9-96474456-blog-51753968.pc_relevant_multi_platform_whitelistv1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-9-96474456-blog-51753968.pc_relevant_multi_platform_whitelistv1&utm_relevant_index=13)
- **点乘**几何意义：
表征或计算两个向量之间的夹角
b向量在a向量方向上的投影
-  **叉乘**几何意义：
![在这里插入图片描述](https://img-blog.csdnimg.cn/a08dc6eca9844d809dc3426b4c900725.png)
向量a和向量b的外积结果称为法向量，该向量垂直于a和b向量构成的平面
- 推理过程：
对于向量$a=(x_1,y_1,z_1)),b=(x_2,y_2,z_2)$
外积公式为：
$$
a \times b=\left|\begin{array}{ccc}
i & j & k \\
x_{1} & y_{1} & z_{1} \\
x_{2} & y_{2} & z_{2}
\end{array}\right|=\left(y_{1} z_{2}-y_{2} z_{1}\right) i-\left(x_{1} z_{2}-x_{2} z_{1}\right) j+\left(x_{1} y_{2}-x_{2} y_{1}\right) k
$$
其中:
$$
i=(1,0,0) \quad j=(0,1,0) \quad k=(0,0,1)
$$
根据i、j、k间关系，有:
$$
a \times b=\left(y_{1} z_{2}-y_{2} z_{1},-\left(x_{1} z_{2}-x_{2} z_{1}\right), x_{1} y_{2}-x_{2} y_{1}\right)
$$


# 二、Hello Graphics~
## 0.tracer坐标系说明
![在这里插入图片描述](https://img-blog.csdnimg.cn/141d87e6616541ffa3434ec367f5d96d.png)
- （0.0.0）为眼睛（或照相中心）
- (x,y,z)摆放符合右手坐标系 
- 光线从（0.0.0）出发，在屏幕左下角(-2,-1,-1)基础上，加上u（x正方向）、v（y正方向）两个偏移向量去计算光线在屏幕的最终点。
## 1.PPM file
A PPM file is a 24-bit color image formatted using a text format. It stores each pixel with a number from 0 to 65536, which specifies the color of the pixel. PPM files also store the image height and width, whitespace data, and the maximum color value
![在这里插入图片描述](https://img-blog.csdnimg.cn/eae57c5898f644a3bdc239a15a14df43.png)


<font color=#999AAA >代码如下（示例）：



```c
#include <iostream>
#include <fstream>  
 using namespace std;

 int main()
 {
     ofstream my;
     my.open("2.ppm");
     my<<"P3"<<endl;
     int x=200;
     int y=100;
     my<<x<<" "<<y<<endl;
     my<<255<<endl;
     for(int i=y-1;i>=0;i--)
     {
         for(int j=0;j<x;j++)
         {
          //绿色从上到下递减--x，range从0趋近1
          //红色从右到左递减--y，range从0趋近1
           float r=float(j)/float(x);
           float g=float(i)/float(y);
           float b=0.3;
           my<<int(r*255.0)<<" "<<int(g*255.0)<<" "<<int(b*255.0)<<endl;
         }
     }
 }
```
运行结果
![在这里插入图片描述](https://img-blog.csdnimg.cn/46781b26d21544df9634b865df01f2a8.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA6YO95Y2c5Yaw,size_20,color_FFFFFF,t_70,g_se,x_16)



## 2.render常用类的说明
### 2.1 三维向量类vec3的建立（用于colors, locations, directions, offsets...）
```cpp
#include<math.h>
#include<iostream>
using namespace std;
class vec3{
    public:
    float edge[3];
    //默认构造函数
    vec3();
    vec3(float e0,float e1,float e2){
        edge[0]=e0;
        edge[1]=e1;
        edge[2]=e2;
    }
};
```
<font color=#999AAA >main函数使用如下（示例）：
```cpp
#include<iostream>
#include<fstream>
#include "vec3.h"
int main()
 {
     ofstream my;
     my.open("2.ppm");
     my<<"P3"<<endl;
     int x=200;
     int y=100;
     my<<x<<" "<<y<<endl;
     my<<255<<endl;
     for(int i=y-1;i>=0;i--)
     {
         for(int j=0;j<x;j++)
         {
          //绿色从上到下递减--x，range从0趋近1
          //红色从右到左递减--y，range从0趋近1
          //float r=float(j)/float(x);
           //float g=float(i)/float(y);
           //float b=0.3;
           //my<<int(r*255.0)<<" "<<int(g*255.0)<<" "<<int(b*255.0)<<endl;
           vec3 col(float(j)/float(x),float(i)/float(y),0.3);
           my<<int(col.edge[0]*255.0)<<" "<<int(col.edge[1]*255.0)<<" "<<int(col.edge[2]*255.0)<<endl;
         }
     }
 }
```

<font color=#999AAA >该处使用的url网络请求的数据。

<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

### 2.2 ray class
- ray的数学定义：
 $p(t)=A+t*B$
其中$A$是光源位置，$B$是光方向，$p$表示经过时间$t$光线所到达位置点,
![在这里插入图片描述](https://img-blog.csdnimg.cn/8a99d404398543bca884edcf1de5200c.png)
【即光线所需关键元素为起点A和方向B】

 【what is a ray tracer？】
**a ray tracer** is to send rays through pixels and compute what color is seen in the direction of those rays   
                                                                                                                                                                                                                                                                                                                                                                                                  
【渲染流程】
1.计算通过屏幕上不同pexels到达人眼的光线向量（的逆向量）
 2.根据光线向量的xyz坐标计算所形成的颜色
### 3. adding a sphere
关键数学式：
![在这里插入图片描述](https://img-blog.csdnimg.cn/97999eb98c2541caa0ed94d5ea8ac438.png)
```
 其中光线：p(t) = A + t*B
 C为球体中心
```

```cpp
//判断光线是否hit sphere
bool hit_sphere(const vec3 center,float radius,const ray r)
{
    float a=r.direction()*r.direction();
    float b=2.0*(r.direction()*(r.origin()-center));
    float c=my_dot2(r.origin()-center)-radius*radius;
    float dert=b*b-4*a*c;
    return (dert>0);

}
```
### 4.Surface normals(曲面法线) and multiple objects.
- For a sphere, the normal is in the direction of the hitpoint minus the center
- 用彩色地图来形象化法线？？？？
-

### 5.Diffuse Materials（漫反射物体）
[参考链接](https://blog.csdn.net/weixin_44374193/article/details/109378600?spm=1001.2014.3001.5501)
1.漫反射材质自身不发光，只吸收和反射周围的环境光。
2. 漫反射材质的光线反射方向是随机的。
3. 假设模型中每次反射光线被吸收50% 的能量
# 总结
<font color=#999AAA >提示：这里对文章进行总结：
例如：以上就是今天要讲的内容，本文仅仅简单介绍了pandas的使用，而pandas提供了大量能使我们快速便捷地处理数据的函数和方法。
