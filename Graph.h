#include <iostream>
#include <cstring>
#include <limits>
#include <vector>
#include <queue>
#include <set>
#include <map>

using std::cout;

struct Edge {
  struct Vertex* dst;
  float weight;

  Edge() {
    memset(this, 0x0, sizeof(Edge));
  }

  Edge(struct Vertex* dst, float weight) {
    this->dst = dst;
    this->weight = weight;
  }
};

struct Vertex { // basically a node
  char label[50];
  std::vector<Edge> edges;

  Vertex(char* label) {
    strcpy(this->label, label);
  }
};

struct TraversalInfo {
  float dist = std::numeric_limits<float>::max(); // Distance from source to this node 
  Vertex* cameFrom = nullptr;
};

struct Graph {
  std::vector<Vertex*> vertices;

  inline bool empty() {
    return vertices.empty();
  }

  Vertex* findVertex(char* label) {
    for (auto v : vertices) {
      if (strcmp(v->label, label) == 0) return v;
    }
    return nullptr;
  }

  // Dijkstra thingy 
  // https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
  void findPath(char* begin, char* end) { 
    Vertex* start = findVertex(begin);
    Vertex* goal = findVertex(end);
    if (start == nullptr || goal == nullptr) return;
    std::map<Vertex*, TraversalInfo> info;
    info[start].dist = 0.f;
    
    auto cmp = [&info](Vertex* a, Vertex* b) -> bool {
      return info[a].dist < info[b].dist;
    };

    std::set<Vertex*, decltype(cmp)> epicSet(cmp);

    for (auto v : vertices) {
      epicSet.insert(v);
    }

    while (!epicSet.empty()) {
      Vertex* u = *epicSet.begin();
      epicSet.erase(epicSet.begin());

      if (u == goal) { // Reached the goal! 
	cout << "Path found, too insane!\n";
	// Reconstruct path (will do later) 
      }

      for (Edge& e : u->edges) {
	float alt = info[u].dist + e.weight;
	TraversalInfo& vInfo = info[e.dst]; // e.dst is like v from the wikipedia thingy 
	if (alt < vInfo.dist) {
	  vInfo.dist = alt;
	  vInfo.cameFrom = u;
	}
      }
      
    }
    
  };
};
