#include <iostream>
#include <glm/glm.hpp>
#include "ModelLoader.h"

#pragma once
class RoadBuilder
{
public:
	void loadRoads(vector<ModelHandler>& roadModels);
	void loadObstacles(vector<ModelHandler>& obstacleModels);

	bool repositionRoad(glm::vec3 camPos, glm::vec3 modelPos);
};

