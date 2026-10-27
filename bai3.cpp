//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <climits>
//#include <iomanip>
#include<bits/stdc++.h>
using namespace std;

const int MAX = 100;
const int INF = INT_MAX;

struct Graph {
    int n;
    int A[MAX][MAX];
};

void Nhap(Graph &G, const string& filename) {
    ifstream file("graph.txt");
    if (!file.is_open()) {
        cout << "Loi: Khong the mo file " << filename << "\n";
        exit(1);
    }

    if (!(file >> G.n)) {
        cout << "Loi doc so dinh.\n";
        file.close();
        exit(1);
    }

    for (int i = 0; i < G.n; i++) {
        for (int j = 0; j < G.n; j++) {
            file >> G.A[i][j];
            if (i != j && G.A[i][j] == 0) {
                G.A[i][j] = INF;
            }
        }
    }
    file.close();
}

void HienThi(const Graph& G) {
    cout << "Ma tran trong so cua do thi (" << G.n << " dinh):\n";
    for (int i = 0; i < G.n; i++) {
        for (int j = 0; j < G.n; j++) {
            if (G.A[i][j] == INF) {
                cout << setw(4) << "INF ";
            } else {
                cout << setw(4) << G.A[i][j] << " ";
            }
        }
        cout << "\n";
    }
}

void TimDuongDi(const Graph& G, int u, int v) {
    int start = u - 1; 
    int end = v - 1;
    
    if (start < 0 || start >= G.n || end < 0 || end >= G.n) return;

    vector<int> distance(G.n, INF);
    vector<int> visited(G.n, 0);
    vector<int> previous(G.n, -1);

    distance[start] = 0;

    for (int i = 0; i < G.n - 1; i++) {
        int minDistance = INF;
        int u_index = -1;

        for (int j = 0; j < G.n; j++) {
            if (!visited[j] && distance[j] <= minDistance) {
                minDistance = distance[j];
                u_index = j;
            }
        }

        if (u_index == -1 || minDistance == INF) break;
        visited[u_index] = 1;

        for (int v_index = 0; v_index < G.n; v_index++) {
            if (!visited[v_index] && G.A[u_index][v_index] != INF && 
                distance[u_index] != INF && 
                distance[u_index] + G.A[u_index][v_index] < distance[v_index]) {
                distance[v_index] = distance[u_index] + G.A[u_index][v_index];
                previous[v_index] = u_index;
            }
        }
    }

    if (distance[end] == INF) {
        cout << "\nKhong co duong di tu V" << u << " den V" << v << "\n";
    } else {
        cout << "\nKhoang cach ngan nhat tu V" << u << " den V" << v << " la: " << distance[end] << "\n";
        vector<int> path;
        int curr = end;
        while (curr != -1) {
            path.push_back(curr);
            curr = previous[curr];
        }
        cout << "Duong di: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << "V" << path[i] + 1;
            if (i > 0) cout << " -> ";
        }
        cout << "\n";
    }
}

int main() {
    Graph G;
    Nhap(G, "Grap.txt");
    HienThi(G);
    
    cout << "\n--- Tim duong di tu V1 den V6 ---\n";
    TimDuongDi(G, 1, 6);
    
    return 0;
}
