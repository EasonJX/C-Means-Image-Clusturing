#include "contoursLib.h"

void exportVariation(vector<angleContourData> &derivVation, string name, Mat &img) {
	string outputLit = "C:\\Users\\mataoui\\Projects\\Image Processing\\cmp\\", finaloutput;
	ofstream otf;
	char derv;
	finaloutput = outputLit + name + ".html";
	otf.open(finaloutput);
	otf << "<body><table border=\"1\">";
	otf << "<tr><th>Variation</th><th>Angluar Interval</th><th>Difference</th></tr>";
	for (size_t j = 0; j < derivVation.size() - 1; ++j) {
		if (derivVation[j].variation > 0)
			derv = '+';
		else if (derivVation[j].variation == 0)
			derv = '.';
		else
			derv = '-';
		otf << "<tr><td>" << derv << "</td><td>" << derivVation[j].interval << "</td><td>" << derivVation[j].diff << "</td></tr>" << endl;
	}
	otf << "</table>";
	finaloutput = outputLit + name + ".png";
	imwrite(finaloutput, img);
	otf << "<img src=\"" << finaloutput << "\"/>";
	finaloutput = outputLit + name + ".bmp";
	otf << "<img src=\"" << finaloutput << "\"/></body>";
	otf.close();
}

void renderGraph(const imgGraph* grph, const vector<Point2d>* derivativ, const char* savefile) {
	//Render arrows
	namedWindow("graphresult");
	int height = 700, width = 1024, hor_interval = 10, vert_interval = 10;double horizenat_val = grph->graph.size(), vertical_val = *max_element(grph->graph.begin(), grph->graph.end());
	Mat img = Mat::zeros(height, width, CV_8UC3);
	//Draw Grid
	//Put text
	putText(img, "Pixel Distance", Point(0, height * 2 / 100), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
	putText(img, "Angles", Point(width * 90 / 100, height * 95 / 100), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
	//Draw lines
	for (int i = 0; i <= max(horizenat_val, vertical_val); i++) {
		if (i % vert_interval == 0 && i <= vertical_val) {
			putText(img, to_string(i), Point(width * 1 / 100, (height * 85 / 100) - (height * 85 / 100 / vertical_val  * i) + (height * 5 / 100)), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
			line(img, Point(width * 5 / 100, (height * 85 / 100) - (height * 85 / 100 / vertical_val * i) + (height * 5 / 100)), Point(width * 90 / 100, (height * 85 / 100) - (height * 85 / 100 / vertical_val * i) + (height * 5 / 100)), Scalar(20, 20, 20));
			circle(img, Point(width * 5 / 100, (height * 85 / 100) - (height * 85 / 100 / vertical_val * i) + (height * 5 / 100)), 1, Scalar(255, 0, 255));
		}
		if (i % hor_interval == 0 && i <= horizenat_val) {
			putText(img, to_string(i), Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), height * 93 / 100), FONT_HERSHEY_PLAIN, 0.7, Scalar(255, 255, 255));
			line(img, Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), height * 5 / 100), Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), height * 90 / 100), Scalar(20, 20, 20));
			circle(img, Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), height * 90 / 100), 1, Scalar(255, 0, 255));
		}
	}
	line(img, Point(width * 5 / 100, height * 5 / 100), Point(width * 5 / 100, height * 90 / 100), Scalar(255, 255, 255));
	line(img, Point(width * 5 / 100, height * 90 / 100), Point(width * 90 / 100, height * 90 / 100), Scalar(255, 255, 255));
	
	//draw data
	if (grph != NULL)
		for (size_t i = 0; i < grph->graph.size() - 1; ++i)
			line(img, Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), (height * 85 / 100) - (height * 85 / 100 / vertical_val * grph->graph[i]) + (height * 5 / 100))
				, Point((width * 85 / 100 / horizenat_val * (i+1)) + (width * 5 / 100), (height * 85 / 100) - (height * 85 / 100 / vertical_val * grph->graph[i+1]) + (height * 5 / 100)), Scalar(0, 0, 255));
			/*line(img, Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), height * 90 / 100)
				, Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), (height * 85 / 100) - (height * 85 / 100 / vertical_val * grph->graph[i]) + (height * 5 / 100)), Scalar(255, 255, 255));*/
	
	if (savefile != NULL)
		imwrite(savefile, img);
	imshow("graphresult", img);
}

void renderGraph(vector<vector<double>> data, vector<vector<double>> U) {
	//Render arrows
	namedWindow("graphresult");
	int height = 700, width = 1024, hor_interval = 1, vert_interval =1; double horizenat_val = 1, vertical_val = 1;
	Mat img = Mat::zeros(height, width, CV_8UC3);
	//Draw Grid
	//Put text
	putText(img, "Pixel Distance", Point(0, height * 2 / 100), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
	putText(img, "Angles", Point(width * 90 / 100, height * 95 / 100), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
	//Draw lines
	for (int i = 0; i <= max(horizenat_val, vertical_val); i++) {
		if (i % vert_interval == 0 && i <= vertical_val) {
			putText(img, to_string(i), Point(width * 1 / 100, (height * 85 / 100) - (height * 85 / 100 / vertical_val  * i) + (height * 5 / 100)), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));
			line(img, Point(width * 5 / 100, (height * 85 / 100) - (height * 85 / 100 / vertical_val * i) + (height * 5 / 100)), Point(width * 90 / 100, (height * 85 / 100) - (height * 85 / 100 / vertical_val * i) + (height * 5 / 100)), Scalar(20, 20, 20));
			circle(img, Point(width * 5 / 100, (height * 85 / 100) - (height * 85 / 100 / vertical_val * i) + (height * 5 / 100)), 1, Scalar(255, 0, 255));
		}
		if (i % hor_interval == 0 && i <= horizenat_val) {
			putText(img, to_string(i), Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), height * 93 / 100), FONT_HERSHEY_PLAIN, 0.7, Scalar(255, 255, 255));
			line(img, Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), height * 5 / 100), Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), height * 90 / 100), Scalar(20, 20, 20));
			circle(img, Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), height * 90 / 100), 1, Scalar(255, 0, 255));
		}
	}
	line(img, Point(width * 5 / 100, height * 5 / 100), Point(width * 5 / 100, height * 90 / 100), Scalar(255, 255, 255));
	line(img, Point(width * 5 / 100, height * 90 / 100), Point(width * 90 / 100, height * 90 / 100), Scalar(255, 255, 255));

	//draw data
	for (size_t i = 0; i < data.size(); ++i) {
		cout << data[i][0] << " " << data[i][1] << endl;
		circle(img, Point((width * 85 / 100 / horizenat_val * data[i][0]) + (width * 5 / 100), (height * 85 / 100) - (height * 85 / 100 / vertical_val *  data[i][1]) + (height * 5 / 100)), 1, Scalar(255 * U[i][0], 0, 255 * U[i][1]), 2);
	}
	/*line(img, Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), height * 90 / 100)
	, Point((width * 85 / 100 / horizenat_val * i) + (width * 5 / 100), (height * 85 / 100) - (height * 85 / 100 / vertical_val * grph->graph[i]) + (height * 5 / 100)), Scalar(255, 255, 255));*/
	imshow("graphresult", img);
}