/*记录所有与光线相交的物体,抽象类*/
#include "ray.h"
#ifndef _HITABLE_H_
#define _HITABLE_H_
 struct hit_record{
     float t; //光线尺度t
      vec3 p;  //交点坐标
      vec3 normal; //交点法线
 };

 class hitable{
       public:
       /*虚函数是指一个类中你希望重载的成员函数 ，当你用一个基类指针或引用 
         指向一个继承类对象的时候，调用一个虚函数时, 实际调用的是继承类的版本*/
       virtual bool hit(const ray & r,float t_min,float t_max,hit_record &rec)const =0;

 };
#endif