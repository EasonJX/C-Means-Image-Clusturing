#include "contoursLib.h"



int zeroValues(imgGraph& graph) {
	int i;
	for (i = 0; i < 360 && graph.graph[i] != 0; ++i);
	return i;
}
void smoothGraph(imgGraph &graph) {
	int i = zeroValues(graph);
	int prev = i, next, curr = i;
	while (i < 360)
	{
		for (next = i; next < 360 && graph.graph[next] == 0; ++next);
		curr = (int)round((i + next) / 2);
		if (i == 0) {
			i = 359;
			while (graph.graph[i] == 0 && i > 0)
				i--;

			curr = 0;
			i++;
		}
		if (next >= 360) {
			next = 0;
			curr = i;
		}
		graph.graph[curr] = (graph.graph[i - 1] + graph.graph[next]) / 2;
		i = zeroValues(graph);
		next = i;
	}


}




char calculateDirection(double i, double j) {
	return (i - j > 0.0 ? -1 : (i - j == 0.0 ? 0 : 1));
}
vector<Point2d> derivateGraph(imgGraph &input) {
	vector<Point2d> ret;
	char prevdirection = calculateDirection(input.graph[0], input.graph[1]), currentdirection;//0 const > 0 up < 0 down
	ret.push_back(Point2d(0, input.graph[0]));
	for (size_t i = 0; i < input.graph.size() - 1; ++i) {
		currentdirection = calculateDirection(input.graph[i], input.graph[i + 1]);
		if (prevdirection != currentdirection)
			ret.push_back(Point2d(i, input.graph[i]));
		prevdirection = currentdirection;

	}
	ret.push_back(Point2d(359, input.graph[359]));
	return ret;
}

vector<angleContourData> exctractVariation(const vector<Point2d> &input) {
	vector<angleContourData> ret;
	for (size_t i = 0; i < input.size() - 1; ++i) {
		angleContourData newData;
		newData.diff = abs(input[i + 1].y - input[i].y);
		newData.interval = input[i + 1].x - input[i].x;
		newData.variation = calculateDirection(input[i].y, input[i + 1].y);
		ret.push_back(newData);
	}
	//If equals(and very close to each others) merge last and first points
	if (ret[0].variation == ret[ret.size() - 1].variation && (int)(input[0].y - input[input.size() - 1].y) == 0) {
		ret[0].interval = ret[0].interval + ret[ret.size() - 1].interval;
		ret[0].diff = input[1].y - input[input.size() - 2].y;
		ret.pop_back();
	}
	return ret;
}

imgGraph normalizeGraph(const imgGraph graph) {
	imgGraph res;
	res.graph.resize(360);
	/*for (int i = 0; i < graph.graph.size(); ++i)
	res.graph[i] = graph.graph[i] / graph.graph[0];*/
	double max = *std::max_element(graph.graph.begin(), graph.graph.end());
	for (size_t i = 0; i < graph.graph.size(); ++i)
		res.graph[i] = graph.graph[i] / max;
	for (size_t i = 1; i < graph.graph.size(); ++i)
		res.graph[i] = res.graph[i] / res.graph[0];
	return res;
}
int getThreshPoint(vector<Point2d> &input, double thresh) {
	for (size_t i = 0; i < input.size() - 1; ++i)
		if (abs(input[i + 1].y - input[i].y) <= thresh)
			return i;
	return -1;
}
void thresholdVariation(vector<Point2d> &input, double thresh) {
	int threshpt = getThreshPoint(input, thresh);
	while (threshpt != -1) {
		input.erase(input.begin() + threshpt);
		threshpt = getThreshPoint(input, thresh);
	}
	if ((input[0].y - input[input.size() - 1].y) <= thresh) {
		input[input.size() - 1].y = input[0].y;
	}
}