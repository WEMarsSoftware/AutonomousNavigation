#include<Vision.h>

Vision::Vision() {

}

Vision::~Vision() {

}

cv::Mat Vision::cvImage(sl::Mat &im) {
	//from StereoLabs example
	// Mapping between MAT_TYPE and CV_TYPE
	int cv_type = -1;
	switch (im.getDataType()) {
	case sl::MAT_TYPE_32F_C1: cv_type = CV_32FC1; break;
	case sl::MAT_TYPE_32F_C2: cv_type = CV_32FC2; break;
	case sl::MAT_TYPE_32F_C3: cv_type = CV_32FC3; break;
	case sl::MAT_TYPE_32F_C4: cv_type = CV_32FC4; break;
	case sl::MAT_TYPE_8U_C1: cv_type = CV_8UC1; break;
	case sl::MAT_TYPE_8U_C2: cv_type = CV_8UC2; break;
	case sl::MAT_TYPE_8U_C3: cv_type = CV_8UC3; break;
	case sl::MAT_TYPE_8U_C4: cv_type = CV_8UC4; break;
	default: break;
	}

	// Since cv::Mat data requires a uchar* pointer, we get the uchar1 pointer from sl::Mat (getPtr<T>())
	// cv::Mat and sl::Mat will share a single memory structure
	return cv::Mat(im.getHeight(), im.getWidth(), cv_type, im.getPtr<sl::uchar1>(sl::MEM_CPU));
}

std::vector<cv::Point> Vision::findTennisBalls(cv::Mat &im) {
	std::vector<cv::Point> foundBalls;
	return foundBalls;
}