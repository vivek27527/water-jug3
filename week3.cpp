#include <bits/stdc++.h>
using namespace std;

struct State {
    int a, b, c;
};

int capA = 8, capB = 5, capC = 3;
int target = 4;

set<tuple<int,int,int>> visited;

// Function to generate all possible next states
vector<State> getNextStates(State cur) {
    vector<State> next;
    int pour;

    // Fill operations
    next.push_back({capA, cur.b, cur.c});
    next.push_back({cur.a, capB, cur.c});
    next.push_back({cur.a, cur.b, capC});

    // Empty operations
    next.push_back({0, cur.b, cur.c});
    next.push_back({cur.a, 0, cur.c});
    next.push_back({cur.a, cur.b, 0});

    // Pour A->B
    pour = min(cur.a, capB - cur.b);
    next.push_back({cur.a - pour, cur.b + pour, cur.c});

    // Pour A->C
    pour = min(cur.a, capC - cur.c);
    next.push_back({cur.a - pour, cur.b, cur.c + pour});

    // Pour B->A
    pour = min(cur.b, capA - cur.a);
    next.push_back({cur.a + pour, cur.b - pour, cur.c});

    // Pour B->C
    pour = min(cur.b, capC - cur.c);
    next.push_back({cur.a, cur.b - pour, cur.c + pour});

    // Pour C->A
    pour = min(cur.c, capA - cur.a);
    next.push_back({cur.a + pour, cur.b, cur.c - pour});

    // Pour C->B
    pour = min(cur.c, capB - cur.b);
    next.push_back({cur.a, cur.b + pour, cur.c - pour});

    return next;
}

//////////////////////////////////////////////////////
// BFS SOLUTION
//////////////////////////////////////////////////////
void BFS() {
    cout << "BFS Solution:\n";
    queue<State> q;
    set<tuple<int,int,int>> visitedBFS;

    q.push({0,0,0});
    visitedBFS.insert({0,0,0});

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        cout << "(" << cur.a << "," << cur.b << "," << cur.c << ")\n";

        if (cur.a == target || cur.b == target || cur.c == target) {
            cout << "Goal reached using BFS!\n";
            return;
        }

        for (auto next : getNextStates(cur)) {
            auto t = make_tuple(next.a, next.b, next.c);
            if (!visitedBFS.count(t)) {
                visitedBFS.insert(t);
                q.push(next);
            }
        }
    }

    cout << "No solution using BFS.\n";
}

//////////////////////////////////////////////////////
// DFS SOLUTION
//////////////////////////////////////////////////////
bool DFS(State cur, set<tuple<int,int,int>> &visitedDFS) {
    auto t = make_tuple(cur.a, cur.b, cur.c);

    if (visitedDFS.count(t))
        return false;

    visitedDFS.insert(t);

    cout << "(" << cur.a << "," << cur.b << "," << cur.c << ")\n";

    if (cur.a == target || cur.b == target || cur.c == target) {
        cout << "Goal reached using DFS!\n";
        return true;
    }

    for (auto next : getNextStates(cur)) {
        if (DFS(next, visitedDFS))
            return true;
    }

    return false;
}

//////////////////////////////////////////////////////
// MAIN FUNCTION
//////////////////////////////////////////////////////
int main() {
    BFS();

    cout << "\nDFS Solution:\n";
    set<tuple<int,int,int>> visitedDFS;
    DFS({0,0,0}, visitedDFS);

    return 0;
}
