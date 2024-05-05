// In the name of Allah

#include <bits/stdc++.h>

using namespace std;

const int MOD = 89779;

int main()
{
    /*vector <int> s = {8, 10, 13, 11, 15};
    for (auto &u : s)
        u = -u;
    vector <pair<int, int>> edge;
    for (int i = 1; i < s.size(); i++)
        edge.push_back({s[i - 1], s[i]});
    edge.push_back({s[0], s[(int)s.size() - 1]});
    for (auto &[u, v] : edge)
    {
        int a = u, b = v;
        u = min(a, b), v = max(a, b);
        cout << u << ' ' << v << endl;
    }
    int ans = 0;
    for (int i = 0; i < edge.size(); i++)
    {
        for (int j = i + 2; j < edge.size(); j++)
        {
            if (i == 0 && j == edge.size() - 1)
                continue;
            int u1 = edge[i].first, u2 = edge[i].second;
            int v1 = edge[j].first, v2 = edge[j].second;
            bool a = (u1 < v1 && v1 < u2);
            bool b = (u1 < v2 && v2 < u2);
            cout << u1 << ' ' << u2 << ", ";
            cout << v1 << ' ' << v2 << " : " << a << ' ' << b << endl;;
            if (a ^ b)
                ans++;
        }
    }
    cout << ans << endl;*/
    vector <int> a, b;
    a.push_back(1);
    for (int i = 0; i < 5; i++)
    {
        for (auto u : a)
        {
            int s = __builtin_popcount(u);
            s %= 2;
            b.push_back(2 * u + s);
            b.push_back(2 * u + 1 - s);
        }
        a = b;
        b.clear();
    }
}