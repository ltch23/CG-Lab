#include "triangle.h"
// constructor
triangle::triangle(matrix<4, 4>& __t, material &__material, vector<3> __v1, vector<3> __v2,
        vector<3> __v3) :
        object(__t, __material) {
    // initialize vertices
    _v1 = __v1;
    _v2 = __v2;
    _v3 = __v3;
}

// rasterize
bool triangle::rasterize(camera* __camera, unsigned short __w, unsigned short __h,
        vector<3> __ambient, dlight *__dlights, unsigned long __num_dlights, plight *__plights,
        unsigned long __num_plights, float*& __color_buffer, float*& __depth_buffer) {
    //<<TODO>> transform, lit, project, rasterize, calculate final color and depth

    // initialize color buffer
    __color_buffer = new float[__w * __h * 4];

    // initialize depth buffer
    __depth_buffer = new float[__w * __h];

    // model transform
    vector<4> __v1;
    __v1[0] = _v1[0];
    __v1[1] = _v1[1];
    __v1[2] = _v1[2];
    __v1[3] = 1.0;
    vector<4> __v2;
    __v2[0] = _v2[0];
    __v2[1] = _v2[1];
    __v2[2] = _v2[2];
    __v2[3] = 1.0;
    vector<4> __v3;
    __v3[0] = _v3[0];
    __v3[1] = _v3[1];
    __v3[2] = _v3[2];
    __v3[3] = 1.0;
    __v1 = _t * __v1;
    __v2 = _t * __v2;
    __v3 = _t * __v3;

    // world
    matrix<4, 4> __ww;
    __ww[0][0] = __camera->right()[0];
    __ww[1][0] = __camera->right()[1];
    __ww[2][0] = __camera->right()[2];
    __ww[0][1] = __camera->up()[0];
    __ww[1][1] = __camera->up()[1];
    __ww[2][1] = __camera->up()[2];
    __ww[0][2] = __camera->dir()[0];
    __ww[1][2] = __camera->dir()[1];
    __ww[2][2] = __camera->dir()[2];

    // world transform
    __v1 = __ww * (__v1 - __camera->pos());
    __v2 = __ww * (__v2 - __camera->pos());
    __v3 = __ww * (__v3 - __camera->pos());

    // orthogonal projection
    vector<2> __pv1;
    __pv1[0] = __v1[0];
    __pv1[1] = __v1[1];
    vector<2> __pv2;
    __pv2[0] = __v2[0];
    __pv2[1] = __v2[1];
    vector<2> __pv3;
    __pv3[0] = __v3[0];
    __pv3[1] = __v3[1];

    // simulating a frustrum
    __pv1[0] += 5.f;
    __pv1[0] *= __w / 10.f;
    __pv1[1] += 5.f;
    __pv1[1] *= __h / 10.f;
    __pv2[0] += 5.f;
    __pv2[0] *= __w / 10.f;
    __pv2[1] += 5.f;
    __pv2[1] *= __h / 10.f;
    __pv3[0] += 5.f;
    __pv3[0] *= __w / 10.f;
    __pv3[1] += 5.f;
    __pv3[1] *= __h / 10.f;

    // RELLENAR AQUI BRESENHAM para trazar
    // las lineas entre los puntos __pv1, __pv2 y __pv3
    // Esto es: trazar la linea entre __pv1 y __pv2,
    // entre __pv1 y __pv3; y entre __pv2 y __pv3

    draw_point(__pv1, __w, __h, __color_buffer);
    draw_point(__pv2, __w, __h, __color_buffer);
    draw_point(__pv3, __w, __h, __color_buffer);

    // everything is alright
    return true;
}

void triangle::draw_point(vector<2> p, unsigned int __w, unsigned int __h, float*& __color_buffer) {
    int __x = p[0];
    int __y = p[1];
    __color_buffer[(__y * __w + __x) * 4 + 0] = _material._color[0];
    __color_buffer[(__y * __w + __x) * 4 + 1] = _material._color[1];
    __color_buffer[(__y * __w + __x) * 4 + 2] = _material._color[2];
    __color_buffer[(__y * __w + __x) * 4 + 3] = _material._color[3];
}

