#pragma once
#include "IynGlobal.h"
#include "image.h"
/*PREPROCESSING*/
void extractROI(Mat &img);

/*UTILITY*/
//Calcule l'angle entre deux points en degrée pas en radian
double calculateAngle(Point2d &a, Point2d &b);
double calculateAngle(Point &a, Point &b);
//Calcule le bax entre deux double
double max(double &a, double &b);
double min(double &a, double &b);
/*CLUSTERING CMEANS*/
/*Entery : Data to cluster , Centers ,
  OutPut : Vector of vector of points where each vector is a cluster*/
vector<vector<double>> cmeans(vector<car>& data, vector<int>& centers, float eps, int m,string centerexport);
vector<vector<double>> altcmeans(vector<car>& data, vector<int>& centers, float eps, int m);
//Calcule la distance cartésienne entre deux matrices
//La norme entre deux caractéristiques
double norm(car&, car&);
//La norme entre deux vecteurs
double norm(vector<double>&, vector<double>&);
//La norme entre deux matrices
double eucnorm(vector<vector<double>>&, vector<vector<double>>&);
//Soustraction de deux vecteurs de parties de formes 
double subVect(vector<double>&, vector<double>&);
//Trouver la meilleur correspondance des parties de forme tels que i représente la ligne [i] est la collone 
vector<Point> PartsMatch(vector<double>, vector<double>);
vector<Point> GlobalAlignmentMatch(vector<double>, vector<double>);
double GlobalAlignmentDistance(vector<double>, vector<double>);

//Sumvect tout simplement
double vec_sum(vector<double>);
//Distance de correspondance de parties de formes
double vecDistance(vector<double>, vector<double>);
//Performe une addition des parties de formes pour calculer les centres de classes
vector<double> addVect(vector<double>&, vector<double>&);
//Matched vectorial distance
double matchVecDist(vector<double>, vector<double>,vector<Point>);
//Match shapes Hu
double matchHuShapes(vector<double>, vector<double>);

double sum_i(vector<double>);

vector<vector<string>> clusterextract(string filename,string exportf,string originDir,string basename);
void exctractcarfiles(string, vector<string> &, vector<car> &);

void exctractcenters(vector<int>&,vector<string>,vector<string>);

void exportcmeansresult(vector<vector<double>>,vector<int>,vector<string>,string);

void exportresult(string,vector<string>,vector<vector<double>>,vector<int>);

vector<car> importcenters(string filename);
vector<vector<int>> importclusters(string filename,vector<string> filenames);