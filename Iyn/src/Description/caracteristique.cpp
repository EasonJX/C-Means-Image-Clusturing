#include "image.h"

// retourne le rapport entre le min et le max de la dictence du cenroid vers le contour 
double image::rappor_min_max() {
	vector<vector<Point>> contour = this->vec_contoursexterne0;
	Point2f centroid = this->p2f_Centroid_hull();
	Point min , max;
	vector<double> dists;
	for (size_t i = 0; i < contour[0].size(); ++i) {
		dists.push_back(norm(centroid - (Point2f)contour[0][i]));
	}
	this->pt_max_centroid = contour[0][max_element(dists.begin(), dists.end()) - dists.begin()];
	this->pt_min_centroid = contour[0][min_element(dists.begin(), dists.end()) - dists.begin()];
	return *min_element(dists.begin(), dists.end()) / *max_element(dists.begin(), dists.end());
	//return (this->min_Dist_centroid_contour() / this->max_Dist_centroid_hull());
}

// retourne la surface  du hull moin la silouhette normalisé par la surface du hull 
double image::d_Surface_convcave() {
	vector<vector<Point>> concave = this->vec_concavehullvec;
	double s(0);
	for (rsize_t i = 0; i < concave.size(); i++)
	{
		s = s + contourArea(concave[i]);
	}
	return (s / this->d_Surface_hull());
}


// retourn le perimetre des parties concave 
vector<double>  image::perimetre_concave() {
	vector<double> vecteur(this->vec_concavehullvec.size());
	vector<vector<Point>> concave = this->vec_concavehullvec;
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
	vector<double> vecteur(this->vec_concavehullvec.size());
	vector<vector<Point>> concave = this->vec_concavehullvec;
	double surface_hull = this->d_Surface_hull();
	double areaConcave;
	//surfaceconcave
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
	vector<vector<Point>> concave = this->vec_concavehullvec;
	double primetreSilou = 0;
	double perimetre_concave;
	for (rsize_t i = 0; i < concave.size(); i++) {
		perimetre_concave = arcLength(concave[i], true);
		primetreSilou += perimetre_concave;
	}
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
double image::d_Perim_concave() {
	vector<double> vecteur;
	vector<vector<Point>> concave = this->vec_concavehullvec;
	double primetreSilou = 0;
	double perimetre_concave = 0;
	for (rsize_t i = 0; i < concave.size(); i++)
	{
			perimetre_concave += arcLength(concave[i], true);
	}
	return perimetre_concave / this->d_Perimetre_silhouette();
}

//contour entre deux points convexe normalisé par le contour  entre ces deux points 
vector<double> image::perim_dist_convexe_concave() {
	vector<vector<Point>> concHull = this->vec_concavehullvec;
	vector<double> perim = this->perimetre_concave();
	vector<double> res;
	double dst(0), tmp(0);
	Point p0, p1;
	size_t z(0);
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
			//tmp = 1;
			if(dst != 0)
				res.push_back(dst/this->d_Perimetre_silhouette());
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
	vector<vector<cv::Point>> contour = this->vec_hull;
	Point2f dist;
	vector<double> distence;
	double sum = somme_distance_centroid_contour(contour);
	Point2f centroid = this->pt_p2f_Centroid_hull;
	double max = this->max_Dist_centroid_hull();

	for (rsize_t i = 0; i < contour[0].size(); i++) {
		double normd = norm(centroid - (Point2f)contour[0][i]);
		if(normd != 0)
			distence.push_back(normd / max);
	}

	return distence;
}

// retourne un vecteur de distence entre le centroid et les points de courbures normalisé par la somme des distences 
vector<double> image::dist_centre_courbure_normalisé() {
	vector<vector<cv::Point>> appro = this->vec_approximation;
	Point2f centr = this->pt_p2f_Centroid_hull;
	vector<double> distence;
	double sum = somme_distance_centroid_contour(appro);
	double  max = this->max_Dist_centroid_hull();
	for (rsize_t i = 0; i < appro[0].size(); i++) {
		double normd = norm(centr - (Point2f)appro[0][i]);
		if(normd != 0)
			distence.push_back(normd /max);
	}
	return distence;
}


// retourn la distence entre le centroid et les point concave normalisé par la distence 
// entre le centroid et les points concaves 

vector<double> image::dist_centre_concave_normalisé() {
	vector<vector<cv::Point>> conc = this->vec_concavepoints;
	Point2f centr = this->pt_p2f_Centroid_hull;
	vector<double> distence;
	double sum = somme_distance_centroid_contour(conc);
	double max = this->max_Dist_centroid_hull();
	for (rsize_t i = 0; i < conc[0].size(); i++) {
		double normd = norm(centr - (Point2f)conc[0][i]);
		if(normd != 0)
		distence.push_back(normd/ max);
	}
	return distence;
}

// 
vector<Point> image::polarDefects(Mat &img, vector<vector<Point>>&contour) {
	vector<vector<int>> hull;
	vector<vector<Vec4i>> conchull;
	vector<vector<Point>> concavePoints = this->vec_concavehullvec;
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
			float depth = v[3] / 80;
			if (depth >10) //  filter defects by depth, e.g more than 10
			{
				int startidx = v[0]; Point ptStart(contour[i][startidx]);
				int endidx = v[1]; Point ptEnd(contour[i][endidx]);
				int faridx = v[2]; Point ptFar(contour[i][faridx]);
				points.push_back({ ptStart,ptEnd,ptFar });
				bool found = false;
				for (size_t ip = 0; ip < concavePoints.size(); ++ip) {
					for (size_t jp = 0; jp < concavePoints[ip].size(); ++jp) {
						if (ptFar == concavePoints[ip][jp]) {
							found = true;
							break;
						}
					}
					if (found)break;

				}
				if (found) {
					line(draw, ptStart, ptEnd, Scalar(255), 1);
					line(draw, ptStart, ptFar, Scalar(255), 1);
					line(draw, ptEnd, ptFar, Scalar(255), 1);
					circle(draw, ptFar, 2, Scalar(255, 0, 255), 1);
				}
			}
		}
	}
	vector<vector<P_Point>> polarPoints = transformToPolarCoordinates(points, img.size());
	imshow("ksdfjkldjs", draw);
	cvWaitKey(0);
	return contour[0];
}

// retourne la surface  des triangle normalisé par la  somme des triangles 

vector<double> image::DefectsArea( ) {
	vector<vector<Point>> contour = this->vec_hull;
	vector < vector<Point>> points = this->convexdeffect;
	vector<double> defectsArea;
	double contoursArea = contourArea(contour[0]);
	for (size_t i = 0; i < points.size(); i++)
	{
		defectsArea.push_back(contourArea(points[i]) / contoursArea);
	}
	return defectsArea;
}


vector<double> image::DefectsDistance() {
	vector < vector<Point>> points = this->convexdeffect;
	Point2f centr = this->pt_p2f_Centroid_hull;
	vector<double> defectsdist;
	double max = this->max_Dist_centroid_hull();
	for (size_t i = 0; i < points.size(); i++)
	{
		for (size_t j = 0; j < points[i].size(); j+=3) {
			double normd = norm(centr - (Point2f)points[i][j]);
			//if (normd != 0)
			defectsdist.push_back(normd /max);
			normd = norm(centr - (Point2f)points[i][j + 2]);
			defectsdist.push_back(normd / max);
			normd = norm(centr - (Point2f)points[i][j+1]);
			defectsdist.push_back(normd /max);
		}

	}
	return defectsdist;
}

double image::surface_hull_defects() {
	vector<vector<Point>> contour = this->vec_contoursexterne;
	vector < vector<Point>> points = this->convexdeffect;
	double contoursArea = 0;
	for (size_t i = 0; i < points.size(); i++)
		contoursArea += contourArea(points[i]);
	double defectsarea = 0;
	for (size_t i = 0; i < points.size(); i++)
	{
		defectsarea += contourArea(points[i]);
	}
	return defectsarea / contoursArea;
}


// retourne le primetre  des triangle normalisé par la  somme des triangles 

vector<double> image::DefectsPerimetre() {
	vector<vector<Point>> hull = this->vec_hull;
	vector<vector<Point>> contour = this->vec_contoursexterne;
	vector < vector<Point>> points = this->convexdeffect;
	vector<double> defectsPerimetre;
	double contoursPerimeter = arcLength(hull[0],true) + arcLength(contour[0],true);
	
	for (size_t i = 0; i < points.size(); i++)
	{
		defectsPerimetre.push_back(arcLength(points[i],true) / contoursPerimeter);
	}
	return defectsPerimetre;
}


vector<double> image::ext_Angles() {
	vector<vector<Point>> poly = this->vec_approximation;
	vector<double> sumret;
	double a, b, c;
	for (size_t i = 0; i < poly.size(); i++) {
		for (size_t j = 0; j < poly[i].size(); j++) {
			a = norm(poly[i][j] - poly[i][(j - 1) % poly[i].size()]);
			b = norm(poly[i][j] - poly[i][(j + 1) % poly[i].size()]);
			c = norm(poly[i][(j + 1) % poly[i].size()] - (poly[i][(j - 1) % poly[i].size()]));
			if (a * b != 0)
				sumret.push_back(acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b)) / M_PI);
		}

	}
	return sumret;
}
vector<double> image::def_Angles() {
	vector < vector<Point>> points = this->convexdeffect;
	vector<double> sumangles;
	double a, b, c;
	for (size_t i = 0; i < points.size(); i++)
	{
		a = norm(points[i][0] - points[i][2]);
		b = norm(points[i][1] - points[i][2]);
		c = norm(points[i][0] - points[i][1]);
		if (a * b != 0)
			sumangles .push_back(acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b)) / M_PI);
	}
	return sumangles;
}

vector<double> image::def_Ext_Angles() {
	vector < vector<Point>> points = this->convexdeffect;
	vector<double> sumangles;
	double a, b, c;
	for (size_t i = 0; i < points.size(); i++)
	{
		//Left
		a = norm(points[i][2] - points[i][0]);
		b = norm(points[i][1] - points[i][0]);
		c = norm(points[i][2] - points[i][1]);
		if (a * b != 0)
			sumangles.push_back(acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b)) / M_PI);
		//Right
		a = norm(points[i][2] - points[i][1]);
		b = norm(points[i][0] - points[i][1]);
		c = norm(points[i][2] - points[i][0]);
		if (a * b != 0)
			sumangles.push_back(acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b)) / M_PI);
	}
	return sumangles;
}

// la sommes des angles du polygone approximatifs de la forme
double image::sumAngles() {
	vector<vector<Point>> poly = this->vec_approximation;
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
int image::PolyPointNbr() {
	vector<vector<Point>> poly = this->vec_approximation;
	int ret = 0;
	for (size_t i = 0; i < poly.size(); i++)
		ret += poly[i].size();
	return ret;
}

double image::internalAngleSumDefects() {
	vector < vector<Point>> points = this->convexdeffect;
	double sumangles = 0;
	double a, b, c;
	for (size_t i = 0; i < points.size(); i++)
	{
		a = norm(points[i][0] - points[i][2]);
		b = norm(points[i][1] - points[i][2]);
		c = norm(points[i][0] - points[i][1]);
		if (a * b != 0)
			sumangles += acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b));
	}
	return sumangles;
}

vector<double> image::ratio_concave_defects() {
	vector<double> ret;
	for (size_t i = 0; i < this->convexdeffect.size(); ++i) {
		ret.push_back(contourArea(this->convexdeffect[i]) / contourArea(vec_concavehullvec[i]));
	}
	return ret;
}

vector<double> image::dist_centre_hull() {
	vector<vector<cv::Point>> hull = this->vec_hull;
	Point2f centr = this->pt_p2f_Centroid_hull;
	vector<double> distence;
	double max = this->max_Dist_centroid_hull();
	for (rsize_t i = 0; i < hull[0].size(); i++) {
		double normd = norm(centr - (Point2f)hull[0][i]);
		if (normd != 0)
			distence.push_back(normd / max);
	}
	return distence;
}

vector<double> image::dist_def_Centroid() {
	vector<vector<Point>> contour = this->vec_contoursexterne;
	vector < vector<Point>> points = this->convexdeffect;
	Point2f centr = this->pt_p2f_Centroid_hull,defect_center;
	vector<double> defectsdist;
	double max = this->max_Dist_centroid_hull();
	for (size_t i = 0; i < points.size(); i++)
	{
		Moments momnt = moments(points[i]);
		defect_center = Point2f(float(momnt.m10 / momnt.m00), float(momnt.m01 / momnt.m00));
			double normd = norm(centr - defect_center);
			if (normd != 0)
				defectsdist.push_back(normd/max);

	}
	/*double max = *max_element(defectsdist.begin(), defectsdist.end());
	for (size_t i = 0; i < defectsdist.size(); ++i)
		defectsdist[i] /= max;*/
	return defectsdist;
}

double image::min_max_angle() {
	vector<vector<Point>> contour = this->vec_contoursexterne0;
	Point2f centroid = this->p2f_Centroid_hull();
	Point min , max;
	vector<double> dists;
	for (size_t i = 0; i < contour[0].size(); ++i) {
		dists.push_back(norm(centroid - (Point2f)contour[0][i]));
	}
	min = contour[0][min_element(dists.begin(), dists.end()) - dists.begin()];
	max = contour[0][max_element(dists.begin(), dists.end()) - dists.begin()];
	double angle = 0;
	double a, b, c;
		a = norm((Point2f)min - centroid);
		b = norm((Point2f)max - centroid);
		c = norm((Point2f)min - (Point2f)max);
		if (a * b != 0)
			angle = acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b))/ M_PI;
	return angle;
}

vector<double> image::ext_hull_Angles() {
	vector<vector<Point>> poly = this->vec_hull;
	vector<double> sumret;
	double a, b, c;
	for (size_t i = 0; i < poly.size(); i++) {
		for (size_t j = 0; j < poly[i].size(); j++) {
			a = norm(poly[i][j] - poly[i][(j - 1) % poly[i].size()]);
			b = norm(poly[i][j] - poly[i][(j + 1) % poly[i].size()]);
			c = norm(poly[i][(j + 1) % poly[i].size()] - (poly[i][(j - 1) % poly[i].size()]));
			if (a * b != 0)
				sumret.push_back(acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b)) / M_PI);
		}

	}
	return sumret;
}

vector<double> image::def_angle_centroid() {
	vector < vector<Point>> points = this->convexdeffect;
	Point2f centroid = this->p2f_Centroid_hull();
	vector<double> angles;
	double a, b, c;
	for (size_t i = 0; i < points.size(); i++)
	{
		a = norm(Point2f(points[i][2]) - centroid);
		b = norm(Point2f(points[(i + 1) % points.size() ][2]) - centroid);
		c = norm(points[i][2] - points[(i + 1) % points.size()][2]);
		if (a * b != 0)
			angles.push_back(acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b)) / M_PI);
	}
	return angles;
}
double image::sommePerimeTriangle() {

	double s(0), perimetreHull;
	for (size_t i = 0; i < this->DefectsPerimetre().size(); i++) {
		s = s + this->DefectsPerimetre()[i];
	}
	perimetreHull = arcLength(this->vec_hull[0], true);

	return s / perimetreHull;
}
double image::surfaceSurHull() {
	return contourArea(this->vec_contoursexterne0[0], false) / contourArea(this->vec_hull[0], false);
}
