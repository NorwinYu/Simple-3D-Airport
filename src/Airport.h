#include "../Framework/Interface/DisplayableObject.h"
#include "objLoader/ObjLoader.h"
using namespace std;

class Airport :
        public DisplayableObject
{
public:
    Airport();
    ~Airport();

    void Display();
    void Update(const double &deltaTime);

private:
    ObjLoader *objLoader;
    GLint texID;
};

