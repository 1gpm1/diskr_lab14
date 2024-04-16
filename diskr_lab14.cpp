#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class GraphRelations {
private:
    int n; // number of vertices
    std::vector<std::vector<bool>> adjMatrix; // adjacency matrix

public:
    GraphRelations(const std::string& filename) {
        std::ifstream file(filename);
        file >> n;
        adjMatrix.resize(n, std::vector<bool>(n, false));
        int m;
        file >> m;
        for (int i = 0; i < m; ++i) {
            int v, u;
            file >> v >> u;
            v--; // Adjust to 0-based indexing
            u--;
            adjMatrix[v][u] = true;
        }
        file.close();
    }

    bool isSymmetric() {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (adjMatrix[i][j] != adjMatrix[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isTransitive() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adjMatrix[i][j]) {
                    for (int k = 0; k < n; ++k) {
                        if (adjMatrix[j][k] && !adjMatrix[i][k]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    GraphRelations gr("graph.txt");
    std::cout << "Is symmetric: " << (gr.isSymmetric() ? "true" : "false") << std::endl;
    std::cout << "Is transitive: " << (gr.isTransitive() ? "true" : "false") << std::endl;
    return 0;
}
