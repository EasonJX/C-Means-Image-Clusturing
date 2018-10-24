#include "opencv/cv.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
using namespace cv;
using namespace std;



int   main() {
	/*image im("..\\..\\Leaves\\Leaves\\1404.jpg",LEAVES);
	im.resize_image(0.5);
	image img("C:\\Users\\Narimane\\Documents\\Image processing\\Base d'image\\IMAGE-MPEG 7\\flatfish-5.bmp",MPEGWHITE);
	image img1("C:\\Users\\Narimane\\Documents\\Image processing\\Base d'image\\traiterMPEG7\\dog-1.bmp",MPEGBLACK);
	image img2("C:\\Users\\Narimane\\Documents\\Image processing\\Base d'image\\kimia-99\\animal-3.bmp",KIMIA);**/
	image img2("..\\Database\\IMAGE-MPEG 7 B\\cup-1.bmp", MPEGBLACK);
	img2.readallfiles("..\\Database\\kimia-99\\", KIMIA);

}

