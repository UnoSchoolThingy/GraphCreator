#include "Graph.h"
#include "Utils.h"

using namespace std;

int main() {
  cout << "Hi, ADD/DEL V/E is add/delete edge (ADDV is add vertex)" << endl;
  Graph graph;
  char in[35], in2[35], in3[35];
  while (true) {
    cout << "Enter command (ADDV, ADDE, DELV, DELE, PATH, PRINT, QUIT): ";
    cin >> in;
    if (Utils::chkcmd(in, "addv")) { // Add a vertex 
      cout << "Enter vertex name: ";
      cin.ignore();
      cin.getline(in2, 35);
      graph.addVertex(in2);
      cout << "Added!\n";
    }
    else if (Utils::chkcmd(in, "adde")) {
      cout << "Enter vertex 1: ";
      cin.ignore();
      cin.getline(in2, 35);
      cout << "Enter vertex 2: ";
      cin.getline(in3, 35);
      int w;
      cout << "Enter edge weight: ";
      cin >> w;
      if (w > 999 || w < 1) cout << "Weight has to be between 1 and 999!\n";
      else cout << (graph.addEdge(in2, in3, w) ? "Added!" : "Couldn't add!") << endl;
    }
    else if (Utils::chkcmd(in, "delv")) {
      cout << "Enter vertex name: ";
      cin.ignore();
      cin.getline(in2, 35);
      cout << (graph.removeVertex(in2) ? "Removed!" : "No such vertex exists!") << endl;
    }
    else if (Utils::chkcmd(in, "dele")) {
      cin.ignore();
      cout << "Enter vertex 1: ";
      cin.getline(in2, 35);
      cout << "Enter vertex 2: ";
      cin.getline(in3, 35);
      cout << (graph.removeEdge(in2, in3) ? "Removed!" : "No such edge exists!") << endl;
    }
    else if (Utils::chkcmd(in, "path")) {
      cin.ignore();
      cout << "Enter vertex 1: ";
      cin.getline(in2, 35);
      cout << "Enter vertex 2: ";
      cin.getline(in3, 35);
      graph.findPath(in2, in3);
    }
    else if (Utils::chkcmd(in, "print")) graph.print();
    else if (Utils::chkcmd(in, "quit")) return 0;
    else cout << "Unrecognized command!\n";
  }
  return 0;
}
