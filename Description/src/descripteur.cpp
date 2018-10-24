#include "image.h"
#include "opencv/cv.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
using namespace cv;
using namespace std;

car image::descripteur_image()
{
	car caracteristique;
	caracteristique.db1 = this->rappor_min_max();
	caracteristique.db2 = this->d_Surface_convcave();
	caracteristique.db3 = this->sumAngles(this->img, this->vec_FindCt_externe());
	caracteristique.db4 = this->PolyPointNbr(this->img, this->vec_FindCt_externe());
	caracteristique.vec_db1 = this->perimetre_concave();
	caracteristique.vec_db2 = this->surface_concave_norme();
	caracteristique.vec_db3 = this->perimetre_concave_norm();
	caracteristique.vec_db4 = this->perim_dist_convexe_concave();
	caracteristique.vec_db5 = this->dist_centre_convexe_normalisé();
	caracteristique.vec_db6 = this->dist_centre_courbure_normalisé();
	caracteristique.vec_db7 = this->dist_centre_concave_normalisé();
	caracteristique.vec_db8 = this->DefectsArea(this->img, this->vec_FindCt_externe());

	cout << "rapport min Max :" << endl <<  caracteristique.db1 << endl;
	cout << "surface concave normalisé : " << endl << caracteristique.db2 << endl;
	cout << "La somme des angles :" << endl << caracteristique.db3 << endl;
	cout << "Le nombre de sommet du polygone  :" << endl << caracteristique.db4 << endl;
	cout << " le perimetre des parties concave" << endl;
	for (int i = 0; i < caracteristique.vec_db1.size(); i++)
	{
		cout << caracteristique.vec_db1[i] ;
		cout << "|";
	}
	cout << endl;

	cout << " la surface des parties concave normalisé " << endl;
	for (int i = 0; i < caracteristique.vec_db2.size(); i++)
	{
		cout  << caracteristique.vec_db2[i]  ;
		cout << "|";
	}
	cout << endl;

	cout << " le perimetre des parties concave normalisé " << endl;

	for (int i = 0; i < caracteristique.vec_db3.size(); i++)
	{	
		cout << caracteristique.vec_db3[i]  ;
		cout << "|";
	}
	cout << endl;

	cout << "partie du hull normalisé par la partie concave" << endl;

	for (int i = 0; i < caracteristique.vec_db4.size(); i++)
	{
		cout  << caracteristique.vec_db4[i] ;
		cout << "|";
	}
	cout << endl;

	cout << "distence du centre vers les points convexe normalisé par la somme des distences " << endl;


	for (int i = 0; i < caracteristique.vec_db5.size(); i++)
	{
		cout << caracteristique.vec_db5[i];
		cout << "|";
	}
	cout << endl;
	cout << "distence du centre vers les points de courbure normalisé par la somme des distences " << endl;

	for (int i = 0; i < caracteristique.vec_db6.size(); i++)
	{
		cout << caracteristique.vec_db6[i] ;
		cout << "|";
	}
	cout << endl;

	cout << "distence du centre vers les points convexe normalisé par la somme des distences " << endl;

	for (int i = 0; i < caracteristique.vec_db7.size(); i++)
	{
		cout << caracteristique.vec_db7[i] ;
		cout << "|";
	}
	cout << endl;
	cout << "distence du centre vers les points convexe normalisé par la somme des distences " << endl;

	for (int i = 0; i < caracteristique.vec_db7.size(); i++)
	{
		cout << caracteristique.vec_db7[i] ;
		cout << "|" ;
	}
	cout << endl;

	cout << "surfaces normalisé des triangles de contours defect " << endl;

	for (int i = 0; i < caracteristique.vec_db8.size(); i++)
	{
		cout << caracteristique.vec_db8[i] ;
		cout << "|";
	}
	cout << endl;
	return caracteristique;
}