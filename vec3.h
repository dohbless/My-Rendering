/*class vec3
 * 用来表示三维向量
 * 如color、location、directions
 * */
#include<math.h>
#include<iostream>
using namespace std;
#ifndef _VEC3_H_  //防止重复包含该头文件
#define _VEC3_H_
class vec3{
    public:
    float edge[3];
    //构造函数
    vec3(){};
    vec3(float e0,float e1,float e2){
        edge[0]=e0;
        edge[1]=e1;
        edge[2]=e2;
    }
    //函数后加const表示不可以修改类成员
    inline float x() const{
           return edge[0];
    }
    inline float y() const{
            return edge[1];
    }
    inline float z() const{
            return edge[2];
    }
    inline float r() const{
           return edge[0];
    }
    inline float g() const{
            return edge[1];
    }
    inline float b() const{
            return edge[2];
    }
    
    //const类型对象只能调用const成员函数，非const对象可以调用const函数
    inline float length() const{
        return sqrt(edge[1]*edge[1]+edge[0]*edge[0]+edge[2]*edge[2]);
    }
    inline float lengthSquared()const{
        return edge[1]*edge[1]+edge[0]*edge[0]+edge[2]*edge[2];
    }

    //运算符重载
    inline vec3 operator /(const float t);
    //运算符重载
    inline vec3 operator *(const float t);

};

//vec3 / float
vec3 vec3::operator /(const float t)
{
    return vec3(this->edge[0]/t,this->edge[1]/t,this->edge[2]/t);
}
//vec3 * (const)float
vec3 vec3::operator *(const float t )
{
    return vec3(this->edge[0]*t,this->edge[1]*t,this->edge[2]*t);
}

//向量归一化
inline vec3 unit_vector(vec3 v)
{
   return v/v.length();
}

//类别外普通运算符重载函数 const&const + - * /
inline vec3 operator +(const vec3 a,const vec3 b)
{
    return vec3(a.x()+b.x(),a.y()+b.y(),a.z()+b.z());
}
inline float operator *(const vec3 a,const vec3 b)
{
    return a.x()*b.x()+a.y()*b.y()+a.z()*b.z();
}
inline vec3 operator -(const vec3 a,const vec3 b)
{
    return vec3(a.x()-b.x(),a.y()-b.y(),a.z()-b.z());
}
inline vec3 operator /(const vec3 a, const vec3 b)
{
    return vec3(a.x()/b.x(),a.y()/b.y(),a.z()/b.z());
}

//const vec3 *float
inline vec3 operator *(const vec3 &v,float t)
{
    return vec3(v.x()*t,v.y()*t,v.z()*t);
}
//float*const vec3
inline vec3 operator *(float t,const vec3 &v)
{
    return vec3(v.x()*t,v.y()*t,v.z()*t);
}
//vec3^2 即vec3平方
inline float my_dot2(const vec3 a)
{
      return a.x()*a.x()+a.y()*a.y()+a.z()*a.z();
}
//vec3.*vec3点积
inline float dot(const vec3 a, const vec3 b)
{
    return a.x()*b.x()+a.y()*b.y()+a.z()+b.z();
}

inline vec3 cross(const vec3 a,const vec3 b)
{
    return vec3(a.y()*b.z()-b.y()*a.z(),-(a.x()*b.z()-b.x()*a.z()),a.x()*b.y()-b.x()*a.y());
}

#endif