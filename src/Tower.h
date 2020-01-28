#include "../Framework/Interface/DisplayableObject.h"
#include "objLoader/ObjLoader.h"
using namespace std;

class Tower :
        public DisplayableObject
{
public:
    Tower();
    ~Tower();

    void Display();
    void Update(const double &deltaTime);

private:
    ObjLoader *objLoader;
    GLint texID;
};


