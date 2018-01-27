#include "PathPlanner.h"
#include "Vision.h"

#include<sl/Camera.hpp>
#include<sl/Chunk.hpp>
#include<opencv2/opencv.hpp>
#include<Gl>

#include<stdio.h>

int main(){

    //Zed objects
    Camera zed;         //Camera object
    sl::Pose pose;      // Pose to hold positional tracking data
    sl::Mesh mesh;      // Mesh to hold the mesh generated during spatial mapping

    std::chrono::high_resolution_clock::time_point t_last; //Last mesh update time


    mapping = false;    //Tracks if spatial mapping is occurring

    // Set configuration parameters
    InitParameters init_params;
    init_params.camera_resolution = RESOLUTION_HD1080;
    init_params.depth_mode = DEPTH_MODE_PERFORMANCE;
    init_params.coordinate_units = UNIT_METER;
    init_params.camera_fps = 100;

    // Configure Spatial Mapping and filtering parameters
    sl::SpatialMappingParameters spatial_mapping_params;
    spatial_mapping_params.range_meter = sl::SpatialMappingParameters::get(sl::SpatialMappingParameters::MAPPING_RANGE_FAR); //MAPPING_RANGE_FAR specified for outdoor use
    spatial_mapping_params.resolution_meter = sl::SpatialMappingParameters::get(sl::SpatialMappingParameters::MAPPING_RESOLUTION_LOW); //Low resolution to detect only large variations to save on memory
    spatial_mapping_params.save_texture = false;        //Textures not needed
    spatial_mapping_params.max_memory_usage = 512;
    spatial_mapping_params.use_chunk_only = true; // If we use chunks we do not need to keep the mesh consistent

    // Open the camera
    ERROR_CODE err = zed.open(init_params);
    if (err != SUCCESS) {
        printf("%s\n", errorCode2str(err).c_str());
        zed.close();
        return 1; // Quit if an error occurred
    }

    RuntimeParameters runtime_parameters;
    runtime_parameters.sensing_mode = SENSING_MODE_STANDARD;

    // Enable positional tracking
    zed.enableTracking();
    // Enable spatial mapping
    zed.enableSpatialMapping(spatial_mapping_params);
    mesh.clear();
    mapping = true;
    
}
