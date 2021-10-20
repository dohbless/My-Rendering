#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "hitable.h"
#include "ray.h"
class sphere:public hitable{
    public:
      vec3 center;
      float radius;
      sphere(){};
      sphere(vec3 cen,float r):center(cen),radius(r) {};
      virtual bool hit(const ray & r,float t_min,float t_max,hit_record &rec)const =0;

};
/*判断给定光线和球体的碰撞情况*/
bool sphere::hit(const ray &r,float t_min,float t_max,hit_record &rec)const{
     vec3 dis=vec3(r.A-center);
     float a=my_dot2(r.B);
     float b=2*r.B*dis;
     float c=my_dot2(dis)-radius*radius;
     float dert=b*b-4.0*a*c;
     if(dert>0)
     { 
         //先求小t，如果符合要求就返回
         float t=(-1.0*b-sqrt(dert))/(2.0*a);
         if((t>t_min)&&(t<t_max))
         {
             rec.t=t;
             rec.p=r.parameter_point(t);
             rec.normal=unit_vector(vec3(rec.p-center));
             return true;
         }
         t=(-1.0*b+sqrt(dert))/(2.0*a);
         if((t>t_min)&&(t<t_max))
         {
             rec.t=t;
             rec.p=r.parameter_point(t);
             rec.normal=unit_vector(vec3(rec.p-center));
             return true;
         }

     }
    return false;
}
#endif