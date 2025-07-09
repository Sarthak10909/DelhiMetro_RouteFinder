#include "headers/Graph.h"
#include "Graph.cpp"
#include <iostream>
#include <string>
#include <climits>
#include <fstream>
#include <unistd.h>
#include <map>
#include <memory>
#include <array>

using namespace std;

// Login function with C++14 improvements
int login()
{
    string name, pwd;
    int flag = 0;

    cout << "\n\n\n\n\n\n\t\t\t\t\t  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb" << endl;
    cout << "\t\t\t\t\t\t*WELCOME TO LOGIN*" << endl;
    cout << "\t\t\t\t\t  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb " << endl;

    cout << "Enter your USER NAME  : ";
    cin >> name;

    cout << "Enter the PASSWORD   : ";
    cin >> pwd;

    ifstream f("user_logins.txt");
    if (!f.is_open())
    {
        cout << "Unable to open user_logins.txt file" << endl;
        return 0;
    }

    string temp_name, temp_pwd;
    while (getline(f, temp_name) && getline(f, temp_pwd))
    {
        if (temp_name == name && temp_pwd == pwd)
        {
            flag = 1;
            cout << "\n\t\t\tYou have Successfully LOGGED IN ";
            break;
        }
        else if (temp_name == name && temp_pwd != pwd)
        {
            do
            {
                cout << "\t\t\t----INCORRECT PASSWORD!!!----";
                cout << "Re-Enter the PASSWORD : " << endl;
                cin >> pwd;
            } while (temp_pwd != pwd);

            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        cout << "\n\t\t\tSORRY!!! USER NAME and PASSWORD does not Exist" << endl;
    }
    f.close();
    system("clear");
    return flag;
}

void signup()
{
    cout << "\n\n\n\n\n\n\t\t\t\t\t  =============================" << endl;
    cout << "\t\t\t\t\t\t*WELCOME TO SIGNUP*" << endl;
    cout << "\t\t\t\t\t  =============================" << endl;

    string name, pwd, check_pwd;
    string temp_name, temp_pwd;

    cout << "Enter your USER NAME : ";
    cin >> name;

    // Check if username already exists
    while (true)
    {
        ifstream f("user_logins.txt");
        bool username_exists = false;

        while (getline(f, temp_name) && getline(f, temp_pwd))
        {
            if (temp_name == name)
            {
                username_exists = true;
                break;
            }
        }
        f.close();

        if (username_exists)
        {
            cout << "\n\t\t\t----USER-NAME ALREADY EXIST!!----" << endl;
            cout << "Enter your USER NAME : ";
            cin >> name;
        }
        else
        {
            break;  // Username is unique, exit loop
        }
    }

    // Password input and confirmation
    cout << "Enter your PASSWORD : ";
    cin >> pwd;
    cout << "Re-Enter your PASSWORD : ";
    cin >> check_pwd;

    while (pwd != check_pwd)
    {
        cout << "\t\t\t----INCORRECT PASSWORD!!!----" << endl;
        cout << "Enter your PASSWORD : ";
        cin >> pwd;
        cout << "Re-Enter your PASSWORD : ";
        cin >> check_pwd;
    }

    // Save user to file
    ofstream f("user_logins.txt", ios::app);
    f << name << endl << pwd << endl;
    f.close();

    // Success message 
    cout << "\n\t\t\t\t\t  YOUR NEW ID IS CREATING PLEASE WAIT";
    for (int i = 0; i < 6; i++)
    {
        cout << ".";
        usleep(500000);
    }

    cout << "\n\n\t\t\t\t\tCONGRATULATION!!! YOUR ID CREATED SUCCESSFULLY....Please wait";
    usleep(500000);
    system("clear");
}


auto main() -> int
{
    map<pairstr, int> m;
    vector<string> station_name;
    vector<string> line;
    map<pairstr, set<string>> intersecting_stations;
    map<int, string> line_num;

    load_lines(line);
    vector<vector<int>> graph(line.size());
    hashes(m, station_name);
    line_hash_function(line_num, line);
    intersecting_stations_function(intersecting_stations, line, m, station_name);
    graph_function(graph);

    int ch, flag = 0;
    char s;

    cout << "----------------------------------------WELCOME TO DELHI METRO ASSISTANCE----------------------------------------\n\n";

    do
    {
        cout << endl;
        cout << "\t\t\t\t\t\t\t \t\t\t\t\t\n";
        cout << "\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb \n";
        cout << "\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb \n";
        cout << "\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb 1) LOGIN    \xdb\xdb\xdb\xdb\xdb\xdb\n";
        cout << "\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb 2) REGISTER \xdb\xdb\xdb\xdb\xdb\xdb\n";
        cout << "\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb 3) EXIT     \xdb\xdb\xdb\xdb\xdb\xdb\n";
        cout << "\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb \n";
        cout << "\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb \n";
        cout << "Enter your Choice : ";
        cin >> ch;
        system("clear");

        switch (ch)
        {
        case 1:
            flag = login();
            break;
        case 2:
            signup();
            cout << "Do you want to LOGIN (Y/N)? : ";
            cin >> s;
            if (s == 'y' || s == 'Y')
            {
                flag = login();
            }
            else
            {
                cout << "\t\t\t\t\t\t\t \t\t\t\t\t ___________ \n";
                cout << "\t\t\t\t\t\t\t \t\t\t\t\t| THANK YOU |\n";
                cout << "\t\t\t\t\t\t\t \t\t\t\t\t|_|\n";
                exit(1);
            }
            break;
        case 3:
            cout << "\t\t\t\t\t\t\t \t\t\t\t\t ___________ \n";
            cout << "\t\t\t\t\t\t\t \t\t\t\t\t| THANK YOU |\n";
            cout << "\t\t\t\t\t\t\t \t\t\t\t\t|_|\n";
            exit(0);
            break;
        default:
            cout << "\t\t\t----INCORRECT CHOICE!!!----" << endl;
            break;
        }
    } while (flag != 1);

    if (flag)
    {
        cout << "\n\t\t\t\t\t  LOGGING IN";
        for (int i = 0; i < 6; ++i)
        {
            cout << ".";
            usleep(500000);
        }
        cout << endl;

        cout << "----------------------------------------WELCOME TO  Delhi Metro Assistant----------------------------------------\n\n";
        cout << "                                      We are here to find you the best route                                        \n\n";
        cout << "                                      Please enter the stations accordingly  :                                         " << endl
             << endl;

        // Clear the newline character left by cin >>
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Taking input from user
        string station1, station2;
        cout << "     Enter the Source/Starting station  :- ";
        getline(cin, station1);
        cout << "\n\n     Enter the Destination/Ending station :- ";
        getline(cin, station2);
        cout << endl;

        // For checking the input station lines
        string line1 = line_name(line, m, station1);
        string line2 = line_name(line, m, station2);

        // For lines to their line number
        int line_num1 = line_num_function(line_num, line1);
        int line_num2 = line_num_function(line_num, line2);

        if (line_num1 == -1 || line_num2 == -1)
        {
            cout << "Sorry! You entered wrong station name. Please Try again." << endl;
        }
        else
        {
            if (line_num1 == line_num2)
            {
                int num = abs(m[{station1, line1}] - m[{station2, line1}]);
                cout << "     -Both of these stations are on the same line (" << line1 << ") so we do not need to change any lines" << endl;
                cout << "     -There is only one Path which makes sense" << endl;
                cout << "     -Start from station '" << station1 << "' to station '" << station2 << "' via " << line1 << " line" << endl;
                cout << "     -Total number of stations you have to cover are: " << num << endl;
                cout << "-----------------------------------THANK YOU. HAVE A SAFE JOURNEY!!-------------------------------------- " << endl;
            }
            else
            {
                // CORRECTED: Remove 'auto' and use explicit types
                vector<vector<int>> dfs_paths = path_function(graph, line_num1, line_num2);

                // CORRECTED: Remove 'auto' and use explicit types
                vector<node> routes = path_with_station(dfs_paths, intersecting_stations, m, line_num, station1, station2);

                // For sorting the path on the basis of their station numbers
                sorting(routes);


                // For printing the output
                int path_number = 0;
                int n = static_cast<int>(routes.size());

                for (const auto &route : routes)
                {
                    if (path_number == 0)
                    {
                        ++path_number;
                        cout << "     -The shortest path from station " << station1 << " to station " << station2 << " is:" << endl;
                        cout << "     ";

                        auto print_route = [](const vector<string> &route_vec)
                        {
                            bool first = true;
                            for (const auto &station : route_vec)
                            {
                                if (first)
                                {
                                    cout << station;
                                    first = false;
                                }
                                else
                                {
                                    cout << "  -->  " << station;
                                }
                            }
                        };

                        print_route(route.route);
                        cout << endl;
                        cout << "     -Total number of stations travelled during this route are: " << route.val << endl
                             << endl;
                    }
                    else if (path_number < n && path_number < 3)
                    {
                        ++path_number;
                        string ordinal = (path_number == 2) ? "nd" : "rd";
                        cout << "     -" << path_number << ordinal << " shortest path from station " << station1 << " to station " << station2 << " is:" << endl;
                        cout << "     ";

                        auto print_route = [](const vector<string> &route_vec)
                        {
                            bool first = true;
                            for (const auto &station : route_vec)
                            {
                                if (first)
                                {
                                    cout << station;
                                    first = false;
                                }
                                else
                                {
                                    cout << "  -->  " << station;
                                }
                            }
                        };

                        print_route(route.route);
                        cout << endl;
                        cout << "     -Total number of stations travelled during this route are: " << route.val << endl
                             << endl;
                    }
                    else if (path_number < n && path_number > 2)
                    {
                        ++path_number;
                        char c;
                        cout << "     Do you want one more path. Enter y/n : ";
                        cin >> c;
                        if (c == 'y')
                        {
                            cout << endl;
                            cout << "     -" << path_number << "th shortest path from station " << station1 << " to station " << station2 << " is:" << endl;
                            cout << "     ";

                            auto print_route = [](const vector<string> &route_vec)
                            {
                                bool first = true;
                                for (const auto &station : route_vec)
                                {
                                    if (first)
                                    {
                                        cout << station;
                                        first = false;
                                    }
                                    else
                                    {
                                        cout << "  -->  " << station;
                                    }
                                }
                            };

                            print_route(route.route);
                            cout << endl;
                            cout << "     -Total number of stations travelled during this route are: " << route.val << endl
                                 << endl;
                        }
                        else
                        {
                            cout << "-----------------------------------THANK YOU. HAVE A SAFE JOURNEY!!-------------------------------------- " << endl
                                 << endl;
                            break;
                        }
                    }

                    if (path_number == n)
                    {
                        cout << "-----------------------------------THANK YOU. HAVE A SAFE JOURNEY!!-------------------------------------- " << endl
                             << endl;
                        break;
                    }
                }
            }
        }
    }

    return 0;
}
