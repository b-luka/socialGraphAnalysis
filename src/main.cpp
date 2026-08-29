#include <iostream>
#include <string>
#include <fstream>

#include "SocialNetworkGraph.h"

using namespace std;

int main(int argc, char** argv) {
	string fileName;
	cout << "> Enter file name: ";
	cin >> fileName;
	ifstream inputFile(fileName);
	if (!inputFile.good()) {
		cout << "Error: Can't read file " << fileName << endl;
		return 1;
	}

	unsigned short numVertices = 0, numEdges = 0;
	string line;
	getline(inputFile, line);
	numVertices = stoi(line);
	getline(inputFile, line);
	numEdges = stoi(line);
	SocialNetworkGraph graph(numVertices, numEdges);
	getline(inputFile, line);
	string current = "";
	for (char c : line) {
		if (isspace(c)) {
			graph.addVertex(current);
			current = "";
		}
		else {
			current += c;
		}
	}
	graph.addVertex(current);
	current = "";
	while (!inputFile.eof()) {
		getline(inputFile, line);
		string nameFrom, nameTo, w;
		double weight;
		nameFrom = line.substr(0, line.find(' '));
		line = line.substr(line.find(' ') + 1, line.length() - 1);
		nameTo = line.substr(0, line.find(' '));
		line = line.substr(line.find(' ') + 1, line.length() - 1);
		w = line;
		weight = stod(w);
		graph.addEdge(nameFrom, nameTo, weight);
	}

	cout << "> Graph successfully loaded.\n";

	int choice;
	cin.clear();
	cout << "> Enter a number [0-9]: ";
	cin >> choice;
	unsigned short k;

	string nameFrom, nameTo, name;
	double weight;

	while (choice != 0) {
		switch (choice) {
		// Exit.
		case 0:
			break;

		// Print.
		case 1:
			graph.print();
			break;

		// Add edge.
		case 2:
			cout << "> Enter first vertex name: ";
			cin >> nameFrom;
			cout << "> Enter second vertex name: ";
			cin >> nameTo;
			cout << "> Enter edge weight: ";
			cin >> weight;
			graph.addEdge(nameFrom, nameTo, weight);
			break;

		// Add vertex.
		case 3:
			cout << "> Enter new vertex name: ";
			cin >> name;
			graph.addVertex(name);
			break;

		// Remove edge.
		case 4:
			cout << "> Enter first vertex name: ";
			cin >> nameFrom;
			cout << "> Enter second vertex name: ";
			cin >> nameTo;
			graph.removeEdge(nameFrom, nameTo);
			break;

		// Remove vertex.
		case 5:
			cout << "> Enter vertex name: ";
			cin >> name;
			graph.removeVertex(name);
			break;

		// Like.
		case 6:
			cout << "> Enter first vertex name: ";
			cin >> nameFrom;
			cout << "> Enter second vertex name: ";
			cin >> nameTo;
			graph.likePost(nameFrom, nameTo);
			break;

		// Largest CC.
		case 7:
			graph.largestConnectedComponent();
			break;

		// Most probable path.
		case 8:
			cout << "> Enter first vertex name: ";
			cin >> nameFrom;
			cout << "> Enter second vertex name: ";
			cin >> nameTo;
			graph.mostProbablePath(nameFrom, nameTo);
			break;

		// K-th most influential.
		case 9:
			cout << "> Enter number [1-" << graph.getCurrentVertices() << "]: ";
			cin >> k;
			if (k < 1 || k > graph.getCurrentVertices()) cout << "Error: Invalid position.\n";
			else graph.kthMostInfluential(k - 1);
			break;

		// Unknown command.
		default:
			cout << "> Command not found. List all commands? [y\\N]: ";
			char listAll;
			cin >> listAll;
			if (listAll == 'y' || listAll == 'Y') {
				cout << "> Available commands:\n";
				cout << "1. Print out the graph representation.\n";
				cout << "2. Add an edge to the graph.\n";
				cout << "3. Add a vertex to the graph.\n";
				cout << "4. Remove an edge from the graph.\n";
				cout << "5. Remove a vertex from the graph.\n";
				cout << "6. Simulate liking a post from one user (vertex) to another.\n";
				cout << "7. Print out the largest strongly connected component in the graph.\n";
				cout << "8. Print the most probable path between two users (vertices).\n";
				cout << "9. List the k-th most influential person on the social network.\n";
				cout << "0. Exit program.\n";
			}
		}

		cout << "\n> Enter a number [0-9]: ";
		cin >> choice;
	}
	return 0;

}