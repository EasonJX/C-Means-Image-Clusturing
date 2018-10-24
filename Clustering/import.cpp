#include "contoursLib.h"

carFile importCar(string path) {
	carFile ret;
	ifstream bdd(path);
	string data_line,data_name;
	getline(bdd, ret.dir);
	while (getline(bdd, data_line)) {
		/*Get path de la base dd*/
		size_t dp_pos = data_line.find_first_of(':', 0);
		ret.name.push_back(data_line.substr(0, dp_pos - 1));
		data_line = data_line.substr(dp_pos + 2, data_line.size() - dp_pos - 1);
		dp_pos = 0;
		size_t sp_pos = data_line.find(' ', dp_pos);
		vector<double> datavect;
		do{
			datavect.push_back(atof(data_line.substr(dp_pos, sp_pos - dp_pos).c_str()));
			dp_pos = sp_pos + 1;
			sp_pos = data_line.find(' ', dp_pos);
		} while (sp_pos != string::npos);
		datavect.push_back(atof(data_line.substr(dp_pos, data_line.size() - dp_pos).c_str()));
		ret.data.push_back(datavect);
	}
	return ret;
}

vector<int> centers(string path, carFile data) {
	vector<int> ret;
	ifstream ff(path);
	string data_line;
	getline(ff, data_line);
	size_t compos = data_line.find(',');
	size_t beg = 0;
	do {
		ret.push_back(find(data.name.begin(),data.name.end(),data_line.substr(beg,compos - beg)) - data.name.begin());
		beg = compos + 1;
		compos = data_line.find(',', beg);
		if (compos == string::npos) 
			ret.push_back(find(data.name.begin(), data.name.end(), data_line.substr(beg, data_line.size() - beg - 1)) - data.name.begin());
	} while (compos != string::npos);

	return ret;
}