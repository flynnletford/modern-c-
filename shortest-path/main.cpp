#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

struct path {
    int currentNode;
    std::vector<int> nodes;
};

int main() {

    std::unordered_map<int, std::vector<int>> graph;

    int startNode = 0;
    int targetNode = 4;
    
    graph[0] = {1};
    graph[1] = {2};
    graph[2] = {3};
    graph[3] = {2,4};

    std::unordered_set<int> visited;

    std::queue<std::shared_ptr<path>> toVisit;

    auto n = std::make_shared<path>();

    n->currentNode = startNode;
    n->nodes = std::vector<int>{startNode};
    toVisit.push(n);

    while (!toVisit.empty()) {

        auto current = toVisit.front();
        toVisit.pop();

        int id = current->currentNode;

        if (visited.contains(id)) {
            std::cout << "skipping already visited node: " << id << std::endl;
            continue;
        }

        visited.insert(id);

        std::cout << "current node: " << id << std::endl;

        if (id == targetNode) {
            std::cout << "target node found with path: " << std::endl;

            for (const int id: current->nodes) {
                std::cout << id << ", ";
            }
            std::cout << std::endl;

            return 0;
        }

        for (const auto& child : graph.at(id)) {

            std::cout << "child of " << id << " found: " << child << std::endl;

            std::vector<int> pathToChild = current->nodes;
            pathToChild.push_back(child);

            auto childNode = std::make_shared<path>();

            childNode->currentNode = child;
            childNode->nodes = pathToChild;

            toVisit.push(childNode);
        }
    }

    return 0;
}