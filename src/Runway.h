#include "../Framework/Interface/DisplayableObject.h"
#include "objLoader/ObjLoader.h"
#include "myFramework/DrawObject.h"
using namespace std;

class Runway :
        public DisplayableObject, DrawObject
{
public:
    Runway();
    ~Runway();

    void Display();
    void Update(const double &deltaTime);

private:
    ObjLoader *objLoader;
    GLint texID;
};