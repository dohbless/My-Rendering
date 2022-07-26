#include<iostream>
#include<fstream>
#include"math.h"
#include "ray.h"
//test if ok
//判断光线hit sphere具体位置
float hit_sphere(const vec3 center,float radius,const ray r)
{
    float a=r.direction()*r.direction();
    float b=2.0*(r.direction()*(r.origin()-center));
    float c=my_dot2(r.origin()-center)-radius*radius;
    float dert=b*b-4*a*c;
   // return (dert>0);
   if (dert<0) return -1.0;
   return (-1.0*b-sqrt(dert))/(2.0*a);

}
//根据光线的y轴长度映射到对应颜色
vec3 color(const ray h)
{  
    float t= hit_sphere(vec3(0,0,-1),0.5,h);
    if(t>0)//光线和小球有交点
    {
      vec3 real_normal=unit_vector(h.parameter_point(t)-vec3(0.0,0.0,-1.0));
      return 0.5*vec3(real_normal.x()+1,real_normal.y()+1,real_normal.z()+1);
    }
      

    vec3 unit_direction=unit_vector(h.direction());
    //将y映射到(0,1)
    t=0.5*(unit_direction.x()+1.0);

    //线性混合插值：blended_value = (1-t)*start_value + t*end_value
    //return vec3(1.0,1.0,1.0)*(1-t)+vec3(1.0,0.72,0.72)*t; 
    return vec3(1.0,1.0,1.0)*(1.0-t)+vec3(0.9529,0.50588,0.50588)*t;             
    
}
//光线从origin射出。从viewport左下角开始计算，自下而上，自左向右，按行遍历像素。
int main()
 {
     ofstream my;
     my.open("2.ppm");
     my<<"P3"<<endl;
     int x=200;
     int y=100;

     my<<x<<" "<<y<<endl;
     my<<255<<endl;
     vec3 ray_start(0.0,0.0,0.0);
    vec3 left_lower_corner(-2.0,-1.0,-1.0);
    vec3 horizontal_range(4.0,0.0,0.0);
    vec3 vertical_range(0.0,2.0,0.0);
     for(int i=y-1;i>=0;i--)
     {
         for(int j=0;j<x;j++)
         {
           float u=float(i)/float(y);  //竖直，在0~1之间
           float v=float(j)/float(x);  //水平，在0~1之间

           vec3 pixel_pos(left_lower_corner+horizontal_range*v+vertical_range*u);
           ray keep(ray_start,pixel_pos);
           vec3 real_degree=color(keep);
           int real_r=int(255.99*real_degree.x());
           int real_g=int(255.99*real_degree.y());
           int real_b=int(255.99*real_degree.z());
           my<<real_r<<" "<<real_g<<" "<<real_b<<endl;
         }
     }
 }