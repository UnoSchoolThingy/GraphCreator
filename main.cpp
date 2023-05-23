#include "Graph.h"
#include "Utils.h"

using namespace std;

int main() {
  Graph graph;
  char in[35];
  while (true) {
    cout << "Enter command (ADDV, ADDE, DELV, DELE, PRINT): ";
    cin >> in;
    if (Utils::chkcmd(in, "addv")) {

    }
  }
  return 0;
}
