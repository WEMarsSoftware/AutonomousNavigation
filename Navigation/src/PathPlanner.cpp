#include<PathPlanner.h>

PathPlanner::PathPlanner() {

}

PathPlanner::~PathPlanner() {

}

float PathPlanner::avAngle(sl::Chunk chunk,int v) {
	size_t N_tri = chunk.triangles.size();
	std::vector<int> neighbours;
	float avAngle = 0;

	//get all neighbouring vertices
	for (size_t i = 0; i<N_tri; i++) {
		sl::uint3 tri = chunk.triangles[i];
		if (tri[0] == v) {
			neighbours.push_back(tri[1]);
			neighbours.push_back(tri[2]);
		}
		else if (tri[1] == v) {
			neighbours.push_back(tri[0]);
			neighbours.push_back(tri[2]);
		}
		else if (tri[2] == v) {
			neighbours.push_back(tri[0]);
			neighbours.push_back(tri[1]);
		}
	}

	//calculate average angle of surrounding normals
	int Nd = neighbours.size(); //direct neighbours of v
	for (int u = 0; u<Nd; u++) {
		avAngle += acos(sl::float3::dot(chunk.normals[u], chunk.normals[v]));
	}
	avAngle /= Nd;

	return avAngle;
}

float PathPlanner::getRoughness(sl::Chunk chunk, int v) {
	float roughness = avAngle(chunk, v);
	int Nl = chunk.vertices.size();

	//get angle of all points in chunk
	for (size_t i = 0; i<Nl; i++) {
		roughness += avAngle(chunk, i);
	}

	//normalize
	roughness /= Nl;

	return roughness;
}

float PathPlanner::getHeight(sl::Chunk chunk) {
	return 0;
}

float PathPlanner::calculateCost(sl::Chunk chunk) {
	return 0;
}

std::vector<sl::float3> PathPlanner::findPath() {
	std::vector<sl::float3> path;
	return path;
}