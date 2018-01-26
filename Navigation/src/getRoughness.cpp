// get roughness heuristic
#include <cmath>
#includ <algorithm>

float avAngle(sl::Chunk chunk, sl::float3 vertex, int v){
	size_t N_tri = chunk.triangles.size();
	vector<int> neighbours;
	float avAngle = 0;
	std::vector<int>::iterator it;
	
	//get v of all neighbour vertices
	for(size_t i=0;i<N_tri;i++){
		//if triangle contains vertex, push other vertices
		std::vector<sl::float3> tri = chunk.triangles[i];
		p = std::find (myints, myints+4, 30);
		if(std::find(tri.begin(), tri.end(), v) != tri.end()){
			for(int j=0;j<2;j++){
				if(tri[j]!=v){
					neighbours.push_back(tri[j]);
				}
			}
		}
	}
	
	//calculate average angle of surrounding normals
	int Nd = neighbours.size(); //direct neighbours of v
	for(int u=0;u<Nd;u++){
		avAngle += acos(sl::float3.dot(chunk.normals[u],chunk.normals[v]));
	}
	avAngle /= Nd;
}

float getRoughness(sl::Chunk chunk,sl::){
	float roughness = avAngle();
	int Nl = chunk.size();
	
	//get angle of all points in chunk
	for(size_t i=0;i<Nl;i++){
		roughness += avAngle(chunk,chunk.vertices[i],i);
	}
	
	//normalize
	roughness /= Nl;	
}