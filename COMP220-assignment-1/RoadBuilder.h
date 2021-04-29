#include <iostream>
#include <glm/glm.hpp>
#include "ModelLoader.h"

#pragma once
class RoadBuilder
{
public:
	void loadRoads(vector<ModelHandler>& roadModels);

	bool repositionRoad(glm::vec3 camPos, glm::vec3 modelPos);
};

