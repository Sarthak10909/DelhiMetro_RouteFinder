#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>

using namespace std;

struct node
{
    int val = 0;
    vector<string> route;
};

typedef pair<string, string> pairstr;

// Updated C++14 function declarations
auto load_lines(vector<string> &lines) -> void;
auto hashes(map<pairstr, int> &result, vector<string> &station_name) -> void;
auto line_hash_function(map<int, string> &line_num, const vector<string> &line) -> void;
auto intersecting_stations_function(map<pairstr, set<string>> &intersecting_stations,
                                    const vector<string> &line,
                                    const map<pairstr, int> &m,
                                    const vector<string> &station_name) -> void;
auto line_name(const vector<string> &l, const map<pairstr, int> &m, const string &name) -> string;
auto graph_function(vector<vector<int>> &graph) -> void;
auto line_num_function(const map<int, string> &line_num, const string &line) -> int;
auto visited(int node, const vector<int> &path) -> bool; // Fixed function name
auto path_function(const vector<vector<int>> &graph, int src, int des) -> vector<vector<int>>;
auto path_with_station(const vector<vector<int>> &dfs_paths,
                       const map<pairstr, set<string>> &intersecting_stations,
                       const map<pairstr, int> &m,
                       const map<int, string> &line_num,
                       const string &start,
                       const string &end) -> vector<node>;
auto sorting(vector<node> &routes) -> void;
