#include "headers/Graph.h"
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <memory>

using namespace std;

// Function to read all lines from a text file
auto load_lines(vector<string>& lines) -> void {
    ifstream myfile("Resources/example.txt");
    if (myfile.is_open()) {
        string line;
        while (getline(myfile, line)) {
            string s;
            s.reserve(line.length());
            
            for (const auto& ch : line) {
                if (ch == '/') break;
                s += ch;
            }
            lines.emplace_back(std::move(s));  // Fixed: Added std::
        }
        myfile.close();
    } else {
        cout << "Unable to open file";
    }
}


// Function to make hash map of stations with their line
auto hashes(map<pairstr, int>& result, vector<string>& station_name) -> void {
    ifstream myfile("Resources/stations.txt");
    if (myfile.is_open()) {
        string full;
        while (getline(myfile, full)) {
            string word;
            int j = 0;
            pairstr x;
            int val = 0;
            
            for (size_t i = 0; i < full.length(); ++i) {
                if (full[i] == ' ' && i + 2 < full.length() && full[i + 2] == 'n') {
                    if (j == 0) {
                        x.first = word;
                        station_name.emplace_back(word);
                    }
                    if (j == 1) {
                        x.second = word;
                        int a = max(static_cast<int>(full[full.length() - 1]) - 48, 0);
                        int b = max(static_cast<int>(full[full.length() - 2]) - 48, 0);
                        val = b * 10 + a;
                        break;
                    }
                    ++j;
                    i += 3;
                    word.clear();
                } else {
                    word += full[i];
                }
            }
            result[x] = val;
        }
        myfile.close();
    } else {
        cout << "Unable to open file";
    }
}

// Function to check the line name of a station
auto line_name(const vector<string>& l, const map<pairstr, int>& m, const string& name) -> string {
    for (const auto& line : l) {
        if (m.find({name, line}) != m.end()) {
            return line;
        }
    }
    return "invalid station name";
}

// Function to make hash map of stations on more than one line
auto intersecting_stations_function(map<pairstr, set<string>>& intersecting_stations, 
                                   const vector<string>& line, 
                                   const map<pairstr, int>& m, 
                                   const vector<string>& station_name) -> void {
    for (size_t i = 0; i < line.size(); ++i) {
        for (size_t j = 0; j < line.size(); ++j) {
            if (line[i] == line[j]) continue;
            
            if (intersecting_stations.find({line[j], line[i]}) == intersecting_stations.end()) {
                for (const auto& k : station_name) {
                    if (m.find({k, line[i]}) != m.end() && m.find({k, line[j]}) != m.end()) {
                        intersecting_stations[{line[i], line[j]}].insert(k);
                    }
                }
            } else {
                intersecting_stations[{line[i], line[j]}] = intersecting_stations[{line[j], line[i]}];
            }
        }
    }
}

// Function to make line_hash
auto line_hash_function(map<int, string>& line_num, const vector<string>& line) -> void {
    for (size_t i = 0; i < line.size(); ++i) {
        line_num[static_cast<int>(i)] = line[i];
    }
}

// Function to make adjacency matrix for the graph
auto graph_function(vector<vector<int>>& graph) -> void {
    ifstream myfile("Resources/matrix.txt");
    if (myfile.is_open()) {
        string l;
        int i = 0;
        while (getline(myfile, l)) {
            for (size_t j = 0; j < l.size(); ++j) {
                if (l[i] == '/') break;
                if (l[j] == '1') {
                    graph[i].push_back(static_cast<int>(j));
                }
            }
            ++i;
        }
        myfile.close();
    } else {
        cout << "Unable to open file";
    }
}

// Function for respective line number - FIXED SIGNATURE
auto line_num_function(const map<int, string>& line_num, const string& line) -> int {
    // Fixed: Replaced C++17 structured binding with traditional loop
    for (auto it = line_num.begin(); it != line_num.end(); ++it) {
        if (it->second == line) {
            return it->first;
        }
    }
    return -1;
}

// For checking the visited node
auto visited(int node, const vector<int>& path) -> bool {
    return find(path.begin(), path.end(), node) == path.end();
}

// For finding the path from source to destination - FIXED SIGNATURE
auto path_function(const vector<vector<int>>& graph, int src, int des) -> vector<vector<int>> {
    vector<vector<int>> ans;
    queue<vector<int>> que;
    vector<int> curr_path{src};
    que.push(curr_path);
    
    while (!que.empty()) {
        curr_path = que.front();
        que.pop();
        int n = static_cast<int>(curr_path.size());
        int last = curr_path[n - 1];
        
        if (last == des && n <= 4) {
            ans.emplace_back(curr_path);
            continue;
        }
        
        for (const auto& i : graph[last]) {
            if (visited(i, curr_path)) {
                auto new_path = curr_path;
                new_path.push_back(i);
                que.push(std::move(new_path));  // Fixed: Added std::
            }
        }
    }
    
    return ans;
}

// Function for finding the path with all stations - FIXED SIGNATURE
auto path_with_station(const vector<vector<int>>& dfs_paths, 
                      const map<pairstr, set<string>>& intersecting_stations, 
                      const map<pairstr, int>& m, 
                      const map<int, string>& line_num, 
                      const string& start, 
                      const string& end) -> vector<node> {
    vector<node> ans;
    
    for (const auto& i : dfs_paths) {
        if (i.size() > 1) {
            vector<node> curr;
            
            for (const auto& k : intersecting_stations.at({line_num.at(i[0]), line_num.at(i[1])})) {
                node temp;
                const string& line = line_num.at(i[0]);
                temp.val = abs(m.at({k, line}) - m.at({start, line}));
                temp.route.push_back(start);
                if (start != k) {
                    temp.route.push_back(k);
                }
                curr.emplace_back(std::move(temp));  // Fixed: Added std::
            }
            
            for (size_t j = 1; j < i.size() - 1; ++j) {
                vector<node> new_curr;
                bool flag = false;
                
                for (const auto& k : intersecting_stations.at({line_num.at(i[j]), line_num.at(i[j + 1])})) {
                    for (const auto& l : curr) {
                        flag = true;
                        node temp = l;
                        int n = static_cast<int>(temp.route.size());
                        const string& prev = temp.route[n - 1];
                        temp.val += abs(m.at({k, line_num.at(i[j])}) - m.at({prev, line_num.at(i[j])}));
                        if (prev != k) {
                            temp.route.push_back(k);
                        }
                        new_curr.emplace_back(std::move(temp));  // Fixed: Added std::
                    }
                }
                
                if (flag) {
                    curr = std::move(new_curr);  // Fixed: Added std::
                }
            }
            
            for (auto j : curr) {
                const string& last_line = line_num.at(i[i.size() - 1]);
                int n = static_cast<int>(j.route.size());
                const string& prev = j.route[n - 1];
                j.val += abs(m.at({end, last_line}) - m.at({prev, last_line}));
                if (end != prev) {
                    j.route.push_back(end);
                }
                ans.emplace_back(std::move(j));  // Fixed: Added std::
            }
        }
    }
    
    return ans;
}

// Function for sorting the paths
auto compare = [](const node& temp1, const node& temp2) -> bool {
    if (temp1.val == temp2.val) {
        return temp1.route.size() < temp2.route.size();
    }
    return temp1.val < temp2.val;
};

auto sorting(vector<node>& routes) -> void {
    sort(routes.begin(), routes.end(), compare);
}
