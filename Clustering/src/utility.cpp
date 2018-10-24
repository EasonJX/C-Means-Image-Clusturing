#include "contoursLib.h"

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

void readallfiles(string path) {
	WIN32_FIND_DATAA dir;
	string pathtmp = path + "*";
	HANDLE h = FindFirstFileA(pathtmp.c_str(), &dir);
	string nom_du_fichier;
	int count = 0;
	if (h != INVALID_HANDLE_VALUE) {
		do {
			nom_du_fichier = path  + String(dir.cFileName);
			if (dir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && strcmp(dir.cFileName,".") != 0 && strcmp(dir.cFileName, "..") != 0) {
				readallfiles(path + String(dir.cFileName) + "\\");
				continue;
			}
			else if (strcmp(dir.cFileName, ".") == 0 || strcmp(dir.cFileName, "..") == 0) {
				continue;
			}
			/*Traitement Debut*/
			//cout << nom_du_fichier.c_str() << endl;
			/*Traitement Fin*/
		} while (FindNextFileA(h, &dir) != 0);
	}
	else
		cout << "Erreur " << endl;
	
}

vector<String> readallfilesRet(string path) {
	WIN32_FIND_DATAA dir;
	string pathtmp = path + "*";
	HANDLE h = FindFirstFileA(pathtmp.c_str(), &dir);
	string nom_du_fichier;
	int count = 0;
	vector<String> ret;
	if (h != INVALID_HANDLE_VALUE) {
		do {
			nom_du_fichier = path + String(dir.cFileName);
			if (dir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && strcmp(dir.cFileName, ".") != 0 && strcmp(dir.cFileName, "..") != 0) {
				readallfiles(path + String(dir.cFileName) + "\\");
				continue;
			}
			else if (strcmp(dir.cFileName, ".") == 0 || strcmp(dir.cFileName, "..") == 0) {
				continue;
			}
			/*Traitement Debut*/
			ret.push_back(nom_du_fichier);
			/*Traitement Fin*/
		} while (FindNextFileA(h, &dir) != 0);
	}
	else
		cout << "Erreur " << endl;
	return ret;
}
