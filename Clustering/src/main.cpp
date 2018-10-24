#include "contoursLib.h"

int main(int argc, char **argv)
{
	/*vector<double> vec1 = { 6 , 3 , 1 , 6 };
	vector<double> vec2 = { 1,6,3 };
	cout << endl <<"Final Result : " <<  altnorm(vec1, vec2) << endl;*/
	//TODO :OPTIMISE FOR FINAL RELEASE**/
	//cout << altpow(3.0,2) << endl;
	carFile cf = importCar("bdd_export.car");
	vector<int> classes = centers("classes.cen", cf);
	vector<vector<double>> result = altcmeans(cf.data, classes, 0.00000001, 2);
	cout << "hklsdfjkdsj";
	ofstream output("classified.cm");
	output << std::setw(25) << " ";
	for (size_t i = 0; i < classes.size(); ++i)
		output << std::setw(25) << cf.name[classes[i]];
	output << std::setw(1) << endl;
	for (size_t i = 0; i < result.size(); ++i) {
		output << std::setw(25) << cf.name[i];
		for (size_t j = 0; j < result[i].size(); ++j)
			output << std::setw(25) << result[i][j] * 100;
		output << std::setw(1) << endl;
	}
	output << "######" << endl;
	for (size_t i = 0; i < result.size(); ++i) {
		output << std::setw(25) << cf.name[i];
		int j = distance(result[i].begin(), max_element(result[i].begin(), result[i].end())); ;
		output << std::setw(25) << cf.name[classes[j]] << "\t" << result[i][j]*100 << endl;
	}
	output.close();
	
	
	return 0;
}



 