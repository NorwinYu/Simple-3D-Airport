#include "../Framework/Interface/DisplayableObject.h"
#include "../Framework/Interface/Input.h"
#include "../Framework/Interface/Animation.h"
#include <cmath>

using namespace std;

class Mannequin :
        public DisplayableObject,
        public Input,
        public Animation
{
public:
    Mannequin();
    ~Mannequin();

    void Display();
    void Reset();
    void DrawCylinder();
    void DrawFillCircleTop();
    void DrawFillCircleBottom();
    void DrawSolidSphere();
    void DrawMainBody(float body_length, float body_thickness);
    void DrawHead(float body_length, float head_diameter);
    void DrawJoint(float joint_diameter);
    void DrawArm(float arm_length, float arm_thickness);
    void DrawLeg(float leg_length, float leg_thickness);
    void DrawHand(float hand_length, float hand_thickness);
    void DrawFoot(float foot_length, float foot_thickness);
    void DrawArmOrLeg(unsigned char type, float length, float thickness);
    void DrawHandOrFoot(unsigned char type, float length, float thickness);
    void TranslateJointCenterToArmCenter(unsigned char normal, float angle, float arm_length, float joint_diameter, float dist);
    void DrawArmsOrLegsAndJoins(unsigned char type, float upper_arm_length, float joint_diameter, float distance_arm_joint, float lower_arm_length, float arm_thickness, float upper_angle_z, float upper_angle_y, float upper_angle_x, float lower_angle_z, float hand_length, float hand_thickness, float distance_arm_hand_leg_foot);
    void RotateByAxis(unsigned char axis, float angle);
    void HandleKey(unsigned char key, int state, int mX, int mY);
    void Update(const double &deltaTime);

private:

    // body size
    float body_length;
    float body_thickness;

    // head size
    float head_diameter;

    // arm size
    float upper_arm_length;
    float lower_arm_length;
    float arm_thickness;

    // leg size
    float leg_length;
    float leg_thickness;

    // hand size
    float hand_length;
    float hand_thickness;

    // foot size
    float foot_length;
    float foot_thickness;

    // joint size
    float joint_diameter;

    // distance
    float distance_arm_joint;
    float distance_leg_joint;
    float distance_arm_hand_leg_foot;

    // left arms angle
    float left_upper_angle_arm_z;
    float left_upper_angle_arm_y;
    float left_upper_angle_arm_x;
    float left_lower_angle_arm_z;

    // right arms angle
    float right_upper_angle_arm_z;
    float right_upper_angle_arm_y;
    float right_upper_angle_arm_x;
    float right_lower_angle_arm_z;

    // left legs angle
    float left_upper_angle_leg_z;
    float left_upper_angle_leg_y;
    float left_upper_angle_leg_x;
    float left_lower_angle_leg_z;

    // right legs angle
    float right_upper_angle_leg_z;
    float right_upper_angle_leg_y;
    float right_upper_angle_leg_x;
    float right_lower_angle_leg_z;

    int iPress, kPress, jPress, lPress, mPress, rPress, xPress, yPress, zPress, cPress, vPress, bPress, emptyPress;
    float right[3];
    float up[3];
};

