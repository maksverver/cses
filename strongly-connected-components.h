#ifndef STRONGLY_CONNECTED_COMPONENT_H_INCLUDED
#define STRONGLY_CONNECTED_COMPONENT_H_INCLUDED

#include <cassert>
#include <vector>
#include <utility>

// Tarjan's algorithm for finding Strongly Connected Components
// https://sci-hub.se/10.1137/0201010
//
// Given a directed graph as an adjacency list, partitions the vertices into
// strongly connected components, which are returned in reverse topological
// order (i.e., if a one component is reachable from another, then the former
// appears before the latter in the result).
//
// This can also be modified to return the components one-by-one.
static std::vector<std::vector<int>>
CalculateStronglyConnectedComponents(const std::vector<std::vector<int>> &adj) {
  using std::pair;
  using std::vector;

  struct Impl {
    const vector<vector<int>> &adj;
    vector<vector<int>> &components;
    vector<int> number;
    vector<int> lowlink;
    vector<int> stack_pos;
    int next_number = 0;
    vector<int> stack;

    Impl(const vector<vector<int>> &adj, vector<vector<int>> &components) :
        adj(adj), components(components), number(adj.size(), -1),
        lowlink(adj.size(), -1), stack_pos(adj.size(), -1) {
    }

    void Run() {
      for (int v = 0; v < adj.size(); ++v) {
        if (number[v] == -1) Dfs(v);
        assert(stack.empty());
      }
    }

    // TODO: change this to not actually use recursion!
    void Dfs(int v) {
      number[v] = lowlink[v] = next_number++;
      stack_pos[v] = stack.size();
      stack.push_back(v);
      for (int w : adj[v]) {
        if (number[w] == -1) {
          Dfs(w);
          lowlink[v] = std::min(lowlink[v], lowlink[w]);
        } else if (stack_pos[w] != -1) {
          lowlink[v] = std::min(lowlink[v], number[w]);
        }
      }
      if (lowlink[v] == number[v]) {
        // New strongly-connected component found!
        int pos = stack_pos[v];
        components.push_back(vector(stack.begin() + pos, stack.end()));
        while (stack.size() > pos) {
          stack_pos[stack.back()] = -1;
          stack.pop_back();
        }
      }
    }
  };

  vector<vector<int>> components;
  Impl(adj, components).Run();
  return components;
}

#endif  // ndef STRONGLY_CONNECTED_COMPONENT_H_INCLUDED
