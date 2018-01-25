// get roughness heuristic
#include <cmath>
#includ <algorithm>

float avAngle(sl::Chunk chunk, float3 vertex, int v){
	size_t N_tri = chunk.triangles.size();
	
	//keep track of which edges have been checked
	//size_t N_vert = chunk.vertices.size();
	//create N_vert x N_vert matrix to keep track of visited cells
	//std::vector<vector<bool>> visited(N_vert,vector<bool>(N_vert));
	
	//get v of all neighbour vertices
	vector<int> neighbours;
	std::vector<int2> edges;
	float avAngle = 0;
	for(size_t i=0;i<N_tri;i++){
		//if triangle contains vertex, push other vertices
		vector<float3> tri = chunk.triangles[i];
		if(std::find(tri.begin(), tri.end(), v) != tri.end()){
			for(int j=0;j<2;j++){
				if(tri[j]!=v){
					neighbours.push_back(tri[j]);
				}
			}
		}		
	}
	
	//calculate average angle of surrounding normals
	for(int u=0;u<tri.size();u++){
		avAngle += acos(chunk.normal[u]*chunk.normal[v]));
	}
	avAngle /= Nd;
}

float getRoughness(sl::Chunk chunk){
	//std::vector<sl::float3> vertices
	float roughness;
	int N = chunk.size();
	
	for(size_t i=0;i<N;i++){
		
	}
	
}