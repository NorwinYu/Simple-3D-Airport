#include "../Framework/Engine/Scene.h"
#include "myFramework/Music.h"
#include "Aircraft.h"
#include "Mannequin.h"
#include "Floor.h"
#include "Airport.h"
#include "Tower.h"
#include "Runway.h"
#include "AirportFloor.h"
#include "Cloud.h"
#include "Billboard.h"
#include "Car.h"

class ProjectScene :
	public Scene
{
public:
    ProjectScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~ProjectScene() {};

private:
	void Initialise();
    void Projection();
    void Update(const double& deltaTime);
    void HandleKey(unsigned char key, int state, int x, int y);

    sf::Music music;

    int isBlue;
    Aircraft *cotrolledAircraft;

    int isControl;
};