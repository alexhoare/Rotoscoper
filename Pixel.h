#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

#pragma once
class Pixel
{
	Point3_<uchar> color;

public:
	Pixel();
	Pixel(Point3_<uchar> color);
	Point3_<uchar> getColor();
	void setColor(Point3_<uchar> color);
};

