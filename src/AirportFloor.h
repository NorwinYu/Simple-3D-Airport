#pragma once

#include "../Framework/Interface/DisplayableObject.h"
#include "../Framework/Interface/Animation.h"
#include "../Framework/Interface/Input.h"

#include <string>

class AirportFloor :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
    AirportFloor(const int& gridX, const int& gridZ, const std::string& filename);
	~AirportFloor();

	void Display();
	void Update(const double& delteTime);
    void changeFrozen();

private:
	int texID;

	int xGridDims, zGridDims;
	float* texCoords;
	double time;
	bool frozen;

	float matAmbient[4];      // matrial properties of the grid
	float matDiffuse[4];
	int   matShininess;
	float matSpecular[4];
};

