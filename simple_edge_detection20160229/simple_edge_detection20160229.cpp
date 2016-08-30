// simple_edge_detection20160229.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
int edgeThresh = 50;
int lowThresHold, ratio = 3, kernalSize = 3;
int const maxLowThreshold = 100;

Mat grayImg;
Mat blurImg;
Mat cannyImg;
Mat sobelImgX;
Mat sobelImgY;
Mat sobelImg;
Mat laplacianImg;
Mat binaryCannyImg;
Mat binarySobelImg;
Mat binaryLaplacianImg;
Mat binary;

using namespace std;
//重建sobel與laplacian演算法

int main(int argc, char* argv[])
/**
  * @param1: filename
  * @param2: low threshold of canny
  * @param3: high threshold of canny
*/
{
	IplImage *pImg = cvLoadImage(argv[1]);
	//cout << argv[1];

	double threshold1 = atof(argv[2]);
	double threshold2 = atof(argv[3]);
	double thresholdBinary = atof(argv[4]);

	if (pImg)
	{
		cvSetImageROI(pImg, cvRect(200, 200, 600, 600));
		Mat srcImg = cvarrToMat(pImg);

		if (!srcImg.data)
		{
			std::cout << "Error: could not open or find the image" << std::endl;
			return -1;
		}

		cvtColor(srcImg, grayImg, CV_BGR2GRAY); //彩色轉灰階
		blur(grayImg, blurImg, Size(3, 3), Point(-1, -1)); //均值濾波

		//canny
		/*Canny(blurImg, cannyImg, threshold1, threshold2, kernalSize);
		threshold(cannyImg, binaryCannyImg, thresholdBinary, 225, THRESH_BINARY);*/

		//sobel
		Sobel(blurImg, sobelImgX, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
		convertScaleAbs(sobelImgX, sobelImgX);
		Sobel(blurImg, sobelImgY, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
		convertScaleAbs(sobelImgY, sobelImgY);
		addWeighted(sobelImgX, 0.5, sobelImgY, 0.5, 0, sobelImg);
		threshold(sobelImg, binarySobelImg, 127, 225, THRESH_OTSU | THRESH_BINARY);

		//laplacian
		/*Laplacian(blurImg, laplacianImg, CV_16S, 3, 1, 0, BORDER_DEFAULT);
		convertScaleAbs(laplacianImg, laplacianImg);
		threshold(laplacianImg, binaryLaplacianImg, 127, 225, THRESH_OTSU | THRESH_BINARY);*/

		cout << countNonZero(binarySobelImg) << endl;
		return 0;
	}

	cvWaitKey(0);
	cvReleaseImage(&pImg);
}

