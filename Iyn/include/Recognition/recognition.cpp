#include "recognitionLib.h"

vector<int> sequencial_recognize(int index_request, vector<car> images) {
	cout << "Start recognition " << endl;
	vector<double> distances;
	for (size_t i = 0; i < images.size(); ++i) {
		distances.push_back(norm(images[i],images[index_request]));
		cout << i*100/images.size() << "%" << i << " " << index_request <<endl;
	}
	cout << "End recognition" << endl << "Start ordering" ;
	vector<int> ret;
	double max_value = *max_element(distances.begin(), distances.end()) + 1;
	for (size_t i = 0; i < distances.size(); ++i) {
		vector<double>::iterator min_index = min_element(distances.begin(), distances.end());
		ret.push_back(min_index - distances.begin());
		distances[min_index - distances.begin()] = max_value;
	}
	cout << "End Ordering" << endl;
	return ret;
}

vector<int> cluster_recognition(int index_request, vector<car> centers, vector<car> images, vector<vector<int>> clusters) {
	vector<double> centerdist;
	for (size_t i = 0; i < centers.size(); ++i) {
		centerdist.push_back(norm(centers[i],images[index_request]));
		//cout << centerdist[i] << " " ;
	}
	cout << endl;
	vector<double> res;
	int best = min_element(centerdist.begin(), centerdist.end()) - centerdist.begin();
	for (size_t i = 0; i < clusters[best].size(); ++i) {
		res.push_back(norm(images[clusters[best][i]], images[index_request]));
	}
	vector<int> ret;
	cout << "Start ordering" << endl;
	double max_value = *max_element(res.begin(), res.end()) + 1;
	for (size_t i = 0; i < res.size(); ++i) {
		vector<double>::iterator min_index = min_element(res.begin(), res.end());
		ret.push_back(clusters[best][min_index - res.begin()]);
		res[min_index - res.begin()] = max_value;
	}
	cout << "End Ordering" << endl;
	return ret;
}
