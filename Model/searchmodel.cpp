#include "searchmodel.h"

void SearchModel::start(int i) {
    if (running) return;
    running = true;
    if (modelThread.joinable()) modelThread.join();
    modelThread = std::thread(&SearchModel::prim, this, 0, 0);
}

void SearchModel::dfs(int x, int y) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if (x < 0 || x >= M || y < 0 || y >= N || vis[x][y])
        return;
    vis[x][y] = true;
    std::vector<int> idx = {0, 1, 2, 3};
    std::ranges::shuffle(idx, g);
    colors[x][y] = sf::Color(0, 51, 102);
    for (int i: idx) {
        int nx = x + d[i][0], ny = y + d[i][1];
        if (nx < 0 || nx >= M || ny < 0 || ny >= N || vis[nx][ny])
            continue;
        int j = (i + 2) % 4;
        grid[x][y].ok[i] = grid[nx][ny].ok[j] = true;
        colors[nx][ny] = sf::Color::White;
        dfs(nx, ny);
    }
}

void SearchModel::prim(int x, int y) {
    std::queue<std::array<int, 2>> q;
    q.push({x, y});
    vis[x][y] = true;
    while (!q.empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        auto [x, y] = q.front(); q.pop();
        colors[x][y] = sf::Color(0, 51, 102);
        for (auto [dx, dy]: d) {
            int nx = x + dx, ny = y + dy;
            if (nx < 0 || nx >= M || ny < 0 || ny >= N || vis[nx][ny])
                continue;
           vis[nx][ny] = true;
            q.push({nx, ny});
        }
    }
}

std::vector<int> SearchModel::getSize() const {
    return {M, N};
}

sf::Color SearchModel::getColor(int x, int y) const {
    return colors[x][y];
}

SearchModel::wall& SearchModel::getWall(int x, int y) {
    return grid[x][y];
}
