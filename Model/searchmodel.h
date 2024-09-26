#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include <array>
#include <queue>
#include <ranges>

#include "model.h"

class SearchModel : public Model {
   private:
    int M, N, grid_size;

    struct wall {
        bool ok[4] = {false, false, false, false};
    };

    std::vector<std::vector<wall>> grid;
    std::vector<std::vector<sf::Color>> colors;
    std::vector<std::vector<bool>> vis;
    std::vector<std::array<int, 2>> d = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    std::vector<int> idx = {0, 1, 2, 3};

   public:
    SearchModel(int width, int height, int grid_size) : grid_size{grid_size} {
        M = width / grid_size;
        N = height / grid_size;
        grid.resize(M, std::vector<wall>(N));
        colors.resize(M, std::vector<sf::Color>(N, sf::Color::Black));
        vis.resize(M, std::vector<bool>(N, false));
    }

    bool check(int x, int y);
    void start(int i) override;
    void work(int i);

    // maze generator
    void dfs_generator(int x, int y);
    void prim();
    void wilson();

    // maze solver
    bool dfs_solver(int x, int y);
    void dijkstra(int x, int y);
    void Astar(int x, int y);

    void resetColor();
    void resetAll();

    // getter
    std::vector<int> getSize() const;
    sf::Color getColor(int x, int y) const;
    wall& getWall(int x, int y);
};

#endif
