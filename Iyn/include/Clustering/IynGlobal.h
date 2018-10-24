#pragma once
/*Trying edge detection*/
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <algorithm>
#include <Windows.h>
#include "opencv2\highgui.hpp"
#include "opencv2\core.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\features2d.hpp"
#include "opencv2\nonfree\nonfree.hpp"
#include "opencv/cv.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <future>
using namespace cv;
using namespace std;

typedef pair<double, double> P_Point;
typedef vector<vector<double>> car;
enum type_image { MPEGWHITE, MPEGBLACK, LEAVES, KIMIA };


