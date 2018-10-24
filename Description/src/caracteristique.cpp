#include "image.h"
#include "opencv/cv.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace cv;
using namespace std;


// retourne le rapport entre le min et le max de la dictence du cenroid vers le contour 
double image::rappor_min_max() {
	return (this->min_Dist_centroid_contour() / this->max_Dist_centroid_hull());
}

// retourne la surface  du hull moin la silouhette normalisé par la surface du hull 
double image::d_Surface_convcave() {
	return ((this->d_Surface_hull() - this->d_Surface_contour()) / this->d_Surface_hull());
}


// retourn le perimetre des parties concave 
vector<double>  image::perimetre_concave() {
	vector<double> vecteur(this->concaveHull().size());
	vector<vector<Point>> concave = this->concaveHull();
	double perimetre_concave;
	for (rsize_t i = 0; i < concave.size(); i++)
	{
		if ((concave[i].size() > 0) && (arcLength(concave[i], true)>0)) {
			vecteur[i] = arcLength(concave[i], true);
		}
		else continue;
	}
	return vecteur;
}



//retourne un vecteur qui contient la surface de chaque partie concave normalisé par la surface du hull
vector<double> image::surface_concave_norme() {
	vector<double> vecteur(this->concaveHull().size());
	vector<vector<Point>> concave = this->concaveHull();
	double surface_hull = this->d_Surface_hull();
	double areaConcave;

	for (rsize_t i = 0; i <concave.size(); i++)
	{
		if (concave[i].size() != 0) {
			areaConcave = contourArea(concave[i]);
			if (areaConcave != 0) vecteur[i] = (areaConcave / surface_hull);
			else continue;
		}
		else continue;
	}
	return vecteur;
}

//retourne le perimetre de la partie concave(i) normalisé par le perimetre de la silhouette  
vector<double> image::perimetre_concave_norm() {
	vector<double> vecteur;
	vector<vector<Point>> concave = this->concaveHull();
	double primetreSilou = this->d_Perimetre_silhouette();
	double perimetre_concave;
	for (rsize_t i = 0; i < concave.size(); i++)
	{
		if (concave[i].size() != 0) {
			perimetre_concave = arcLength(concave[i], true);
			if (perimetre_concave != 0) vecteur.push_back(perimetre_concave / primetreSilou);
			else continue;
		}
		else continue;
	}
	return vecteur;
}

//contour entre deux points convexe normalisé par le contour  entre ces deux points 
vector<double> image::perim_dist_convexe_concave() {
	vector<vector<Point>> concHull = this->concaveHull();
	vector<double> perim = this->perimetre_concave();
	vector<double> res;
	double dst(0), tmp(0);
	Point p0, p1;
	int z(0);
	for (rsize_t i = 0; i < concHull.size(); i++)
	{
		if (concHull[i].size() > 1)
		{
			p0 = concHull[i][0];
			do
			{
				p1 = concHull[i][z];
				z++;
			} while (z < concHull[i].size());
			dst = norm(p0 - p1);
			tmp = perim[i] - dst;
			res.push_back(dst / tmp);
			dst = 0;
			tmp = 0;
			z = 0;
		}
	}
	/*for (rsize_t j = 0; j < res.size(); j++)
	cout << "sdkljfdksjf" << res[j] << endl;*/
	return res;
}

// retourne un vecteur des distence entre le centoid et les points convexe normalisé par la somme des distence
vector<double> image::dist_centre_convexe_normalisé() {
	vector<vector<cv::Point>> contour = this->v_hull();
	Point2f dist;
	vector<double> distence;
	double sum = somme_distance_centroid_contour(contour);
	Point2f centroid = this->p2f_Centroid_hull();
	for (rsize_t i = 0; i < contour[0].size(); i++) {

		distence.push_back(norm(centroid - (Point2f)contour[0][i]) / sum);
	}

	return distence;
}

// retourne un vecteur de distence entre le centroid et les points de courbures normalisé par la somme des distences 
vector<double> image::dist_centre_courbure_normalisé() {
	vector<vector<cv::Point>> appro = this->approximation();
	Point2f centr = this->p2f_Centroid_hull();
	vector<double> distence;
	double sum = somme_distance_centroid_contour(appro);
	for (rsize_t i = 0; i < appro[0].size(); i++) {

		distence.push_back(norm(centr - (Point2f)appro[0][i]) / sum);
	}
	return distence;
}


// retourn la distence entre le centroid et les point concave normalisé par la distence 
// entre le centroid et les points concaves 

vector<double> image::dist_centre_concave_normalisé() {
	vector<vector<cv::Point>> conc = this->concave_points();
	Point2f centr = this->p2f_Centroid_hull();
	vector<double> distence;
	double sum = somme_distance_centroid_contour(conc);
	for (rsize_t i = 0; i < conc[0].size(); i++) {

		distence.push_back(norm(centr - (Point2f)conc[0][i]) / sum);
	}
	return distence;
}

// 
vector<Point> image::polarDefects(Mat &img, vector<vector<Point>>&contour) {
	vector<vector<int>> hull;
	vector<vector<Vec4i>> conchull;
	hull.resize(contour.size());
	conchull.resize(contour.size());
	for (int i = 0; i < contour.size(); i++) {
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
			float depth = v[3] / 80;
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

// retourne la surface  des triangle normalisé par la  somme des triangles 

vector<double> image::DefectsArea(Mat &img, vector<vector<Point>>&contour) {
	vector<vector<int>> hull;
	vector<vector<Vec4i>> conchull;
	hull.resize(contour.size());
	conchull.resize(contour.size());
	for (int i = 0; i < contour.size(); i++) {
		convexHull(contour[i], hull[i], true);
		convexityDefects(contour[i], hull[i], conchull[i]);
	}
	vector < vector<Point>> points;
	for (rsize_t i = 0; i < contour.size(); ++i)
	{
		for (const Vec4i& v : conchull[i])
		{
			float depth = v[3] / 80;
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
	}
	return defectsArea;
}

// retourne le primetre  des triangle normalisé par la  somme des triangles 

vector<double> image::DefectsPerimetre(Mat &img, vector<vector<Point>>&contour) {
	vector<vector<int>> hull;
	vector<vector<Vec4i>> conchull;
	hull.resize(contour.size());
	conchull.resize(contour.size());
	for (int i = 0; i < contour.size(); i++) {
		convexHull(contour[i], hull[i], true);
		convexityDefects(contour[i], hull[i], conchull[i]);
	}
	vector < vector<Point>> points;
	for (rsize_t i = 0; i < contour.size(); ++i)
	{
		for (const Vec4i& v : conchull[i])
		{
			float depth = v[3] / 80;
			if (depth >10) //  filter defects by depth, e.g more than 10
			{
				int startidx = v[0]; Point ptStart(contour[i][startidx]);
				int endidx = v[1]; Point ptEnd(contour[i][endidx]);
				int faridx = v[2]; Point ptFar(contour[i][faridx]);
				points.push_back({ ptStart,ptEnd,ptFar });
			}
		}
	}
	vector<double> defectsPerimetre;
	double contoursPerimeter = 0;
	for (size_t i = 0; i < contour.size(); i++)
		contoursPerimeter += perimetre(contour[i]);
	for (size_t i = 0; i < points.size(); i++)
	{
		defectsPerimetre.push_back(contourArea(points[i]) / contoursPerimeter);
	}
	return defectsPerimetre;
}


// la sommes des angles du polygone approximatifs de la forme
double image::sumAngles(Mat &img, vector<vector<Point>>&contours) {
	vector<vector<Point>> poly;
	poly.resize(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
		approxPolyDP(contours[i], poly[i], 5, true);

	double sumret = 0;
	double a, b, c;
	for (size_t i = 0; i < poly.size(); i++) {
		for (size_t j = 0; j < poly[i].size(); j++) {
			a = norm(poly[i][j] - poly[i][(j - 1) % poly[i].size()]);
			b = norm(poly[i][j] - poly[i][(j + 1) % poly[i].size()]);
			c = norm(poly[i][(j + 1) % poly[i].size()] - (poly[i][(j - 1) % poly[i].size()]));
			if (a * b != 0)
				sumret += acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b));
		}

	}
	return sumret;
}

// retourne le nombre de sommet polygonale de la forme 
int image::PolyPointNbr(Mat &img, vector<vector<Point>>&contours) {
	vector<vector<Point>> poly;
	poly.resize(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
		approxPolyDP(contours[i], poly[i], 5, true);
	int ret = 0;
	for (size_t i = 0; i < poly.size(); i++)
		ret += poly[i].size();
	return ret;
}
