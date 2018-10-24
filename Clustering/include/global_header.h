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

using namespace cv;
using namespace std;

//Graphe résultat des exctraction d'information sur une image
typedef struct _imggraph { vector<double> graph; } imgGraph;
//L'information angulaire d'un graph (variation , difference avec le prochain point, intervalle de difference)
typedef struct _angleInfo { char variation; double diff; int interval; } angleContourData;
//Point polaire
typedef pair<double, double> P_Point;
//Structure représentant un fichier caractéristique qui contient le descripteur de chaque image le nom de l'image et le chemin vers le dossier global
typedef struct _carFile { string dir; vector<string> name; vector<vector<double>> data; } carFile;