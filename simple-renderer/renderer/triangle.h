#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <iostream>
#include <utility>
#include "object.h"

using namespace std;

//! triangle
class triangle: public object {
public:
    //! constructor
    triangle(matrix<4, 4>& __t, material &__material, vector<3> __v1, vector<3> __v2,
            vector<3> __v3);

    //! rasterize
    virtual bool rasterize(camera* __camera, unsigned short __w, unsigned short __h,
            vector<3> __ambient, dlight *__dlights, unsigned long __num_dlights, plight *__plights,
            unsigned long __num_plights, float*& __color_buffer, float*& __depth_buffer);

    //! draw_points
    void draw_point(vector<2> p, unsigned int __w, unsigned int __h, float*& __color_buffer);
    void bresenham(vector<2> pv1, vector<2> pv2,unsigned int __w, unsigned int __h, float*& __color_buffer);
    void draw_polygon(vector<2> p1, vector<2> p2, vector<2> p3,unsigned int __w, unsigned int __h, float*& __color_buffer);

    void clipping(vector<2> &__pv1, vector<2> &__pv2);
    void interseccion(vector<2> &__pv1);
    int code(vector<2> __pv1);
    float dist(vector<2> p1, vector<2> p2);

    protected:
        //! vertex 1
    vector<3> _v1;

    //! vertex 2
    vector<3> _v2;

    //! vertex 3
    vector<3> _v3;
    
    vector<2> v1;

    vector<2> v2;

    vector<2> v3;

    float area;
};

#endif
