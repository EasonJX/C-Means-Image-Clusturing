#include "image.h"

// constructeur pour l'image 
// MPEGWHITE, MPEGBLACK, LEAVES, KIMIA 

image::image(const char * path) {

	this->img = cvLoadImage(path);

}

image::image(const char * path, type_image type)
{
	this->type = type;
	// importer image 
	this->img = cvLoadImage(path);
	if (this->img.empty()) {
		cout << "WARNING : l'eimage n'existe pas " << endl;
	}
	else {
		switch (type) {
			// mpeg7 a traiter 
		case (MPEGBLACK):
			cvtColor(this->img, this->img, CV_RGB2GRAY);
			//threshold(this->img, this->img, 2 * 255 / 3, 255, THRESH_BINARY_INV);
			medianBlur(this->img, this->img, 7);
			Laplacian(this->img, this->img, 8);
		
		break;

		// mpeg7 mpeg7
		case (MPEGWHITE):
			cvtColor(this->img, this->img, CV_RGB2GRAY);
			medianBlur(this->img, this->img, 7);
		break;

		// leaves feuilles vertes
		case (LEAVES):
			//this->resize_image(0.5);
			medianBlur(this->img, this->img, 9);
			cvtColor(this->img, this->img, CV_RGB2GRAY);
			threshold(this->img, this->img, 2 * 255 / 3, 255, THRESH_BINARY_INV);
			
			Laplacian(this->img, this->img, 8);
		break;
		
		// kimia 
		case (KIMIA):
			cvtColor(this->img, this->img, CV_RGB2GRAY);
			medianBlur(this->img, this->img, 7);
			Laplacian(this->img, this->img, 8);
		break;
		}
	}
	this->prevectors();
}
	
	

	// destructeur 
image::~image()
{
	img.release();
}

// retourne le contour avec une approximation 
vector<vector<Point>> image::approximation() {
	vector<vector<Point>> contours = this->vec_contoursexterne;
	vector<Point> tmp;
	vector<vector<Point>> res;
	
	int seuil;
	if (this->type == KIMIA)
		seuil = 5;
	else
		seuil = 7;
	for (size_t j = 0; j < contours.size(); j++) {

		double epsilon = 0.01*arcLength(contours[j], true)/2.5;
		for (size_t i = 0; i < contours[j].size(); i++) {
		
			approxPolyDP(contours[j], tmp, seuil, true );
		}
		res.push_back(tmp);
	}
	return res;
	
}
	

// retourne la somme des distennce entre le somet et les point de courbure avec approximation
double image::dist_poly() {
	double s(0); 
	vector<vector<Point>> approx = this->vec_approximation;
	for (rsize_t i = 0; i < approx.size(); i++)
	{
		s = s + norm(Point(this->pt_p2f_Centroid_hull) - approx[0][i]);
	}
	return s;
}

// retourne les point convexe 

vector<vector<Point>> image::convexe_points() {
	vector<vector<Point>> tmp = this->vec_approximation;
	vector<vector<Point>> tmp1 (tmp.size());
	Point2f a, b;
	
	for (rsize_t j = 0; j < tmp.size(); j++)
	{
		for (rsize_t i = 1; i < tmp[j].size(); i++)
		{
			a = tmp[j][(i-1) % tmp[j].size()]; b = tmp[j][(i + 1) % tmp[j].size()];
			if ((pointPolygonTest(tmp[j], Point2f((a+b)*0.5), false) > 0) && (!tmp[j].empty()))
			{
				tmp1[j].push_back(tmp[j][i]);			
			}
		}
	}
	return tmp1;
}

// retourne les points concaves 
vector<vector<Point>> image::concave_points() {
	vector<vector<Point>> tmp = this->vec_approximation;
	vector<vector<Point>> tmp1(tmp.size());
	Point2f a, b;
	
	for (rsize_t j = 0; j < tmp.size(); j++)
	{
		for (rsize_t i = 1; i < tmp[j].size(); i++)
		{
			a = tmp[j][(i-1) % tmp[j].size()]; b = tmp[j][(i + 1) % tmp[j].size()];

			if ((pointPolygonTest(tmp[j], Point2f((a + b)* 0.5), false) < 0) && (!tmp[j].empty()))
			{
				tmp1[j].push_back(tmp[j][i]);
			}
		}
	}

	return tmp1;
}

void image::prevectors() {
	
	this->vec_contoursexterne = this->vec_FindCt_externe();
	this->vec_contoursexterne0 = this->vec_FindCt_externe_0();
	this->vec_hull = this->v_hull();
	this->vec_ihull = this->i_hull();
	this->vec_approximation  = this->approximation();
	this->vec_concavehullvec = this->concaveHull();
	this->vec_concavepoints = this->concave_points();
	this->vec_convexpoints = this->convexe_points();
	this->pt_min_centroid_contour = this->point_min_centroid_contour();
	this->pt_max_centroid = this->point_max_centroid();
	this->pt_p2f_Centroid_hull = this->p2f_Centroid_hull();
	this->convexdeffect = this->convex_deffect();
}

double image::similaire(vector<vector<Point>> contours) {
	return matchShapes(this->vec_contoursexterne[0], contours[0], 1, 0.0);

}
