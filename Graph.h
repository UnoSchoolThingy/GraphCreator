#include <iostream>
#include <cstring>
#include <limits>
#include <vector>
#include <queue>
#include <set>
#include <map>

using std::cout; using std::endl;

struct Edge {
  struct Vertex* e1, *e2;
  int weight;

  Edge() {
    memset(this, 0x0, sizeof(Edge));
  }

  Edge(Vertex* e1, Vertex* e2, int weight) {
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
  void addEdge(Vertex* otherEnd, int weight) {
    Edge* edge = new Edge(this, otherEnd, weight);
    edges.insert(edge);
    otherEnd->edges.insert(edge);
  }

  // Check if connected
  Edge* getConnectingEdge(Vertex* v) {
    for (Edge* e : edges) {
      if (e->getOtherEnd(v) == v) return e;
    }
    return nullptr;
  }
  
  ~Vertex() {
    for (Edge* e : edges) { // Go through all the edges and get rid of them 
      e->getOtherEnd(this)->edges.erase(e);
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
  bool addEdge(char* v1n, char* v2n, int weight) {
    Vertex* v1 = findVertex(v1n);
    Vertex* v2 = findVertex(v2n);
    if (!v1 || !v2) return false;
    v1->addEdge(v2, weight);
    return true;
  }

  bool removeEdge(char* v1n, char* v2n) {
    Vertex* v1 = findVertex(v1n);
    Vertex* v2 = findVertex(v2n);
    if (!v1 || !v2) return false;
    for (Edge* e : v1->edges) {
      if (e->getOtherEnd(v1) == v2) { // Found edge
	v1->edges.erase(e);
	v2->edges.erase(e);
	delete e;
	return true;
      }
    }
    return false;
  }

  bool removeVertex(char* label) { // Terrible code but I was done by the time I realized so it's staying 
    Vertex* v = findVertex(label);
    if (v == nullptr) return false;
    // Vertex destructor handles edges
    for (int i = 0; i < vertices.size(); i++) {
      if (v == vertices.at(i)) {
	vertices.erase(vertices.begin() + i);
	delete v;
	return true;
      }
    }
    return false;
  }
  
  void print() {
    // Print key 
    cout << "Key:\n";
    int size = vertices.size();
    for (int i = 0; i < size; i++) {
      cout << (i < 10 ? "00" : "0") << i << " | " << vertices.at(i)->label << endl;
    }
    // Print adjacency table 
    cout << "TABLE:\n";
    cout << "   |";
    for (int i = 0; i < size; i++) cout << (i < 10 ? "00" : "0") << i << '|';
    cout << endl;
    for (int y = 0; y < size; y++) {
      cout << (y < 10 ? "00" : "0") << y << '|';
      for (int x = 0; x < size; x++) {
	if (x == y) {
	  cout << "---|";
	  continue;
	}
	Edge* e = vertices.at(x)->getConnectingEdge(vertices.at(y));
	if (e != nullptr) {
	  cout << (e->weight < 10 ? "00" : "0") << e->weight << '|';
	}
	else cout << "INF|";
      }
      cout << endl;
    }
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
	return;
      }

      for (Edge* e : u->edges) {
	float alt = info[u].dist + e->weight;
	TraversalInfo& vInfo = info[e->getOtherEnd(u)]; // e.dst is like v from the wikipedia thingy 
	if (alt < vInfo.dist) {
	  vInfo.dist = alt;
	  vInfo.cameFrom = u;
	}
      }
      
    }
    cout << "No path found!\n";
  };
};
