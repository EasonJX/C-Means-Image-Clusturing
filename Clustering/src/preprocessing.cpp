#include "contoursLib.h"

void fourierTransform(Mat& srcimg, Mat& magnituderes, Mat& phaseres) {
	Mat imgborder;
	int m = getOptimalDFTSize(srcimg.rows), n = getOptimalDFTSize(srcimg.cols);
	copyMakeBorder(srcimg, imgborder, 0, m - srcimg.rows, 0, n - srcimg.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[]{ Mat_<float>(imgborder),Mat::zeros(imgborder.size(),CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);

	dft(complexI, complexI);

	split(complexI, planes);
	magnitude(planes[0], planes[1], magnituderes);
	magnituderes += Scalar::all(1);
	log(magnituderes, magnituderes);
	normalize(magnituderes, magnituderes, 0, 1, CV_MINMAX);

	phase(planes[0], planes[1], phaseres);
	phaseres += Scalar::all(1);
	log(phaseres, phaseres);
	normalize(phaseres, phaseres, 0, 1, CV_MINMAX);
}
Mat contourExtraction(Mat &img, int median_value) {
	Mat resImg;
	//resize(img, img, Size(img.cols * 2, img.rows * 2),0,0,INTER);
	cvtColor(img, resImg, COLOR_BGR2GRAY);
	threshold(resImg, resImg, 2*255/3, 255, THRESH_BINARY_INV);
	medianBlur(resImg, resImg, median_value);
	//Laplacian(resImg, resImg, 8);
	return resImg;
}

Mat externalCountExtraction(Mat &imgCount) {
	Mat externCount(imgCount.rows, imgCount.cols, CV_8UC1, Scalar(0));
	vector<vector<Point>> contours;
	findContours(imgCount, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < contours.size();++i) {
		drawContours(externCount, contours, i, Scalar(255));
	}
	return externCount;
}
Mat externalCountExtraction(Mat &imgCount, vector<vector<Point>> &contourPoints) {
	Mat externCount(imgCount.rows, imgCount.cols, CV_8UC1, Scalar(0));
	contourPoints.clear();
	findContours(imgCount, contourPoints, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < contourPoints.size();++i) {
		drawContours(externCount, contourPoints, i, Scalar(255));
	}
	return externCount;
}

Point centroid(Mat &contours) {
	//I'll do this what ever the number of hulls i'll have
	Moments moment = moments(contours);
	Point gp(moment.m10 / moment.m00, moment.m01 / moment.m00);
	return gp;
}

Point centroid(vector<vector<Point>> &contours) {
	//I'll do this what ever the number of hulls i'll have
		Moments moment = moments(contours[0]);
		Point gp(moment.m10 / moment.m00, moment.m01 / moment.m00), tmpgp;
		for (size_t i = 0; i < contours.size(); ++i) {
			moment = moments(contours[i]);
			tmpgp = Point(moment.m10 / moment.m00, moment.m01 / moment.m00);
			gp = Point((gp.x + tmpgp.x) / 2, (gp.y + tmpgp.y) / 2);

		}
		return gp;
}

Point centerROI(vector<vector<Point>> &input) {
	vector<int> x;
	vector<int> y;
	for (size_t i = 0; i < input.size(); ++i) {
		for (size_t j = 0; j < input[i].size(); ++j) {
			x.push_back(input[i][j].x);
			y.push_back(input[i][j].y);
		}
	}
	int x_e  = *min_element(x.begin(),x.end());
	int y_e = *min_element(y.begin(), y.end());
	int w_e = (*max_element(x.begin(), x.end())) ;
	int h_e = (*max_element(y.begin(), y.end())) ;
	return Point(x_e + w_e / 2, y_e + h_e / 2);
}

vector<vector<Point>> concaveHull(Mat &img) {
	vector<vector<Point>> hull, contour;
	vector<vector<Point>> conchull;
	findContours(img, contour, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	hull.resize(contour.size());
	for (size_t i = 0; i < contour.size(); i++) {
		convexHull(contour[i], hull[i], true);
	}
	//conchull.resize(hull.size());
	// recuperer les point convexe dans un autre vecteur 
	Rect rect;
	Point p1, p2, pul , pbr;
	vector<Point> tmp;
	
	for (size_t i = 0; i < hull.size(); ++i) {
		for (size_t j = 0; j < hull[i].size(); j++) {
			p1 = hull[i][j%hull[i].size()]; p2 = hull[i][(j + 1) % hull[i].size()];
			//Debut de l'ajout
			if (norm(p2 - p1) < 10)
				continue;
			//Fin de l'ajout
			tmp.clear();
			for (size_t z = 0; z < contour[i].size(); z++) {
				if (p1 == contour[i][z]) {
					do {
						tmp.push_back(contour[i][z]);
						z++;
						(z > contour[i].size() - 1 ? z = 0 : 0);
					} while (contour[i][z] != p2);
					break;
				}
			}
			  
			if (tmp.size() > 0) {
				conchull.push_back(tmp);
			}
		}
	}
	Mat draw = Mat::zeros(img.size(), CV_8UC3);
	draw = Mat::zeros(img.size(), CV_8UC3);
	namedWindow("ksdfjkldjs");
	for (size_t i = 0; i < conchull.size(); i++) {
		drawContours(draw, conchull, i, Scalar(rand()*1000%255, rand() * 1000 % 255, rand() * 1000 % 255));
	}
	imshow("ksdfjkldjs", draw);
	cvWaitKey(0);
	return conchull;
}


vector<vector<Point>> concavePoints(Mat &img, vector<vector<Point>>&) {
	namedWindow("something");
	Mat draw = Mat::zeros(img.size(), CV_8UC3);
	vector<vector<Point>> hull = concaveHull(img);
	vector<vector<Point>> concPoints(hull.size());
	double curH, prevH = 0;
	for (size_t i = 0; i < hull.size(); ++i) {
		prevH = 0;
		for (size_t j = 0; j < hull[i].size(); ++j) {
			vector<Point> tmp  = { hull[i][0],hull[i][hull.size() - 1],hull[i][j] };
			curH = 2*contourArea(tmp)/norm(hull[i][0] - hull[i][hull.size() - 1]);
			if (curH < prevH) {
				circle(draw, hull[i][j], 1, Scalar(255, 0, 255));
				imshow("something", draw);
				cvWaitKey(0);
				concPoints[i].push_back(hull[i][j]);
				do {
					curH = 2 * contourArea(tmp) / norm(hull[i][0] - hull[i][hull.size() - 1]);
					prevH = curH;
					j++;
				} while (curH < prevH &&  j < hull[i].size());
			}
			
		}
	}
	for (size_t i = 0; i < hull.size(); ++i) {
		for (size_t j = 0; j < hull[i].size(); ++j) {
		}
	}
	return concPoints;
}






void extractROI(Mat &img) {
	int x = -1, y = -1, h = -1, w = -1;
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			if (y == -1)
				if (img.data[i * img.cols + j] != 0)
					y = i - 1;
			if (h == -1)
				if (img.data[(img.rows - i - 1) * img.cols + j] != 0)
					h = (img.rows - i) ;
			if (h != -1 && y != -1)
				break;
		}
	}
	for (int i = 0; i < img.cols; ++i) {
		for (int j = 0; j < img.rows; ++j) {
			if (x == -1)
				if (img.data[j * img.cols + i] != 0)
					x = i - 1;
			if (w == -1)
				if (img.data[j * img.cols + (img.cols - i - 1)] != 0)
					w = (img.cols - i) ;
			if (w != -1 && x != -1)
				break;
		}
	}
	img = img(Rect(x , y ,  w - x  + 1, h - y  + 1));
}