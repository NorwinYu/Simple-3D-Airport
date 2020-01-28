#include "../Framework/Interface/DisplayableObject.h"
#include "../Framework/Interface/Animation.h"
#include "objLoader/ObjLoader.h"
#include "myFramework/DrawObject.h"
#include "iostream"
using namespace std;

class Billboard :
        public DisplayableObject,
        public DrawObject,
        public Animation,
        public Input
{
public:
    Billboard();
    ~Billboard();

    void Display();
    void Update(const double &deltaTime);
    void HandleKey(unsigned char key, int state, int x, int y);

private:
    ObjLoader *objLoader;
    GLint texID;
    GLint texIDbillboard[2];
    double time;
    int isNext;
    int textLabel;
    int tmp;
};

