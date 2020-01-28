#include "Tower.h"

Tower::Tower()
{
    objLoader = new ObjLoader("../src/data/tower.obj");
    texID = Scene::GetTexture("../src/img/metal.bmp");
}

Tower::~Tower()
{
    delete objLoader;
}

void Tower::Display()
{
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDisable(GL_COLOR_MATERIAL);

    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, texID);

    objLoader->Draw();

   // glDisable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);

    glPopAttrib();
    glPopMatrix();
}

void Tower::Update(const double &deltaTime)
{

}