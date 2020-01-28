#include "../Framework/Interface/Input.h"
#include "../Framework/Interface/Animation.h"
#include "../Framework/Interface/DisplayableObject.h"

#include "myFramework/DrawObject.h"
#include "iostream"

using namespace std;

class Aircraft :
        public DrawObject,
        public DisplayableObject,
        public Input,
        public Animation
{
public:
    Aircraft();
    ~Aircraft();

    void Display();
    void Update(const double &deltaTime);
    void DrawBodyCylinder();
    void DrawHead();
    void DrawTail();
    void DrawTopTailWing();
    void DrawRightTailWing();
    void DrawLeftTailWing();
    void DrawRightWing();
    void DrawLeftWing();
    void DrawWing();
    void Reset();

    void GetDriverCamera(float &x, float &y, float &z);
    void GetDriverViewDir(float &x, float &y, float &z);

    void Rotate(float &x, float &y, float &z);
    void HandleKey(unsigned char key, int state, int x, int y);

    int isControlled;

private:
    float white[3];
    float blue[3];
    float appearance[3];

    float driverCamera[3];
    float driverViewDir[3];

    GLint texID;

    int uKey, hKey, jKey, kKey, zKey, xKey, cKey, vKey;

};

