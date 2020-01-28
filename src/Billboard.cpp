
#include "Billboard.h"

Billboard::Billboard()
{
    objLoader = new ObjLoader("../src/data/billboard.obj");
    texID = Scene::GetTexture("../src/img/metal.bmp");
    texIDbillboard[0] = Scene::GetTexture("../src/img/billboard.bmp");
    texIDbillboard[1] = Scene::GetTexture("../src/img/billboard2.bmp");
    textLabel = 0;
    isNext = false;
    time = 0.0f;
    tmp = 0;
}

Billboard::~Billboard()
{
    delete objLoader;
}

void Billboard::Display()
{
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, texID);

    //glColor3f(1.0f, 1.0f, 1.0f);
    objLoader->Draw();

    glDisable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);

    glPopAttrib();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texIDbillboard[textLabel] );

    glPushMatrix();
    glTranslatef(pos[0] - 60.0f, pos[1] + 265.0f, pos[2]+2.0f);
    glScalef(scale[0], scale[1], scale[2]);
    //glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(-66.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glScalef(180.0f, 1.0f, 48.0f);

    DrawCube();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);
}

void Billboard::Update(const double &deltaTime)
{
    time += deltaTime;

    if (!isNext)
    {
        if ( (int )time / 60 != tmp)
        {
            return;
        }
        else
        {
            tmp = tmp + 1;
        }

    }
    else
    {
        isNext = false;
    }

    textLabel = (textLabel + 1) % 2;
}


void Billboard::HandleKey(unsigned char key, int state, int x, int y)
{
    if (key == 'n' && state)
        isNext = true;
}