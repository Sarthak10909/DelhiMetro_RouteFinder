#include "headers/Graph.h"
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <memory>

using namespace std;

// Function to read all lines from a line text file
void load_lines(vector<string> &lines)
{
    ifstream file("Resources/example.txt");

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            string clean_line = "";

            // Read characters until we hit '/' (comment marker)
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == '/')
                {
                    break; // Stop at comment
                }
                clean_line += line[i];
            }

            lines.push_back(clean_line);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}

// Function to make hash map of stations with their line
void hashes(map<pair<string, string>, int> &result, vector<string> &station_names)
{
    ifstream file("Resources/stations.txt");

    if (file.is_open())
    {
        string full_line;
        while (getline(file, full_line))
        {
            string word = "";
            int word_count = 0;
            pair<string, string> station_line_pair;
            int position = 0;

            // Parse each line character by character
            for (int i = 0; i < full_line.length(); i++)
            {
                // Check for " on" pattern (indicates line name follows)
                if (full_line[i] == ' ' && i + 2 < full_line.length() && full_line[i + 2] == 'n')
                {
                    if (word_count == 0)
                    {
                        // First word is station name
                        station_line_pair.first = word;
                        station_names.push_back(word);
                    }
                    if (word_count == 1)
                    {
                        // Second word is line name
                        station_line_pair.second = word;

                        // Extract position number from end of line
                        int last_digit = full_line[full_line.length() - 1] - '0';
                        int second_last_digit = full_line[full_line.length() - 2] - '0';
                        position = second_last_digit * 10 + last_digit;
                        break;
                    }
                    word_count++;
                    i += 3; // Skip " on"
                    word = "";
                }
                else
                {
                    word += full_line[i];
                }
            }

            // Store station-line pair with its position
            result[station_line_pair] = position;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}

string line_name(const vector<string> &lines, const map<pair<string, string>, int> &station_map, const string &station_name)
{
    // Check each metro line
    for (int i = 0; i < lines.size(); i++)
    {
        string current_line = lines[i];

        // Check if this station exists on this line
        pair<string, string> station_line_pair = {station_name, current_line};

        if (station_map.find(station_line_pair) != station_map.end())
        {
            return current_line; // Found the line!
        }
    }

    return "invalid station name"; // Station not found
}

// Function to make hash map of stations on more than one line
void intersecting_stations_function(map<pair<string, string>, set<string>> &transfer_stations,
                                    const vector<string> &lines,
                                    const map<pair<string, string>, int> &station_map,
                                    const vector<string> &all_stations)
{

    // Compare every pair of lines
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines.size(); j++)
        {
            if (lines[i] == lines[j])
            {
                continue; // Skip same line
            }

            string line1 = lines[i];
            string line2 = lines[j];
            pair<string, string> line_pair = {line1, line2};
            pair<string, string> reverse_pair = {line2, line1};

            // Check if we already processed this pair in reverse
            if (transfer_stations.find(reverse_pair) == transfer_stations.end())
            {
                // Find stations that exist on both lines
                for (int k = 0; k < all_stations.size(); k++)
                {
                    string station = all_stations[k];

                    // Check if station exists on both lines
                    bool on_line1 = (station_map.find({station, line1}) != station_map.end());
                    bool on_line2 = (station_map.find({station, line2}) != station_map.end());

                    if (on_line1 && on_line2)
                    {
                        transfer_stations[line_pair].insert(station);
                    }
                }
            }
            else
            {
                // Copy from already processed reverse pair
                transfer_stations[line_pair] = transfer_stations[reverse_pair];
            }
        }
    }
}

// Function to make line_hash
auto line_hash_function(map<int, string> &line_num, const vector<string> &line) -> void
{
    for (size_t i = 0; i < line.size(); ++i)
    {
        line_num[static_cast<int>(i)] = line[i];
    }
}

// Function to make adjacency matrix for the graph
void graph_function(vector<vector<int>>& graph) {
    ifstream file("Resources/matrix.txt");
    
    if (!file.is_open()) {
        cout << "Unable to open file" << endl;
        return;
    }

    string line;
    int row = 0;
    
    while (getline(file, line)) {
        for (int col = 0; col < line.length(); col++) {
            if (line[row] == '/') {
                break;  // Skip comments
            }
            if (line[col] == '1') {
                graph[row].push_back(col);  // Add connection from row to col
            }
        }
        row++;
    }
    file.close();
}


// Function for respective line number - FIXED SIGNATURE
int line_num_function(const map<int, string>& line_numbers, const string& line_name) {
    for (auto it = line_numbers.begin(); it != line_numbers.end(); ++it) {
        if (it->second == line_name) {
            return it->first;  // Found the line number
        }
    }
    return -1;  // Line not found
}


// For checking the visited node
bool visited(int node, const vector<int>& current_path) {
    // Check if node is NOT in the current path
    for (int i = 0; i < current_path.size(); i++) {
        if (current_path[i] == node) {
            return false;  // Node already visited
        }
    }
    return true;  // Node not visited yet
}


// For finding the path from source to destination - FIXED SIGNATURE
auto path_function(const vector<vector<int>> &graph, int src, int des) -> vector<vector<int>>
{
    vector<vector<int>> ans;
    queue<vector<int>> que;
    vector<int> curr_path{src};
    que.push(curr_path);

    while (!que.empty())
    {
        curr_path = que.front();
        que.pop();
        int n = static_cast<int>(curr_path.size());
        int last = curr_path[n - 1];

        if (last == des && n <= 4)
        {
            ans.emplace_back(curr_path);
            continue;
        }

        for (const auto &i : graph[last])
        {
            if (visited(i, curr_path))
            {
                auto new_path = curr_path;
                new_path.push_back(i);
                que.push(std::move(new_path)); // Fixed: Added std::
            }
        }
    }

    return ans;
}

// Function for finding the path with all stations - FIXED SIGNATURE
auto path_with_station(const vector<vector<int>> &dfs_paths,
                       const map<pairstr, set<string>> &intersecting_stations,
                       const map<pairstr, int> &m,
                       const map<int, string> &line_num,
                       const string &start,
                       const string &end) -> vector<node>
{
    vector<node> ans;

    for (const auto &i : dfs_paths)
    {
        if (i.size() > 1)
        {
            vector<node> curr;

            for (const auto &k : intersecting_stations.at({line_num.at(i[0]), line_num.at(i[1])}))
            {
                node temp;
                const string &line = line_num.at(i[0]);
                temp.val = abs(m.at({k, line}) - m.at({start, line}));
                temp.route.push_back(start);
                if (start != k)
                {
                    temp.route.push_back(k);
                }
                curr.emplace_back(std::move(temp)); // Fixed: Added std::
            }

            for (size_t j = 1; j < i.size() - 1; ++j)
            {
                vector<node> new_curr;
                bool flag = false;

                for (const auto &k : intersecting_stations.at({line_num.at(i[j]), line_num.at(i[j + 1])}))
                {
                    for (const auto &l : curr)
                    {
                        flag = true;
                        node temp = l;
                        int n = static_cast<int>(temp.route.size());
                        const string &prev = temp.route[n - 1];
                        temp.val += abs(m.at({k, line_num.at(i[j])}) - m.at({prev, line_num.at(i[j])}));
                        if (prev != k)
                        {
                            temp.route.push_back(k);
                        }
                        new_curr.emplace_back(std::move(temp)); // Fixed: Added std::
                    }
                }

                if (flag)
                {
                    curr = std::move(new_curr); // Fixed: Added std::
                }
            }

            for (auto j : curr)
            {
                const string &last_line = line_num.at(i[i.size() - 1]);
                int n = static_cast<int>(j.route.size());
                const string &prev = j.route[n - 1];
                j.val += abs(m.at({end, last_line}) - m.at({prev, last_line}));
                if (end != prev)
                {
                    j.route.push_back(end);
                }
                ans.emplace_back(std::move(j)); // Fixed: Added std::
            }
        }
    }

    return ans;
}

// Function for sorting the paths
auto compare = [](const node &temp1, const node &temp2) -> bool
{
    if (temp1.val == temp2.val)
    {
        return temp1.route.size() < temp2.route.size();
    }
    return temp1.val < temp2.val;
};

auto sorting(vector<node> &routes) -> void
{
    sort(routes.begin(), routes.end(), compare);
}
