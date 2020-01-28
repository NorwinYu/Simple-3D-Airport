#include "Runway.h"

Runway::Runway()
{
    objLoader = new ObjLoader("../src/data/runway.obj");
    texID = Scene::GetTexture("../src/img/runway.bmp");
}

Runway::~Runway()
{
    delete objLoader;
}

void Runway::Display()
{
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);

    glDisable(GL_COLOR_MATERIAL);

    //glEnable(GL_TEXTURE_2D);
    //glEnable(GL_COLOR_MATERIAL);
    //glBindTexture(GL_TEXTURE_2D, texID);

    objLoader->Draw();

    // glDisable(GL_COLOR_MATERIAL);
    // glBindTexture(GL_TEXTURE_2D, NULL);
    //glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    glPushMatrix();
    glTranslatef(pos[0], pos[1] + 20.0f, pos[2]);
    glScalef(scale[0]* 200.0f, scale[1], scale[2]*3800.0f);
    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);

    DrawCube();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);


}

void Runway::Update(const double &deltaTime)
{

}

