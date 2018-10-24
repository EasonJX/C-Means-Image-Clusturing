#include "clusterLib.h"

double calculateAngle(Point2d &a, Point2d &b) {
	double angle = atan2((b.y - a.y), (b.x - a.x)) * 180 / M_PI;
	return angle;
}
double calculateAngle(Point &a, Point &b) {
	double angle = atan2((b.y - a.y), (b.x - a.x)) * 180 / M_PI;
	return (angle < 0 ? 360.0 + angle : angle);
}

double max(double &a, double &b) {
	return (a > b ? a : b);
}

double min(double &a, double &b) {
	return (a > b ? b : a);
}

double sum_i(vector<double> vec) {
	double ret = 0;
	for (size_t i = 0; i < vec.size(); ++i)
		ret = +vec[i];
	return ret;
}

vector<vector<string>> clusterextract(string filename, string exportf, string originDir, string basename) {
	ifstream result(filename);
	ofstream exportl(exportf);
	vector<string> lines;
	string line;
	while (getline(result, line))lines.push_back(line);
	vector<vector<string>> clusters;
	string cmd;
	//Get 
	for (size_t i = 0; i < lines.size(); ++i) {
		if (lines[i] != "") {
			string image = "", cluster = "";
			for (size_t j = 0; j < lines[i].size(); ++j) {
				if (lines[i][j] != ' ') {
					do{
						image += lines[i][j++];
					}while (lines[i][j] != '\t');
					j++;
					do{
						cluster += lines[i][j++];
					} while (j < lines[i].size() && lines[i][j] != '\t');
					break;
				}
			}
			clusters.push_back(vector<string>({ image,cluster }));
			image.clear(); cluster.clear();

		}
	}
	vector<vector<string>> clusteral;
	for (size_t i = 0; i < clusters.size(); ++i) {
		if (find(clusteral.begin(), clusteral.end(), vector<string>({ clusters[i][1] })) == clusteral.end()) {
			clusteral.push_back(vector<string>({ clusters[i][1] }));
		}
	}
	for (size_t i = 0; i < clusters.size(); ++i) {
		for (size_t j = 0; j < clusteral.size(); ++j) {
			if (clusteral[j][0] == clusters[i][1]) {
				clusteral[j].push_back(clusters[i][0]);
				break;
			}
		}
	}
	vector<vector<string>> ret;
	cmd = "mkdir " + basename;
	system(cmd.c_str());
	for (size_t i = 0; i < clusteral.size(); ++i) {
		exportl << clusteral[i][0] << "("<< clusteral[i].size() - 1<<")"<<" = ";
		vector<string> clust;
		cmd = "cd " + basename + "& mkdir " + clusteral[i][0];//cluster" + to_string(i);
		system(cmd.c_str());
		for (size_t j = 1; j < clusteral[i].size(); ++j) {
			cmd = "cd " + basename + " & copy \"..\\" + originDir + clusteral[i][j] + "\" " + clusteral[i][0];
			system(cmd.c_str());
			clust.push_back(clusteral[i][j]);
			exportl << clusteral[i][j] << " ";
		}
		ret.push_back(clust);
		exportl << endl;
	}
	exportl.close();
	result.close();
	return ret;
}

void exctractcarfiles(string cars, vector<string> &filenames,vector<car> &carect) {
	ifstream read_cars(cars);//Fichier caractéristiques
	if (!read_cars.is_open()) {
		cout << "Fichier caractéristiques introuvable" << endl;
		exit(-1000);
	}

	string cur_line, cur_filename, cur_value;
	int i = 0;
	cout << "Chargement du fichier de caracteristiques : " << endl;
	do {
		getline(read_cars, cur_line);
		//get file names
		cur_filename = cur_line.substr(0, find(cur_line.begin(), cur_line.end(), '=') - cur_line.begin() - 1);
		cout << cur_filename << endl;
		filenames.push_back(cur_filename);
		car imgCar;
		vector<double> one_car;
		if (cur_line == "")
			break;
		for (string::iterator it = find(cur_line.begin(), cur_line.end(), '{'); it != cur_line.end(); ++it) {
			if (*it != '}') {
				it = find(it, cur_line.end(), '[');
				do {
					*it++;
					if (*it != ',' && *it != ']') {
						cur_value = cur_value + *it;
					}
					else if (*it == ',') {
						one_car.push_back(atof(cur_value.c_str()));
						cur_value.clear();
					}
					else{
						one_car.push_back(atof(cur_value.c_str()));
						imgCar.push_back(one_car);
						one_car.clear();
						cur_value.clear();
					}
				} while (*it != ']');
			}
			else
				break;
		}
		carect.push_back(imgCar);
		imgCar.clear();
	} while (!read_cars.eof());
	read_cars.close();
	cout << "Reussi" << endl;
}

void exctractcenters(vector<int>& ret, vector<string> inputcenters, vector<string> filenames) {
	for (size_t i = 0; i < inputcenters.size(); i++) {
		ret.push_back(find(filenames.begin(), filenames.end(), inputcenters[i]) - filenames.begin());
		cout << inputcenters[i] << " " << ret[i] << endl;
	}
}

void exportcmeansresult(vector<vector<double>> means,vector<int> centers,vector<string> filenames,string fileexport) {
	ofstream cmeansresult(fileexport);
	//Resultat c means
	cmeansresult << setw(15) << "\t";
	for (size_t i = 0; i < centers.size(); ++i)
		cmeansresult << setw(15) << filenames[centers[i]] << "\t";
	cmeansresult << endl;
	for (size_t i = 0; i < means.size(); ++i) {
		cmeansresult << setw(15) << filenames[i] << "\t";
		for (size_t j = 0; j < means[i].size(); ++j)
			cmeansresult << setw(15) << means[i][j] << "\t";
		cmeansresult << endl;
	}
	cmeansresult.close();
}

void exportresult(string file, vector<string>filenames, vector<vector<double>> res,vector<int> centers) {
	ofstream finalresult(file);
	int perc = 0;
	for (size_t i = 0; i < res.size(); ++i) {
		int j = max_element(res[i].begin(), res[i].end()) - res[i].begin();
		finalresult << setw(25) << filenames[i] << "\t" << filenames[centers[j]] << "\t" << (res[i][j] * 100) << " ";
		finalresult << endl;
	}
	finalresult.close();
}

vector<car> importcenters(string filename) {
	ifstream centerfile(filename);
	vector<string> lines;
	string line;
	while(getline(centerfile, line)) { lines.push_back(line); }
	car imgCar;
	vector<double> one_car;
	vector<car> caracters;
	for (size_t i = 0; i < lines.size(); i++) {
		if (lines[i] != "") {
			string cur_line = lines[i],cur_value;
			for (string::iterator it = find(cur_line.begin(), cur_line.end(), '{'); it != cur_line.end(); ++it) {
				if (*it != '}') {
					it = find(it, cur_line.end(), '[');
					do {
						*it++;
						if (*it != ',' && *it != ']') {
							cur_value = cur_value + *it;
						}
						else if (*it == ',' || *it != ']') {
							one_car.push_back(atof(cur_value.c_str()));
							cur_value.clear();
						}
						else {
							one_car.push_back(atof(cur_value.c_str()));
							imgCar.push_back(one_car);
							one_car.clear();
							cur_value.clear();
						}
					} while (*it != ']');
				}
				else
					break;
			}
			caracters.push_back(imgCar);
			imgCar.clear();
		}
	}
	return caracters;
}
vector<vector<int>> importclusters(string filename,vector<string> filenames) {
	ifstream clusterfil(filename);
	vector<vector<string>> clusters;
	vector<string> lines;
	string line;
	while (getline(clusterfil, line)) { lines.push_back(line); }
	for (size_t i = 0; i < lines.size(); ++i) {
		if (lines[i] == "")
			break;
		string cur_line = lines[i], cur_value;
		for (string::iterator it = find(cur_line.begin(), cur_line.end(), '='); it != cur_line.end(); ++it) {
				it++;
				string file = "";
				vector<string> clust;
				while (it != cur_line.end()) {
					if (*it != ' ') {
						file += *it;
					}
					else {
						clust.push_back(file);
						file.clear();
					}
					*it++;
				}
				clusters.push_back(clust);
				break;
			}
	}
	vector<vector<int>> clustttt;
	for (size_t i = 0; i < clusters.size(); ++i) {
		vector<int> clt;
		for (size_t j = 1; j < clusters[i].size(); ++j) {
			clt.push_back(find(filenames.begin(), filenames.end(), clusters[i][j]) - filenames.begin());
		}
		clustttt.push_back(clt);
		clt.clear();
	}
	return clustttt;
}