#pragma once
#ifndef VISION_H
#define VISION_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <sl/Camera.hpp>
#include <opencv2/opencv.hpp>
#include <SaveDepth.hpp>

class Vision {
public:
    Vision();
    ~Vision();
	cv::Mat Vision::cvImage(sl::Mat &im);
	std::vector<cv::Point> findTennisBalls(cv::Mat &im);
};

#endif // !VISION_H
