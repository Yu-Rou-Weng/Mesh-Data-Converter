#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Tuple
{
    int x, y, z;
};

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

    /* Process first line of the header: Numeber of blocks*/
    string line;
    getline(p3d_File, line);
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    int numblock = stoi(line);
    long long NPOIN = 0;

    /* Read & record IMAX, JMAX, KMAX informations according to each block */
    vector<int> RecordBlockDim;
    getline(p3d_File, line);
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    vector<string> dimensions = split(line, ' ');

    if (dimensions.size() == 3) // 3D File Format
    {
        for (int i = 0; i < numblock; ++i)
        {
            int dim1 = stoi(dimensions[0]);
            int dim2 = stoi(dimensions[1]);
            int dim3 = stoi(dimensions[2]);
            // cout << dim1 << endl;
            RecordBlockDim.push_back(dim1);
            // cout << RecordBlockDim[0];
            RecordBlockDim.push_back(dim2);
            RecordBlockDim.push_back(dim3);
            NPOIN += static_cast<long long>(dim1) * dim2 * dim3;
        }
    }
    if (dimensions.size() == 2) // 2D File Format
    {
        for (int i = 0; i < numblock; ++i)
        {
            int dim1 = stoi(dimensions[0]);
            int dim2 = stoi(dimensions[1]);
            RecordBlockDim.push_back(dim1);
            RecordBlockDim.push_back(dim2);
            NPOIN += static_cast<long long>(dim1) * dim2;
        }
    }
    for (size_t i = 0; i < RecordBlockDim.size(); ++i)
    {
        cout << RecordBlockDim[i] << endl;
    }
    /*for (int i = 0; i < numblock; ++i) // Read & record IMAX, JMAX, KMAX informations according to each block
    {

        getline(p3d_File, line);
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        vector<string> dimensions = split(line, ' ');
        // cout << dimensions[0] << endl;
        if (dimensions.size() == 3) // 3D File Format
        {
            int dim1 = stoi(dimensions[0]);
            int dim2 = stoi(dimensions[1]);
            int dim3 = stoi(dimensions[2]);
            RecordBlockDim.push_back(dim1);
            RecordBlockDim.push_back(dim2);
            RecordBlockDim.push_back(dim3);
            NPOIN += static_cast<long long>(dim1) * dim2 * dim3;
        }
        if (dimensions.size() == 2) // 2D File Format
        {
            int dim1 = stoi(dimensions[0]);
            int dim2 = stoi(dimensions[1]);
            RecordBlockDim.push_back(dim1);
            RecordBlockDim.push_back(dim2);
            NPOIN += static_cast<long long>(dim1) * dim2;
        }
    }*/

    // cout << "NPOIN: " << NPOIN << endl;
    /*Tuple tuples[8];
    for (int i = 0; i < NPOIN; i++)
    {
        for (int i = 0; i < 8; i++)
        {
            tuples[i].x = 0;
            tuples[i].y = 0;
            tuples[i].z = 0;
        }
    }*/

    vector<Tuple> tuples;
    int x_vals[8], y_vals[8], z_vals[8];

    for (int &x_val : x_vals)
    {
        p3d_File >> x_val;
    }
    for (int &y_val : y_vals)
    {
        p3d_File >> y_val;
    }
    for (int &z_val : z_vals)
    {
        p3d_File >> z_val;
    }

    for (int i = 0; i < 8; ++i)
    {
        tuples.push_back(Tuple{x_vals[i], y_vals[i], z_vals[i]});
    }
    for (const auto &tuple : tuples)
    {
        cout << tuple.x << " " << tuple.y << " " << tuple.z << endl;
    }

    p3d_File.close();
    return 0;
}
