// copy from UNNC CG Lab 5.2
// Edit By Binghong YU 16518735 2018.11.27

#pragma once

#ifdef _WIN32
#include <GL/glut.h>
#include <Windows.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <string>
#include <cmath>
#include <map>

#include "../../Framework/Engine/Scene.h"
using namespace std;

class ObjLoader{

public:

    ObjLoader(string filename);
    //void Init();
    void Draw();

private:

    //GLint lastFrameTime;
    //GLint animationLastingTime;

    vector<vector<GLfloat>>vSets;
    vector<vector<vector<GLint>>>fSets;
    vector<string>fSetsMtlLabel;
    vector<vector<GLfloat>>vnSets;
    vector<vector<GLfloat>>vtSets;

    map<string, vector<vector<GLfloat>>>mtlMap;

};

