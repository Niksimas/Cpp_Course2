#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

struct Point {int index, p;};
struct Conn {
    int start, end; int mass;
    bool operator<(const Conn& other) const {
        return mass < other.mass;
    }
};

class Graph {
private:
    vector<Point> points;
    vector<Conn> connects;
public:
    Graph() {
        int kol_point=0, start, end, mass;
        ifstream file("../4--11-03-24/input.txt");
        if (file.is_open()) {
            file >> kol_point;
            for (int i=0; i< kol_point; i++){points.emplace_back(Point{i, -1});}
            while (file.get()) {
                file.unget();
                file >> start >> end >> mass;
                if(!connects.empty()) {
                    if(connects[connects.size()-1].start == start && connects[connects.size()-1].end == end){break;}
                }
                connects.emplace_back(Conn{start, end, mass});
            }
        }else {
            cout << "Файл не найден!\n";
        }
        file.close();
    }

    void print_points() {
        for (const Point& point : points) {
            cout << point.index << " ";
        }
        cout << endl;
    }
    void print_vertex() {
        for (const Conn& c : connects) {
            cout << "start: " << c.start << " end: " << c.end << " mass:  " << c.mass << endl;
        }
    }

    int find(vector<int>& parent, int i) {
        if (parent[i] != i) {
            parent[i] = find(parent, parent[i]);
        }
        return parent[i];
    }

    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }


    void kruskal() {
        vector<Conn> mst;
        int num_points = points.size();
        vector<int> parent(num_points);
        vector<int> rank(num_points, 0);
        for (int i = 0; i < num_points; ++i) {
            parent[i] = i;
        }
        sort(connects.begin(), connects.end());
        for (const Conn& edge : connects) {
            int root1 = find(parent, edge.start);
            int root2 = find(parent, edge.end);
            if (root1 != root2) {
                mst.push_back(edge);
                unionSets(parent, rank, root1, root2);
            }
            if (mst.size() == num_points - 1) {break;}
        }
        cout << "Метод Крусаклы\nСвязи необходимые для остовного дерева:" << endl;
        for (const Conn& edge : mst) {
            cout << "start: " << edge.start << " end: " << edge.end << " mass: " << edge.mass << endl;
        }
    }

    void prim() {
        int num_points = points.size();
        if (num_points == 0) return;
        vector<bool> inMST(num_points, false);
        vector<Conn> mst;
        auto compare = [](Conn& a, Conn& b) {
            return a.mass > b.mass;
        };
        priority_queue<Conn, vector<Conn>, decltype(compare)> pq(compare);
        inMST[0] = true;
        for (const Conn& edge : connects) {
            if (edge.start == 0 || edge.end == 0) {
                pq.push(edge);
            }
        }
        while (!pq.empty() && mst.size() < num_points - 1) {
            Conn edge = pq.top();
            pq.pop();
            if (inMST[edge.start] && inMST[edge.end]) continue;
            mst.push_back(edge);
            int new_vertex = inMST[edge.start] ? edge.end : edge.start;
            inMST[new_vertex] = true;
            for (const Conn& next_edge : connects) {
                if ((next_edge.start == new_vertex && !inMST[next_edge.end]) ||
                    (next_edge.end == new_vertex && !inMST[next_edge.start])) {
                    pq.push(next_edge);
                    }
            }
        }
        cout << "Алгоритм Прима\nНеобходимые связи для остовного дерева:" << endl;
        for (const Conn& edge : mst) {
            cout << "start: " << edge.start << " end: " << edge.end << " mass: " << edge.mass << endl;
        }
    }
};

int main() {
    Graph graph;
    // graph.print_points();
    // graph.print_vertex();
    cout << "\n";
    graph.kruskal();
    cout << "\n";
    graph.prim();
    return 0;
}



