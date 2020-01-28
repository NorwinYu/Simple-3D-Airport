// copy from UNNC CG Lab 8
// Edit By Binghong YU 16518735 2018.11.27

#include "Floor.h"

void Floor::Display()
{
    // Draws an exciting chequered floor
    glPushMatrix();

    glTranslatef(pos[0], pos[1], pos[2]);

    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_COLOR_MATERIAL);
    float bDiffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float gDiffuse[] = { 0.0f, 1.0f, 0.0f, 0.5f };
    float wDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float shininess = 128.0f;

    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_SPECULAR, static_cast<GLfloat*>(specular));
    glMaterialf(GL_FRONT, GL_SHININESS, static_cast<GLfloat>(shininess));

    for (int i = -20; i < 20; i++)
    {
        for (int j = -10 ; j < 20; j++)
        {
            if ( j >= -2 && j <= 1)
            {
                if (i % 2)
                {
                    if (j % 2)
                    {
                        if (j == 1)
                        {
                            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(bDiffuse));
                        }
                        else
                        {
                            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(gDiffuse));
                        }
                    }
                    else
                    {
                        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(wDiffuse));
                    }
                }
                else
                {
                    if (j % 2)
                        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(wDiffuse));
                    else
                    {
                        if (j == -2)
                        {
                            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(bDiffuse));
                        }
                        else
                        {
                            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(gDiffuse));
                        }
                    }
                }
                glNormal3f(0.0f, 1.0f, 0.0f);
                glVertex3f(scale[0] * static_cast<float>(i)+scale[0], 0.0f, scale[2] * static_cast<float>(j)+scale[2]);
                glVertex3f(scale[0] * static_cast<float>(i)+scale[0], 0.0f, scale[2] * static_cast<float>(j));
                glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j));
                glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j)+scale[2]);
            }
        }
    }
    glEnd();
    glEnable(GL_COLOR_MATERIAL);
    glPopAttrib();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, NULL);

    glDisable(GL_TEXTURE_2D);
}

Floor::Floor()
{
}

Floor::~Floor()
{

}

