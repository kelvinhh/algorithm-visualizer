#include "searchmodel.h"

void SearchModel::start(int i) {
    if (running) return;
    running = true;
    if (modelThread.joinable()) modelThread.join();
    modelThread = std::thread(&SearchModel::prim, this);
}

void SearchModel::dfs(int x = -1, int y = -1) {
    if (x == -1 && y == -1)
        x = rand() % M, y = rand() % N;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if (x < 0 || x >= M || y < 0 || y >= N || vis[x][y])
        return;
    vis[x][y] = true;
    std::ranges::shuffle(idx, g);
    colors[x][y] = MyColor::cornflower_blue;
    for (int i: idx) {
        int nx = x + d[i][0], ny = y + d[i][1];
        if (nx < 0 || nx >= M || ny < 0 || ny >= N || vis[nx][ny])
            continue;
        int j = (i + 2) % 4;
        grid[x][y].ok[i] = grid[nx][ny].ok[j] = true;
        colors[nx][ny] = MyColor::azure;
        dfs(nx, ny);
    }
}

void SearchModel::prim() {
    int x = rand() % M, y = rand() % N;
    std::vector<std::array<int, 2>> points;
    points.push_back({x, y});
    vis[x][y] = true;
    colors[x][y] = MyColor::azure;
    while (!points.empty()) {
        int select_idx = rand() % points.size();
        auto [x, y] = points[select_idx];
        points.erase(points.begin() + select_idx);
        std::ranges::shuffle(idx, g);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        for (int i: idx) {
            int nx = x + d[i][0], ny = y + d[i][1];
            if (nx < 0 || nx >= M || ny < 0 || ny >= N || vis[nx][ny])
                continue;
            vis[nx][ny] = true;
            int j = (i + 2) % 4;
            grid[x][y].ok[i] = grid[nx][ny].ok[j] = true;
            colors[nx][ny] = MyColor::turquoise;
            points.push_back({nx, ny});
        }
        colors[x][y] = MyColor::cornflower_blue;
    }
}

void SearchModel::wilson() {
    int x = rand() % M, y = rand() % N;
    vis[x][y] = true;
    std::vector vis2(M, std::vector<bool>(N, false));
    std::vector<std::array<int, 3>> pre;
    int remain = M * N - 1;
    while (remain) {
        int i = rand() % 4;
        int nx = x + d[i][0], ny = y + d[i][1];
        if (nx < 0 || nx >= M || ny < 0 || ny >= N)
            continue;
        if (vis[nx][ny]) {
            // add to maze
            vis2.resize(M, std::vector<bool>(N, false));
        } else if (vis2[nx][ny]) {
            auto [tx, ty, dir] = pre[pre.size() - 1];
        } else {
            pre.push_back({x, y, i});
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
