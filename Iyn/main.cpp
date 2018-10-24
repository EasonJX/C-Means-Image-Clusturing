#include "clusterLib.h"
#include "image.h"
#include "recognitionLib.h"

int main(int argc, char**argv) {
	/*NARRRRIIIII les parametres sont : nom_du_fichier_car Base_de_donnée(MPEG||LEAVES||KIMIA) fichier_exportation_cmeans fichier_exportation_correspondances*/
	//CHARACTERISTICS
	/*clusterextract(argv[6], String(String(argv[6]) + ".clusters"), argv[1], argv[3]);
	exit(0);*/
	
	vector<string> filenames;
	//image::readallfiles(argv[1], type_image::LEAVES, filenames, argv[2]);
	type_image ti;
	if (strcmp(argv[3], "LEAVES") == 0)
		ti = type_image::LEAVES;
	else if (strcmp(argv[3], "KIMIA") == 0)
		ti = type_image::KIMIA;
	else
		ti = type_image::MPEGBLACK;
	vector<car> cars = image::readallfiles(argv[1], ti, filenames, argv[2]);
	//exctractcarfiles(argv[2], filenames, cars);
	//RECOGNITION
	/*string inputrequest;
	string exortfile;
	vector<car> centers = importcenters("leaves.centers");
	vector<vector<int>> clusters = importclusters("leaves.clusters",filenames);
	do {
	cout << "Fichier requete : ";
	cin >> inputrequest;
	ofstream exortfile("reco1.reco");
	vector<int> recog = cluster_recognition(find(filenames.begin(), filenames.end(), inputrequest) - filenames.begin(),centers,cars,clusters);
	for (size_t i = 0; i < recog.size(); ++i) {
	exortfile << i << ".position = " << filenames[recog[i]] << " " << endl;
	}
	exortfile << "Image requete => " << inputrequest << endl;
	exortfile.close();
	} while (inputrequest != "quit");
	system("pause");*/
	//CLUSTERING
	vector<string> cen;
	if (strcmp(argv[3], "LEAVES") == 0) {
		cen = { "1010.jpg","1067.jpg","1134.jpg","1258.jpg","1275.jpg","1335.jpg","1395.jpg","1461.jpg","1522.jpg",
			"1579.jpg","1615.jpg","2023.jpg","2063.jpg", "2127.jpg","2179.jpg","2243.jpg","2303.jpg","2359.jpg","2437.jpg",
			"2494.jpg","2554.jpg","2621.jpg","3010.jpg","3070.jpg","3127.jpg","3195.jpg","3235.jpg","3295.jpg","3343.jpg",
			"3399.jpg","3455.jpg","3523.jpg","3577.jpg" };
		/*cen = { "1004.jpg" ,"1064.jpg","1129.jpg" ,"1198.jpg" ,"1271.jpg" ,"1332.jpg" ,"1389.jpg" ,"1444.jpg" ,"1510.jpg" ,"1584.jpg",
		"2008.jpg" ,"2060.jpg","2124.jpg" ,"2172.jpg" ,"2388.jpg" ,"2440.jpg" ,"2504.jpg" ,"2556.jpg" ,"2192.jpg" ,"2244.jpg",
		"2588.jpg" ,"2639.jpg","3016.jpg" ,"3068.jpg" ,"3116.jpg" ,"3184.jpg" ,"3240.jpg" ,"3296.jpg" ,"3516.jpg" ,"3586.jpg",
		"3316.jpg" ,"3338.jpg","3414.jpg","3464.jpg"};
		/*cen = { "1006.jpg","1072.jpg","1131.jpg","1206.jpg","1281.jpg","1336.jpg","1401.jpg","1451.jpg","1511.jpg","1576.jpg","2010.jpg","2060.jpg","2125.jpg",
		"2180.jpg","2240.jpg","2305.jpg","2355.jpg","2435.jpg","2500.jpg","2555.jpg","2633.jpg","3018.jpg","3073.jpg","3123.jpg","3223.jpg","3233.jpg","3293.jpg",
		"3343.jpg","3398.jpg","3458.jpg","3523.jpg","3575.jpg" };*/
	}
	else if (strcmp(argv[3], "KIMIA") == 0) {
		cen = { "airplane-11.bmp","animal-7.bmp","dude-11.bmp","fish-11.bmp","greeble-5.bmp","hand-11.bmp","rabbit-11.bmp","seaanimal-9.bmp","tool-2.bmp" };
	}
	else {
		cen = { "apple-5.bmp","bat-4.bmp","beetle-4.bmp","bell-6.bmp","bird-5.bmp","Bone-9.bmp","bottle-9.bmp",
			"brick-9.bmp" ,"butterfly-2.bmp","camel-2.bmp","car-9.bmp","carriage-10.bmp","cattle-14.bmp",
			"chicken-17.bmp","children-15.bmp","chopper-15.bmp","classic-12.bmp","Comma-4.bmp",
			"crown-12.bmp","cup-10.bmp","deer-12.bmp","device0-7.bmp","device1-10.bmp","device2-10.bmp","device3-10.bmp",
			"device4-1.bmp","device5-11.bmp","device6-11.bmp","device7-15.bmp","device8-12.bmp","device9-11.bmp","dog-7.bmp",
			"elephant-5.bmp","face-13.bmp","fish-10.bmp","flatfish-12.bmp","fly-9.bmp","fork-13.bmp","fountain-15.bmp","frog-12.bmp","Glas-12.bmp",
			"guitar-10.bmp","hammer-9.bmp","hat-5.bmp","HCircle-7.bmp","Heart-12.bmp","horse-20.bmp","horseshoe-4.bmp","jar-6.bmp","key-7.bmp",
			"lizzard-6.bmp","lmfish-13.bmp","Misk-5.bmp","mouse-10.bmp","octopus-3.bmp","pencil-2.bmp","personal_car-8.bmp","phone-11.bmp",
			"pocket-13.bmp","ray-6.bmp","sea_snake-10.bmp","shoe-10.bmp","spoon-12.bmp","spring-13.bmp","stef-06.bmp","teddy-4.bmp",
			"tree-15.bmp","truck-12.bmp","turtle-7.bmp","watch-18.bmp" };
	}
	//Leavs.car LEAVES leaves.cmeas leaves.res
	vector<int> centers;
	exctractcenters(centers, cen, filenames);
	cout << "Finish extracion" << endl;
	//centers.push_back(i);
	cout << "Start clustering" << endl;
	double epsilone = 0.001;
	vector<vector<double>> res = cmeans(cars, centers, sqrt(epsilone*cen.size()*filenames.size()), 2, argv[4]);
	cout << "End clustering" << endl;
	exportcmeansresult(res, centers, filenames, argv[5]);
	//Resultat final
	exportresult(argv[6], filenames, res, centers);
	clusterextract(argv[6], String(String(argv[6]) + ".clusters"), argv[1], argv[3]);
	//*/
	return 0;
}