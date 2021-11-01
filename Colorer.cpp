#include "Colorer.h"

void Colorer::calculateRowSegments()
{
	for (int i = 0; i < rows; i++) {
		int start = 0;
		Point3_<uchar> hostColor = colSegments[i][0].getColor();
		int numRed = (int)hostColor.x, numGreen = (int)hostColor.y, numBlue = (int)hostColor.z;
		int numPixelsInGroup = 0;
		for (int j = 0; j < cols; j++) {
			//printf("reading pixel at (%i, %i)\n", i, j);
			numPixelsInGroup++;
			//printf("numRed: %i, numGreen: %i, numBlue: %i\nnumPixels: %i\n", numRed, numGreen, numBlue, numPixelsInGroup);
			hostColor = Point3_<uchar>((uchar)(numRed / numPixelsInGroup), (uchar)(numGreen / numPixelsInGroup), (uchar)(numBlue / numPixelsInGroup));
			Point3_<uchar> currentColor = colSegments[i][j].getColor();
			if (abs(hostColor.x - currentColor.x) > threshold || abs(hostColor.y - currentColor.y) > threshold || abs(hostColor.z - currentColor.z) > threshold)
			{
				//counting numColors can be easily optimized
				//Point3_<uchar> averageColor(numRed / numPixelsInGroup, numGreen / numPixelsInGroup, numBlue / numPixelsInGroup);
				for (int k = start; k < j; k++) {
					rowSegments[i][k].setColor(hostColor);
				}
				start = j;
				hostColor = colSegments[i][j].getColor();
				numPixelsInGroup = 0;
				numRed = 0;
				numGreen = 0;
				numBlue = 0;
			}
			numRed += (int)currentColor.x;
			numGreen += (int)currentColor.y;
			numBlue += (int)currentColor.z;
		}
	}
}

void Colorer::calculateColSegments()
{
	//printf("calculating col segments\n");
	for (int i = 0; i < cols; i++) {
		int start = 0;
		Point3_<uchar> hostColor = rowSegments[0][i].getColor();
		int numRed = (int)hostColor.x, numGreen = (int)hostColor.y, numBlue = (int)hostColor.z;
		int numPixelsInGroup = 0;
		for (int j = 0; j < rows; j++) {
			//printf("location: (%i, %i)\n", j, i);
			//printf("host color: (%d, %d, %d)", hostColor.x, hostColor.y, hostColor.z);
			numPixelsInGroup++;
			hostColor = Point3_<uchar>((uchar)(numRed / numPixelsInGroup), (uchar)(numGreen / numPixelsInGroup), (uchar)(numBlue / numPixelsInGroup));
			Point3_<uchar> currentColor = rowSegments[j][i].getColor();
			if (abs(hostColor.x - currentColor.x) > threshold || abs(hostColor.y - currentColor.y) > threshold || abs(hostColor.z - currentColor.z) > threshold)
			{
				for (int k = start; k < j; k++) {
					//this->image.at<Point3_<uchar>>(j, i) = hostColor;
					colSegments[k][i].setColor(hostColor);
				}
				start = j;
				hostColor = rowSegments[j][i].getColor();
				numPixelsInGroup = 0;
				numRed = 0;
				numGreen = 0;
				numBlue = 0;
			}
			numRed += (int)currentColor.x;
			numGreen += (int)currentColor.y;
			numBlue += (int)currentColor.z;
		}
		if (start < rows - 2) {
			for (int k = start; k < rows; k++) {
				//this->image.at<Point3_<uchar>>(j, i) = hostColor;
				colSegments[k][i].setColor(hostColor);
			}
		}
	}
}

Colorer::Colorer(Mat image, int threshold, int iterations, int blurSize)
{
	image.copyTo(this->image);
	this->threshold = threshold;
	this->iterations = iterations;
	this->blurSize = blurSize;
	rows = image.rows;
	cols = image.cols;
	rowSegments = new Pixel*[rows];
	colSegments = new Pixel*[rows];
	for (int i = 0; i < rows; i++) {
		rowSegments[i] = new Pixel[cols];
		colSegments[i] = new Pixel[cols];
		for (int j = 0; j < cols; j++) {
			Point3_<uchar> pixelColor = image.at<Point3_<uchar>>(i, j);
			rowSegments[i][j] = Pixel(pixelColor);
			colSegments[i][j] = Pixel(pixelColor);
		}
	}
}

Mat Colorer::color()
{
	Mat blurredImage;
	for (int i = 0; i < iterations; i++) {
		//printf("i: %i\n", i);
		//GaussianBlur(this->image, blurredImage, Size(blurSize, blurSize), 2.0);
		medianBlur(this->image, blurredImage, blurSize);
		blurredImage.copyTo(this->image);
		calculateRowSegments();
		calculateColSegments();
		////this->threshold += 5;
		//imshow("window", this->image);
		//waitKey(1);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				this->image.at<Point3_<uchar>>(i, j) = colSegments[i][j].getColor();
			}
		}
	}
	//GaussianBlur(this->image, blurredImage, Size(blurSize, blurSize), 2.0);
	medianBlur(this->image, blurredImage, blurSize);
	blurredImage.copyTo(this->image);
	//calculateRowSegments();
	//for (int i = 0; i < rows; i++) {
	//	for (int j = 0; j < cols; j++) {
	//		this->image.at<Point3_<uchar>>(i, j) = rowSegments[i][j].getColor();
	//	}
	//}
	//imshow("row segments", this->image);
	//waitKey(0);
	//calculateColSegments();
	//for (int i = 0; i < rows; i++) {
	//	for (int j = 0; j < cols; j++) {
	//		this->image.at<Point3_<uchar>>(i, j) = colSegments[i][j].getColor();
	//	}
	//}
	return this->image;
}
