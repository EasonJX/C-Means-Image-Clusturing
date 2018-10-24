#include "image.h"

// retourne la surface du	ntour 
double image::d_Surface_contour() {
	vector<vector<Point>> tmp = this->vec_contoursexterne;
	double area(0);
	for (int i = 0; i < tmp.size(); i++) {
		 area = area + contourArea(tmp[i]);
	}
	return area;
}

// retourne la surface du hull
double image::d_Surface_hull() {

	vector<vector<Point>> tmp = this->vec_hull;
	double area(0);
	for (int i = 0; i < tmp.size(); i++) {
		area = area += contourArea(tmp[i]);
	}
	return area;
}

// le perimetre de l'image 
double image::d_Perimetre_silhouette() {
	vector<vector<cv::Point>> tmp = this->vec_contoursexterne;
	double pr(0);
	for (int i = 0; i < tmp.size(); i++) {
		 pr = pr + arcLength(tmp[i], true);
	}
	return pr;
}

// retourne le moment de l'image 
Moments image::m_Moment() {
	return moments(this->vec_hull[0], false);
}

//retourne le centroid du le forme
Point2f image::p2f_Centroid_hull() {
	Moments momnt = this->m_Moment();
	return Point2f(float(momnt.m10 / momnt.m00),float( momnt.m01 / momnt.m00));
}


// retourne la surface du contour devisé par la plus longue distence entre le centroid et le ocntour 
double image::surface_norm_contour() {
	return (this->d_Surface_contour() / this->max_Dist_centroid_hull());
}

// redimentionne l'image
void image::resize_image(double i) {
	resize(this->img, this->img, Size(this->img.cols * i, this->img.rows * i));
}

// retourne la distence entre le centroid et le contour 
double image::max_Dist_centroid_hull() {
	vector<vector<cv::Point>> contour = this->vec_hull;
	Point2f dist;
	const rsize_t n = contour[0].size();
	double *resultat = new double[n];
	double  maxim(0);

	resultat[0] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][0]);
	maxim = resultat[0];
	for (rsize_t i = 0; i < contour[0].size(); i++) {
		resultat[i] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][i]);
		if (resultat[i] >= maxim) {
			maxim = resultat[i];
		}
	}
	return maxim;
}

// retourne le point de distance macximal entre le centroid et le hull 
Point image::point_max_centroid() {
	vector<vector<cv::Point>> contour = this->vec_hull;
	Point2f dist;
	
	const rsize_t n = contour[0].size();
	double *resultat = new double[n];
	double  maxim(0);
	int j(0);
	
	resultat[0] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][0]);
	maxim = resultat[0];
	for (rsize_t i = 0; i < contour[0].size(); i++) {
		resultat[i] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][i]);
		if (resultat[i] >= maxim) {
			maxim = resultat[i];
			j = i;
		}
	}
	return contour[0][j];
}

// retourne la distence eminimal ntre le controid et le hull 
double image::min_Dist_centroid_hull() {
	vector<vector<cv::Point>> contour = this->vec_hull;
	Point2f dist;
	const rsize_t n = contour[0].size();
	double *resultat = new double[n];
	double  minim(0);

	resultat[0] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][0]);
	minim = resultat[0];
	for (rsize_t i = 0; i < contour[0].size(); i++) {
		resultat[i] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][i]);
		if (resultat[i] <= minim) {
			minim = resultat[i];
		}
	}
	return minim;
}

// retourne la distence minimal entre le centroid et le contour 
double image::min_Dist_centroid_contour() {
	vector<vector<cv::Point>> contour = this->vec_contoursexterne;
	Point2f dist;
	const rsize_t n = contour[0].size();
	double *resultat = new double[n];
	double  minim(0);

	resultat[0] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][0]);
	minim = resultat[0];
	for (rsize_t i = 0; i < contour[0].size(); i++) {
		resultat[i] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][i]);
		if (resultat[i] <= minim) {
			minim = resultat[i];
		}
	}
	return minim;
}

// retourne le point de distence minimal entre le centroid et le contour 
Point image::point_min_centroid() {
	vector<vector<cv::Point>> contour = this->vec_hull;
	Point2f dist;

	const rsize_t n = contour[0].size();
	double *resultat = new double[n];
	double  minim(0);
	int j(0);

	resultat[0] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][0]);
	minim = resultat[0];
	for (rsize_t i = 0; i < contour[0].size(); i++) {
		resultat[i] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][i]);
		if (resultat[i] <= minim) {
			minim = resultat[i];
			j = i;
		}
	}	
	return contour[0][j];
}

// retourne le point min entre le centroid et le contour 

Point image::point_min_centroid_contour() {
	vector<vector<cv::Point>> contour = this->vec_contoursexterne;
	Point2f dist;
	const rsize_t n = contour[0].size();
	double *resultat = new double[n];
	double  minim(0);
	int j(0);
	resultat[0] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][0]);
	minim = resultat[0];
	for (rsize_t i = 0; i < contour[0].size(); i++) {
		resultat[i] = norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][i]);
		if (resultat[i] <= minim) {
			minim = resultat[i];
			j = i;
		}
	}
	return contour[0][j];
}

// calucle l a distence minimal entre un point et un vecteur de point 

Point image::min_dst( vector<Point> tmp ,Point2f cnt) {
	double  min = norm(Point2f( tmp[0])-cnt);
	Point pt = tmp[0];
	for (rsize_t i = 1; i < tmp.size(); i++)
	{
		if (min > norm( cnt-Point2f(tmp[i]) )) {
			min = norm(Point2f(tmp[i]) - cnt);
			pt = tmp[i];
		}
		else continue;
	}
	return pt;
}
double image::somme_distance_centroid_contour(vector<vector<cv::Point>> contour) {
	Point2f dist;
	double distence(0);
	for (rsize_t i = 0; i < contour[0].size(); i++) {
		
		distence = distence +norm(this->pt_p2f_Centroid_hull - (Point2f)contour[0][i]);
		
		}
	return distence;
}

double image::perimetre(vector<Point> &tmp) {
	return arcLength(tmp, true);
}