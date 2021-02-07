#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Digraph {
private:
    // 頂点集合
    std::unordered_set<int> vertices;

    // 隣接リスト
    // unordered_map<int, unordered_map<int>> も良いと思うが、今回はシンプルのため
    // vector<vector<int>> も良いと思うが、vector の resize が必要になりそうでつまづきやすいかなと思った
    // 一番簡単なのが unordered_map * vector な気がしている
    // エッジ (u, v) が存在するか？に答えるのには次数 d に対して O(d) かかるが、PageRank ではその場面はなさそう
    // これが必要十分と思う
    std::unordered_map<int, std::vector<int>> adjacency_list;

public:
    // --------------------------------------------------
    // セッター
    // --------------------------------------------------
    void add_vertex(int v)
    {
        // もしすでに頂点が登録済みなら、隣接リストの初期化を避けるため return
        if (has_vertex(v))
            return;
        vertices.insert(v);
        // 初期化したベクターの参照を渡す
        adjacency_list[v] = std::vector<int>();
    }

    // 頂点 s から頂点 t へのエッジを追加する
    // graph loop や multiple edge を許容する（実装を複雑にしないため）
    void add_edge(int s, int t)
    {
        if (!has_vertex(s))
            add_vertex(s);
        if (!has_vertex(t))
            add_vertex(t);

        adjacency_list[s].push_back(t);
    }

    // --------------------------------------------------
    // ゲッター
    // --------------------------------------------------

    bool has_vertex(int v)
    {
        return !(vertices.find(v) == vertices.end());
    }

    std::vector<int> get_vertices()
    {
        // 必ずしもノード ID 順にはソートされていない
        std::vector<int> vertices_vector;
        for (int u : vertices)
            vertices_vector.push_back(u);

        return vertices_vector;
    }

    int get_num_vertices()
    {
        return vertices.size();
    }

    std::vector<int> get_neighbors(int v)
    {
        if (has_vertex(v))
            return adjacency_list[v];

        // もしそんな頂点が存在しなければ初期化したベクターを返す
        // この辺は好みの問題かもしれない
        return std::vector<int>();
    }

    int get_degree(int v)
    {
        if (has_vertex(v))
            return adjacency_list[v].size();

        // もしそんな頂点が存在しなければ-1を返す
        return -1;
    }
};