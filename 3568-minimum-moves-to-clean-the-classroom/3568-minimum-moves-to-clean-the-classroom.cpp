class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr, sc;
        vector<pair<int, int>> litter;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();
        if (k == 0) return 0;

        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            id[litter[i].first][litter[i].second] = i;
        }

        int masks = 1 << k;
        int fullMask = masks - 1;

        int total = m * n * masks;

        vector<int> best(total, -1);

        auto getId = [&](int r, int c, int mask) {
            return (r * n + c) * masks + mask;
        };

        queue<array<int, 4>> q;

        q.push({sr, sc, 0, energy});
        best[getId(sr, sc, 0)] = energy;

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, mask, e] = q.front();
                q.pop();

                if (mask == fullMask)
                    return moves;

                if (e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    if (classroom[nr][nc] == 'L')
                        nmask |= 1 << id[nr][nc];

                    if (classroom[nr][nc] == 'R')
                        ne = energy;

                    int idx = getId(nr, nc, nmask);

                    if (ne <= best[idx])
                        continue;

                    best[idx] = ne;
                    q.push({nr, nc, nmask, ne});
                }
            }

            moves++;
        }

        return -1;
    }
};