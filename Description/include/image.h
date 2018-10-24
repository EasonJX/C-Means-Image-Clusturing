#pragma once
#ifndef image_H
#define image_H
#include "opencv/cv.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace cv;
using namespace std;
typedef pair<double, double> P_Point;

enum type_image { MPEGWHITE, MPEGBLACK, LEAVES, KIMIA };
struct car
	{
		double db1;
		double db2;
		double db3;
		double db4;
		vector<double> vec_db1;
		vector<double> vec_db2;
		vector<double> vec_db3;
		vector<double> vec_db4;
		vector<double> vec_db5;
		vector<double> vec_db6;
		vector<double> vec_db7;
		vector<double> vec_db8;
	} ;
class image
{
public:
	
	Mat img;
	

	image(const char* path, type_image type);

	void affiche_centroid(Mat image);
	image(const char * path);

	~image();

	void afficheImage(Mat image);
	
	Point point_min_centroid_contour();

	double min_Dist_centroid_contour();

	void affiche_min_max(Mat drawing);

	Point point_min_centroid();

	double perimetre(vector<Point> &tmp);

	Point point_max_centroid();

	vector<double> DefectsPerimetre(Mat &img, vector<vector<Point>>&contour);
	
	double sumAngles(Mat &img, vector<vector<Point>>&contours);

	int PolyPointNbr(Mat &img, vector<vector<Point>>&contours);

	double Max(double &a, double &b);

	double Min(double &a, double &b);

	double calculateAngle(Point &a, Point &b);

	vector<double> DefectsArea(Mat &img, vector<vector<Point>>&contour);

	vector<Point> polarDefects(Mat &img, vector<vector<Point>>&contour);

	vector<vector<P_Point>> image::transformToPolarCoordinates(vector<vector<Point>> &contours, Size imgsize);

	double calculateAngle(Point2d &a, Point2d &b);

	vector<vector<cv::Point>>   vec_FindCt();
	
	void   v_Affichage(vector<vector<Point>> cnt);
	
	vector<vector<Point>>   v_hull();
	
	vector<vector<Point>>   v_hull_all();
	
	double   d_Surface_contour();
	
	double   d_Surface_hull();
	
	void   affiche_hull_contour(Mat image);
	
	double   d_Surface_convcave();
	
	double   surface_norm_contour();
	
	double   d_Perimetre_silhouette();
	
	Moments   m_Moment();
	
	double   max_Dist_centroid_hull();
	
	double   min_Dist_centroid_hull();
	
	Point2f   p2f_Centroid_hull();
	
	void   resize_image(double i);
	
	double   similaire(image tmp);
	
	double   similaire(Mat tmp);
	
	vector<vector<int>>   i_hull();
	

	void   v_Affiche_pt_convexe(Mat image);
	
	Mat   convex_deffect();
	
	vector<vector<Point>>   vec_FindCt_externe();
	
	double   rappor_min_max();
	
	
	//double   concaveI_surface_enveloppe();
	
	vector<vector<Point>>   approximation();
	

	vector<vector<Point>>   concaveHull();
	
	vector<double>   surface_concave_norme();
	
	vector<double>   perimetre_concave_norm();
	
	vector<double>   perimetre_concave();
	
	vector<double>   perim_dist_convexe_concave();
	
	vector<double>   dist_centre_convexe_normalisé();
	
	double   dist_poly();
	
	vector<vector<Point>>   convexe_points();
	
	vector<vector<Point>>   concave_points();
	
	void   v_Affiche_pt_cncave(Mat image);
	
	void   v_Affiche_convexe(Mat image);
	
	Point   min_dst(vector<Point> tmp, Point2f cnt);
	
	vector<vector<Point>>   vec_FindCt_externe_0();
	
	void readallfiles(string path, type_image type);
	
	Mat  image::convex_deffect1(Mat image);
	
	void affiche_pt_hull(Mat image);
	
	double somme_distance_centroid_contour(vector<vector<cv::Point>> contour);
	
	vector<double> dist_centre_courbure_normalisé();
	
	vector<double> dist_centre_concave_normalisé();

	car descripteur_image();


	vector<vector<Point>> image::concaveHull1(Mat img);
};
#endif

