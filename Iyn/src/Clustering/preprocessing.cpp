#include "clusterLib.h"


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