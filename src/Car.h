#include "../Framework/Interface/DisplayableObject.h"
#include "../Framework/Interface/Animation.h"
#include "objLoader/ObjLoader.h"
#include "myFramework/DrawObject.h"
#include "iostream"
using namespace std;

class Car :
        public DisplayableObject,
        public DrawObject,
        public Animation,
        public Input
{
public:
    Car();
    ~Car();

    void Display();
    void Update(const double &deltaTime);
    void HandleKey(unsigned char key, int state, int x, int y);

private:
    ObjLoader *objLoader;
    GLint texID;
    double time;
};

