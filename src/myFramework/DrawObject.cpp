#include "DrawObject.h"

DrawObject::DrawObject()
{

}

DrawObject::~DrawObject()
{

}

void DrawObject::DrawFillCircleTop(float circle_radius, float half_height, float color[])
{
    float res = 0.1f*M_PI;
    float r = circle_radius;
    float x = r, z = 0.f;
    float t = 2.0f * M_PI;

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(color[0], color[1], color[2]);
    do
    {
        glVertex3f(x, half_height, z);
        t -= res;
        x = r*cos(t);
        z = r*sin(t);
    } while (t >= 0);

    glEnd();
}

void DrawObject::DrawFillCircleBottom(float circle_radius, float half_height, float color[])
{
    float res = 0.1f*M_PI;
    float r = circle_radius;
    float x = r, z = 0.f;
    float t = 0.f;

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glColor3f(color[0], color[1], color[2]);
    do
    {
        glVertex3f(x, -half_height, z);
        t += res;
        x = r*cos(t);
        z = r*sin(t);
    } while (t <= 2 * M_PI);

    glEnd();
}

void DrawObject::DrawCylinder(float circle_radius, float half_height,
                              float top_color[], float bottom_color[], float body_color[])
{
    float res = 0.1f*M_PI;
    float r = circle_radius;
    float x = r, z = 0.f;
    float t = 0.f;

    glColor3f(body_color[0], body_color[1], body_color[2]);
    do
    {
        glBegin(GL_QUADS);
        glVertex3f(x, -half_height, z);
        glVertex3f(x, half_height, z);
        t += res;
        x = r*cos(t);
        z = r*sin(t);
        glVertex3f(x, half_height, z);
        glVertex3f(x, -half_height, z);
        glEnd();
    } while (t <= 2 * M_PI);

    DrawFillCircleTop(circle_radius, half_height, top_color);
    DrawFillCircleBottom(circle_radius, half_height, bottom_color);
}

void DrawObject::DrawTruncatedCone(
        float top_circle_radius, float bottom_circle_radius, float half_height,
        float top_offset,float bottom_offset, float top_color[], float bottom_color[], float body_color[])
{
    float res = 0.1f*M_PI;
    float r_top = top_circle_radius;
    float r_bottom = bottom_circle_radius;
    float x_top = r_top, x_bottom = r_bottom, z_top = 0.f, z_bottom = 0.f;
    float t = 0.f;

    glColor3f(body_color[0], body_color[1], body_color[2]);
    do
    {
        glBegin(GL_QUADS);
        glVertex3f(x_bottom+bottom_offset, -half_height, z_bottom);
        glVertex3f(x_top+top_offset, half_height, z_top);
        t += res;
        x_bottom = r_bottom*cos(t);
        z_bottom  = r_bottom *sin(t);
        x_top = r_top*cos(t);
        z_top  = r_top *sin(t);
        glVertex3f(x_top+top_offset, half_height, z_top);
        glVertex3f(x_bottom+bottom_offset, -half_height, z_bottom);
        glEnd();
    } while (t <= 2 * M_PI);

    glPushMatrix();
    glTranslatef(top_offset, 0.0f, 0.0f);
    DrawFillCircleTop(top_circle_radius, half_height, top_color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(bottom_offset, 0.0f, 0.0f);
    DrawFillCircleBottom(bottom_circle_radius, half_height, bottom_color);
    glPopMatrix();
}

void DrawObject::DrawTruncatedConeWithSkipAngle(
        float top_circle_radius, float bottom_circle_radius, float half_height,
        float top_offset,float bottom_offset, float top_color[], float bottom_color[], float body_color[])
{
    float res = 0.1f*M_PI;
    float r_top = top_circle_radius;
    float r_bottom = bottom_circle_radius;
    float x_top = r_top, x_bottom = r_bottom, z_top = 0.f, z_bottom = 0.f;
    float t = 0.f;

    do
    {
        if (t < 0.2*M_PI || t >1.8*M_PI)
        {
            glColor4f(body_color[0], body_color[1], body_color[2], 0.1);
        } else{
            glColor3f(body_color[0], body_color[1], body_color[2]);
        }

        glBegin(GL_QUADS);
        glVertex3f(x_bottom+bottom_offset, -half_height, z_bottom);
        glVertex3f(x_top+top_offset, half_height, z_top);
        t += res;
        x_bottom = r_bottom*cos(t);
        z_bottom  = r_bottom *sin(t);
        x_top = r_top*cos(t);
        z_top  = r_top *sin(t);
        glVertex3f(x_top+top_offset, half_height, z_top);
        glVertex3f(x_bottom+bottom_offset, -half_height, z_bottom);
        glEnd();
    } while (t <= 2 * M_PI);

    glPushMatrix();
    glTranslatef(top_offset, 0.0f, 0.0f);
    DrawFillCircleTop(top_circle_radius, half_height, top_color);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(bottom_offset, 0.0f, 0.0f);
    DrawFillCircleBottom(bottom_circle_radius, half_height, bottom_color);
    glPopMatrix();
}

void DrawObject::DrawSolidSphere(float radius, float slices, float stacks)
{
    glutSolidSphere(radius, slices, stacks);
}

void DrawObject::DrawCube()
{
    glPushMatrix();
    glBegin(GL_POLYGON);
    glNormal3d(0.0f, 0.0f, 1.0f);
    glColor3f( 1.0f, 0.0f, 0.0f ); // red
    glVertex3f( 1.0f, -1.0f, 1.0f );
    glColor3f( 0.0f, 1.0f, 0.0f ); // green
    glVertex3f( 1.0f, 1.0f, 1.0f );
    glColor3f( 0.0f, 0.0f, 1.0f ); // blue
    glVertex3f( -1.0f, 1.0f, 1.0f );
    glColor3f( 1.0f, 0.0f, 1.0f );
    glVertex3f( -1.0f, -1.0f, 1.0f);// purple
    glEnd();
    // White ¨C BACK
    glBegin(GL_POLYGON);
    glNormal3d(0.0f, 0.0f, -1.0f);
    glColor3f(   1.0f,  1.0f, 1.0f );
    glVertex3f(  1.0f, -1.0f, -1.0f );
    glVertex3f(  1.0f, 1.0f, -1.0f );
    glVertex3f( -1.0f, 1.0f, -1.0f );
    glVertex3f( -1.0f, -1.0f, -1.0f );
    glEnd();
    // Blue ¨C TOP

    glBegin(GL_POLYGON);
    glNormal3d(0.0f, 1.0f, 0.0f);
    glColor3f( 0.0f, 0.0f, 1.0f );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, -1.0f );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( -1.0f, 1.0f, -1.0f );
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( -1.0f, 1.0f, 1.0f );
    glEnd();

    // Red ¨C BOTTOM
    glBegin(GL_POLYGON);
    glNormal3d(0.0f, -1.0f, 0.0f);
    glColor3f( 1.0f,  0.0f,  0.0f );
    glVertex3f( -1.0f, -1.0f, 1.0f );
    glVertex3f( -1.0f, -1.0f, -1.0f );
    glVertex3f( 1.0f, -1.0f, -1.0f );
    glVertex3f( 1.0f, -1.0f, 1.0f );
    glEnd();
    // Green ¨C LEFT
    glBegin(GL_POLYGON);
    glNormal3d(-1.0f, 0.0f, 0.0f);
    glColor3f(   0.0f,  1.0f,  0.0f );
    glVertex3f( -1.0f, -1.0f, 1.0f );
    glVertex3f( -1.0f, 1.0f, 1.0f );
    glVertex3f( -1.0f, 1.0f, -1.0f );
    glVertex3f( -1.0f, -1.0f, -1.0f );
    glEnd();
    // Purple ¨C RIGH
    glBegin(GL_POLYGON);
    glNormal3d(1.0f, 0.0f, 0.0f);
    glColor3f(  1.0f,  0.0f,  1.0f );
    glVertex3f( 1.0f, -1.0f, -1.0f );
    glVertex3f( 1.0f, 1.0f, -1.0f );
    glVertex3f( 1.0f, 1.0f, 1.0f );
    glVertex3f( 1.0f, -1.0f, 1.0f );
    glEnd();

    glPopMatrix();
}