#include "contoursLib.h"

imgGraph anglesToDistanceGraph(Point centroid, Mat &contourPoints) {
	Point current;
	int radius;
	imgGraph grph;
	Mat res = Mat::zeros(contourPoints.size(), CV_8UC3);
	double d1 = norm(centroid - Point(0, 0)),
		d2 = norm(centroid - Point(0, contourPoints.cols)),
		d3 = norm(centroid - Point(contourPoints.rows, contourPoints.cols)),
		d4 = norm(centroid - Point(contourPoints.rows, 0));
	int max_radius = (int)round(max({ d1,d2,d3,d4 }));
	for (int i = 0; i < 360; ++i) {
		for (radius = 0; radius < max_radius; ++radius) {
			current.x = (int)round(cos(i) * radius + centroid.x);
			current.y = (int)round(sin(i) * radius + centroid.y);
			if (current.x > contourPoints.cols || current.y > contourPoints.rows || current.x < 0 || current.y < 0)
				break;
			rectangle(res, Rect(current.x, current.y, 1, 1), Scalar(255, 0, 255));
			if (contourPoints.data[current.y * contourPoints.cols + current.x] != 0)
				grph.graph[i] = norm(centroid - current);

		}
		grph.graph[i] = norm(centroid - current);
	}
	imshow("kimia-99", res);
	cvWaitKey(0);
	return grph;
}

imgGraph contoursToDistanceGraph(Point centroid, vector<vector<Point>> contourPoints) {
	imgGraph resGrph;
	//InitGraph
	for (int i = 0; i < 360; ++i)
		resGrph.graph.push_back(0);
	size_t j;
	int angle;
	for (size_t i = 0; i < contourPoints.size();++i) {
		for (j = 0; j < contourPoints[i].size(); ++j) {
			angle = round(calculateAngle(centroid, contourPoints[i][j]));
			(angle == 360 ? angle = 0 : 0);
			
			//resGrph.graph[angle] = norm(centroid- contourPoints[i][j]) +  resGrph.graph[angle];
			resGrph.graph[angle] = max(norm(centroid - contourPoints[i][j]),resGrph.graph[angle]);
			//resGrph.graph[angle] = min(norm(centroid - contourPoints[i][j]), resGrph.graph[angle]);
		}
	}
	return resGrph;
}
imgGraph contoursToDistanceGraph(Point centroid, Mat &img){
	imgGraph resGrph;
	//InitGraph
	for (size_t i = 0; i < 360; ++i)
		resGrph.graph.push_back(0);
	int j;
	int angle;
	map<int,double> angl;
	for (int i = 0; i < img.rows;++i) {
		for (j = 0; j < img.cols; ++j) {
			if (img.data[i * img.cols + j] != 0) {
				angle = calculateAngle(centroid, Point(j,i));
				angl[angle] = max(norm(centroid - Point(j, i)), resGrph.graph[angle]);
				//cout << angle << " " << i << " " << j << endl;
				//resGrph.graph[angle] = norm(centroid- contourPoints[i][j]) +  resGrph.graph[angle];
				resGrph.graph[angle] = max(norm(centroid - Point(j,i)), resGrph.graph[angle]);
				//resGrph.graph[angle] = min(norm(centroid - contourPoints[i][j]), resGrph.graph[angle]);
			}
		}
	}
	cout << angl.size() << endl;
	return resGrph;
}

imgGraph sinusoidalGraph(vector<vector<P_Point>> &input) {
	imgGraph sinus,angles;
	//sinus.graph.resize(361);
	int angle;
	for (size_t i = 0; i < input.size(); ++i) {
		for (size_t j = 0; j < input[i].size(); ++j) {
			angle = input[i][j].first;
			//cout << input[i][j].first << " "  <<  M_PI << endl;
			sinus.graph.push_back(input[i][j].second);
			angles.graph.push_back(input[i][j].first + 180);
		}
	}
	/*Normalization*/
	
	double min_sinus = *min_element(sinus.graph.begin(), sinus.graph.end());
	for (size_t j = 0; j < sinus.graph.size(); ++j) {
		sinus.graph[j] = sinus.graph[j] - min_sinus;
	}
	double max_sinus = *max_element(sinus.graph.begin(), sinus.graph.end());
	for (size_t j = 0; j < sinus.graph.size(); ++j) {
		sinus.graph[j] = sinus.graph[j]/ max_sinus;
	}
	imgGraph normalized;
	normalized.graph.resize(100);
	for (size_t j = 0; j < 100; ++j) {
		normalized.graph[j] = sinus.graph[j * sinus.graph.size() / 100];
	}
	srand((unsigned int)time(NULL));
	String lol = "../cmp/sinusgraph" + to_string(rand() ) + ".png";
	renderGraph(&normalized, NULL, String(lol).c_str());
	cvWaitKey(0);
	lol += "gg.png" ;
	/*renderGraph(&angles, NULL, String(lol).c_str());
	cvWaitKey(0);*/
	return sinus;
}
imgGraph calculateInsideAngles(vector<vector<Point>>contours) {
	imgGraph test;
	double angle1,angle2;
	double a, b, c;
	for (size_t i = 0; i < contours.size(); ++i) {
		for (size_t j = 0; j < contours[i].size(); ++j) {
			a = norm(contours[i][j] - Point(contours[i][j].x + 100, contours[i][j].y));
			b = norm(contours[i][j] - contours[i][(j + 1) % contours[i].size()]);
			c = norm(contours[i][(j + 1) % contours[i].size()] - Point(contours[i][j].x + 100, contours[i][j].y));
			angle1 = M_PI - acos((pow(a,2)+pow(b,2)-pow(c,2)) / (2*a*b));
			angle1 *= 180 / M_PI;
			a = norm(contours[i][j] - Point(contours[i][j].x + 100, contours[i][j].y));
			b = norm(contours[i][j] - contours[i][(j - 1) % contours[i].size()]);
			c = norm(contours[i][(j - 1) % contours[i].size()] - Point(contours[i][j].x + 100, contours[i][j].y));
			angle2 = M_PI - acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b));
			angle2 *= 180 / M_PI;
			//cout << a << " "  << b << " " << c << endl;
			test.graph.push_back(log(angle1));
		}
	}
	renderGraph(&test, NULL, NULL);
	cvWaitKey(0);
	return test;
}

imgGraph createstupidGraph(vector<vector<Point>> pts) {
	imgGraph grph;
	for (size_t i = 0; i < pts.size(); ++i)
		for (size_t j = 0; j < pts[i].size(); ++j)
			grph.graph.push_back(pts[i][j].y);
	return grph;
}