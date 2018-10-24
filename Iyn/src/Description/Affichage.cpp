#include "image.h"

// caract 1 : distence min max depuis le centroid 
void image::affiche_min_max(Mat image) {
	Mat drawing = image.clone();
	circle(drawing, this->pt_max_centroid, 2, Scalar(255, 255, 255),2);
	circle(drawing, this->pt_min_centroid, 2, Scalar(255, 255, 255),2);
	line(drawing, this->pt_p2f_Centroid_hull, this->pt_max_centroid, Scalar(255, 255, 255),2);
	line(drawing, this->pt_p2f_Centroid_hull, this->pt_min_centroid_contour, Scalar(255, 255, 255),2);
	namedWindow("lsd");
	imshow("lsd", drawing);
	cvWaitKey(0);
	//imwrite ("minMax.png",drawing);
}
void image::affiche_centroid(Mat image) {
	Mat drawing = image.clone();
	circle(drawing, this->pt_p2f_Centroid_hull, 2, Scalar(255, 255, 255), 2);
	namedWindow("lsd");
	imshow("lsd", drawing);
	cvWaitKey(0);
	imwrite("centroid.png", drawing);
}
// afficher l'image de l'objet
void image::afficheImage(Mat image) {
	namedWindow("Source", WINDOW_AUTOSIZE);
	imshow("Source", image);
	waitKey(0);
}

// affiche l'image apartir de son contour 
void image::v_Affichage(vector<vector<Point>> cnt) {
	RNG rng(12345);
	
	vector<Vec4i> heir;
	Mat drawing = Mat::zeros(this->img.size(), CV_8UC3);
	
	for (size_t i = 0; i<cnt.size(); i++)
	{
		drawContours(drawing, cnt, CV_RETR_EXTERNAL, Scalar(255, 255, 255), 1, 8, heir, 0, Point());
		
	}
	namedWindow("lsd");
	imshow("lsd", drawing);
	cvWaitKey(0);
	imwrite("contour.png", drawing);

}



// affiche les point convexe et concave de la forme dans l'image
void image::v_Affiche_pt_convexe(Mat image) {
	vector<vector<Point>> cnt = this->vec_contoursexterne;
	vector<vector<Point>> cnt1 = this->convexe_points();
	RNG rng(12345);
	vector<Vec4i> heir;
	Mat drawing =  image.clone();
	
	for (size_t j = 0; j < cnt1.size(); j++)
	{
		for (size_t i = 0; i < cnt1[j].size(); i++)
		{
			line(drawing, this->pt_p2f_Centroid_hull,cnt1[j][i] , Scalar(255, 255, 255), 2);
			circle(drawing, cnt1[j][i], 1, Scalar(255, 255, 255),2);
		}
	}
	namedWindow("lsd");
	imshow("lsd", drawing);
	cvWaitKey(0);
	imwrite("PointConvexe.png", drawing);
}

// affiche le contour avec l'enveloppe englobante  
void image::affiche_hull_contour(Mat image) {
	vector<vector<Point>> cnt = this->vec_contoursexterne;
	vector<vector<Point>> hul = this->vec_hull;
	RNG rng(12345);
	vector<Vec4i> heir;
	Mat drawing = image.clone();
	for (size_t i = 0; i<cnt.size(); i++)
	{
		drawContours(drawing, hul, i, Scalar(255,255,255), 2, 8, heir, 0, Point());
	}
	namedWindow("lsd");
	imshow("lsd", drawing);
	cvWaitKey(0);
	imwrite("Hull.png", drawing);
}

void image::affiche_pt_hull(Mat image) {
	vector<vector<Point>> cnt = this->vec_contoursexterne;
	vector<vector<Point>> hul = this->vec_hull;
	RNG rng(12345);
	vector<Vec4i> heir;
	Mat drawing = image.clone();
	
	for (size_t j = 0; j < hul.size(); j++)
	{

		for (size_t i = 0; i < hul[j].size(); i++)
		{
			line(drawing, this->pt_p2f_Centroid_hull, hul[j][i], Scalar(255, 255, 255), 2);

			circle(drawing, hul[j][i], 1, Scalar(255, 255, 255),2);
		}
	}
	namedWindow("lsd");
	imshow("lsd", drawing);
	cvWaitKey(0);
	imwrite("PointHull.png", drawing);

}


void image::v_Affiche_pt_cncave(Mat image) {
	vector<vector<Point>> cnt = this->vec_contoursexterne;
	vector<vector<Point>> cnt1 = this->vec_concavepoints;
	RNG rng(12345);
	vector<Vec4i> heir;
	Mat drawing = image.clone();

	for (size_t j = 0; j < cnt1.size(); j++)
	{
		for (size_t i = 0; i < cnt1[j].size(); i++)
		{

			line(drawing, this->pt_p2f_Centroid_hull, cnt1[j][i], Scalar(255, 255, 255), 2);

			circle(drawing, cnt1[j][i], 1, Scalar(255, 255, 255),2);
		}
	}
	namedWindow("lsd");
	imshow("lsd", drawing);
	cvWaitKey(0);
	imwrite("concave.png", drawing);
}
void image::v_Affiche_convexe(Mat image) {
	vector<vector<Point>> cnt = this->vec_contoursexterne;
	vector<vector<Point>> cnt1 = this->vec_approximation;
	RNG rng(12345);
	vector<Vec4i> heir;
	Mat drawing = image.clone();


	for (size_t j = 0; j < cnt1.size(); j++)
	{
		for (size_t i = 0; i < cnt1[j].size(); i++)
		{

			line(drawing, this->pt_p2f_Centroid_hull, cnt1[j][i], Scalar(255, 255, 255), 2);

			circle(drawing, cnt1[j][i], 1, Scalar(255, 255, 255),2);
		}
	}
	namedWindow("lsd");
	imshow("lsd", drawing);
	cvWaitKey(0);
	imwrite("courbure.png", drawing);

}

vector<vector<Point>> image::concaveHull1(Mat img) {
	vector<vector<Point>> hull, contour;
	vector<vector<Point>> conchull;
	contour = this->vec_contoursexterne;
	hull.resize(contour.size());
	for (size_t i = 0; i < contour.size(); i++)
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
			if (norm(p1 - p2) < 50) continue;
			//Fin de l'ajout
			tmp.clear();
			for (size_t z = 0; z < contour[i].size(); z++)

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


	draw = img.clone();
	for (size_t i = 0; i < conchull.size(); i++) {
		drawContours(draw, conchull, i, Scalar(rand() * 1000 % 255, rand() * 1000 % 255, rand() * 1000 % 255),2);
	}
	namedWindow("lsd");
	imshow("lsd", draw);
	cvWaitKey(0);
	imwrite("PartieConcave.png", draw);
	return conchull;
}


Mat  image::convex_deffect1(Mat image) {
	vector<vector<Point>> contour = this->vec_contoursexterne;
	vector<vector<int>> hull = this->vec_ihull;
	RNG rng(12345);
	vector<Vec4i> heir;
	Mat drawing = image.clone();
	Mat img = this->img.clone();

	// vecteur pour contenir les convex deffect 
	vector<vector<Vec4i>> defect(contour.size());

	for (rsize_t i = 0; i < contour.size(); i++)
	{

		convexityDefects(contour[i], hull[i], defect[i]);

	}

	for (rsize_t i = 0; i < contour.size(); ++i)
	{
		for (const Vec4i& v : defect[i])
		{
			float depth = v[3] / 80;
			if (depth > 10) //  filter defects by depth, e.g more than 10
			{
				int startidx = v[0]; Point ptStart(contour[i][startidx]);
				int endidx = v[1]; Point ptEnd(contour[i][endidx]);
				int faridx = v[2]; Point ptFar(contour[i][faridx]);

				line(drawing, ptStart, ptEnd, Scalar(255), 2);
				line(drawing, ptStart, ptFar, Scalar(255), 2);
				line(drawing, ptEnd, ptFar, Scalar(255), 2);
				circle(drawing, ptFar, 2, Scalar(255), 2);
			}
		}
	}
	namedWindow("lsd");
	imshow("lsd", drawing);
	cvWaitKey(0);
	imwrite("triangle.png", drawing);
	return img;
}
