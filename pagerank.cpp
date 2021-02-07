#include "digraph.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#define ALPHA 0.9
#define STEPS 100000000

// argv でやる必要もない気がしている
// #define GRAPH_FILE "simple.digraph"
#define GRAPH_FILE "p2p-Gnutella04.txt"

Digraph read_graph(std::string path)
{
    std::ifstream file(path);
    if (!file.good())
        exit(-1);

    Digraph digraph;

    // ファイルには # foo information 的なコメントアウトされた別の情報は含まれないとする
    int u, v;
    // エッジの追加
    while (file >> u >> v)
        digraph.add_edge(u, v);

    file.close();

    return digraph;
}

int main()
{
    // graph ファイルから読み込んで Digraph クラスを完成させる
    Digraph digraph = read_graph(GRAPH_FILE);
    std::vector<int> vertices = digraph.get_vertices();
    std::sort(vertices.begin(), vertices.end());

    // 到達回数をカウントする連想配列
    std::unordered_map<int, int> counts; // <id, count>
    for (int vertex : vertices)
        counts[vertex] = 0;

    // 乱数生成器
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_real_distribution<> rand_double(0, 1.0);
    std::uniform_int_distribution<> rand_vertices(0, digraph.get_num_vertices() - 1);

    // どうせ始点固定したって同じ PageRank になるだろ？みたいなお気持ちもありつつ
    // 始点をランダムに決定
    int random_index = rand_vertices(engine);
    int vertex = vertices[random_index];

    for (int i = 0; i < STEPS; ++i) {
        int next_index;

        if (digraph.get_degree(vertex) == 0) {
            // Dangling Node だったらランダムなノードへ遷移
            next_index = rand_vertices(engine); // ランダムなノードへ遷移
            vertex = vertices[next_index];
        } else if (rand_double(engine) > ALPHA) {
            // 上と or してもいいけど、こっちのほうが論理としては綺麗だと思う
            next_index = rand_vertices(engine); // ランダムなノードへ遷移
            vertex = vertices[next_index];
        } else {
            std::uniform_int_distribution<> rand_neighbors(0, digraph.get_degree(vertex) - 1);
            next_index = rand_neighbors(engine); // 近所のどれかへ遷移
            vertex = digraph.get_neighbors(vertex)[next_index];
        }
        counts[vertex]++; // 到達したノードのカウントをインクリメント
    }

    for (int vertex : vertices)
        std::cout << vertex << ": " << (double)counts[vertex] / STEPS << std::endl;

    return 0;
}