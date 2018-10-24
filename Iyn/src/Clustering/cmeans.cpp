#include "clusterLib.h"



vector<vector<double>> cmeans(vector<car>& data, vector<int>& centers, float eps, int m, string centerexport) {
	//Lines are objets and rows are clusters
	//Centers
	vector<car> C(centers.size());
	for (size_t i = 0; i < centers.size(); ++i)
		for (size_t j = 0; j < data[0].size(); ++j)
			C[i].push_back(data[centers[i]][j]);
	//Cluster matrix
	vector<vector<double>> U(data.size()), U1;
	double r, r1, tmp;
	int data_car = data[0].size();

	//MULTITHREADING
	future<double> a, b;
	//Randomly initialize U
	cout << "Random initialization" << endl;
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
	cout << "Start calculate coeficients" << endl;
	U1 = U;
	//Do while
	int it = 0;
	double  centroid_down, norm_x_c, norm_x_ck, m_calc = 2 / (m - 1); //M != 1 !!!!
	double cmp;//Norm between the matrix
	vector<double> xcik_norm;
	do {
		//Update U1
		for (size_t i = 0; i < U.size(); ++i) {
			for (size_t k = 0; k < C.size(); ++k)
				xcik_norm.push_back(norm(data[i], C[k]));
			for (size_t j = 0; j < U[i].size(); ++j) {
				norm_x_c = xcik_norm[j];
				norm_x_ck = 0;
				for (size_t k = 0; k < C.size(); ++k) {
					//double cik = norm(data[i], C[k]);
					if (xcik_norm[k] != 0)
						norm_x_ck += pow(norm_x_c / xcik_norm[k], m_calc);
				}
				if (norm_x_ck != 0)
					U1[i][j] = 1 / norm_x_ck;
				else
					U1[i][j] = 1;
			}
			xcik_norm.clear();
			cout << "U " << i << endl;
		}
		//if (cmp < eps)break;
		//Calculate centers
		for (size_t j = 0; j < C.size(); ++j) {
			centroid_down = 0;
			vector<double> vt;
			for (size_t i = 0; i < U1.size(); ++i) {
				centroid_down += pow(U1[i][j], m);
			}
			for (size_t di = 0; di < data_car; ++di) {
				//centroid_up = 0;
				vector<double> centroid_up(C[j][di].size());
				for (size_t c = 0; c < centroid_up.size(); ++c)
					centroid_up[c] = 0;
				for (size_t i = 0; i < U1.size(); ++i) {
					vector<double> db = data[i][di];
					for (size_t c = 0; c < db.size(); ++c)
						db[c] *= pow(U1[i][j], m);
					centroid_up = addVect(centroid_up, db);
					//centroid_up += pow(U1[i][j], m) * data[i][di];
				}
				for (size_t c = 0; c < centroid_up.size(); ++c)
					centroid_up[c] /= centroid_down;
				C[j][di] = centroid_up;
			}
			cout << "C" << j << endl;
		}

		//Compare U1 and U
		cmp = norm(U1, U);
		U = U1;
		cout << "Iteration : " << ++it << "cmp = " << cmp << endl;
		if (it > 50) break;
	} while (cmp > eps);
	//Export centers 
	ofstream ff(centerexport);
	for (size_t i = 0; i < C.size(); ++i) {
		ff << "{";
		for (size_t j = 0; j < C[i].size(); ++j) {
			ff << "[";
			for (size_t z = 0; z < C[i][j].size(); ++z) {
				if (z + 1 == C[i].size())
					ff << C[i][j][z];
				else
					ff << C[i][j][z] << ",";
			}
			ff << ']';
		}
		ff << "}" << endl;
	}
	
	return U1;
}


double norm(car& x, car& c) {
	double ret = 0;
	double sub;
	for (size_t i = 0; i < x.size(); ++i) {

		sub = subVect(x[i], c[i]);
		ret += pow(sub, 2);
	}
	return sqrt(ret);
}

double norm(vector<double>& x, vector<double>& c) {
	double ret = 0;
	for (size_t i = 0; i < x.size(); ++i) {
		ret += pow((x[i] - c[i]), 2);
	}
	return sqrt(ret);
}

double eucnorm(vector<vector<double>>& U1, vector<vector<double>>& U) {
	double sum = 0;
	for (size_t i = 0; i < U1.size(); ++i) {
		for (size_t j = 0; j < U1[i].size(); ++j)
			sum += pow(U1[i][j] - U[i][j], 2);
	}
	return sqrt(sum);
}

double subVect(vector<double>& vec1, vector<double> &vec2) {
	if (vec1.size() == 1 && vec2.size() == 1)
		return abs(vec1[0] - vec2[0]);
	else {
		return vecDistance(vec1, vec2);
	}

}


double vecDistance(vector<double> vec1, vector<double> vec2) {
	/*vector<Point> vec = GlobalAlignmentMatch(vec1, vec2);
	double distance = matchVecDist(vec1, vec2, vec);*/
	return GlobalAlignmentDistance(vec1, vec2);
}

vector<double> addVect(vector<double>& vec1, vector<double>& vec2) {
	vector<Point> vec = GlobalAlignmentMatch(vec1, vec2);
	vector<double> add;
	for (size_t i = 0; i < vec.size(); ++i) {
		if (vec1.size() > vec2.size()) {
			if (vec[i].y != -1 && vec[i].x != -1)
				add.push_back(vec1[vec[i].y] + vec2[vec[i].x]);
			else if (vec[i].y != -1)
				add.push_back(vec1[vec[i].y]);
			add[i];
		}
		else {
			if (vec[i].x != -1 && vec[i].y != -1)
				add.push_back(vec1[vec[i].x] + vec2[vec[i].y]);
			else if (vec[i].x != -1)
				add.push_back(vec1[vec[i].x]);
		}
	}
	return add;
}

vector<vector<double>> altcmeans(vector<car>& data, vector<int>& centers, float eps, int m) {
	//Lines are objets and rows are clusters
	//Centers
	vector<car> C(centers.size());
	for (size_t i = 0; i < centers.size(); ++i)
		for (size_t j = 0; j < data[0].size(); ++j)
			C[i].push_back(data[centers[i]][j]);
	//Cluster matrix
	vector<vector<double>> U(data.size()), U1;
	double r, r1, tmp;
	int data_car = data[0].size();
	//Randomly initialize U
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
	//Do while
	int it = 0;
	double  centroid_down, norm_x_c, norm_x_ck, m_calc = 2 / (m - 1); //M != 1 !!!!
	double cmp;//Norm between the matrix
	vector<double> xcik_norm;
	do {

		//Update U1
		for (size_t i = 0; i < U.size(); ++i) {
			for (size_t k = 0; k < C.size(); ++k)
				xcik_norm.push_back(matchHuShapes(data[i][0], C[k][0]));
			for (size_t j = 0; j < U[i].size(); ++j) {
				norm_x_c = matchHuShapes(data[i][0], C[j][0]);
				norm_x_ck = 0;
				for (size_t k = 0; k < C.size(); ++k) {
					//double cik = norm(data[i], C[k]);
					if (xcik_norm[k] != 0)
						norm_x_ck += pow(norm_x_c / xcik_norm[k], m_calc);
				}
				if (norm_x_ck != 0)
					U1[i][j] = 1 / norm_x_ck;
				else
					U1[i][j] = 1;
			}
			xcik_norm.clear();
			cout << "U " << i << endl;
		}
		//Calculate centers
		for (size_t j = 0; j < C.size(); ++j) {
			centroid_down = 0;
			vector<double> vt;
			for (size_t i = 0; i < U1.size(); ++i) {
				centroid_down += pow(U1[i][j], m);
			}
			for (size_t di = 0; di < data_car; ++di) {
				//centroid_up = 0;
				vector<double> centroid_up(C[j][di].size());
				for (size_t c = 0; c < centroid_up.size(); ++c)
					centroid_up[c] = 0;
				for (size_t i = 0; i < U1.size(); ++i) {
					vector<double> db = data[i][di];
					for (size_t c = 0; c < db.size(); ++c)
						db[c] *= pow(U1[i][j], m);
					for (size_t cu = 0; cu < centroid_up.size(); ++cu)
						centroid_up[cu] += db[cu];
					//centroid_up += pow(U1[i][j], m) * data[i][di];
				}
				for (size_t c = 0; c < centroid_up.size(); ++c)
					C[j][di][c] = centroid_up[c] / centroid_down;
				//C[j][di] = centroid_up / centroid_down;

			}
		}
		//Compare U1 and U
		cmp = norm(U1, U);
		U = U1;
		cout << "Iteration : " << ++it << endl;
	} while (cmp > eps);

	return U1;
}

double matchHuShapes(vector<double>hu1, vector<double>hu2) {
	double ret = 0;
	for (size_t i = 0; i < 7; ++i)
		ret += abs(hu1[i] - hu2[i]);
	//ret += abs(1 / hu1[i] - 1 / hu2[i]);
	return ret;
}

double vec_sum(vector<double>) {
	return 0;
}