#include "RoadBuilder.h"

// load road models into correct positions.
void RoadBuilder::loadRoads(vector<ModelHandler> &roadModels)
{
	glm::vec3 scale = glm::vec3(3.5, 2.3, 2.3);
	glm::vec2 xyOffset = glm::vec2(0, -5);

	ModelHandler Road1("Models/road/road.fbx", "roadTex.png", 1); // Model taken from: https://free3d.com/3d-model/road-47211.html
	Road1.scale(scale);
	Road1.translate(glm::vec3(xyOffset, 0));
	ModelHandler Road2("Models/road/road.fbx", "roadTex.png", 1);
	Road2.scale(scale);
	Road2.translate(glm::vec3(xyOffset, -20));
	ModelHandler Road3("Models/road/road.fbx", "roadTex.png", 1);
	Road3.scale(scale);
	Road3.translate(glm::vec3(xyOffset, -40));
	ModelHandler Road4("Models/road/road.fbx", "roadTex.png", 1);
	Road4.scale(scale);
	Road4.translate(glm::vec3(xyOffset, -60));
	ModelHandler Road5("Models/road/road.fbx", "roadTex.png", 1);
	Road5.scale(scale);
	Road5.translate(glm::vec3(xyOffset, -80));
	ModelHandler Road6("Models/road/road.fbx", "roadTex.png", 1);
	Road6.scale(scale);
	Road6.translate(glm::vec3(xyOffset, -100));
	ModelHandler Road7("Models/road/road.fbx", "roadTex.png", 1);
	Road7.scale(scale);
	Road7.translate(glm::vec3(xyOffset, -120));
	ModelHandler Road8("Models/road/road.fbx", "roadTex.png", 1);
	Road8.scale(scale);
	Road8.translate(glm::vec3(xyOffset, -140));
	ModelHandler Road9("Models/road/road.fbx", "roadTex.png", 1);
	Road9.scale(scale);
	Road9.translate(glm::vec3(xyOffset, -160));
	ModelHandler Road10("Models/road/road.fbx", "roadTex.png", 1);
	Road10.scale(scale);
	Road10.translate(glm::vec3(xyOffset, -180));

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


void RoadBuilder::loadObstacles(vector<ModelHandler>& obstacleModels)
{
	ModelHandler CraggyRock("Models/rocks/craggyRock.fbx", "craggyRock.png", 1);
	CraggyRock.scale(glm::vec3(0.02, 0.02, 0.02));
	CraggyRock.translate(glm::vec3(0, -3, 20));
	ModelHandler MossyRock("Models/rocks/mossyRock.fbx", "mossyRock.png", 1);
	MossyRock.scale(glm::vec3(0.4, 1, 0.6));
	MossyRock.translate(glm::vec3(-1, -2.25, 20));
	MossyRock.modelPosition.x = 0;
	ModelHandler Log("Models/logs/logPile.fbx", "logTex.png", 1);
	Log.scale(glm::vec3(0.8, 1, 1));
	Log.rotation(90.0f, glm::vec3(0, 1, 0));
	Log.translate(glm::vec3(-1, -3.25, 20));
	Log.modelPosition.x = 0;
	ModelHandler CraggyRock2("Models/rocks/craggyRock.fbx", "craggyRock.png", 1);
	CraggyRock2.scale(glm::vec3(0.02, 0.02, 0.02));
	CraggyRock2.translate(glm::vec3(0, -3, 20));
	ModelHandler MossyRock2("Models/rocks/mossyRock.fbx", "mossyRock.png", 1);
	MossyRock2.scale(glm::vec3(0.4, 1, 0.6));
	MossyRock2.translate(glm::vec3(-1, -2.25, 20));
	MossyRock2.modelPosition.x = 0;
	ModelHandler Log2("Models/logs/logPile.fbx", "logTex.png", 1);
	Log2.scale(glm::vec3(0.8, 1, 1));
	Log2.rotation(90.0f, glm::vec3(0, 1, 0));
	Log2.translate(glm::vec3(-1, -3.25, 20));
	Log2.modelPosition.x = 0;

	obstacleModels.push_back(CraggyRock);
	obstacleModels.push_back(MossyRock);
	obstacleModels.push_back(Log);
	obstacleModels.push_back(CraggyRock2);
	obstacleModels.push_back(MossyRock2);
	obstacleModels.push_back(Log2);
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

// move obstacles into road with random left, center, or right.
void RoadBuilder::repositionObstacle(glm::vec3 camPos, vector<ModelHandler>& obstacleModels)
{
	int selectedModel = selectObstacle(obstacleModels.size());
	int sidewaysTrans = rand() % 9;
	if (sidewaysTrans < 3)
	{
		sidewaysTrans = -5;
	}
	else if (sidewaysTrans > 6)
	{
		sidewaysTrans = 5;
	}
	else sidewaysTrans = 0;

	// make sure obstacle is behind camera before spawning it in.
	if (obstacleModels[selectedModel].modelPosition.z > camPos.z + 10)
	{
		// reset pos and set new pos.
		obstacleModels[selectedModel].translate(glm::vec3(-obstacleModels[selectedModel].modelPosition.x, 0, -obstacleModels[selectedModel].modelPosition.z));
		obstacleModels[selectedModel].translate(glm::vec3(sidewaysTrans, 0, -200) + glm::vec3(0, 0, camPos.z));
	}

}

int RoadBuilder::selectObstacle(int size)
{
	return rand() % size;
}
