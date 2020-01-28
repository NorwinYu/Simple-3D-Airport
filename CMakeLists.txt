# -------------------
#  Projects Settings 
# -------------------

cmake_minimum_required(VERSION 3.8)
project(project)

# -------------------
#  Compilation flags 
# -------------------

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_CXX_STANDARD 11)

# -------------------
#  Load libraries 
# -------------------

#opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#glut
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

#glew
find_package(GLEW REQUIRED)
include_directories(/usr/local/Cellar/glew/2.1.0)

#glfw
find_package(GLFW3 REQUIRED)
include_directories(/usr/local/Cellar/glfw/3.2.1)

#sfml
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()

# -------------------
#  Build executable  
# -------------------

set(SOURCE_FILES
        Framework/Engine/Engine.cpp
        Framework/Engine/Engine.h
        Framework/Engine/Scene.cpp
        Framework/Engine/Scene.h
        Framework/Interface/Animation.h
        Framework/Interface/DisplayableObject.h
        Framework/Interface/Input.h
        Framework/Utility/Camera.cpp
        Framework/Utility/Camera.h
        Framework/Utility/Texture.cpp
        Framework/Utility/Texture.h
        Framework/Utility/VectorMath.h
        src/main.cpp
        src/ProjectScene.cpp
        src/ProjectScene.h
        src/Mannequin.cpp
        src/Mannequin.h src/Aircraft.cpp src/Aircraft.h src/myFramework/DrawObject.cpp src/myFramework/DrawObject.h src/Floor.cpp src/Floor.h src/objLoader/ObjLoader.cpp src/objLoader/ObjLoader.h src/Airport.cpp src/Airport.h src/Tower.cpp src/Tower.h src/myFramework/Music.h src/Runway.cpp src/Runway.h src/AirportFloor.cpp src/AirportFloor.h src/Cloud.cpp src/Cloud.h src/Billboard.cpp src/Billboard.h src/Car.cpp src/Car.h)
add_executable(project ${SOURCE_FILES})
target_link_libraries(project ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${SFML_LIBRARIES})