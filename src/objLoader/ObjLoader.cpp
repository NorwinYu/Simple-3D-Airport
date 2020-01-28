// copy from UNNC CG Lab 5.2
// Edit By Binghong YU 16518735 2018.11.27

#include "ObjLoader.h"
#include <fstream>
#include <iostream>
using namespace std;

//GLfloat m = 1.0f;

ObjLoader::ObjLoader(string filename)
{
    string line;
    fstream f;

    f.open(filename, ios::in);

    if (!f.is_open())
    {
        cout << "Something Went Wrong When Opening .obj files" << endl;
    }

    string tmpFGroupName = "";

    while (!f.eof())
    {
        getline(f, line);

        vector<string>parameters;
        string tailMark = " ";
        string ans = "";
        line = line.append(tailMark);

        for (int i = 0; i < line.length(); i++)
        {
            char ch = line[i];
            if (ch != ' ')
            {
                ans+=ch;
            }
            else
            {
                if (ans != "")
                {
                    parameters.push_back(ans);
                }
                ans = "";
            }
        }

        if (parameters.size() != 0)
        {
            string resourceDirectory = "../src/data/";

            if (parameters[0] == "mtllib")
            {
                resourceDirectory = resourceDirectory.append(parameters[1]);
                resourceDirectory.pop_back();
                // cout << "find mtl file: " << resourceDirectory << endl;

                fstream fm;
                string lineM;

                fm.open(resourceDirectory, ios::in);

                if (!fm.is_open())
                {
                    cout << "Something Went Wrong When Opening .mtl files" << endl;
                }
                else
                {
                    vector<GLfloat> tmpKa;
                    vector<GLfloat> tmpKd;
                    vector<GLfloat> tmpKs;

                    string tmpGroupName = "";

                    while (!fm.eof())
                    {
                        getline(fm, lineM);

                        vector<string>parametersM;
                        string tailMarkM = " ";
                        string ansM = "";
                        lineM = lineM.append(tailMarkM);

                        for (int i = 0; i < lineM.length(); i++)
                        {
                            char ch = lineM[i];
                            if (ch != ' ' && ch != '\t')
                            {
                                ansM+=ch;
                            }
                            else
                            {
                                if (ansM != "")
                                {
                                    parametersM.push_back(ansM);
                                }
                                ansM = "";
                            }
                        }

                        if (parametersM.size() != 0)
                        {
                            if (parametersM[0] != "#")
                            {
                                if (parametersM[0] == "newmtl")
                                {
                                    // cout << "find new mtl name: "<< parametersM[1] << endl;

                                    tmpGroupName = parametersM[1];
                                }

                                if (parametersM[0] == "Ka")
                                {
                                    tmpKa.clear();
                                    tmpKa.push_back(atof(parametersM[1].c_str()));
                                    tmpKa.push_back(atof(parametersM[2].c_str()));
                                    tmpKa.push_back(atof(parametersM[3].c_str()));
                                }

                                if (parametersM[0] == "Kd")
                                {
                                    tmpKd.clear();
                                    tmpKd.push_back(atof(parametersM[1].c_str()));
                                    tmpKd.push_back(atof(parametersM[2].c_str()));
                                    tmpKd.push_back(atof(parametersM[3].c_str()));
                                }

                                if (parametersM[0] == "Ks")
                                {
                                    tmpKs.clear();
                                    tmpKs.push_back(atof(parametersM[1].c_str()));
                                    tmpKs.push_back(atof(parametersM[2].c_str()));
                                    tmpKs.push_back(atof(parametersM[3].c_str()));

                                    vector<vector<GLfloat>> newMtl;
                                    newMtl.push_back(tmpKa);
                                    newMtl.push_back(tmpKd);
                                    newMtl.push_back(tmpKs);

                                    mtlMap.insert(pair <string, vector<vector<GLfloat>>> (tmpGroupName, newMtl));
                                    tmpGroupName = "";
                                }
                            }
                        }
                    }
                }

                fm.close();

            }

            if (parameters[0] == "usemtl")
            {
                tmpFGroupName = parameters[1];
            }

            if (parameters[0] != "#")
            {
                if (parameters[0] == "v")
                {
                    vector<GLfloat>Point;
                    for (int i = 0; i < 3; i++)
                    {
                        GLfloat xyz = atof(parameters[i+1].c_str());
                        Point.push_back(xyz);
                    }
                    vSets.push_back(Point);
                    // cout << "find v point: " << Point[0] << ", " << Point[1] << ", " << Point[2] << endl;
                }
                else if (parameters[0] == "vn") {
                    vector<GLfloat>vnValueSets;
                    for (int i = 0; i < 3; i++) {
                        GLfloat vnxyz = atof(parameters[i+1].c_str());
                        vnValueSets.push_back(vnxyz);
                    }
                    vnSets.push_back(vnValueSets);
                    // cout << "find vn point: " << vnValueSets[0] << ", " << vnValueSets[1] << ", " << vnValueSets[2] << endl;
                }
                else if (parameters[0] == "vt") {
                    vector<GLfloat>vtValueSets;
                    for (int i = 0; i < 3; i++) {
                        GLfloat vnxyz = atof(parameters[i+1].c_str());
                        vtValueSets.push_back(vnxyz);
                    }
                    vtSets.push_back(vtValueSets);
                    // cout << "find vn point: " << vtValueSets[0] << ", " << vtValueSets[1] << ", " << vtValueSets[2] << endl;
                }
                else if (parameters[0] == "f")
                {
                    //cout << "find f: " << endl;
                    vector<vector<GLint>>fIndexSets;
                    vector<GLint>vIndexSets;
                    vector<GLint>vtIndexSets;
                    vector<GLint>vnIndexSets;

                    for (int i = 1; i < parameters.size(); i++)
                    {
                        int mode = 0;
                        string x = parameters[i];
                        string ans = "";
                        for (int j = 0; j < x.length(); j++)
                        {
                            char ch = x[j];
                            if (ch != '/')
                            {
                                ans += ch;
                            }
                            else
                            {
                                GLint index = atof(ans.c_str());
                                index = index - 1;

                                if (mode == 0)
                                {
                                    // cout << "find v index: " << index << endl;
                                    vIndexSets.push_back(index);
                                }
                                else if (mode == 1)
                                {
                                    // cout << "find vt index: " << index << endl;
                                    vtIndexSets.push_back(index);
                                }

                                mode = mode + 1;
                                ans = "";
                            }
                        }

                        GLint index = atof(ans.c_str());

                        if (index > 0)
                        {
                            index = index - 1;

                            // cout << "find vn index: " << index << " ans: "<< ans << endl;
                            vnIndexSets.push_back(index);
                        }
                    }
                    fIndexSets.push_back(vIndexSets);
                    fIndexSets.push_back(vtIndexSets);
                    fIndexSets.push_back(vnIndexSets);
                    fSets.push_back(fIndexSets);
                    fSetsMtlLabel.push_back(tmpFGroupName);

                    cout << " " << endl;
                }
            }
        }
    }
    f.close();
    cout << "find v: " << vSets.size() << endl;
    cout << "find vt: " << vtSets.size() << endl;
    cout << "find vn: " << vnSets.size() << endl;
    cout << "find f: " << fSets.size() << endl;

}

//void ObjLoader::Init()
//{
//	lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
//	animationLastingTime = 0;
//}
//
//GLfloat morphRadis(vector<vector<GLfloat>>x) {
//	GLfloat maxL = 0.0f;
//	for (int i = 0; i < x.size(); i++)
//	{
//		GLfloat vertex[3];
//		vertex[0] = (x[i])[0];
//		vertex[1] = (x[i])[1];
//		vertex[2] = (x[i])[2];
//
//		GLfloat L = sqrt(vertex[0] * vertex[0] + vertex[1] * vertex[1] + vertex[2] * vertex[2]);
//		if (L > maxL) {
//			maxL = L;
//		}
//	}
//
//	return maxL;
//}


void ObjLoader::Draw(){

    //GLfloat morphR = morphRadis(vSets);
    //cout << morphR << endl;

    //const GLint animationEndTime = 4000;

    //GLint currentFrameTime = glutGet(GLUT_ELAPSED_TIME);

    //animationLastingTime += currentFrameTime - lastFrameTime;

    /*GLfloat step = (GLfloat)animationLastingTime / animationEndTime;

    if (step > 1.0f) {
        step = 1.0f;
        glutSolidSphere(morphR, 40, 50);
    }*/

//    glBegin(GL_TRIANGLES);

    //glDisable(GL_COLOR_MATERIAL);

//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_COLOR_MATERIAL);
//    glBindTexture(GL_TEXTURE_2D, texID);

    for (int i = 0; i < fSets.size(); i++) {

        if(fSets[i][0].size() == 3)
        {
            glBegin(GL_TRIANGLES);
        }
        else
        {
            glBegin(GL_POLYGON);
        }

        //three vertex represrnt a surface
        GLfloat SV1[3];
        GLfloat	SV2[3];
        GLfloat SV3[3];
        GLfloat SV4[3];

        GLfloat VN1[3];
        GLfloat VN2[3];
        GLfloat VN3[3];
        GLfloat VN4[3];

        GLfloat VT1[2];
        GLfloat VT2[2];
        GLfloat VT3[2];
        GLfloat VT4[2];

        GLint firstVertexIndex = (fSets[i][0])[0];
        GLint secondVertexIndex = (fSets[i][0])[1];
        GLint thirdVertexIndex = (fSets[i][0])[2];
        GLint fourthVertexIndex;

        GLint firstNVertexIndex = (fSets[i][2])[0];
        GLint secondNVertexIndex = (fSets[i][2])[1];
        GLint thirdNVertexIndex = (fSets[i][2])[2];
        GLint fourthNVertexIndex;

        GLint firstTVertexIndex = (fSets[i][1])[0];
        GLint secondTVertexIndex = (fSets[i][1])[1];
        GLint thirdTVertexIndex = (fSets[i][1])[2];
        GLint fourthTVertexIndex;

        SV1[0] = (vSets[firstVertexIndex])[0];
        SV1[1] = (vSets[firstVertexIndex])[1];
        SV1[2] = (vSets[firstVertexIndex])[2];

        SV2[0] = (vSets[secondVertexIndex])[0];
        SV2[1] = (vSets[secondVertexIndex])[1];
        SV2[2] = (vSets[secondVertexIndex])[2];

        SV3[0] = (vSets[thirdVertexIndex])[0];
        SV3[1] = (vSets[thirdVertexIndex])[1];
        SV3[2] = (vSets[thirdVertexIndex])[2];

        VN1[0] = (vnSets[firstNVertexIndex])[0];
        VN1[1] = (vnSets[firstNVertexIndex])[1];
        VN1[2] = (vnSets[firstNVertexIndex])[2];

        VN2[0] = (vnSets[secondNVertexIndex])[0];
        VN2[1] = (vnSets[secondNVertexIndex])[1];
        VN2[2] = (vnSets[secondNVertexIndex])[2];

        VN3[0] = (vnSets[thirdNVertexIndex])[0];
        VN3[1] = (vnSets[thirdNVertexIndex])[1];
        VN3[2] = (vnSets[thirdNVertexIndex])[2];

        VT1[0] = (vtSets[firstTVertexIndex])[0];
        VT1[1] = (vtSets[firstTVertexIndex])[1];

        VT2[0] = (vtSets[secondTVertexIndex])[0];
        VT2[1] = (vtSets[secondTVertexIndex])[1];

        VT3[0] = (vtSets[thirdTVertexIndex])[0];
        VT3[1] = (vtSets[thirdTVertexIndex])[1];

        if ((fSets[i][0]).size() == 4)
        {
            fourthVertexIndex = (fSets[i][0])[3];
            fourthNVertexIndex = (fSets[i][2])[3];
            fourthTVertexIndex = (fSets[i][1])[3];

            SV4[0] = (vSets[fourthVertexIndex])[0];
            SV4[1] = (vSets[fourthVertexIndex])[1];
            SV4[2] = (vSets[fourthVertexIndex])[2];

            VN4[0] = (vnSets[fourthNVertexIndex])[0];
            VN4[1] = (vnSets[fourthNVertexIndex])[1];
            VN4[2] = (vnSets[fourthNVertexIndex])[2];

            VT4[0] = (vtSets[fourthTVertexIndex])[0];
            VT4[1] = (vtSets[fourthTVertexIndex])[1];
        }

        if (mtlMap.size() != 0)
        {
            map<string, vector<vector<GLfloat>>>::iterator j = mtlMap.find(fSetsMtlLabel[i]);

            if (j != mtlMap.end())
            {
                vector<vector<GLfloat>> mtl = j->second;

                float ka[4] = {mtl[0][0], mtl[0][1], mtl[0][2], 1};
                float kd[4] = {mtl[1][0], mtl[1][1], mtl[1][2], 1};
                float ks[4] = {mtl[2][0], mtl[2][1], mtl[2][2], 1};

                glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
                glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
            }
        }

        glColor3f(1.0f, 1.0f, 1.0f);

        glNormal3f(VN1[0], VN1[1], VN1[2]);
        glTexCoord2f(VT1[0], VT1[1]);
        glVertex3f(SV1[0], SV1[1], SV1[2]);
        glNormal3f(VN2[0], VN2[1], VN2[2]);
        glTexCoord2f(VT2[0], VT2[1]);
        glVertex3f(SV2[0], SV2[1], SV2[2]);
        glNormal3f(VN3[0], VN3[1], VN3[2]);
        glTexCoord2f(VT3[0], VT3[1]);
        glVertex3f(SV3[0], SV3[1], SV3[2]);

        if ((fSets[i][0]).size() == 4)
        {
            glNormal3f(VN4[0], VN4[1], VN4[2]);
            glTexCoord2f(VT4[0], VT4[1]);
            glVertex3f(SV4[0], SV4[1], SV4[2]);
        }

        glEnd();

    }

//    glDisable(GL_COLOR_MATERIAL);
//    glBindTexture(GL_TEXTURE_2D, NULL);
//    glDisable(GL_TEXTURE_2D);

//    glEnd();

    //lastFrameTime = currentFrameTime;
}



