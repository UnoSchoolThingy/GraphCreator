#include <iostream>
#include <cstring>
#include <limits>
#include <vector>
#include <queue>
#include <set>
#include <map>

using std::cout;

struct Edge {
  struct Vertex* e1, *e2;
  float weight;

  Edge() {
    memset(this, 0x0, sizeof(Edge));
  }

  Edge(Vertex* e1, Vertex* e2, float weight) {
    this->e1 = e1;
    this->e2 = e2;
    this->weight = weight;
  }

  Vertex* getOtherEnd(Vertex* v) {
    return (v == e1) ? e2 : e1;
  }
};

struct Vertex { // basically a node
  char label[50];
  std::set<Edge*> edges;

  Vertex(char* label) {
    strcpy(this->label, label);
  }

  // Make a new edge and connect it 
  void addEdge(Vertex* otherEnd, float weight) {
    Edge* edge = new Edge(this, otherEnd, weight);
    edges.insert(edge);
    otherEnd->edges.insert(edge);
  }

  
  
  ~Vertex() {
    for (Edge* e : edges) { // Go through all the edges and get rid of them 
      e->getOtherEnd(this)->deleteEdge(e);
      delete e;
    }
  }
};

struct TraversalInfo {
  float dist = std::numeric_limits<float>::max(); // Distance from source to this node 
  Vertex* cameFrom = nullptr;
};

struct Graph {
  std::vector<Vertex*> vertices;

  void addVertex(char* name) {
    vertices.push_back(new Vertex(name));
  }


  inline bool empty() {
    return vertices.empty();
  }

  Vertex* findVertex(char* label) {
    for (auto v : vertices) {
      if (strcmp(v->label, label) == 0) return v;
    }
    return nullptr;
  }

  // Add an edge with two vertex labels and weight 
  bool addEdge(char* v1n, char* v2n, float weight) {
    Vertex* v1 = findVertex(v1n);
    Vertex* v2 = findVertex(v2n);
    if (!v1 || !v2) return false;
    v1.addEdge(v2, weight);
    return true;
  }

  bool removeEdge(char* v1n, char* v2n) {
    Vertex* v1 = findVertex(v1n);
    Vertex* v2 = findVertex(v2n);
    if (!v1 || !v2) return false;
    for (Edge* e : v1->edges) {
      if (e->getOtherSide(v1) == v2) { // Found edge
	
	return true;
      }
    }
    return false;
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
