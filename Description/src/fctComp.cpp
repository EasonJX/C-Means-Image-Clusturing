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


// retourne la surface des partie concave une par une concave(i) 
vector<vector<Point>> image::concaveHull() {
	vector<vector<Point>> hull, contour;
	vector<vector<Point>> conchull;
	contour = this->vec_FindCt_externe();
	hull.resize(contour.size());
	for (int i = 0; i < contour.size(); i++)
		convexHull(contour[i], hull[i], true);
	conchull.resize(hull.size());
	// recuperer les point convexe dans un autre vecteur 
	Rect rect;
	Point p1, p2, pul, pbr;
	vector<Point> tmp;
	Mat draw = Mat::zeros(img.size(), CV_8UC3);

	for (size_t i = 0; i < hull.size(); i++)
	{
		for (size_t j = 0; j < hull[i].size(); j++)
		{
			p1 = hull[i][j%hull[i].size()];
			p2 = hull[i][(j + 1) % hull[i].size()];

			//Fin de l'ajout
			tmp.clear();
			for (int z = 0; z < contour[i].size(); z++)

			{

				if (p1 == contour[i][z])
				{
					do {
						tmp.push_back(contour[i][z]);
						z++;
						(z > contour[i].size() - 1 ? z = 0 : 0);
					} while (contour[i][z] != p2);
					break;
				}
			}

			if (tmp.size() > 0)
			{
				conchull.push_back(vector<Point>(tmp));
			}
		}
	}


	draw = Mat::zeros(img.size(), CV_8UC3);
	for (int i = 0; i < conchull.size(); i++) {
		drawContours(draw, conchull, i, Scalar(rand() * 1000 % 255, rand() * 1000 % 255, rand() * 1000 % 255));
	}
	
	namedWindow("point convexe", WINDOW_AUTOSIZE);
	imshow("point convexe", draw);
	waitKey(0);
	return conchull;
}

// retourne une convexité plus exacte 
Mat  image::convex_deffect() {
	vector<vector<Point>> contour = this->vec_FindCt_externe();
	vector<vector<int>> hull = this->i_hull();
	RNG rng(12345);
	vector<Vec4i> heir;
	Mat drawing = Mat::zeros(this->img.size(), CV_8UC3);
	Mat img = this->img.clone();

	// vecteur pour contenir les convex deffect 
	vector<vector<Vec4i>> defect(contour.size());

	for (rsize_t i = 0; i < contour.size(); i++)
	{

		convexityDefects(contour[i], hull[i], defect[i]);

	}

	for (size_t i = 0; i<contour.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contour, i, color, 1, 8, heir, 0, Point());
	}

	for (rsize_t i = 0; i < contour.size(); ++i)
	{
		for (const Vec4i& v : defect[i])
		{
			float depth = v[3] / 80;
			if (depth >10) //  filter defects by depth, e.g more than 10
			{
				int startidx = v[0]; Point ptStart(contour[i][startidx]);
				int endidx = v[1]; Point ptEnd(contour[i][endidx]);
				int faridx = v[2]; Point ptFar(contour[i][faridx]);

				line(drawing, ptStart, ptEnd, Scalar(255), 1);
				line(drawing, ptStart, ptFar, Scalar(255), 1);
				line(drawing, ptEnd, ptFar, Scalar(255), 1);
				circle(drawing, ptFar, 2, Scalar(255), 1);
			}
		}
	}
	namedWindow("point convexe", WINDOW_AUTOSIZE);
	imshow("point convexe", drawing);
	waitKey(0);
	return drawing;
}

// retourne un vecteur d'entier qui contient tout les points concave et convexe 
vector<vector<int>> image::i_hull() {
	vector<vector<Point>> cnt = this->vec_FindCt_externe();
	vector<vector<int>> hull(cnt.size());
	for (rsize_t i = 0; i < cnt.size(); i++)
	{
		convexHull(cnt[i], hull[i], false);
	}

	return hull;
}



// pareil que lautre sauf que lobjet en entré est une matrice 
double image::similaire(Mat tmp) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(tmp, contours, hierarchy, cv::RETR_TREE, CV_RETR_EXTERNAL, cv::Point(0, 0));
	return matchShapes(this->vec_FindCt_externe(), contours[0], 1, 0.0);

}
// verifie si deux image son tsimilaire ie : identique meme si la dimention change elle a comme argument un objet de type image
double  image::similaire(image tmp) {
	return matchShapes(this->vec_FindCt_externe()[0], tmp.vec_FindCt_externe()[0], 1, 0.0);
}
// retourne le contour de l'image
vector<vector<Point>> image::vec_FindCt() {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Mat tmp = (Mat)(this->img).clone();
	findContours(tmp, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	return contours;
}

// retourne le contour externe de la forme
vector<vector<Point>> image::vec_FindCt_externe() {
	vector<vector<Point>> contours,vec;
	vector<Vec4i> hierarchy;
	vector<Point> tmp1;
	Mat tmp = (this->img).clone();
	findContours(tmp, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	size_t j;
	rsize_t size_contour = contours.size();
	bool f = false ;
	if (size_contour == 1)
	{
		return contours;
	}
	else
	{
		int max = contours[0].size();
		for (size_t i = 1; i < contours.size(); i++) 
		{

			if (max < contours[i].size())
			{
				max = contours[i].size();
				f = true;
				j = i;
			}
		}
		if (f == false) {

			tmp1 = contours[0];
			vec.push_back(tmp1);
		}
		else {
			tmp1 = contours[j];
			vec.push_back(tmp1);
		}
		return vec;
	}
}
vector<vector<Point>> image::vec_FindCt_externe_0() {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	vector<Point> tmp1;
	Mat tmp = (this->img).clone();
	findContours(tmp, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	return contours;
}

// retourne un vecteur qui contien tout les point convexe et concave
vector<vector<Point>> image::v_hull() {
	vector<vector<Point>> cnt = this->vec_FindCt_externe();
	vector<vector<Point>> hull(cnt.size());
	for (rsize_t i = 0; i < cnt.size(); i++)
	{
		convexHull(cnt[i], hull[i], false);
	}
	return hull;
}

// retourne un vecteur d'entier qui contient tout les points concave et convexe 
vector<vector<Point>> image::v_hull_all() {
	vector<vector<Point>> cnt = this->vec_FindCt();
	vector<vector<Point>> hull(cnt.size());
	
	for (rsize_t j = 0; j < cnt.size(); j++)
	{
		for (rsize_t i = 0; i < cnt[j].size(); i++)
		{	
			convexHull(cnt[i], hull[i], false);
		}
	}
	return hull;
}

void image::readallfiles(string path, type_image type) {
	WIN32_FIND_DATAA dir;
	string pathtmp = path + "*";
	HANDLE h = FindFirstFileA(pathtmp.c_str(), &dir);
	string nom_du_fichier;
	int c(0);
	
	if (h != INVALID_HANDLE_VALUE) {
		do {
			nom_du_fichier = path + String(dir.cFileName);
			if (dir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && strcmp(dir.cFileName, ".") != 0 && strcmp(dir.cFileName, "..") != 0) {
				readallfiles(path + String(dir.cFileName) + "\\",type);
				continue;
			}
			else if (strcmp(dir.cFileName, ".") == 0 || strcmp(dir.cFileName, "..") == 0) {
				continue;
			}
			/*Traitement Debut*/
			const char* tmp = nom_du_fichier.c_str();

		image im(tmp,type);
		cout << nom_du_fichier.c_str() << endl;
		im.descripteur_image();
		//cout << im.d_Surface_convcave() << endl;
		/*Traitement Fin*/
		} while (FindNextFileA(h, &dir) != 0);
	}
	else
		cout << "Erreur " << endl;

}


vector<vector<P_Point>> image::transformToPolarCoordinates(vector<vector<Point>> &contours, Size imgsize) {
	vector<vector<P_Point>> contoursPolar(contours.size());
	double radius = norm(Point(0, 0) - Point(imgsize.width, imgsize.height)) / 2;
	cout << radius << " " << imgsize.height / 2 << " " << imgsize.width / 2 << " " << endl;
	Point2d origin(imgsize.width / 2, imgsize.height / 2);
	int angle;	double distance;
	for (size_t i = 0; i < contours.size(); ++i) {
		for (size_t j = 0; j < contours[i].size(); ++j) {
			angle = calculateAngle(origin, Point2d(contours[i][j].x, contours[i][j].y));
			distance = norm(origin - Point2d(contours[i][j].x, contours[i][j].y)) / radius;
			//cout << origin << " " << Point2d(contours[i][j].x, contours[i][j].y) << " " << norm(origin - Point2d(contours[i][j].x, contours[i][j].y)) << " " << radius << endl;
			contoursPolar[i].push_back(P_Point(angle, distance));
		}
	}
	Mat imgs = Mat::ones(imgsize, CV_8UC1) * 255;
	for (size_t i = 0; i < contoursPolar.size(); ++i) {
		for (size_t j = 0; j < contoursPolar[i].size(); ++j) {
			circle(imgs, Point(cos(contoursPolar[i][j].first * M_PI / 180)*contoursPolar[i][j].second*radius + origin.x, sin(contoursPolar[i][j].first* M_PI / 180)*contoursPolar[i][j].second*radius + origin.y), 1,
				Scalar(rand() * 1000 % 255, rand() * 1000 % 255, rand() * 1000 % 255));
		}
	}
	/*
	imshow("kimia-99", imgs);
	cvWaitKey(0);*/
	return contoursPolar;
}

double image::calculateAngle(Point2d &a, Point2d &b) {
	double angle = atan2((b.y - a.y), (b.x - a.x)) * 180 / M_PI;
	return angle;
}
double image::calculateAngle(Point &a, Point &b) {
	double angle = atan2((b.y - a.y), (b.x - a.x)) * 180 / M_PI;
	return (angle < 0 ? 360.0 + angle : angle);
}

double image::Max(double &a, double &b) {
	return (a > b ? a : b);
}

double image::Min(double &a, double &b) {
	return (a > b ? b : a);
}

void readallfiles(string path) {
	WIN32_FIND_DATAA dir;
	string pathtmp = path + "*";
	HANDLE h = FindFirstFileA(pathtmp.c_str(), &dir);
	string nom_du_fichier;
	int count = 0;
	if (h != INVALID_HANDLE_VALUE) {
		do {
			nom_du_fichier = path + String(dir.cFileName);
			if (dir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && strcmp(dir.cFileName, ".") != 0 && strcmp(dir.cFileName, "..") != 0) {
				readallfiles(path + String(dir.cFileName) + "\\");
				continue;
			}
			else if (strcmp(dir.cFileName, ".") == 0 || strcmp(dir.cFileName, "..") == 0) {
				continue;
			}
			/*Traitement Debut*/
			//cout << nom_du_fichier.c_str() << endl;
			/*Traitement Fin*/
		} while (FindNextFileA(h, &dir) != 0);
	}
	else
		cout << "Erreur " << endl;

}

vector<String> readallfilesRet(string path) {
	WIN32_FIND_DATAA dir;
	string pathtmp = path + "*";
	HANDLE h = FindFirstFileA(pathtmp.c_str(), &dir);
	string nom_du_fichier;
	int count = 0;
	vector<String> ret;
	if (h != INVALID_HANDLE_VALUE) {
		do {
			nom_du_fichier = path + String(dir.cFileName);
			if (dir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && strcmp(dir.cFileName, ".") != 0 && strcmp(dir.cFileName, "..") != 0) {
				readallfiles(path + String(dir.cFileName) + "\\");
				continue;
			}
			else if (strcmp(dir.cFileName, ".") == 0 || strcmp(dir.cFileName, "..") == 0) {
				continue;
			}
			/*Traitement Debut*/
			ret.push_back(nom_du_fichier);
			/*Traitement Fin*/
		} while (FindNextFileA(h, &dir) != 0);
	}
	else
		cout << "Erreur " << endl;
	return ret;
}
/*I need something like to normalize between graphs by adding to the one that has less points extra points even if they are
on a line */