#include <cstdint>
#include <string>
class Mesh
{
public:
    Mesh();
    ~Mesh();
    void loadMesh(const std::string &fileName);
    void renderMesh();

private:
    uint8_t ndim = 0;
    uint8_t num_node = 0; // number of nodes
    uint8_t Imax = 0;     // number of nodes in x-direction
    uint8_t Jmax = 0;     // number of nodes in y-direction
    uint8_t Kmax = 0;     // number of nodes in z-direction
};
