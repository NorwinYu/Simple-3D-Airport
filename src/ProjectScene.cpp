#include "ProjectScene.h"

ProjectScene::ProjectScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
    if (!music.openFromFile("../src/bg/bg.ogg"))
        cout << "Can not open music file "<< endl;

    music.setLoop(true);
    music.play();

    isBlue = true;
    isControl = false;


}

void ProjectScene::Initialise()
{
	glClearColor(0.527f, 0.77f, 0.886f, 1.0f);

    Floor *floor = new Floor();
    floor->size(100.0f);
    floor->position(600.0f, 0.0f, 0.0f);
    floor->orientation(0.0f, 90.0f, 0.0f);

//
//    Mannequin *mannequin = new Mannequin();
//    mannequin->size(1.0f);
//    mannequin->position(200.0f, 0.06f, 0.0f);
//    mannequin->orientation(0.0f, 90.0f, 0.0f);
//
    Airport *airport = new Airport();
    airport->size(0.1f);

    Tower *tower = new Tower();
    tower->size(0.07f);
    tower->position(1000.0f, -20.0f, -500.0f);
    tower->orientation(0.0f, 70.0f, 0.0f);

    Runway *runway = new Runway();
    runway->size(0.4f, 0.4f, 0.55f);
    runway->position(600.0f, -10.0f, 0.0f);

    AirportFloor *airportFloor = new AirportFloor(20, 20, "../src/img/ground1.bmp");
    airportFloor->position(0.0f, 0.01f, 0.0f);
    airportFloor->size(800.0f, 0.0f, 4000.0f);

    AirportFloor *airportFloor2 = new AirportFloor(20, 20, "../src/img/ground2.bmp");
    airportFloor2->position(1700.0f, 0.01f, 0.0f);
    airportFloor2->size(1800.0f, 0.0f, 4000.0f);


    AirportFloor *water = new AirportFloor(20, 20, "../src/img/water.bmp");
    water->changeFrozen();
    water->position(0.0f, -1.0f, 0.0f);
    water->size(10000.0f, 0.0f, 10000.0f);

    Billboard *billboard = new Billboard();
    billboard->size(0.5f);
    billboard->position(1000.0f, -10.0f, 0.0f);
    billboard->orientation(0.0f, -90.0f, 0.0f);

//    Aircraft *aircraft = new Aircraft();
//    aircraft->size(13.0f);
//    aircraft->position(130.0f, 20.0f, 10.0f);
//    aircraft->orientation(0.0f, 210.0f, 0.0f);

    cotrolledAircraft = new Aircraft();
    cotrolledAircraft->size(13.0f);
    cotrolledAircraft->position(130.0f, 20.0f, 10.0f);
    cotrolledAircraft->orientation(0.0f, 210.0f, 0.0f);
    cotrolledAircraft->isControlled = true;

    Aircraft *aircraft2 = new Aircraft();
    aircraft2->size(13.0f);
    aircraft2->position(130.0f, 20.0f, 260.0f);
    aircraft2->orientation(0.0f, 210.0f, 0.0f);

    Aircraft *aircraft3 = new Aircraft();
    aircraft3->size(13.0f);
    aircraft3->position(190.0f, 20.0f, 930.0f);
    aircraft3->orientation(0.0f, 70.0f, 0.0f);

    Aircraft *aircraft4 = new Aircraft();
    aircraft4->size(13.0f);
    aircraft4->position(-200.0f, 20.0f, 325.0f);
    aircraft4->orientation(0.0f, 30.0f, 0.0f);

    Aircraft *aircraft5 = new Aircraft();
    aircraft5->size(13.0f);
    aircraft5->position(-200.0f, 20.0f, 60.0f);
    aircraft5->orientation(0.0f, 30.0f, 0.0f);

    Aircraft *aircraft6 = new Aircraft();
    aircraft6->size(13.0f);
    aircraft6->position(-200.0f, 20.0f, -200.0f);
    aircraft6->orientation(0.0f, 30.0f, 0.0f);

//    Car *car = new Car();
//    car->position(0.0f, 0.0f, 620.0f);
//    car->size(10.0f);

    Car *car2 = new Car();
    car2->position(0.0f, 0.0f, 550.0f);
    car2->size(10.0f);

    Car *car3 = new Car();
    car3->position(-60.0f, 0.0f, 620.0f);
    car3->size(10.0f);

    AddObjectToScene(floor);
    AddObjectToScene(cotrolledAircraft);
//    AddObjectToScene(mannequin);
    AddObjectToScene(airport);
    AddObjectToScene(tower);
    AddObjectToScene(runway);
    AddObjectToScene(airportFloor);
    AddObjectToScene(airportFloor2);
    AddObjectToScene(water);
    AddObjectToScene(billboard);
//    AddObjectToScene(car);
    AddObjectToScene(car2);
    AddObjectToScene(car3);
    AddObjectToScene(aircraft2);
    AddObjectToScene(aircraft3);
    AddObjectToScene(aircraft4);
    AddObjectToScene(aircraft5);
    AddObjectToScene(aircraft6);

    float eye[3] = {855.984, 210, 82.0659};
    camera.SetEyePosition(eye[0], eye[1], eye[2]);
    float dir[3] = {0.77527, 0.199578, -0.59927f};
    camera.SetViewDirection(dir[0] , dir[1], dir[2]);

}

void ProjectScene::Projection()
{
    GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
    gluPerspective(60.0, aspect, 1.0, 2000.0);
//    glOrtho(static_cast<GLdouble>(-windowWidth) / static_cast<GLdouble>(6.0), static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(1.5),
//            static_cast<GLdouble>(-windowHeight) / static_cast<GLdouble>(6.0), static_cast<GLdouble>(windowHeight) / static_cast<GLdouble>(1.5),
//            static_cast<GLdouble>(1.0), static_cast<GLdouble>(2000.0));
}

void ProjectScene::Update(const double& deltaTime)
{
    Animation* animated_obj;
    // Update camera/view
    camera.Update(deltaTime);
    // Iterate through objects to update animations

    if (isControl)
    {
        float eye[3];
        cotrolledAircraft->GetDriverCamera(eye[0], eye[1], eye[2]);
        camera.SetEyePosition(eye[0], eye[1], eye[2]);
        float dir[3];
        cotrolledAircraft->GetDriverViewDir(dir[0], dir[1], dir[2]);
        camera.SetViewDirection(dir[0] , dir[1], dir[2]);
    }

    if (isBlue)
    {
        glClearColor(0.527f, 0.77f, 0.886f, 1.0f);
    }
    else
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    for (DisplayableObject* obj : objects)
    {
        animated_obj = dynamic_cast<Animation*>(obj); // Cast to animation
        if (animated_obj != NULL) // If cast successful
            animated_obj->Update(deltaTime); // Call update sequence for obj
    }
}

void  ProjectScene::HandleKey(unsigned char key, int state, int x, int y)
{
    // Handle Keyboard input (ASCII) and pass to objects.
    // State is 1 for key press, 0 for key release

    if (key == 27 && state) // Check for escape key pressed
    {
        exit(0); // EXIT ON ESCAPE PRESS
    }

    if (key == 'b' && state)
        isBlue = !isBlue;


    if (key == '6' && state)
    {
        float eye[3];
        camera.GetEyePosition(eye[0] , eye[1], eye[2]);
        cout << "(" << eye[0] << ", " << eye[1] << ", " << eye[2] << ")"<< endl;
    }

    if (key == '7' && state)
    {
        float dir[3];
        camera.GetViewDirection(dir[0] , dir[1], dir[2]);
        cout << "{" << dir[0] << ", " << dir[1] << ", " << dir[2] << "}"<< endl;
    }

    if (key == '1' && state)
    {
        float eye[3] = {855.984, 210, 82.0659};
        camera.SetEyePosition(eye[0], eye[1], eye[2]);
        float dir[3] = {0.77527, 0.199578, -0.59927f};
        camera.SetViewDirection(dir[0] , dir[1], dir[2]);

        isControl = false;
    }

    if (key == '2' && state)
    {
        float eye[3] = {-31.2647f, 268, 753.57};
        camera.SetEyePosition(eye[0], eye[1], eye[2]);
        float dir[3] = {0.271686, -0.205592f, -0.940169f};
        camera.SetViewDirection(dir[0] , dir[1], dir[2]);

        isControl = false;
    }

    if (key == '3' && state)
    {
        float eye[3] = {919.903, 552, 592.121};
        camera.SetEyePosition(eye[0], eye[1], eye[2]);
        float dir[3] = {-0.452299f, -0.496826f, -0.740669f};
        camera.SetViewDirection(dir[0], dir[1], dir[2]);

        isControl = false;
    }

    if (key == '4' && state)
    {
        float eye[3] = {600.12, 40, 1521.52};
        camera.SetEyePosition(eye[0], eye[1], eye[2]);
        float dir[3] = {-0.0519261, -0.111391, -0.992419};
        camera.SetViewDirection(dir[0] , dir[1], dir[2]);

        isControl = false;
    }

    if (key == '5' && state)
    {
        float eye[3] = {141.098, 21, 665.282};
        camera.SetEyePosition(eye[0], eye[1], eye[2]);
        float dir[3] = {-0.702746, -0.244084, -0.66826};
        camera.SetViewDirection(dir[0] , dir[1], dir[2]);

        isControl = false;
    }

    if (key == '8' && state)
    {
        cotrolledAircraft->size(13.0f);
        cotrolledAircraft->position(130.0f, 20.0f, 10.0f);
        cotrolledAircraft->orientation(0.0f, 210.0f, 0.0f);
        cotrolledAircraft->Reset();
    }

    if (key == '9' && state)
    {
        float eye[3];
        cotrolledAircraft->GetDriverCamera(eye[0], eye[1], eye[2]);
        camera.SetEyePosition(eye[0], eye[1], eye[2]);
        float dir[3];
        cotrolledAircraft->GetDriverViewDir(dir[0], dir[1], dir[2]);
        camera.SetViewDirection(dir[0] , dir[1], dir[2]);

        isControl = true;
    }

    Input* input_obj;
    camera.HandleKey(key, state, x, y);
    for (DisplayableObject* obj : objects)
    {
        input_obj = dynamic_cast<Input*>(obj);
        if (input_obj != NULL)
            input_obj->HandleKey(key, state, x, y);
    }

}
