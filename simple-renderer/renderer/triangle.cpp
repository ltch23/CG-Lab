#include "triangle.h"
#include <utility>
// constructor
#define TOOL 9;  // =  1001 
#define TOOO 8;  // =  1000 
#define TORO 10; // =  1010 
#define OOOL 1;  // =  0001 
#define OOOO 0;  // =  0000 
#define OORO 2;  // =  0010 
#define OBOL 5;  // =  0101 
#define OBOO 4;  // =  0100 
#define OBRO 6;  // =  0110 
#define width 600
#define height 400

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

    
    // draw_point(__pv1, __w, __h, __color_buffer);
    // draw_point(__pv2, __w, __h, __color_buffer);
    // draw_point(__pv3, __w, __h, __color_buffer);
     
    // RELLENAR AQUI BRESENHAM para trazar
    // las lineas entre los puntos __pv1, __pv2 y __pv3
    // cout<<"bresenham pv1"<<endl;
    // bresenham(__pv1,__pv2,__w, __h, __color_buffer);
    // // Esto es: trazar la linea entre __pv1 y __pv2,
    // cout<<"bresenham pv2"<<endl;
    // bresenham(__pv2,__pv3,__w, __h, __color_buffer);
    // // entre __pv1 y __pv3; y entre __pv2 y __pv3
    // cout<<"bresenham pv3"<<endl;
    // bresenham(__pv3,__pv1,__w, __h, __color_buffer);

    cout<<"*************************************"<<endl;
    cout<<"p1: "<<__pv1[0]<<" - "<<__pv1[1]<<endl;    
    cout<<"p2: "<<__pv2[0]<<" - "<<__pv2[1]<<endl;    
    cout<<"p3: "<<__pv3[0]<<" - "<<__pv3[1]<<endl;    
    cout<<"*************************************"<<endl;

    draw_polygon(__pv1,__pv2,__pv3,__w, __h, __color_buffer);
    // scan_line( __pv1,__pv2,__pv3 ,__w,  __h, __color_buffer);
        
            
          

    // everything is alright
    return true;
}

void triangle::draw_point(vector<2> p, unsigned int __w, unsigned int __h, float*& __color_buffer) {
    int __x = p[0];
    int __y = p[1];
    // cout<<"x: "<<__x<<" y: "<<__y<<endl;
    __color_buffer[(__y * __w + __x) * 4 + 0] = _material._color[0];
    __color_buffer[(__y * __w + __x) * 4 + 1] = _material._color[1];
    __color_buffer[(__y * __w + __x) * 4 + 2] = _material._color[2];
    __color_buffer[(__y * __w + __x) * 4 + 3] = _material._color[3];
}




void triangle::bresenham(vector<2> pv1, vector<2> pv2,unsigned int __w, unsigned int __h, float*& __color_buffer){

    // cout<<"x1: "<<pv1[0]<<" - y1: "<<pv1[1]<<endl;
    // cout<<"x2 : "<<pv2[0]<<" - y2: "<<pv2[1]<<endl;

    int dx = abs(pv2[0] - pv1[0]);
    int dy = abs(pv2[1] - pv1[1]);

    if (dx >= dy){
        int i, j, k;
        i = 2*dy-dx;
        j = 2*dy;
        k = 2*(dy-dx);
        if (!(pv1[0] < pv2[0])) {
            swap(pv1[0], pv2[0]);
            swap(pv1[1], pv2[1]);
        }
        draw_point(pv1, __w, __h, __color_buffer);
        
        while (pv1[0] < pv2[0]) {
            if (i < 0)
            i += j;
            else {
                if (pv1[1] < pv2[1])
                pv1[1]++;
                else
                pv1[1]--;
                i += k;
            }
            pv1[0]++;
            draw_point(pv1, __w, __h, __color_buffer);
        }
    }
            
    else{
        
        int i, j, k;
        
        i = 2*dx-dy;
        j = 2*dx;
        k = 2*(dx-dy);
        if (!(pv1[1] < pv2[1])) {
            swap(pv1[0], pv2[0]);
            swap(pv1[1], pv2[1]);
        }
        draw_point(pv1, __w, __h, __color_buffer);
        while (pv1[1] < pv2[1]) {
            if (i < 0)
            i += j;
            else {
                if (pv1[0] < pv2[0])
                pv1[0]++;
                else
                pv1[0]--;
                i += k;
            }
            pv1[1]++;
        draw_point(pv1, __w, __h, __color_buffer);
        }
    }
    
}





void triangle::draw_polygon(vector<2> p1, vector<2> p2, vector<2> p3,unsigned int __w, unsigned int __h, float*& __color_buffer){
    
        
    int p[4][4];
    int inter[4],x,y;
    int xmin,ymin,xmax,ymax;
    
    p[0][0]=p1[0];
    p[0][1]=p1[1];
    p[1][0]=p2[0];
    p[1][1]=p2[1];
    p[2][0]=p3[0];
    p[2][1]=p3[1];

    p[3][0]=p[0][0];
    p[3][1]=p[0][1];
    xmin=xmax=p[0][0];
    ymin=ymax=p[0][1];


    for(int i=0;i<3;i++){
        if(xmin>p[i][0])
        xmin=p[i][0];
        if(xmax<p[i][0])
        xmax=p[i][0];
        if(ymin>p[i][1])
        ymin=p[i][1];
        if(ymax<p[i][1])
        ymax=p[i][1];
    }
    
    
    float z=ymin+0.1;

    while(z<=ymax){

        int x1,x2,y1,y2,temp;
        int c=0;
        for(int i=0;i<3;i++)
        {
            x1=p[i][0];
            y1=p[i][1];
            x2=p[i+1][0];
            y2=p[i+1][1];
            if(y2<y1)
            {
                swap(x1,x2);
                swap(y1,y2);

            }
            if(z<=y2&&z>=y1)
            {
                if((y1-y2)==0)
                     x=x1;
                else{ // used to make changes in x. so that we can fill our polygon after cerain distance
                    x=((x2-x1)*(z-y1))/(y2-y1);
                    x=x+x1;
                }
                if(x<=xmax && x>=xmin)
                inter[c++]=x;
            }
        }

        //SORT FUNCTION
        int j,i;

        // for(i=0;i<3;i++){
        //     cout<<p[i][0]<<","<<p[i][1]<<"-"<<p[i+1][0]<<","<<p[i+1][1]<<endl;
        // }

        cout<<endl;
        for(int i=0; i<c;i+=2){
            vector<2> p1;
            vector<2> p2;
            p1[0] = inter[i];
            p2[0] = inter[i+1];
            p1[1]=p2[1]=int(z);

            clipping(p1,p2);
            bresenham(p1,p2,__w,__h,__color_buffer);
            }
        z++;
        }
    }
    
    int triangle::code(vector<2> __pv1)
    {
        int a = 0;
        if (__pv1[1] <= 0){
            //RIGHT
            if (__pv1[0] >= width){
                a = TORO;
            }
            else if (__pv1[0] <= 0){
                //LEFT
                a = TOOL;
            }
            else{
                //CENTER
                a = TOOO;
            }
        }
        else if (__pv1[1] >= height){
            if (__pv1[0] >= width){
                a = OBRO;
            }
            else if (__pv1[0] <= 0){
                //LEFT
                a = OBOL;
            }
            else{
                //CENTER
                a = OBOO;
            }
        }
        else{
            //CENTER
            if (__pv1[0] >= width){
                a = OORO;
            }
            else if (__pv1[0] <= 0){
                //LEFT
                a = OOOL;
            }
            else{
                //CENTER
                a = OOOO;
            }
        }
        return a;
    }
    
    int triangle::interseccion(vector<2> &__pv1)
    {

        if (__pv1[0] >= width){
            __pv1[0] = width - 1;
        }
        else if (__pv1[0] <= 0){
            __pv1[0] = 1;
        }
        if (__pv1[1] >= height){
            __pv1[1] = height - 1;
        }
        else if (__pv1[1] <= 0){
            __pv1[1] = 1;
        }
    }

    void triangle::clipping(vector<2> &__pv1, vector<2> &__pv2)
    {
        // int a = code(__pv1);
        // // //std::cout << "a " <<a<< '\n';
        // int b = code(__pv2);
        // // //std::cout << "b " <<b<< '\n';
        // // int c = a & b;
        // // //CASO 1
        // //SE ACEPTA COMPLETO
        // if (a & b > 0) {
        interseccion(__pv1);
        interseccion(__pv2);
        //  }
    }
