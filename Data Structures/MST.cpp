#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
typedef vector<PII> VPII;

int Prims_MST(int source_node, vector<VPII> &graph)
{
    // minimum heap:
    // carries PII <cost, next node>
    // container is a vector of PII
    // function: minimum heap: give it the function greater, maximum: default (no function needed)
    priority_queue<PII, vector<PII>, greater<PII>> q;

    // push the source_node with weight = 0
    q.push(make_pair(0, source_node));

    // all are false by default
    vector<bool> added(graph.size(), false);

    // initialize cost with zero
    int mst_cost = 0;

    while (!q.empty())
    {
        // get smallest next edge

        PII item;
        item = q.top();
        q.pop();

        int node = item.second;
        int cost = item.first;

        // if the node isn't added yet, add it to the mst
        if (!added[node])
        {
            mst_cost += cost;
            added[node] = true;
        }

        // add the edges to the non added (visited) nodes
        for (auto &pair_cost_node : graph[node])
        {
            int adj_node = pair_cost_node.second;
            if (!added[adj_node])
            {
                q.push(pair_cost_node);
            }
        }
    }
    return mst_cost;
}

int main(void)
{

    // (Graph) Adjacency List

    // Outgoing edges from the node: <cost, adjacent_node> in graph 1
    VPII from_node_zero_in_graph_1 = {{1, 1}, {2, 2}, {1, 3}, {1, 4}, {2, 5}, {1, 6}};
    VPII from_node_one_in_graph_1 = {{1, 0}, {2, 2}, {2, 6}};
    VPII from_node_two_in_graph_1 = {{2, 0}, {2, 1}, {1, 3}};
    VPII from_node_three_in_graph_1 = {{1, 0}, {1, 2}, {2, 4}};
    VPII from_node_four_in_graph_1 = {{1, 0}, {2, 3}, {2, 5}};
    VPII from_node_five_in_graph_1 = {{2, 0}, {2, 4}, {1, 6}};
    VPII from_node_six_in_graph_1 = {{1, 0}, {2, 2}, {1, 5}};

    int num_nodes = 7;

    vector<VPII> graph_1;
    graph_1.resize(num_nodes);
    graph_1[0] = from_node_zero_in_graph_1;
    graph_1[1] = from_node_one_in_graph_1;
    graph_1[2] = from_node_two_in_graph_1;
    graph_1[3] = from_node_three_in_graph_1;
    graph_1[4] = from_node_four_in_graph_1;
    graph_1[5] = from_node_five_in_graph_1;
    graph_1[6] = from_node_six_in_graph_1;

    cout << Prims_MST(0, graph_1) << "\n";
}