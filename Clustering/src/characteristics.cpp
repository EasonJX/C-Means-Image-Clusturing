#include "contoursLib.h"

vector<Point> polarDefects(Mat &img, vector<vector<Point>>&contour) {
	vector<vector<int>> hull;
	vector<vector<Vec4i>> conchull;
	hull.resize(contour.size());
	conchull.resize(contour.size());
	for (size_t i = 0; i < contour.size(); i++) {
		convexHull(contour[i], hull[i], true);
		convexityDefects(contour[i], hull[i], conchull[i]);
	}
	Mat draw = Mat::ones(img.size(), CV_8UC3);
	draw = Mat::ones(img.size(), CV_8UC3);
	namedWindow("ksdfjkldjs");
	vector < vector<Point>> points;
	for (rsize_t i = 0; i < contour.size(); ++i)
	{
		drawContours(draw, contour, i, Scalar(255, 255, 255));
		for (const Vec4i& v : conchull[i])
		{
			float depth = v[3] / 80.0;
			if (depth >10) //  filter defects by depth, e.g more than 10
			{
				int startidx = v[0]; Point ptStart(contour[i][startidx]);
				int endidx = v[1]; Point ptEnd(contour[i][endidx]);
				int faridx = v[2]; Point ptFar(contour[i][faridx]);
				points.push_back({ ptStart,ptEnd,ptFar });
				line(draw, ptStart, ptEnd, Scalar(255), 1);
				line(draw, ptStart, ptFar, Scalar(255), 1);
				line(draw, ptEnd, ptFar, Scalar(255), 1);
				circle(draw, ptFar, 2, Scalar(255, 0, 255), 1);
			}
		}
	}
	vector<vector<P_Point>> polarPoints = transformToPolarCoordinates(points, img.size());
	imshow("ksdfjkldjs", draw);
	cvWaitKey(0);
	return contour[0];
}

vector<double> DefectsArea(Mat &img,vector<vector<Point>>&contour) {
	vector<vector<int>> hull;
	vector<vector<Vec4i>> conchull;
	hull.resize(contour.size());
	conchull.resize(contour.size());
	for (size_t i = 0; i < contour.size(); i++) {
		convexHull(contour[i], hull[i], true);
		convexityDefects(contour[i], hull[i], conchull[i]);
	}
	vector < vector<Point>> points;
	for (rsize_t i = 0; i < contour.size(); ++i)
	{
		for (const Vec4i& v : conchull[i])
		{
			float depth = v[3] / 80.0;
			if (depth >10) //  filter defects by depth, e.g more than 10
			{
				int startidx = v[0]; Point ptStart(contour[i][startidx]);
				int endidx = v[1]; Point ptEnd(contour[i][endidx]);
				int faridx = v[2]; Point ptFar(contour[i][faridx]);
				points.push_back({ ptStart,ptEnd,ptFar });
			}
		}
	}
	vector<double> defectsArea;
	double contoursArea = 0;
	for (size_t i = 0; i < contour.size(); i++)
		contoursArea += contourArea(contour[i]);
	for (size_t i = 0; i < points.size(); i++)
	{
		defectsArea.push_back(contourArea(points[i]) / contoursArea);
		cout << defectsArea[i] <<endl;
	}
	cout << endl;
	return defectsArea;

}
/*Cette fonction plus nombre de sommet ca devrait faire l'affaire non ?*/
double sumAngles(Mat &img, vector<vector<Point>>&contours) {
	vector<vector<Point>> poly;
	poly.resize(contours.size());
	for(size_t i = 0; i < contours.size(); i++)
		approxPolyDP(contours[i], poly[i],5 ,true);
	
	double sumret = 0;
	double a, b, c;
	for (size_t i = 0; i < poly.size(); i++) {
		for (size_t j = 0; j < poly[i].size(); j++) {
			a = norm(poly[i][j] - poly[i][(j - 1) % poly[i].size()]);
			b = norm(poly[i][j] - poly[i][(j + 1) % poly[i].size()]);
			c = norm(poly[i][(j + 1) % poly[i].size()] - (poly[i][(j - 1) % poly[i].size()]));
			if(a * b != 0)
				sumret += acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b));
		}
			
	}
	return sumret;
}
int PolyPointNbr(Mat &img, vector<vector<Point>>&contours) {
	vector<vector<Point>> poly;
	poly.resize(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
		approxPolyDP(contours[i], poly[i], 5, true);
	int ret = 0;
	for (size_t i = 0; i < poly.size(); i++)
		ret += poly[i].size();
	return ret;
}