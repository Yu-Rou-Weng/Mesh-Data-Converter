#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    istringstream tokenStream(s);
    string token;
    while (getline(tokenStream, token, delimiter))
    {
        if (!token.empty() && token.find_first_not_of(" \t\n") != string::npos)
        {
            tokens.push_back(token);
        }
    }
    return tokens;
}

int main(int argc, char *argv[])
{
    string filename = "Test.p3d";
    if (argc > 1)
    {
        filename = argv[1];
    }

    ifstream p3d_File(filename);
    if (!p3d_File.is_open())
    {
        cerr << "Cannot open file: " << filename << endl;
        return 1;
    }

    string line;
    getline(p3d_File, line); // Read the first line
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    int numblock = stoi(line);
    long long NPOIN = 0;

    for (int i = 0; i < numblock; ++i)
    {
        getline(p3d_File, line); // Read each subsequent line
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        vector<string> dimensions = split(line, ' ');

        if (dimensions.size() >= 3)
        {
            int dim1 = stoi(dimensions[0]);
            int dim2 = stoi(dimensions[1]);
            int dim3 = stoi(dimensions[2]);
            NPOIN += static_cast<long long>(dim1) * dim2 * dim3;
        }
    }

    cout << "NPOIN: " << NPOIN << endl;

    p3d_File.close();
    return 0;
}
