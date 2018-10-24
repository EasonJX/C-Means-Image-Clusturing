#include "clusterLib.h"

vector<Point> PartsMatch(vector<double> vec1, vector<double> vec2) {
	if (vec1.size() < vec2.size()) {
		vector<double> tmp = vec1;
		vec1 = vec2;
		vec2 = tmp;
	}
	//Crée la matrice des distances globals
	vector<vector<double>> distMat(vec2.size()+1),realsdist(vec2.size());
	for (size_t i = 0; i < realsdist.size(); ++i) {
		for (size_t j = 0; j < vec1.size(); ++j) {
			realsdist[i].push_back(abs(vec1[j] - vec2[i]));
		}
	}
	//Trouver le plus petit chiffre d de la matrice des distances
	double d = realsdist[0][0];
	for (size_t i = 0; i < realsdist.size(); ++i) {
		for (size_t j = 0; j < realsdist[i].size(); ++j) {
			if (d < realsdist[i][j])
				d = realsdist[i][j];
		}
	}
	d++;
	//Initialize 0,0
	distMat[0].push_back(0);
	//Initializer la matrice F 
	size_t max_size = max(vec1.size(), vec2.size());
	double sum_i = 0, sum_j = 0;
	distMat[0].resize(vec1.size()+1);
	distMat[0][0] = 0;
	for (size_t i = 0; i < max_size; ++i) {
		//Init line i = 0
		if (i < vec1.size()) {
			sum_j += vec1[i];
			distMat[0][i+1] = (i+1)*d;
		}
		//Init collumn j = 0;
		if (i < vec2.size()) {
			sum_i += vec2[i];
			distMat[i+1].push_back((i + 1)*d);
		}
	}

	//MAJ Dynamique
	double delta,min_val;
	for (size_t i = 1; i < distMat.size(); ++i) {
		for (size_t j = 1; j < vec1.size() + 1; ++j) {
			//TODO try abs et non abs
			delta = realsdist[i - 1][j - 1];
			min_val = min(distMat[i-1][j] + d , distMat[i][j-1] +d);
			min_val = min(min_val, distMat[i-1][j-1] + delta);
			distMat[i].push_back(min_val);
		}
	}

	
	//Trouver le plus court chemin ???
	size_t i = vec2.size() , j = vec1.size() ;
	vector<Point> indices;
	string match1 = "";
	string match2 = "";

	while (i > 0 || j > 0) {
		/*cout << match1 << endl;
		cout << match2 << endl;*/
		//cout << i << " " << j << endl;
		//Get minimal val
		if (i > 0 && j > 0 && distMat[i][j] == distMat[i - 1][j - 1] + realsdist[i - 1][j - 1]) {
			indices.push_back(Point(i - 1, j - 1));
			match1 = "." + to_string((double)vec2[i - 1]) + "." + match1;
			match2 = "." + to_string((double)vec1[j - 1]) + "." + match2;
			i--;
			j--;

		}
		else if (i > 0 && distMat[i][j] == distMat[i - 1][j] + d) {
			indices.push_back(Point(i - 1, -1));
			match1 = "." + to_string((double)vec2[i - 1]) + "." + match1;
			match2 = ".-." + match2;
			i--;
		}
		else  {
			indices.push_back(Point(-1, j - 1));
			match2 = "." + to_string((double)vec1[j - 1]) + "." + match2;
			match1 = ".-." + match1;
			j--;
		}
	}
	//indices[0].push_back(Point(i, j));
	/*cout << "#######"  << indices.size() << endl;
	for (size_t i = 0; i < indices.size(); ++i) {
		cout << indices[i].x << " ";
	}
	cout << endl;
	for (size_t i = 0; i < indices.size(); ++i) {
		cout << indices[i].y << " ";
	}
	cout << endl;
	cout << "#######" << indices.size() << endl;*/
	return indices;
}

vector<Point> GlobalAlignmentMatch(vector<double> vec1, vector<double> vec2) {
	if (vec1.size() < vec2.size()) {
		vector<double> tmp = vec1;
		vec1 = vec2;
		vec2 = tmp;
	}
	vector<double> left, right;
	vector<Point> leftmatch,rightmatch,finalMatch;
	vector <future<vector<Point>>> threads;
	vector<vector<Point>> res;
	vector<vector<double>> matchesvecs;
	vector<double> res2;
	//future<vector<Point>> a, b;
	for (size_t i = 0; i < vec1.size(); ++i) {
		//Shift left right
		for (size_t j = 0; j < vec1.size(); j++) {
			left.push_back(vec1[(i + j) % vec1.size()]);
			right.push_back(vec1[(vec1.size() - 1 - i - j) % vec1.size()]);
		}
		matchesvecs.push_back(left);
		threads.push_back(async(PartsMatch, left, vec2));
		matchesvecs.push_back(right);
		threads.push_back(async(PartsMatch, right, vec2));
		right.clear();
		left.clear();
	}
	for (size_t i = 0; i < threads.size(); ++i) {
		res.push_back(threads[i].get());
		res2.push_back(matchVecDist(matchesvecs[i],vec2,res[i]));
	}
	int bestmatch = min_element(res2.begin(), res2.end()) - res2.begin();
	vector<Point> finalmatch = res[bestmatch];
	for (size_t i = 0; i < finalMatch.size(); ++i) {
		//[i].y = res[bestmatch][(i + (int)(bestmatch)) % vec1.size()].y;
		if(bestmatch % 2 == 0)
			finalmatch[i].y = res[bestmatch][(i+(int)(bestmatch/2))%vec1.size()].y;
		else
			finalmatch[i].y = res[bestmatch][(vec1.size() - 1 - i - (int)(bestmatch / 2)) % vec1.size()].y;
	}
	return finalmatch;//finalMatch
}

double matchVecDist(vector<double> vec1, vector<double> vec2,vector<Point> match) {
	double res = 0;
	if (vec1.size() < vec2.size()) {
		vector<double> tmp = vec1;
		vec1 = vec2;
		vec2 = tmp;
	}
	for (size_t i = 0; i < match.size(); ++i) {
		if (match[i].x != -1 && match[i].y != -1) {
			res += pow(abs(vec1[match[i].y] - vec2[match[i].x]),2);
		}
		else if(match[i].y == -1)
			res += pow(vec2[match[i].x],2);
		else 
			res += pow(vec1[match[i].y],2);
	}
	return sqrt(res);
}

double GlobalAlignmentDistance(vector<double> vec1, vector<double> vec2) {
	if (vec1.size() < vec2.size()) {
		vector<double> tmp = vec1;
		vec1 = vec2;
		vec2 = tmp;
	}
	vector<double> left, right;
	vector<Point> leftmatch, rightmatch;
	vector <future<vector<Point>>> threads;
	vector<vector<Point>> res;
	vector<vector<double>> matchesvecs;
	vector<double> res2;
	//future<vector<Point>> a, b;
	for (size_t i = 0; i < vec1.size(); ++i) {
		//Shift left right
		for (size_t j = 0; j < vec1.size(); j++) {
			left.push_back(vec1[(i + j) % vec1.size()]);
			right.push_back(vec1[(vec1.size() - 1 - i - j) % vec1.size()]);
		}
		matchesvecs.push_back(left);
		threads.push_back(async(PartsMatch, left, vec2));
		matchesvecs.push_back(right);
		threads.push_back(async(PartsMatch, right, vec2));
		right.clear();
		left.clear();
	}
	for (size_t i = 0; i < threads.size(); ++i) {
		res.push_back(threads[i].get());
		res2.push_back(matchVecDist(matchesvecs[i],vec2,res[i]));
	}
	return *min_element(res2.begin(),res2.end());//finalMatch;
}