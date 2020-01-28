
#include "Cloud.h"

Cloud::Cloud()
{
    objLoader = new ObjLoader("../src/data/billboard.obj");
    //texID = Scene::GetTexture("../src/img/metal.bmp");
}

Cloud::~Cloud()
{
    delete objLoader;
}

void Cloud::Display()
{
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    //glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    //glBindTexture(GL_TEXTURE_2D, texID);

    //glColor3f(1.0f, 1.0f, 1.0f);
    objLoader->Draw();

    glDisable(GL_COLOR_MATERIAL);
    //glBindTexture(GL_TEXTURE_2D, NULL);
    //glDisable(GL_TEXTURE_2D);

    glPopAttrib();
    glPopMatrix();
}

void Cloud::Update(const double &deltaTime)
{

}
