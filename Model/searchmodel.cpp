#include "searchmodel.h"

void SearchModel::start(int i) {
    if (running) return;
    running = true;

    if (modelThread.joinable()) modelThread.join();
    modelThread = std::thread(&SearchModel::wilson, this);
}

void SearchModel::dfs(int x = -1, int y = -1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    if (x == -1 && y == -1) x = rand() % M, y = rand() % N;
    if (x < 0 || x >= M || y < 0 || y >= N || vis[x][y]) return;

    vis[x][y] = true;
    colors[x][y] = MyColor::cornflower_blue;

    std::ranges::shuffle(idx, g);
    for (int i : idx) {
        int nx = x + d[i][0], ny = y + d[i][1];
        if (nx < 0 || nx >= M || ny < 0 || ny >= N || vis[nx][ny]) continue;

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
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        std::ranges::shuffle(idx, g);
        for (int i : idx) {
            int nx = x + d[i][0], ny = y + d[i][1];
            if (nx < 0 || nx >= M || ny < 0 || ny >= N || vis[nx][ny]) continue;

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
    std::function<bool(int, int)> check = [&](int x, int y) -> bool {
        return !(x < 0 || x >= M || y < 0 || y >= N);
    };

    int x = rand() % M, y = rand() % N;
    int remain = M * N - 1;
    std::vector<std::array<int, 3>> pre;

    vis[x][y] = true;
    colors[x][y] = MyColor::cornflower_blue;

    while (remain) {
        std::vector walked(M, std::vector<bool>(N, false));
        bool walking = true;

        int nx = rand() % M, ny = rand() % N;
        while (vis[nx][ny]) nx = rand() % M, ny = rand() % N;

        while (walking) {
            colors[nx][ny] = MyColor::azure;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            int nxx, nyy, dir;
            walking = false;
            walked[nx][ny] = true;

            if (vis[nx][ny]) {
                remain -= pre.size();
                for (auto &[x, y, i] : pre) {
                    int j = (i + 2) % 4;
                    grid[x][y].ok[i] = grid[x + d[i][0]][y + d[i][1]].ok[j] =
                        true;
                    vis[x][y] = true;
                    colors[x][y] = MyColor::cornflower_blue;
                }
                colors[nx][ny] = MyColor::cornflower_blue;
                break;
            }

            std::ranges::shuffle(idx, g);
            for (int i : idx) {
                if (check(nx + d[i][0], ny + d[i][1])) {
                    nxx = nx + d[i][0], nyy = ny + d[i][1];
                    dir = i;
                    walking = true;
                    break;
                }
            }
            colors[nx][ny] = MyColor::turquoise;
            pre.push_back({nx, ny, dir});

            if (walked[nxx][nyy]) {
                while (!pre.empty()) {
                    int px = pre.back()[0], py = pre.back()[1];
                    colors[px][py] = MyColor::midnight_blue;
                    pre.pop_back();
                    if (px == nxx && py == nyy)
                        break;
                    walked[px][py] = false;
                }
            }

            nx = nxx, ny = nyy;
        }
    }
}

std::vector<int> SearchModel::getSize() const { 
    return {M, N, grid_size};
}

sf::Color SearchModel::getColor(int x, int y) const { 
    return colors[x][y]; 
}

SearchModel::wall &SearchModel::getWall(int x, int y) { 
    return grid[x][y]; 
}
