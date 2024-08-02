#include "searchmodel.h"

bool SearchModel::check(int x, int y) {
    return !(x < 0 || x >= M || y < 0 || y >= N);
}

void SearchModel::start(int i) {
    if (running) return;
    running = true;

    if (modelThread.joinable()) modelThread.join();
    modelThread = std::thread(&SearchModel::work, this, i);
 }

void SearchModel::work(int i) {
    switch(i) {
        case 1:
            wilson();
            break;
        case 2:
            dfs_solver(0, 0);
            break;
        case 3:
            dijkstra(0, 0);
            break;
        case 4:
            break;
        default:
            break;
    }
    for (auto &row: vis)
        std::fill(row.begin(), row.end(), false);
    running = false;
}

void SearchModel::dfs_generator(int x = -1, int y = -1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    if (x == -1 && y == -1) x = rand() % M, y = rand() % N;
    if (check(x, y) || vis[x][y]) return;

    vis[x][y] = true;
    colors[x][y] = MyColor::cornflower_blue;

    std::ranges::shuffle(idx, g);
    for (int i : idx) {
        int nx = x + d[i][0], ny = y + d[i][1];
        if (check(nx, ny) || vis[nx][ny]) continue;

        int j = (i + 2) % 4;
        grid[x][y].ok[i] = grid[nx][ny].ok[j] = true;
        colors[nx][ny] = MyColor::azure;

        dfs_generator(nx, ny);
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
            if (check(nx, ny) || vis[nx][ny]) continue;

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
            // std::this_thread::sleep_for(std::chrono::milliseconds(1));

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
                pre.clear();
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

bool SearchModel::dfs_solver(int x, int y) {
    if (!check(x, y) || vis[x][y]) 
        return false;

    vis[x][y] = true;
    colors[x][y] = MyColor::azure;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    if (x == M - 1 && y == N - 1) {
        colors[x][y] = sf::Color::Green;
        return true;
    }

    for (int i: idx) {
        if (grid[x][y].ok[i])
            if (dfs_solver(x + d[i][0], y + d[i][1])) {
                colors[x][y] = sf::Color::Green;
                return true;
            }
    }
    colors[x][y] = sf::Color::Red;
    return false;
}

void SearchModel::dijkstra(int x, int y) {
    std::map<std::array<int, 2>, std::array<int, 2>> pre;
    std::vector dist(M, std::vector<int>(N, M * N + 1));
    std::priority_queue<std::array<int, 3>, std::vector<std::array<int, 3>>, std::greater<>> q;

    q.push({0, x, y});
    dist[x][y] = 0;
    pre[{x, y}] = {x, y};

    while (!q.empty()) {
        auto [now, x, y] = q.top();
        q.pop();

        vis[x][y] = true;
        colors[x][y] = MyColor::azure;
        if (x == M - 1 && y == N - 1) break;

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        for (int i: idx) {
            if (grid[x][y].ok[i]) {
                int nx = x + d[i][0], ny = y + d[i][1];

                if (dist[nx][ny] > now + 1 && !vis[nx][ny]) {
                    pre[{nx, ny}] = {x, y};
                    dist[nx][ny] = now + 1;
                    q.push({dist[nx][ny], nx, ny});
                }
            }
        }

        colors[x][y] = MyColor::turquoise;
    }
    x = M - 1, y = N - 1;
    while (x != pre[{x, y}][0] || y != pre[{x, y}][1]) {
        colors[x][y] = sf::Color::Green;
        int tx = x, ty = y;
        x = pre[{tx, ty}][0], y = pre[{tx, ty}][1];
    }
    colors[0][0] = sf::Color::Green;
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
