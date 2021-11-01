#include "Pixel.h"

using namespace std;
using namespace cv;

#pragma once
class Colorer
{
	Pixel** rowSegments;
	Pixel** colSegments;
	Mat image;
	int rows;
	int cols;
	int threshold;
	int iterations;
	int blurSize;
	void calculateRowSegments();
	void calculateColSegments();
public:
	Colorer(Mat image, int threshold, int iterations, int blurSize);
	Mat color();
};

