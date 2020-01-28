
#include "Car.h"

Car::Car()
{
    objLoader = new ObjLoader("../src/data/car2.obj");
    texID = Scene::GetTexture("../src/img/metal2.bmp");
}

Car::~Car()
{
    delete objLoader;
}

void Car::Display()
{
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    //glDisable(GL_COLOR_MATERIAL);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, texID);

    objLoader->Draw();

    glDisable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);

    glPopAttrib();
    glPopMatrix();
}

void Car::Update(const double &deltaTime)
{

}

void Car::HandleKey(unsigned char key, int state, int x, int y)
{
    Input::HandleKey(key, state, x, y);
}
