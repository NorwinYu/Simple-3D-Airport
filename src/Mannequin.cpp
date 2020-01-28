#include "Mannequin.h"
#include "../Framework/Utility/VectorMath.h"

Mannequin::Mannequin() : iPress(0), kPress(0), jPress(0), lPress(0), mPress(0), rPress(0), xPress(0), yPress(0),
                         zPress(0), cPress(0), vPress(0), bPress(0), emptyPress(0)
{
    Reset();
}

Mannequin::~Mannequin()
{

}

void Mannequin::Reset()
{
    // body size
    body_length = 8.0f;
    body_thickness = 3.0f;

    // head size
    head_diameter = 5.0f;

    // arm size
    upper_arm_length = 5.0f;
    lower_arm_length = 3.0f;
    arm_thickness = 1.0f;

    // leg size
    leg_length = 4.0f;
    leg_thickness = 1.5f;

    // hand size
    hand_length = 2.0f;
    hand_thickness = 1.0f;

    // foot size
    foot_length = 2.0f;
    foot_thickness = 1.0f;

    // joint size
    joint_diameter = 1.0f;

    // distance
    distance_arm_joint = 0.5f;
    distance_leg_joint = 0.2f;
    distance_arm_hand_leg_foot = 0.4f;

    // left arms angle
    left_upper_angle_arm_z = 45.0f;
    left_upper_angle_arm_y = 20.0f;
    left_upper_angle_arm_x = 20.0f;
    left_lower_angle_arm_z = 30.0f;

    // right arms angle
    right_upper_angle_arm_z = 45.0f;
    right_upper_angle_arm_y = 0.0f;
    right_upper_angle_arm_x = 0.0f;
    right_lower_angle_arm_z = 30.0f;

    // left legs angle
    left_upper_angle_leg_z = 10.0f;
    left_upper_angle_leg_y = 0.0f;
    left_upper_angle_leg_x = 0.0f;
    left_lower_angle_leg_z = 10.0f;

    // right legs angle
    right_upper_angle_leg_z = 10.0f;
    right_upper_angle_leg_y = 0.0f;
    right_upper_angle_leg_x = 0.0f;
    right_lower_angle_leg_z = 10.0f;

    // set default position
    pos[0] = 0.0f;
    pos[1] = 0.0f;
    pos[2] = 0.0f;

    // set the right vector to point along the x axis
    right[0] = 1.0f;
    right[1] = 0.0f;
    right[2] = 0.0f;

    // set the up vector of the camera to be up the y axis
    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;

    // set default rotation
    rotation[0] = 0.0f;
    rotation[1] = 0.0f;
    rotation[2] = 0.0f;

}

void Mannequin::Display()
{
    glTranslatef(pos[0], pos[1], pos[2]);

    glScalef(scale[0], scale[1], scale[2]);

    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);

    glTranslatef(0.0f, 4.0f, 0.0f);

    glPushMatrix();
        // main body
        DrawMainBody(body_length, body_thickness);
        // head
        DrawHead(body_length, head_diameter);

        glPushMatrix();
            // left arms and joints
            glTranslatef(-(body_thickness+joint_diameter)/2.0f-0.5f, body_length/2.0f-0.5f, 0.0f);
            DrawArmsOrLegsAndJoins('a', upper_arm_length, joint_diameter, distance_arm_joint,
                             lower_arm_length, arm_thickness, left_upper_angle_arm_z,
                             left_upper_angle_arm_y, -left_upper_angle_arm_x, left_lower_angle_arm_z,
                             hand_length, hand_thickness, distance_arm_hand_leg_foot);
        glPopMatrix();

        glPushMatrix();
            // right arms and joints
            glTranslatef((body_thickness+joint_diameter)/2.0f+0.5f, body_length/2.0f-0.5f, 0.0f);
            DrawArmsOrLegsAndJoins('a', upper_arm_length, joint_diameter, distance_arm_joint,
                             lower_arm_length, arm_thickness, -right_upper_angle_arm_z,
                             -right_upper_angle_arm_y, right_upper_angle_arm_x, -right_lower_angle_arm_z,
                             hand_length, hand_thickness, distance_arm_hand_leg_foot);
        glPopMatrix();

        glPushMatrix();
            // left legs and joints
            glTranslatef(-(body_thickness+joint_diameter)/2.0f-0.2f, -body_length/2.0f-0.7f, 0.0f);
            DrawArmsOrLegsAndJoins('l', leg_length, joint_diameter, distance_leg_joint,
                             leg_length, leg_thickness, left_upper_angle_leg_z,
                             left_upper_angle_leg_y, -left_upper_angle_leg_x, left_lower_angle_leg_z,
                             foot_length, foot_thickness, distance_arm_hand_leg_foot);
        glPopMatrix();

        glPushMatrix();
            // right legs and joints
            glTranslatef((body_thickness+joint_diameter)/2.0f+0.2f, -body_length/2.0f-0.7f, 0.0f);
            DrawArmsOrLegsAndJoins('l', leg_length, joint_diameter, distance_leg_joint,
                             leg_length, leg_thickness, -right_upper_angle_leg_z,
                             -right_upper_angle_leg_y, right_upper_angle_leg_x, -right_lower_angle_leg_z,
                             foot_length, foot_thickness, distance_arm_hand_leg_foot);
        glPopMatrix();

    glPopMatrix();
}

void Mannequin::DrawCylinder()
{
    float res = 0.1f*M_PI;
    float r = 0.5f;
    float x = r, z = 0.f;
    float t = 0.f;

    do
    {
        glBegin(GL_QUADS);
        glVertex3f(x, -0.5f, z);
        glVertex3f(x, 0.5f, z);
        t += res;
        x = r*cos(t);
        z = r*sin(t);
        glVertex3f(x, 0.5f, z);
        glVertex3f(x, -0.5f, z);
        glEnd();
    } while (t <= 2 * M_PI);

    DrawFillCircleTop();
    DrawFillCircleBottom();
}

void Mannequin::DrawFillCircleTop()
{
    float res = 0.1f*M_PI;
    float r = 0.5f;
    float x = r, z = 0.f;
    float t = 2.0f * M_PI;

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    do
    {
        glVertex3f(x, 0.5f, z);
        t -= res;
        x = r*cos(t);
        z = r*sin(t);
    } while (t >= 0);

    glEnd();
}

void Mannequin::DrawFillCircleBottom()
{
    float res = 0.1f*M_PI;
    float r = 0.5f;
    float x = r, z = 0.f;
    float t = 0.f;

    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    do
    {
        glVertex3f(x, -0.5f, z);
        t += res;
        x = r*cos(t);
        z = r*sin(t);
    } while (t <= 2 * M_PI);

    glEnd();
}

void Mannequin::DrawSolidSphere()
{
    glutSolidSphere(0.5f, 40, 40);
}

void Mannequin::DrawMainBody(float body_length, float body_thickness)
{
    glPushMatrix();
    glScalef(body_thickness, body_length, body_thickness);
    glColor3f(1.0f, 1.0f, 0.0f);
    DrawCylinder();
    glPopMatrix();
}

void Mannequin::DrawHead(float body_length, float head_diameter)
{
    glPushMatrix();
    glTranslatef(0.0f, (head_diameter+body_length)/2.0f+0.5f, 0.0f);
    glScalef(head_diameter, head_diameter, head_diameter);
    glColor3f(1.0f, 1.0f, 1.0f);
    DrawSolidSphere();
    glPopMatrix();
}

void Mannequin::DrawJoint(float joint_diameter)
{
    glPushMatrix();
    glScalef(joint_diameter, joint_diameter, joint_diameter);
    glColor3f(0.0f, 0.0f, 1.0f);
    DrawSolidSphere();
    glPopMatrix();
}

void Mannequin::DrawArm(float arm_length, float arm_thickness)
{
    glPushMatrix();
    glScalef(arm_thickness, arm_length, arm_thickness);
    glColor3f(1.0f, 0.0f, 0.0f);
    DrawCylinder();
    glPopMatrix();
}

void Mannequin::DrawLeg(float leg_length, float leg_thickness)
{
    glPushMatrix();
    glScalef(leg_thickness, leg_length, leg_thickness);
    glColor3f(0.0f, 1.0f, 0.0f);
    DrawCylinder();
    glPopMatrix();
}

void Mannequin::DrawHand(float hand_length, float hand_thickness)
{
    glPushMatrix();
    glScalef(hand_thickness, hand_length, hand_thickness);
    glColor3f(1.0f, 0.0f, 1.0f);
    DrawSolidSphere();
    glPopMatrix();
}

void Mannequin::DrawFoot(float foot_length, float foot_thickness)
{
    glPushMatrix();
    glScalef(foot_thickness, foot_length, foot_thickness);
    glColor3f(1.0f, 1.0f, 0.0f);
    DrawSolidSphere();
    glPopMatrix();
}

void Mannequin::DrawArmOrLeg(unsigned char type, float length, float thickness)
{
    switch (type) {
        case 'a':
            DrawArm(length, thickness);
            break;
        case 'l':
            DrawLeg(length, thickness);
    }
}

void Mannequin::DrawHandOrFoot(unsigned char type, float length, float thickness)
{
    switch (type) {
        case 'a':
            DrawHand(length, thickness);
            break;
        case 'l':
            DrawFoot(length, thickness);
    }
}

void Mannequin::TranslateJointCenterToArmCenter(
        unsigned char normal, float angle, float arm_length, float joint_diameter, float distance_arm_joint)
{
    float move_distance = (arm_length+joint_diameter)/2.0f+distance_arm_joint;
    switch (normal) {
        case 'z':
            glTranslatef(-sin(angle/360.0f*2.0f*M_PI)*move_distance,
                         -cos(angle/360.0f*2.0f*M_PI)*move_distance, 0.0f);
            break;
    }
}

void Mannequin::DrawArmsOrLegsAndJoins( unsigned char type,
        float upper_arm_or_leg_length, float joint_diameter, float distance_arm_or_leg_joint,
        float lower_arm_or_leg_length, float arm_or_leg_thickness, float upper_angle_z,
        float upper_angle_y, float upper_angle_x, float lower_angle_z,
        float hand_or_foot_length, float hand_or_foot_thickness, float distance_arm_hand_leg_foot)
{
    RotateByAxis('y', upper_angle_y);
    RotateByAxis('x', upper_angle_x);

    // shoulder
    DrawJoint(joint_diameter);

    glPushMatrix();
        // upper arm or leg
        TranslateJointCenterToArmCenter(
            'z', upper_angle_z, upper_arm_or_leg_length, joint_diameter, distance_arm_or_leg_joint);
        glPushMatrix();
        RotateByAxis('z', -upper_angle_z);
        DrawArmOrLeg(type, upper_arm_or_leg_length, arm_or_leg_thickness);
        glPopMatrix();

        glPushMatrix();
            // elbow
            TranslateJointCenterToArmCenter(
                    'z', upper_angle_z, upper_arm_or_leg_length, joint_diameter, distance_arm_or_leg_joint);
            DrawJoint(joint_diameter);

            glPushMatrix();
                //lower arm or leg
                TranslateJointCenterToArmCenter(
                        'z', upper_angle_z - lower_angle_z, lower_arm_or_leg_length, joint_diameter, distance_arm_or_leg_joint);
                glPushMatrix();
                RotateByAxis('z', -(upper_angle_z - lower_angle_z));
                DrawArmOrLeg(type, lower_arm_or_leg_length, arm_or_leg_thickness);

                    glPushMatrix();
                        // hand or foot
                        glTranslatef(0.0f, -(distance_arm_hand_leg_foot+(hand_or_foot_length+lower_arm_or_leg_length)/2), 0.0f);
                        DrawHandOrFoot(type, hand_or_foot_length, hand_or_foot_thickness);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Mannequin::RotateByAxis(unsigned char axis, float angle)
{
    switch (axis) {
        case 'x':
            glRotatef(angle, 1.0f, 0.0f, 0.0f);
            break;
        case 'y':
            glRotatef(angle, 0.0f, 1.0f, 0.0f);
            break;
        case 'z':
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            break;
    }
}

void Mannequin::HandleKey(unsigned char key, int state, int mX, int mY)
{
    switch(key){
        case 'i':
            iPress = state;
            break;
        case 'k':
            kPress = state;
            break;
        case 'j':
            jPress = state;
            break;
        case 'l':
            lPress = state;
            break;
        case 'm':
            mPress = state;
            break;
        case 'r':
            rPress = state;
            break;
        case 'x':
            xPress = state;
            break;
        case 'y':
            yPress = state;
            break;
        case 'z':
            zPress = state;
            break;
        case 'c':
            cPress = state;
            break;
        case 'v':
            vPress = state;
            break;
        case 'b':
            bPress = state;
            break;
        case ' ':
            emptyPress = state;
            break;
    }
}

void Mannequin::Update(const double &deltaTime)
{
    float speed = 1.0f;

    // move up
    if (iPress * bPress) {
        add(pos, up, speed);
    }

    // move down
    if (kPress * bPress) {
        sub(pos, up, speed);
    }

    // move left
    if (jPress * bPress) {
        sub(pos, right, speed);
    }

    // move right
    if (lPress * bPress) {
        add(pos, right, speed);
    }

    // rotate by z axis
    if (zPress * rPress) {
        rotation[2] += 5.0f*speed;
    }

    // rotate by y axis
    if (yPress * rPress) {
        rotation[1] += 5.0f*speed;
    }

    // rotate by x axis
    if (xPress * rPress) {
        rotation[0] += 5.0f*speed;
    }

    // upper left arm's angle += by x axis
    if (xPress * cPress * iPress) {
        left_upper_angle_arm_x += 5.0f*speed;
    }

    // upper left arm's angle -= by x axis
    if (xPress * cPress * kPress) {
        left_upper_angle_arm_x -= 5.0f*speed;
    }

    // upper left arm's angle += by y axis
    if (yPress * cPress * iPress) {
        left_upper_angle_arm_y += 5.0f*speed;
        if (left_upper_angle_arm_y > 120) {
            left_upper_angle_arm_y = 120.0f;
        }
    }

    // upper left arm's angle -= by y axis
    if (yPress * cPress * kPress) {
        left_upper_angle_arm_y -= 5.0f*speed;
        if (left_upper_angle_arm_y < -30) {
            left_upper_angle_arm_y = -30.0f;
        }
    }

    // upper left arm's angle += by z axis
    if (zPress * cPress * iPress) {
        left_upper_angle_arm_z += 5.0f*speed;
    }

    // upper left arm's angle -= by z axis
    if (zPress * cPress * kPress) {
        left_upper_angle_arm_z -= 5.0f*speed;
    }

    // lower left arm's angle +=
    if (vPress * iPress) {
        left_lower_angle_arm_z += 5.0f*speed;
        if (left_lower_angle_arm_z > 175) {
            left_lower_angle_arm_z = 175.0f;
        }
    }

    // lower left arm's angle -=
    if (vPress * kPress) {
        left_lower_angle_arm_z -= 5.0f*speed;
        if (left_lower_angle_arm_z < 5) {
            left_lower_angle_arm_z = 5.0f;
        }
    }

    if (emptyPress) {
        Reset();
    }
}
