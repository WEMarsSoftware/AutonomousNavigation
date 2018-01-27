#pragma once
#ifndef PATHPLANNER_H
#define PATHPLANNER_H

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
    float getRoughness(sl::Chunk chunk);
    float getHeight(sl::Chunk chunk);
    float calculateCost(sl::Chunk chunk);
    Node generateNode(sl::Chunk chunk);
    std::vector<Node> findPath();
};

#endif // !PATHPLANNER_H