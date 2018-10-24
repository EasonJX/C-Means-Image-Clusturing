#pragma once
#include "IynGlobal.h"
#include "clusterLib.h"

vector<int> sequencial_recognize(int index_request, vector<car> images);
vector<int> cluster_recognition(int index_request,vector<car> centers,vector<car> images,vector<vector<int>> clusters);