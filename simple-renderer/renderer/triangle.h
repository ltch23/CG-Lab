#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "object.h"

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

protected:
    //! vertex 1
    vector<3> _v1;

    //! vertex 2
    vector<3> _v2;

    //! vertex 3
    vector<3> _v3;
};

#endif
