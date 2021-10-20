#include "vec3.h"
#ifndef _RAY_H_
#define _RAY_H_
class ray{
    public:
    vec3 A;
    vec3 B;
    ray(){};
    ray(const vec3 a,const vec3 b)
    {
        A=a;
        B=b;
    }
    //返回起点值,此处const表示参数不可更改
    vec3 origin() const{
        return A;
    }
    //返回方向值
    vec3 direction() const{
       return B; 
    }
    
    //返回给定t的坐标
    vec3 parameter_point(float t)const{
        return A+B*t;
    }


};
#endif