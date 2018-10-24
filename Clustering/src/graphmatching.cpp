#include "contoursLib.h"

double graphMatch(imgGraph & grph1, imgGraph & grph2) {
	double max_percent = 0.0;
	/*
	theoriquement les 2 graphes auront la meme taille
	*/
	imgGraph tmp,cmpres;
	for (size_t j = 0; j < grph2.graph.size(); ++j) {
		tmp.graph.push_back(0);
		cmpres.graph.push_back(0);
	}
	double moy = 100,tmpmoy = 0;
	for (size_t i = 0; i < grph1.graph.size(); ++i) {
		tmpmoy = 0;
		for (size_t j = 0; j < grph2.graph.size(); ++j) {
			tmp.graph[j] = abs(grph1.graph[j] - grph2.graph[(i + j) % 100]);
		}
		for (size_t j = 0; j < grph2.graph.size(); ++j)
			tmpmoy += tmp.graph[j] / tmp.graph[(j + 1) % 100];
		tmpmoy /= 100;
		(tmpmoy < moy ? moy = tmpmoy : 0);
		renderGraph(&tmp, NULL, NULL);
		cvWaitKey(1000/30);
	}
	cout << moy << endl;
	return 0;
}

