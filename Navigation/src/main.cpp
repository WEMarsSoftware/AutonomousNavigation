//WE Mars Mars Rover Navigation Team 2018

//headers
#include "PathPlanner.h"
#include "Vision.h"

#include <sl/Camera.hpp>

#include <opencv2/opencv.hpp>

// OpenGL includes
#include <GL/glew.h>
#include "GL/freeglut.h"

#include <stdio.h>
#include <math.h>
#include <thread>

#define USE_CHUNKS 1

sl::TRACKING_STATE tracking_state;  //Pose data
bool mapping;

void meshSync(Camera &zed, std::chrono::high_resolution_clock::time_point t_last, int duration);
void updatePath(sl::Mesh &mesh);

int main(){

    //Zed objects
    sl::Camera zed;         //Camera object
    sl::Pose pose;      // Pose to hold positional tracking data
    sl::Mesh mesh;      // Mesh to hold the mesh generated during spatial mapping
    std::vector<sl::float3> path;
    PathPlanner::PathPlanner pathObj;

    std::chrono::high_resolution_clock::time_point t_last; //Last mesh update time


    bool mapping = false;    //Tracks if spatial mapping is occurring
    int sync_duration = 500; //Time between mesh updates

    // Set configuration parameters
    sl::InitParameters init_params;
    init_params.camera_resolution = sl::RESOLUTION_HD1080;
    init_params.depth_mode = sl::DEPTH_MODE_PERFORMANCE;
    init_params.coordinate_units = sl::UNIT_METER;
    init_params.camera_fps = 100;

    // Configure Spatial Mapping and filtering parameters
    sl::SpatialMappingParameters spatial_mapping_params;
    spatial_mapping_params.range_meter = sl::SpatialMappingParameters::get(sl::SpatialMappingParameters::MAPPING_RANGE_FAR); //MAPPING_RANGE_FAR specified for outdoor use
    spatial_mapping_params.resolution_meter = sl::SpatialMappingParameters::get(sl::SpatialMappingParameters::MAPPING_RESOLUTION_LOW); //Low resolution to detect only large variations to save on memory
    spatial_mapping_params.save_texture = false;        //Textures not needed
    spatial_mapping_params.max_memory_usage = 512;
    spatial_mapping_params.use_chunk_only = true; // If we use chunks we do not need to keep the mesh consistent

    // Open the camera
    sl::ERROR_CODE err = zed.open(init_params);
    if (err != sl::SUCCESS) {
        printf("%s\n", errorCode2str(err).c_str());
        zed.close();
        return 1; // Quit if an error occurred
    }

    sl::RuntimeParameters runtime_parameters;
    runtime_parameters.sensing_mode = sl::SENSING_MODE_STANDARD;

    // Enable positional tracking
    zed.enableTracking();
    // Enable spatial mapping
    zed.enableSpatialMapping(spatial_mapping_params);
    mesh.clear();
    mapping = true;


    //Mesh Sync Thread
    t_last = std::chrono::high_resolution_clock::now();
    thread meshSyncThread(meshSync, zed, t_start, t_last, duration);

    //Path calculation thread
    thread pathCalcThread();

    //Ball detection
    thread ballDetectionThread();

    //Finish task
    mapping = false;

    while (true) {
        if (meshSyncThread.joinable()) {
            meshSyncThread.join();
        }
        if (pathCalcThread.joinable()) {
            pathCalcThread.join();
        }
        if (ballDetectionThread.joinable()) {
            ballDetectionThread.join();
        }
    }

    zed.close();
}

//Update the mesh
void meshSync(Camera &zed, std::chrono::high_resolution_clock::time_point t_last, int duration) {
    while (mapping) {
        //Check if zed is grabbing images properly
        if (zed.grab() == sl::SUCCESS) {
            tracking_state = zed.getPosition(pose);
            //Check time since last mesh sync
            auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t_last).count();

            if (timeElapsed > duration) {
                zed.requestMeshAsync();
                t_last = std::chrono::high_resolution_clock::now();
            }
        }
        else {
            mapping = false;
        }
    }
}

//Updates current path
void updatePath(sl::Mesh &mesh, std::vector<sl::float3> &path, PathPlanner::PathPlanner &pathObj) {
    path = pathObj.getPath();
}