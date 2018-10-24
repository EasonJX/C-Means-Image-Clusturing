#pragma once
#ifndef traitement_image_H
#define traitement_image_H
#include "opencv/cv.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace cv;
using namespace std;
class taitement_image : Mat
{
public:
	taitement_image();
	~taitement_image();
	vector<Point> findCt(Mat img);
	void affichage(vector<vector<Point>> tmp, Mat src);
	void affichage(vector<Point> tmp, Mat src);
	vector<Point> convxHull(vector<Point> tmp);
	double surface(vector<Point> tmp);
	double perimetre(vector<Point> tmp);
	Moments moment(vector<Point> cnt);
	double dist_centroid_contour(Mat img);
	Point2f centroid(vector<Point> cnt);

};
#endif

