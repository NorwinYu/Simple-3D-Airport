#include "Aircraft.h"
#include "../Framework/Utility/VectorMath.h"

Aircraft::Aircraft()
{
    white[0] = 1.0f;
    white[1] = 1.0f;
    white[2] = 1.0f;

    blue[0] = 0.0f;
    blue[1] = 0.0f;
    blue[2] = 1.0f;

    appearance[0] = 0.25f;
    appearance[1] = 0.55f;
    appearance[2] = 0.75f;

    texID = Scene::GetTexture("../src/img/dashboard.bmp");

    isControlled = false;

    Reset();
}

void Aircraft::Reset()
{
    driverCamera[0] = 6.98834;
    driverCamera[1] = 0.3;
    driverCamera[2] = 0.0246112;

    driverViewDir[0] = 1.0;
    driverViewDir[1] = 0.0;
    driverViewDir[2] = 0.0;

    uKey = 0;
    hKey = 0;
    jKey = 0;
    kKey = 0;
    zKey = 0;
    xKey = 0;
    cKey = 0;
    vKey = 0;
}

Aircraft::~Aircraft()
{

}

void Aircraft::Display()
{
    //glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_COLOR_MATERIAL);

    glPushMatrix();

    glTranslatef(pos[0], pos[1], pos[2]);

    glScalef(scale[0], scale[1], scale[2]);

//    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);
    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);

    glTranslatef(0.0f, 0.0f, 0.0f);

    DrawBodyCylinder();
    DrawRightWing();
    DrawLeftWing();
    DrawTail();
    DrawTopTailWing();
    DrawRightTailWing();
    DrawLeftTailWing();
    DrawHead();

    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    glPushMatrix();

    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);

    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);

    glPushMatrix();

    glTranslatef(7.4f, -0.06f, 0.0f);

    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.2f,  0.002f,  0.2f);

    DrawCube();

    glPopMatrix();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Aircraft::DrawBodyCylinder()
{
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    DrawCylinder(1.0f, 6.0f, white, white, white);
    glPopMatrix();
}

void Aircraft::DrawHead()
{
    glPushMatrix();
    glTranslatef(6.7f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    DrawTruncatedConeWithSkipAngle(1.0f, 0.4f, 0.7f, 0.0f, -0.2f, white, white, white);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.7f+0.7f+0.2f, -0.2f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    DrawTruncatedCone(0.4f, 0.1f, 0.2f, 0.0f, 0.0f, white, white, white);
    glPopMatrix();
}

void Aircraft::DrawTail()
{
    glPushMatrix();
    glTranslatef(-7.5f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    DrawTruncatedCone(0.25f, 1.0f, 1.50f, 0.4f, 0.0f, white, white, white);
    glPopMatrix();
}

void Aircraft::DrawRightTailWing()
{
    glPushMatrix();
    glTranslatef(-7.8f, 0.3f, 0.50f);
    glScalef(0.4, 0.4, 0.4);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    DrawWing();
    glPopMatrix();
}

void Aircraft::DrawLeftTailWing()
{
    glPushMatrix();
    glTranslatef(-7.8f, -0.9f*0.4 + 0.3f, -0.50f);
    glScalef(0.4, 0.4, 0.4);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    DrawWing();
    glPopMatrix();
}

void Aircraft::DrawTopTailWing()
{
    glPushMatrix();
    glTranslatef(-7.8f, 0.3f, -0.9f*0.5f*0.4f);
    glScalef(0.4, 0.3, 0.4);
    glRotatef(-180.0f, 1.0f, 0.0f, 0.0f);
    DrawWing();
    glPopMatrix();
}

void Aircraft::DrawRightWing()
{
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.50f);
    glScalef(1.0f, 0.4f, 1.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    DrawWing();
    glPopMatrix();
}

void Aircraft::DrawLeftWing()
{
    glPushMatrix();
    glTranslatef(0.0f, -0.9f*0.4f, -0.50f);
    glScalef(1.0f, 0.4f, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    DrawWing();
    glPopMatrix();
}

void Aircraft::DrawWing()
{
    // top
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
//    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-3.0f, -9.0f, -0.3f);
    glVertex3f(-2.0f, -9.0f, -0.3f);
    glVertex3f(3.0f, 0.0f, 0.0f);
    glEnd();

    // right
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
//    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(3.0f, 0.0f, 0.0f);
    glVertex3f(-2.0f, -9.0f, -0.3f);
    glVertex3f(-2.0f, -9.0f, -0.6f);
    glVertex3f(3.0f, 0.0f, -0.9f);
    glEnd();

    // back
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
//    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(3.0f, 0.0f, 0.0f);
    glVertex3f(3.0f, 0.0f, -0.9f);
    glVertex3f(0.0f, 0.0f, -0.9f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    // left
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
//    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -0.9f);
    glVertex3f(-3.0f, -9.0f, -0.6f);
    glVertex3f(-3.0f, -9.0f, -0.3f);
    glEnd();

    // front
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
//    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-3.0f, -9.0f, -0.3f);
    glVertex3f(-3.0f, -9.0f, -0.6f);
    glVertex3f(-2.0f, -9.0f, -0.6f);
    glVertex3f(-2.0f, -9.0f, -0.3f);
    glEnd();

    // bottom
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
//    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -0.9f);
    glVertex3f(3.0f, 0.0f, -0.9f);
    glVertex3f(-2.0f, -9.0f, -0.3f);
    glVertex3f(-3.0f, -9.0f, -0.3f);
    glEnd();
}

void Aircraft::Update(const double &deltaTime)
{
    if (isControlled)
    {
        float v = 1.0f;
        float v_r = 0.5f;
        if (uKey)
        {
            float dir[3];
            GetDriverViewDir(dir[0], dir[1], dir[2]);
            pos[0] += dir[0] * v;
            pos[1] += dir[1] * v;
            pos[2] += dir[2] * v;
        }

        if (jKey)
        {
            float dir[3];
            GetDriverViewDir(dir[0], dir[1], dir[2]);
            pos[0] -= dir[0] * v;
            pos[1] -= dir[1] * v;
            pos[2] -= dir[2] * v;
        }

        if (hKey)
        {
            rotation[1] += 1.0f * v_r;
        }

        if (kKey)
        {
            rotation[1] -= 1.0f * v_r;
        }

        if (zKey)
        {
            rotation[0] += 1.0f * v_r;
        }

        if (xKey)
        {
            rotation[0] -= 1.0f * v_r;
        }

        if (cKey)
        {
            pos[1] += 1.0f * v;
        }

        if (vKey)
        {
            if (pos[1] - 1.0f * v >= 20.0)
                pos[1] -= 1.0f * v;
        }
    }
}

void Aircraft::GetDriverCamera(float &x, float &y, float &z)
{

    x = driverCamera[0]*scale[0];
    y = driverCamera[1]*scale[1];
    z = driverCamera[2]*scale[2];

    Rotate(x, y, z);

    x = x +pos[0];
    y = y +pos[1];
    z = z +pos[2];
}

void Aircraft::GetDriverViewDir(float &x, float &y, float &z)
{
    x = driverViewDir[0];
    y = driverViewDir[1];
    z = driverViewDir[2];

    Rotate(x, y, z);
}

void Aircraft::Rotate(float &x, float &y, float &z)
{
    float y1 = cos(rotation[0] / (float)360 * (float)2 * M_PI)* y
               + sin(rotation[0] / (float)360 * (float)2 * M_PI) * z;

    float z1 = - sin(rotation[0] / (float)360 * (float)2 * M_PI)* y
               + cos(rotation[0] / (float)360 * (float)2 * M_PI) * z;
    float x1 = x;

    float x2 = cos(rotation[1] / (float)360 * (float)2 * M_PI)* x1
               + sin(rotation[1] / (float)360 * (float)2 * M_PI) * z1;

    float z2 = - sin(rotation[1] / (float)360 * (float)2 * M_PI)* x1
               + cos(rotation[1] / (float)360 * (float)2 * M_PI) * z1;
    float y2 = y1;

    float x3 = cos(rotation[2] / (float)360 * (float)2 * M_PI)* x2
               - sin(rotation[2] / (float)360 * (float)2 * M_PI) * y2;

    float y3 = sin(rotation[2] / (float)360 * (float)2 * M_PI)* x2
               + cos(rotation[2] / (float)360 * (float)2 * M_PI) * y2;
    float z3 = z2;

    x = x3; y = y3; z = z3;

}


void Aircraft::HandleKey(unsigned char key, int state, int x, int y)
{
    switch (key)
    {
        case 'H':
        case 'h':
            hKey = state;
            break;
        case 'k':
        case 'K':
            kKey = state;
            break;
        case 'u':
        case 'U':
            uKey = state;
            break;
        case 'j':
        case 'J':
            jKey = state;
            break;
        case 'Z':
        case 'z':
            zKey = state;
            break;
        case 'x':
        case 'X':
            xKey = state;
            break;
        case 'C':
        case 'c':
            cKey = state;
            break;
        case 'V':
        case 'v':
            vKey = state;
            break;

        default:
            break;
    }
}

