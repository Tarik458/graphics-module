#include "RoadBuilder.h"

// load road models into correct positions.
void RoadBuilder::loadRoads(vector<ModelHandler> &roadModels)
{
	ModelHandler Road1("Models/road/road.fbx", "roadTex.png", 1); // Model taken from: https://free3d.com/3d-model/road-47211.html
	Road1.scale(glm::vec3(2.3, 2.3, 2.3));
	Road1.translate(glm::vec3(0, -5, 0));
	ModelHandler Road2("Models/road/road.fbx", "roadTex.png", 1);
	Road2.scale(glm::vec3(2.3, 2.3, 2.3));
	Road2.translate(glm::vec3(0, -5, -20));
	ModelHandler Road3("Models/road/road.fbx", "roadTex.png", 1);
	Road3.scale(glm::vec3(2.3, 2.3, 2.3));
	Road3.translate(glm::vec3(0, -5, -40));
	ModelHandler Road4("Models/road/road.fbx", "roadTex.png", 1);
	Road4.scale(glm::vec3(2.3, 2.3, 2.3));
	Road4.translate(glm::vec3(0, -5, -60));
	ModelHandler Road5("Models/road/road.fbx", "roadTex.png", 1);
	Road5.scale(glm::vec3(2.3, 2.3, 2.3));
	Road5.translate(glm::vec3(0, -5, -80));
	ModelHandler Road6("Models/road/road.fbx", "roadTex.png", 1);
	Road6.scale(glm::vec3(2.3, 2.3, 2.3));
	Road6.translate(glm::vec3(0, -5, -100));
	ModelHandler Road7("Models/road/road.fbx", "roadTex.png", 1);
	Road7.scale(glm::vec3(2.3, 2.3, 2.3));
	Road7.translate(glm::vec3(0, -5, -120));
	ModelHandler Road8("Models/road/road.fbx", "roadTex.png", 1);
	Road8.scale(glm::vec3(2.3, 2.3, 2.3));
	Road8.translate(glm::vec3(0, -5, -140));
	ModelHandler Road9("Models/road/road.fbx", "roadTex.png", 1);
	Road9.scale(glm::vec3(2.3, 2.3, 2.3));
	Road9.translate(glm::vec3(0, -5, -160));
	ModelHandler Road10("Models/road/road.fbx", "roadTex.png", 1);
	Road10.scale(glm::vec3(2.3, 2.3, 2.3));
	Road10.translate(glm::vec3(0, -5, -180));

	roadModels.push_back(Road1);
	roadModels.push_back(Road2);
	roadModels.push_back(Road3);
	roadModels.push_back(Road4);
	roadModels.push_back(Road5);
	roadModels.push_back(Road6);
	roadModels.push_back(Road7);
	roadModels.push_back(Road8);
	roadModels.push_back(Road9);
	roadModels.push_back(Road10);
}

// if road section behind camera then move to front of road.
bool RoadBuilder::repositionRoad(glm::vec3 camPos, glm::vec3 modelPos)
{
	if (modelPos.z > camPos.z +5)
	{
		return true;
	}
	else
	{
		return false;
	}
}
