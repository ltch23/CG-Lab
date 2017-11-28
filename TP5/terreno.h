#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

template<typename Out>
void split(const string &s, char delim, Out result) {
  stringstream ss;
  ss.str(s);
  string item;
  while (getline(ss, item, delim)) {
    *(result++) = item;
  }
}

vector<string> split(const string &s, char delim) {
  vector<string> elems;
  split(s, delim, back_inserter(elems));
  return elems;
}
typedef struct{
  GLfloat s, t;
  GLfloat nx, ny, nz;
  GLfloat x, y, z;
} PuntoTerreno;

class Terreno{

public:
  Terreno();
  ~Terreno();
  bool load(string filename) ;
  void display();
  void computeNormals();
  int nb_pt_x, nb_pt_z;
  float dist_x, dist_z;
  int coord_x, coord_y;

  GLvoid Normalizar(GLfloat&, GLfloat&, GLfloat&);
  vector<GLuint> list_ind;
  vector<PuntoTerreno> list_point;
  void calcularNormal(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, PuntoTerreno &);
};

Terreno::Terreno(){

  nb_pt_x=nb_pt_z= coord_x= coord_y=0;
  dist_x=dist_z=0.0;
  list_ind.reserve(60000);
}

Terreno::~Terreno(){}
void Terreno::display(){
 
  glPointSize(5.0f);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(PuntoTerreno),&list_point[0].s);
  glDrawElements(GL_TRIANGLES,60000, GL_UNSIGNED_INT,(void*)&list_ind[0]);
}

bool Terreno::load(string filename){

  ifstream file(filename);
  string text;

  int cont = 0;
  int cont_x = 0,cont_z = 0;
  float cont_s = 0.0, cont_t = 0.0;
  int ii=0;
  char white_space[] = " ";

  getline(file, text);
  vector<string> values = split(text,'\t');
  coord_x=stoi(values[5]);
  coord_y=stoi(values[6]);
  dist_x=stoi(values[7]);
  dist_z=stoi(values[8]);
  nb_pt_x=stoi(values[9]);
  nb_pt_z=stoi(values[10]);
  

  while (getline(file, text)){
    istringstream iss(text);
    string word;

    while(iss>>word){
        if(cont==nb_pt_x){
            cont_z += dist_z;
            cont_t += 0.01;
            cont_s = 0.0;
            cont_x = 0;
            cont = 0;
        }
        PuntoTerreno point;
        point.x = cont_x;
        point.y = stoi(word);
        point.z = cont_z;

        point.s = cont_s;
        point.t = cont_t;

        list_point.push_back(point);
        cont++;
        cont_x+=dist_x;
        cont_s+=1.0f/101.0f;
        ii++;
      }

    }
  
    file.close();
    int r=0;
    for(int i=0; i<nb_pt_z-1; i++){
        for(int j=0; j<nb_pt_x-1; j++){
            list_ind[r]=i*nb_pt_z+j;          r++;
            list_ind[r]=(i+1)*nb_pt_z+j;      r++;
            list_ind[r]=(i+1)*nb_pt_z+(j+1);  r++;
            list_ind[r]=i*nb_pt_z+j;          r++;
            list_ind[r]=(i+1)*nb_pt_z+(j+1);  r++;
            list_ind[r]=i*nb_pt_z+(j+1);      r++;
          }
      }
    computeNormals();
}

void Terreno::calcularNormal(GLfloat p1x, GLfloat p1y, GLfloat p1z, GLfloat p2x, GLfloat p2y, GLfloat p2z,
                             GLfloat p3x, GLfloat p3y, GLfloat p3z, PuntoTerreno & pt){
  GLfloat V1x = p2x-p1x;
  GLfloat V1y = p2y-p1y;
  GLfloat V1z = p2z-p1z;
  GLfloat V2x = p3x-p2x;
  GLfloat V2y = p3y-p2y;
  GLfloat V2z = p3z-p2z;
  pt.nx += V1y*V2z - V1z*V2y;
  pt.ny += V1z*V2x - V1x*V2z;
  pt.nz += V1x*V2y - V1y*V2x;

}

GLvoid Terreno::Normalizar(GLfloat &nx,GLfloat &ny,GLfloat &nz){
  GLfloat distancia =sqrt(nx*nx+ny*ny+nz*nz);
  ny /= distancia;
  nz /= distancia;
}

void Terreno::computeNormals(){
  
  int r = 0,c=0;
  for(int i=0; i<nb_pt_z; i++){
    for(int j=0; j<nb_pt_x; j++){
        int pos=i*nb_pt_z+j;
        if(j+1<nb_pt_x and i+1<nb_pt_z){
            calcularNormal(list_point[pos].x,list_point[pos].z,list_point[pos].y,list_point[pos+1].x,
                            list_point[pos+1].z, list_point[pos+1].y,list_point[pos+nb_pt_x+1].x,
                            list_point[pos+nb_pt_x+1].z,list_point[pos+nb_pt_x+1].y,list_point[pos]);
            calcularNormal(list_point[pos].x,list_point[pos].z,list_point[pos].y,list_point[pos+nb_pt_x].x,
                            list_point[pos+nb_pt_x].z,list_point[pos+nb_pt_x].y,list_point[pos+nb_pt_x+1].x,
                            list_point[pos+nb_pt_x+1].z,list_point[pos+nb_pt_x+1].y,list_point[pos]);
            c+=2;
          }
        if(j-1>=0 and i+1<nb_pt_z){
            calcularNormal(list_point[pos].x,list_point[pos].z,list_point[pos].y,list_point[pos-1].x,
                            list_point[pos-1].z,list_point[pos-1].y,list_point[pos+nb_pt_x].x,
                            list_point[pos+nb_pt_x].z,list_point[pos+nb_pt_x].y,list_point[pos]);
            c++;
          }
        if(j-1>=0 and i-1>=0){
            calcularNormal(list_point[pos].x,list_point[pos].z,list_point[pos].y,list_point[pos-1].x,
                            list_point[pos-1].z,list_point[pos-1].y,list_point[pos+nb_pt_x-1].x,
                            list_point[pos+nb_pt_x-1].z,list_point[pos+nb_pt_x-1].y,list_point[pos]);

            calcularNormal(list_point[pos].x,list_point[pos].z,list_point[pos].y,list_point[pos-nb_pt_x].x,
                            list_point[pos-nb_pt_x].z,list_point[pos-nb_pt_x].y,list_point[pos-nb_pt_x-1].x,
                            list_point[pos-nb_pt_x-1].z,list_point[pos-nb_pt_x-1].y,list_point[pos]);

            c+=2;
          }
        if(j+1<nb_pt_x and i-1>=0){
            calcularNormal(list_point[pos].x,list_point[pos].z,list_point[pos].y,list_point[pos+1].x,
                            list_point[pos+1].z,list_point[pos+1].y,list_point[pos-nb_pt_x].x,
                            list_point[pos-nb_pt_x].z,list_point[pos-nb_pt_x].y,list_point[pos]);

            c++;
          }
        list_point[pos].nx/=c;
        list_point[pos].ny/=c;
        list_point[pos].nz/=c;

        Normalizar(list_point[pos].nx,list_point[pos].ny,list_point[pos].nz);
      }
  }
}
