#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include "model.h"
#include <ranges>
#include <queue>
#include <array>

class SearchModel: public Model {
private:
    int M, N;

    struct wall {
        bool ok[4] = {false, false, false, false};
    };

    std::vector<std::vector<wall>> grid;
    std::vector<std::vector<sf::Color>> colors;
    std::vector<std::vector<bool>> vis;
    std::vector<std::array<int, 2>> d = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    std::vector<int> idx = {0, 1, 2, 3};

public:
    SearchModel(int M, int N): M{M}, N{N} {
        grid.resize(M, std::vector<wall>(N));
        colors.resize(M, std::vector<sf::Color>(N, MyColor::midnight_blue));
        vis.resize(M, std::vector<bool>(N, false));
    }

    void start(int i) override;

    void dfs(int x, int y);
    void prim();
    void wilson();

    // getter
    std::vector<int> getSize() const;
    sf::Color getColor(int x, int y) const;
    wall& getWall(int x, int y);
};

#endif
