#include "../Framework/Interface/DisplayableObject.h"
#include "objLoader/ObjLoader.h"
using namespace std;

class Cloud :
        public DisplayableObject
{
public:
    Cloud();
    ~Cloud();

    void Display();
    void Update(const double &deltaTime);

private:
    ObjLoader *objLoader;
    GLint texID;
};

