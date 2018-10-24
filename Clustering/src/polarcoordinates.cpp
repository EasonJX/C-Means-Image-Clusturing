#include "contoursLib.h"

vector<vector<P_Point>> transformToPolarCoordinates(vector<vector<Point>> &contours, Size imgsize) {
	vector<vector<P_Point>> contoursPolar(contours.size());
	double radius = norm(Point(0,0) - Point(imgsize.width,imgsize.height))/2;
	cout << radius << " " << imgsize.height / 2 << " " << imgsize.width / 2 << " " << endl;
	Point2d origin(imgsize.width / 2, imgsize.height / 2);
	int angle;	double distance;
	for (size_t i = 0; i < contours.size(); ++i) {
		for (size_t j = 0; j < contours[i].size(); ++j) {
			angle = calculateAngle(origin, Point2d(contours[i][j].x, contours[i][j].y));
			distance = norm(origin - Point2d(contours[i][j].x, contours[i][j].y))/radius;
			//cout << origin << " " << Point2d(contours[i][j].x, contours[i][j].y) << " " << norm(origin - Point2d(contours[i][j].x, contours[i][j].y)) << " " << radius << endl;
			contoursPolar[i].push_back(P_Point(angle, distance));
		}
	}
	Mat imgs = Mat::ones(imgsize, CV_8UC1)*255;
	for (size_t i = 0; i < contoursPolar.size(); ++i) {
		for (size_t j = 0; j < contoursPolar[i].size(); ++j) {
			circle(imgs, Point(cos(contoursPolar[i][j].first * M_PI / 180)*contoursPolar[i][j].second*radius +origin.x, sin(contoursPolar[i][j].first* M_PI / 180)*contoursPolar[i][j].second*radius+ origin.y), 1,
				Scalar(rand() * 1000 % 255, rand() * 1000 % 255 , rand() * 1000 % 255));
		}
	}
	imshow("kimia-99", imgs);
	cvWaitKey(0);
	return contoursPolar;
}

/*I need something like to normalize between graphs by adding to the one that has less points extra points even if they are 
on a line */