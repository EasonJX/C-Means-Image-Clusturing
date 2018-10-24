#include "contoursLib.h"

vector<vector<double>> cmeans(vector<vector<double>>& data, vector<int>& centers, float eps,int m) {
	srand(time(0));
	//Lines are objets and rows are clusters
	//Centers
	vector<vector<double>> C(centers.size());
	for (size_t i = 0; i < centers.size(); ++i)
		for (size_t j = 0; j < data[0].size(); ++j)
			C[i].push_back(data[centers[i]][j]);
	//Cluster matrix
	vector<vector<double>> U(data.size()),U1;
	double r,r1,tmp;
	int data_car = data[0].size();
	/*Randomly initialize U*/
	for (size_t i = 0; i < U.size(); ++i) {
		r1 = 0;
		for (size_t j = 0; j < centers.size(); ++j) {
			r = ((double)(rand() % (RAND_MAX / centers.size())) / RAND_MAX );
			tmp = ((double)RAND_MAX / centers.size() / RAND_MAX) - r;
			r +=  r1;
			r1 = tmp;
			U[i].push_back(r);
		}
		U[i][centers.size() - 1] += r1;
	}
	U1 = U;
	/*Do while*/
	int it = 0;
	double centroid_up, centroid_down,norm_x_c,norm_x_ck,m_calc = 2 / (m - 1); //M != 1 !!!!
	double cmp;//Norm between the matrix
	do {
		/*Calculate centers*/
		for (size_t j = 0; j < C.size(); ++j) {
			centroid_down = 0;
			for (size_t i = 0; i < U1.size(); ++i)
				centroid_down += pow(U1[i][j],m);
			for (size_t di = 0; di < data_car; ++di) {
				centroid_up = 0;
				for (size_t i = 0; i < U1.size(); ++i) {
					centroid_up += pow(U1[i][j], m) * data[i][di];
				}
				C[j][di] = centroid_up / centroid_down;
			}
		}
		/*Update U1*/
		for (size_t i = 0; i < U.size(); ++i) {
			for (size_t j = 0; j < U[i].size(); ++j) {
				norm_x_c = norm(data[i], C[j]);
				norm_x_ck = 0;
				for (size_t k = 0; k < C.size(); ++k)
					norm_x_ck += pow(norm_x_c / norm(data[i], C[k]), m_calc);
				U1[i][j] = 1 / norm_x_ck;
			}
		}
		//break;
		/*Compare U1 and U*/
		cmp = norm(U1, U);
		U = U1;
		cout << "Iteration : " << ++it << endl;
	} while (cmp > eps);
	
	return U1;
}

vector<vector<double>> altcmeans(vector<vector<double>>& data, vector<int>& centers, float eps, int m) {
	srand(time(0));
	//Lines are objets and rows are clusters
	//Centers
	vector<vector<double>> C(centers.size());
	for (size_t i = 0; i < centers.size(); ++i)
		for (size_t j = 0; j < data[0].size(); ++j)
			C[i].push_back(data[centers[i]][j]);
	//Cluster matrix
	vector<vector<double>> U(data.size()), U1;
	double r, r1, tmp;
	int data_car = data[0].size();
	/*Randomly initialize U*/
	for (size_t i = 0; i < U.size(); ++i) {
		r1 = 0;
		for (size_t j = 0; j < centers.size(); ++j) {
			r = ((double)(rand() % (RAND_MAX / centers.size())) / RAND_MAX);
			tmp = ((double)RAND_MAX / centers.size() / RAND_MAX) - r;
			r += r1;
			r1 = tmp;
			U[i].push_back(r);
		}
		U[i][centers.size() - 1] += r1;
	}
	U1 = U;
	/*Do while*/
	int it = 0;
	double centroid_up, centroid_down, norm_x_c, norm_x_ck, m_calc = 2 / (m - 1); //M != 1 !!!!
	double cmp;//Norm between the matrix
	do {
		
		/*Update U1*/
		for (size_t i = 0; i < U.size(); ++i) {
			for (size_t j = 0; j < U[i].size(); ++j) {
				norm_x_c = norm(data[i], C[j]);
				norm_x_ck = 0;
				for (size_t k = 0; k < C.size(); ++k) {
					if(norm(data[i], C[k]) != 0)
						norm_x_ck += pow(norm_x_c / norm(data[i], C[k]), m_calc);
				}
				if (norm_x_ck != 0)
					U1[i][j] = 1 / norm_x_ck;
				else
					U1[i][j] = 1;
			}
			
		}
		cout.precision(30);
		/*Calculate centers*/
		for (size_t j = 0; j < C.size(); ++j) {
			centroid_down = 0;
			vector<double> vt;
			for (size_t i = 0; i < U1.size(); ++i) {
				centroid_down += pow(U1[i][j], m);
			}
	
			for (size_t di = 0; di < data_car; ++di) {
				centroid_up = 0;
				for (size_t i = 0; i < U1.size(); ++i) {
					centroid_up += pow(U1[i][j], m) * data[i][di];
				}
				C[j][di] = centroid_up / centroid_down;
				
			}
		}
		/*Compare U1 and U*/
		cmp = norm(U1, U);
		U = U1;
		cout << "Iteration : " << ++it << endl;
	} while (cmp > eps);

	return U1;
}

double norm(vector<double>& x, vector<double>& c) {
	double ret = 0;
	for (size_t i = 0; i < x.size(); ++i)
		ret += pow((x[i] - c[i]), 2);
	return sqrt(ret);
}

double norm(vector<vector<double>>& U1, vector<vector<double>>& U) {
	double sum = 0;
	for (size_t i = 0; i < U1.size(); ++i) {
		for (size_t j = 0; j < U1[i].size(); ++j)
			sum += pow(U1[i][j] - U[i][j], 2);
	}
	return sqrt(sum);
}

double altpow(double num, int exp) {
	double res = 0;
	int natural = (int)num,decimal_i = 0,dp = 0;
	double decimal_d = num - natural;
	cout << natural << endl;
	cout << decimal_d << endl;
	while (decimal_d - (int)(decimal_d*10) ){
		decimal_i += (int)(decimal_d * 10);
		dp++;
	}
	cout << decimal_i << endl;
	while (exp--) {
		decimal_i *= decimal_i;
		natural *= natural;
	}
	res = natural;
	decimal_d = 0;

	return res;
}

double altnorm(vector<double>& vec1, vector<double>& vec2) {
	//Set vec1 longest matrix vec2 smallest
	if (vec1.size() < vec2.size()) {
		vector<double> tmp = vec1;
		vec1 = vec2;
		vec2 = tmp;
	}
	cout << "Dist Mat" << endl;
	/*Creation de matrice des distances absolue*/
	vector<vector<double>> distMat(vec2.size());
	for (size_t i = 0; i < vec2.size(); ++i) {
		for (size_t j = 0; j < vec1.size(); ++j) {
			distMat[i].push_back(abs(vec2[i] - vec1[j]));
			cout << distMat[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Ord Mat" << endl;
	/*Creation de la matrice d'ordonencement*/
	vector<vector<double>> tmp = distMat;
	vector<vector<unsigned int>> ordMat(vec2.size());
	for (size_t i = 0; i < tmp.size(); ++i) {
		for (size_t j = 0; j < tmp[i].size(); ++j) {
			int j_min =  min_element(tmp[i].begin(),tmp[i].end()) - tmp[i].begin();
			ordMat[i].push_back(j_min);
			tmp[i][j_min] = *max_element(tmp[i].begin(), tmp[i].end()) + 1 ;
			cout << ordMat[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Vectors" << endl;
	/*Parcourir pour chaque ligne la matrice pour trouver la meilleur combinaison possible*/
	vector<vector<int>> bestmatch;
	vector<int> upmatch, downmatch;
	vector<int> upmatch_i, downmatch_i;
	for (int i = 0; i < vec2.size(); ++i) {
		for (int i_p = 0; i_p < vec2.size(); ++i_p) {
			/*Vers le bas*/
			for (size_t j = 0; j < vec1.size(); ++j) {
				/*Vers le bas */
				if ((downmatch.size() == 0) || (downmatch.size() > 0 && find(downmatch.begin(), downmatch.end(), ordMat[(i + i_p) % vec2.size()][j]) == downmatch.end())
					&& (ordMat[(i + i_p) % vec2.size()][j] == *max_element(downmatch.begin(), downmatch.end()) + 1 || ordMat[(i + i_p) % vec2.size()][j] == *max_element(downmatch.begin(), downmatch.end()) - 1)) {
					downmatch.push_back(ordMat[(i + i_p) % vec2.size()][j]);
					downmatch_i.push_back(i);
					break;
				}
			}
			/*Vers le haut*/
			for (size_t j = 0; j < vec1.size(); ++j) {
				if ((upmatch.size() == 0) || (upmatch.size() > 0 && find(upmatch.begin(), upmatch.end(), ordMat[(vec2.size() + i - i_p) % vec2.size()][j]) == upmatch.end())
					&& (ordMat[(vec2.size() + i - i_p) % vec2.size()][j] == *max_element(upmatch.begin(), upmatch.end()) + 1 || ordMat[(vec2.size() + i - i_p) % vec2.size()][j] == *max_element(upmatch.begin(), upmatch.end()) -1) ) {
					upmatch.push_back(ordMat[(vec2.size() + i - i_p) % vec2.size()][j]);
					upmatch_i.push_back(i);
					break;
				}
			}
		}
		bool db;
		/*Verifier les doublons avant l'ajout*/
		for (size_t id = 0; id < bestmatch.size(); ++id) {
			db = true;
			for (size_t jd = 0; jd < bestmatch[id].size(); ++jd) {
				if (bestmatch[id][jd] != upmatch[jd]) {
					db = false;
					break;
				}
			}
			if (db == true)
				break;
		}
		if ((bestmatch.size() == 0 || db == false) && upmatch.size() == vec2.size()) {
			bestmatch.push_back(upmatch);
		}
		for (size_t id = 0; id < bestmatch.size(); ++id) {
			db = true;
			for (size_t jd = 0; jd < bestmatch[id].size(); ++jd) {
				if (bestmatch[id][jd] != downmatch[jd]) {
					db = false;
					break;
				}
			}
			if (db == true)
				break;
		}
		if ((bestmatch.size() == 0 || db == false) && downmatch.size() == vec2.size()) {
			bestmatch.push_back(downmatch);
		}
		upmatch.clear();
		downmatch.clear();
	}
	/*Calculer la distance entre les vecteurs et prendre la plus courte distance et ajouter le vecteur*/
	for (size_t i = 0; i < bestmatch.size(); ++i) {
		for (size_t j = 0; j < bestmatch[i].size(); ++j)
			cout << vec2[j] << " " << vec1[bestmatch[i][j]] << " " << bestmatch[i][j] << endl;
		cout << endl;
	}
	cout << "Res Distance" << endl;
	/*Calcul de la distance minimal requise*/
	//TODO Calculate the miniman distance
	vector<double> distanceSum(bestmatch.size());
	for (size_t i = 0; i < vec1.size(); ++i)
		cout << vec1[i] << " ";
	cout << endl;
	for (size_t i = 0; i < vec2.size(); ++i)
		cout << vec2[i] << " ";
	cout << endl;	
	double finalsum;
	for (size_t i = 0; i < bestmatch.size(); ++i) {
		finalsum = 0.0;
		for (size_t j = 0; j < vec1.size(); ++j) {
			if (find(bestmatch[i].begin(), bestmatch[i].end(), j) == bestmatch[i].end())
				finalsum += vec1[j];
			else
				finalsum += distMat[find(bestmatch[i].begin(), bestmatch[i].end(), j) - bestmatch[i].begin()][*find(bestmatch[i].begin(), bestmatch[i].end(), j)];
		}
		distanceSum[i] =  (finalsum);
	}
	for (size_t i = 0; i < distanceSum.size(); ++i)
		cout << distanceSum[i] << " ";
	return *min_element(distanceSum.begin(), distanceSum.end());
}
