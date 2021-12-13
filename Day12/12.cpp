#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <set>
struct Graph {
	std::unordered_map<std::string, std::vector<std::string>> tree;
	//WARNING It is not the best option to store the entire solutions but I wanted to see all the combinations
	std::vector<std::vector<std::string>> solutions;
};
void walkGraph(Graph& graph, std::string currentNode, std::vector<std::string> path, std::multiset<std::string> visited, bool partTwo);
void startSolving(Graph& graph, bool partTwo);

int main() {
	Graph graph;
	std::string line;
	std::ifstream file("12.txt");
	while (std::getline(file, line)) {
		std::stringstream X(line);
		std::string nodeName;
		std::vector<std::string> temp = {};
		while (std::getline(X, nodeName, '-')) {
			temp.push_back(nodeName);
		}
		graph.tree[temp[0]].push_back(temp[1]);
		graph.tree[temp[1]].push_back(temp[0]);
	}

	startSolving(graph, false);
	int solution = graph.solutions.size();
	std::cout << "There were " << solution << " possible solutions for part1" << std::endl;

	std::cout << "To run second part press enter:" << std::endl << std::endl;
	getchar();

	graph.solutions = {};
	startSolving(graph, true);
	solution = graph.solutions.size();
	std::cout << "There were " << solution << " possible solutions for part2" << std::endl;
	return 0;
}

void startSolving(Graph& graph, bool partTwo) {
	// Store solution
	std::vector<std::string> path = {};
	// Store visited nodes
	std::multiset<std::string> visited = {};
	// We visited twice
	walkGraph(graph, "start", path, visited, partTwo);
}

void walkGraph(Graph& graph, std::string currentNode, std::vector<std::string> path, std::multiset<std::string> visited, bool partTwo) {
	if (std::islower(currentNode[0])) {
		if (visited.count(currentNode) == 1) { partTwo = false; }
		visited.insert(currentNode);
	}
	path.push_back(currentNode);

	if (currentNode == "end") {
		graph.solutions.push_back(path);
		//Uncomment to print solutions
		//for (const auto& item : path) {
		//	std::cout << item << ",";
		//}
		//std::cout << std::endl;
	} else {
		for (const auto& item : graph.tree[currentNode]) {
			if (item == "start") continue;
			if (!visited.count(item) > 0 || (partTwo && visited.count(item) < 2)) {
				walkGraph(graph, item, path, visited, partTwo);
			}
		}
	}
}