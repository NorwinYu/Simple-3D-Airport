#include "ProjectScene.h"

int main(int argc, char* argv[])
{
    ProjectScene *scene = NULL;
	scene = new ProjectScene(argc, argv, "CG Project BINGHONG YU 6518735",
                         static_cast<const int>(1200), static_cast<const int>(800));

	scene->Run();

	delete scene;
	return 0;
}