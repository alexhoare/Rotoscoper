#include <iostream>
#include "Colorer.h"

using namespace std;
using namespace cv;

int main() {
	namedWindow("processed", WINDOW_FREERATIO);
	namedWindow("unprocessed", WINDOW_FREERATIO);
	Mat image;
	//Mat image = imread("C:/Users/alext/Pictures/apple.png");
	int threshold = 20;
	int iterations = 4;
	int blurSize = 5;
	VideoCapture vc(0);
	vc >> image;
	while (!image.empty()) {
		Colorer c(image, threshold, iterations, blurSize);
		imshow("processed", c.color());
		waitKey(1);
		imshow("unprocessed", image);
		waitKey(1);
		vc >> image;
	}
	//Colorer c(image, threshold);
	//imshow("window", c.color());
	//waitKey(0);
}