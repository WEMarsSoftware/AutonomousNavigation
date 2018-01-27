#pragma once
#ifndef PATHPLANNER_H
#define PATHPLANNER_H

#include<sl/Camera.hpp>
#include<math.h>
#include<stdio.h>

class PathPlanner {
private:
    struct Node {
        float roughness;
        float height;
        float cost;
        std::vector<Node*> neighbours;
        sl::Chunk* chunk;
    };

    std::vector<Node> nodes;

public:
    PathPlanner();
    ~PathPlanner();
	float PathPlanner::avAngle(sl::Chunk chunk, int v);
    float getRoughness(sl::Chunk chunk,int v);
    float getHeight(sl::Chunk chunk);
    float calculateCost(sl::Chunk chunk);
    Node generateNode(sl::Chunk chunk);
	std::vector<sl::float3> findPath();
};

#endif // !PATHPLANNER_H