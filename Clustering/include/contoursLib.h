#pragma once
#include "global_header.h"

/*PREPROCESSING*/
/*Retour d'une image qu'on aura transformer en niveau de gris et sur laquelle on aura appliquer un filtre median puis laplacien*/
Mat contourExtraction(Mat &, int);
//Retourne le contour externe seulement de l'image
Mat externalCountExtraction(Mat &);
Mat externalCountExtraction(Mat &, vector<vector<Point>> &);
/*Retour du point de gravité de l'objet contour qu'on aura acquise*/
Point centroid(Mat &);
Point centroid(vector<vector<Point>> &);
Point centerROI(vector<vector<Point>> &);
void fourierTransform(Mat&, Mat&, Mat&);
vector<vector<Point>> concaveHull(Mat &);
void extractROI(Mat &img);


/*GRAPH CREATION*/
/*Transforme les angles en graphe d'angles d'apres le plus loins point du centre de gravité*/
imgGraph anglesToDistanceGraph(Point, Mat &);
/*Transforme les contours en graphe d'angles d'apres le plus loins point du centre de gravité*/
imgGraph contoursToDistanceGraph(Point, vector<vector<Point>> );
//
imgGraph contoursToDistanceGraph(Point,Mat &);
//Create a graph that has sinusoidal data
imgGraph sinusoidalGraph(vector<vector<P_Point>> &);
//UNDONE Rename this graph and check what it does 
imgGraph createstupidGraph(vector<vector<Point>>);

//Extraction d'un graph d'angles internes
imgGraph calculateInsideAngles(vector<vector<Point>>);

/*UTILITY*/
//Calcule l'angle entre deux points en degrée pas en radian
double calculateAngle(Point2d &a, Point2d &b);
double calculateAngle(Point &a, Point &b);
//Calcule le bax entre deux double
double max(double &a, double &b);
double min(double &a, double &b);
//Importation du fichier caractéristiques
carFile importCar(string path);
//Importation du fichier centres
vector<int> centers(string path, carFile data);
//Lecture de tous les fichiers d'un dossier
void readallfiles(string path);
//Retourne tout les fichiers d'un dossier
vector<String> readallfilesRet(string path);

/*GRAPH PROCESSING*/
//retourne le point x d'un graphe qui est = a 0
int zeroValues(imgGraph &);
//Lisse un graphe en faisant la moyenne des deux sommets les n'étant pas = 0 et le sommet qui se rouve au centre de ces deux
void smoothGraph(imgGraph &);
//Normaliser le graph
imgGraph normalizeGraph(const imgGraph);
//Utilisé pour calculer la direction d'un graphe elle retourne 0 si les deux chiffres sont egaux sinon -1 si i < j ou 1 si i > j
char calculateDirection(double i, double j);
//Calcule un graphe dérivée de ce graphe qui cherche les points de changement du graphe précédent
vector<Point2d> derivateGraph(imgGraph &);
//Rendu du graphe dans une fenetre
void renderGraph(const imgGraph* = NULL, const vector<Point2d>* = NULL, const char* = NULL);
void renderGraph(vector<vector<double>> data, vector<vector<double>> U);
//Extrait du vecteur dérivée du graphe angulaire les changements de sens
vector<angleContourData> exctractVariation(const vector<Point2d> &);
//Threshold vector
void thresholdVariation(vector<Point2d> &, double);
//Write variation data
void exportVariation(vector<angleContourData> &derivVation, string name, Mat &img);

/*CHARACTERISTICS*/
//Extraction des points concaves
vector<vector<Point>> concavePoints(Mat &,vector<vector<Point>>&);
//Exctraction du contours defects en utilisant les coordonées polaires
vector<Point> polarDefects(Mat &, vector<vector<Point>>&);
//Extraction de la surface defect
vector<double> DefectsArea(Mat &, vector<vector<Point>>&);
//La somme des angles de l'approximtion polygonal de la forme 
double sumAngles(Mat &, vector<vector<Point>>&);
//Le nombre de point résultant de l'approximation polygonal de la forme
int PolyPointNbr(Mat &, vector<vector<Point>>&);

/*GRAPH MATCHING*/
//Comapre Two Graphs
double graphMatch( imgGraph &,  imgGraph &);



/*NEW IDEA POLAR COORDINATES*/
//Transformation d'une forme de coordonées cartésiènne en coordonées polaire
vector<vector<P_Point>> transformToPolarCoordinates(vector<vector<Point>> &contours, Size imgsize);

/*CLUSTERING CMEANS*/
/*Entery : Data to cluster , Centers ,
  OutPut : Vector of vector of points where each vector is a cluster*/
vector<vector<double>> cmeans(vector<vector<double>>& data,vector<int>& centers,float eps,int m);
vector<vector<double>> altcmeans(vector<vector<double>>& data, vector<int>& centers, float eps, int m);
//Calcule la distance cartésienne entre deux matrices
double norm(vector<double>& , vector<double>&);
double norm(vector<vector<double>>&, vector<vector<double>>&);


double altnorm(vector<double>&, vector<double>&);

