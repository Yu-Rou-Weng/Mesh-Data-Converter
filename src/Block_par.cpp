#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <vector>
#include <cmath>
#include <algorithm>
#include <array>
using namespace std;

class Block
{
public:
    std::vector<std::vector<std::vector<double>>> X, Y, Z;
    size_t IMAX, JMAX, KMAX;
    double cx, cy, cz;
    long long NPOINT;

    Block(const std::vector<std::vector<std::vector<double>>> &X,
          const std::vector<std::vector<std::vector<double>>> &Y,
          const std::vector<std::vector<std::vector<double>>> &Z)
        : X(X), Y(Y), Z(Z)
    {
        IMAX = X.size();
        JMAX = X[0].size();
        KMAX = X[0][0].size();

        // Calculate centroid
        cx = mean(X);
        cy = mean(Y);
        cz = mean(Z);

        NPOINT = IMAX * JMAX * KMAX;
    }

private:
    double mean(const std::vector<std::vector<std::vector<double>>> &arr)
    {
        double sum = 0;
        size_t count = 0;
        for (const auto &mat : arr)
        {
            for (const auto &row : mat)
            {
                for (double val : row)
                {
                    sum += val;
                    ++count;
                }
            }
        }
        return sum / count;
    }
};

struct Coordinate
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
    string filename;
    if (argc > 1) // Usage: ./parser data/Test.p3d
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
    int n_block = stoi(line);
    long long NPOIN = 0;

    /* Read & record IMAX, JMAX, KMAX informations according to each block */
    vector<int> RecordBlockDim;
    getline(p3d_File, line);
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    vector<string> dimensions = split(line, ' ');

    if (dimensions.size() == 3) // 3D File Format
    {
        for (int i = 0; i < n_block; ++i)
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
        for (int i = 0; i < n_block; ++i)
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

    vector<Coordinate> Coordinates;
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
        Coordinates.push_back(Coordinate{x_vals[i], y_vals[i], z_vals[i]});
    }
    for (const auto &Coordinate : Coordinates)
    {
        cout << Coordinate.x << " " << Coordinate.y << " " << Coordinate.z << endl;
    }

    p3d_File.close();
    return 0;
}
