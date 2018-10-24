	#include "image.h"

car image::descripteur_image()
{
	car caracteristique;
	vector<vector<Point>> ctexterne = this->vec_contoursexterne;
	//BEST BEST BEST
	caracteristique.push_back(vector<double>({ this->rappor_min_max() }));
	caracteristique.push_back(vector<double>({ this->min_max_angle() }));
	caracteristique.push_back(vector<double>({ this->d_Surface_convcave() }));
	caracteristique.push_back(vector<double>({ this->surfaceSurHull() }));
	caracteristique.push_back(vector<double>({ this->sommePerimeTriangle() }));
	caracteristique.push_back(this->def_Ext_Angles());
	//caracteristique.push_back(vector<double>({ (double) this->def_Ext_Angles().size() }));
	
	//caracteristique.push_back(this->ext_hull_Angles());
	//caracteristique.push_back(this->ext_Angles());
	//caracteristique.push_back(this->def_Angles());
	//caracteristique.push_back(vector<double>({ this->def_Angles().size() }));
	
	//caracteristique.push_back(this->def_angle_centroid());
	//OTHERS 
	//caracteristique.push_back(vector<double>({ this->sumAngles() }));
	//caracteristique.push_back(vector<double>({ this->internalAngleSumDefects() }));
	//caracteristique.push_back(vector<double>({ (double)this->def_Angles().size() }));
	//caracteristique.push_back(vector<double>({ this->surface_hull_defects() }));
	//caracteristique.push_back(this->perimetre_concave());
	caracteristique.push_back(this->surface_concave_norme());
	//caracteristique.push_back(this->perimetre_concave_norm());
	//caracteristique.push_back(this->perim_dist_convexe_concave());
	//caracteristique.push_back(this->dist_centre_hull());
	//caracteristique.push_back(this->ratio_concave_defects());
	//caracteristique.push_back(this->dist_centre_courbure_normalisé());
	//caracteristique.push_back(this->dist_centre_convexe_normalisé());
	//caracteristique.push_back(vector<double>({ this->dist_centre_convexe_normalisé().size() }));
	//caracteristique.push_back(this->dist_centre_concave_normalisé());
	//caracteristique.push_back(this->DefectsArea());
	//caracteristique.push_back(this->DefectsPerimetre());
	//caracteristique.push_back(vector<double>({ (double)this->DefectsPerimetre().size() }));
	//caracteristique.push_back(this->DefectsDistance());
	
	//caracteristique.push_back(this->dist_def_Centroid());
	
	
	//this->polarDefects(this->img, this->vec_FindCt_externe_0());
	/*cout << "rapport min Max :" << endl <<  caracteristique.db1 << endl;
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
	cout << endl;*/
	return caracteristique;
}