#pragma once
#include "IynGlobal.h"
#ifndef image_H
#define image_H

class image
{
public:
	//Attribus
	Mat img;
	type_image type;
	vector<vector<Point>> vec_findcontour;
	vector<vector<Point>> vec_hull;
	vector<vector<Point>> vec_hullall;
	vector<vector<int>> vec_ihull;
	vector<vector<Point>> vec_convexpoints;
	vector<vector<Point>> vec_concavepoints;
	vector<vector<Point>> vec_contoursexterne;
	vector<vector<Point>> vec_contoursexterne0;
	vector<vector<Point>> vec_approximation;
	vector<vector<Point>> vec_concavehullvec;
	vector<vector<Point>> convexdeffect;

	Point pt_min_centroid_contour;
	Point pt_min_centroid;
	Point pt_max_centroid;
	Point2f   pt_p2f_Centroid_hull;
	//Construct
	image(const char* path, type_image type);
	image(const char * path);
	~image();
	void prevectors();
	//Affichage
	void affiche_centroid(Mat image);
	void afficheImage(Mat image);
	void affiche_min_max(Mat drawing);
	void v_Affichage(vector<vector<Point>> cnt);
	void affiche_hull_contour(Mat image);
	void v_Affiche_pt_convexe(Mat image);
	void   v_Affiche_pt_cncave(Mat image);
	void   v_Affiche_convexe(Mat image);
	void affiche_pt_hull(Mat image);

	//Contours
	vector<vector<cv::Point>>   vec_FindCt();
	vector<vector<Point>>   v_hull();
	vector<vector<Point>>   v_hull_all();
	vector<vector<Point>> image::concaveHull1(Mat img);
	vector<vector<int>>   i_hull();
	vector<vector<Point>>   convexe_points();
	vector<vector<Point>>   concave_points();
	vector<vector<Point>>   vec_FindCt_externe_0();
	vector<vector<Point>>   vec_FindCt_externe();
	vector<vector<Point>>   approximation();
	vector<vector<Point>>   concaveHull();
	vector<vector<P_Point>> image::transformToPolarCoordinates(vector<vector<Point>> &contours, Size imgsize);
	vector<Point> polarDefects(Mat &img, vector<vector<Point>>&contour);
	Mat  image::convex_deffect1(Mat image);
	vector<vector<Point>>   convex_deffect();

	//Points
	Point point_min_centroid_contour();
	Point point_min_centroid();
	Point point_max_centroid();
	Point2f   p2f_Centroid_hull();
	Point   min_dst(vector<Point> tmp, Point2f cnt);

	//Scalar values
	double min_Dist_centroid_contour();
	double perimetre(vector<Point> &tmp);
	double   d_Surface_contour();
	double   d_Surface_hull();
	double   surface_norm_contour();
	double   d_Perimetre_silhouette();
	double   max_Dist_centroid_hull();
	double   min_Dist_centroid_hull();
	double   similaire(image tmp);
	double   similaire(Mat tmp);
	double image::similaire(vector<vector<Point>> contours);
	double somme_distance_centroid_contour(vector<vector<cv::Point>> contour);
	Moments   m_Moment();
	double   dist_poly();
	double surface_hull_defects();
	//double   concaveI_surface_enveloppe();

	//Util
	double Max(double &a, double &b);
	double Min(double &a, double &b);
	double calculateAngle(Point &a, Point &b);
	double calculateAngle(Point2d &a, Point2d &b);
	void   resize_image(double i);
	static vector<car> image::readallfiles(string path, type_image type, vector<string> &filenames,string export_filename);
	double image::sum_concavité(vector <vector <Point>> concHull);

	//Car
	vector<double> ratio_concave_defects();
	vector<double>   surface_concave_norme();
	vector<double>   perimetre_concave_norm();
	vector<double>   perimetre_concave();
	vector<double>   perim_dist_convexe_concave();
	vector<double>   dist_centre_convexe_normalisé();
	vector<double> dist_centre_courbure_normalisé();
	vector<double> dist_centre_concave_normalisé();
	vector<double> ext_Angles();
	vector<double> def_Angles();
	vector<double> def_Ext_Angles();
	vector<double> ext_hull_Angles();
	vector<double> dist_centre_hull();
	vector<double> dist_def_Centroid();
	double   rappor_min_max();
	double min_max_angle();
	double   d_Surface_convcave();
	double sumAngles();
	int PolyPointNbr();
	double internalAngleSumDefects();
	vector<double> DefectsPerimetre();
	vector<double> DefectsArea();
	vector<double> DefectsDistance();
	double d_Perim_concave();
	double sommePerimeTriangle();
	double surfaceSurHull();
	vector<double> def_angle_centroid();
	car descripteur_image();
};
#endif

