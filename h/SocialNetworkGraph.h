#ifndef ALGPROJECT_SOCIALNETWORKGRAPH_H
#define ALGPROJECT_SOCIALNETWORKGRAPH_H
#include <string>
#include <iostream>

#include "TStack.h"
#include "TQueue.h"

class GraphVertex;
class GraphEdge;

// todo
class SocialNetworkGraph {
public:
	// Constructor.
	SocialNetworkGraph(const unsigned short maxVertices_, const unsigned short maxEdges_);

	// Destructor.
	~SocialNetworkGraph();

	// Add a vertex to the graph.
	void addVertex(const std::string& name);

	// Add an edge to the graph.
	void addEdge(const std::string& fromName, const std::string toName, const float weight);

	// Prints all vertices.
	void printVertices() const;

	// Prints all edges.
	void printEdges() const;

	// Prints all indices.
	void printIndices() const;

	// Prints graph representation.
	void print() const;

	// Removes an edge from the graph.
	void removeEdge(const std::string& fromName, const std::string& toName);

	// Removes a vertex from the graph.
	void removeVertex(const std::string& name);

	// Simulates liking a post on social media, increases edge weight by 0.1. Creates new edge if it doesn't exist.
	void likePost(const std::string& fromName, const std::string& toName);

	// Depth first search implementation.
	void depthFirstSearch(const std::string& startVertex) const;

	// Breadth first search implementation.
	void breadthFirstSearch(const std::string& startVertex) const;

	// Returns largest connected component in the graph.
	void largestConnectedComponent() const;

	// Prints the transposed graph.
	void printTransposedGraph() const;

	// Prints the most probable path between two vertices.
	void mostProbablePath(const std::string& fromName, const std::string& toName) const;

	// Prints the k-th most influential person in the social network.
	void kthMostInfluential(const unsigned short kth) const;

	unsigned short getCurrentVertices() const;

private:
	unsigned short maxVertices;
	unsigned short maxEdges;
	unsigned short currentVertices;
	unsigned short currentEdges;
	GraphEdge** edges;
	GraphVertex** vertices;
	unsigned short* indices;

	// Given a name, returns the index of a vertex in the internal vertices array.
	// -1 if the search is unsuccessful.
	int getVertexByName(const std::string& name) const;

	// Add an edge to the graph using internal indices.
	void addEdgeByIndex(const unsigned short fromIndex, const unsigned short toIndex, const float weight);

	// Ditto.
	void removeEdgeByIndex(const unsigned short fromIndex, const unsigned short toIndex);

	// Returns true if an edge between two vertices exists in the graph.
	bool edgeExists(const unsigned short fromIndex, const unsigned short toIndex) const;

	// Returns the weight of the edge between two vertices or 0 if the edge doesn't exist.
	double edgeWeight(const unsigned short fromIndex, const unsigned short toIndex) const;
};


// Auxiliary class.
class GraphVertex {
public:
	// Constructor.
	GraphVertex(const std::string& name_);

	// Destructor.
	~GraphVertex() = default;

	// Returns a string with data about the object.
	std::string toString() const;

private:
	// Vertex name.
	std::string name;
};

// Auxiliary class.
class GraphEdge {
public:
	// Constructor.
	GraphEdge(unsigned short indexTo_, double weight_ = 0.0);

	// Destructor.
	~GraphEdge() = default;

	// Returns outgoing vertex index.
	unsigned short getIndexTo() const;

	// Sets outgoing vertex index.
	void setIndexTo(const unsigned short indexTo_);

	// Returns edge weight.
	double getWeight() const;

	// Sets edge weight.
	void setWeight(const double weight_);

	// Returns a string with data about the object.
	std::string toString() const;


private:
	// Index of 
	unsigned short indexTo;

	// Edge weight
	double weight;
};

#endif
