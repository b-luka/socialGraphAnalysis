#include "SocialNetworkGraph.h"

// Constructor.
GraphVertex::GraphVertex(const std::string& name_) {
	this->name = name_;
}

// Returns a string with data about the object.
std::string GraphVertex::toString() const {
	return this->name;
}

// Constructor.
GraphEdge::GraphEdge(unsigned short indexTo_, double weight_) {
	this->indexTo = indexTo_;
	if (weight_ > 1.0 || weight_ < 0.0) this->weight = 0.0;
	else this->weight = weight_;
}

// Returns outgoing vertex index.
unsigned short GraphEdge::getIndexTo() const {
	return this->indexTo;
}

// Sets outgoing vertex index.
void GraphEdge::setIndexTo(const unsigned short indexTo_) {
	this->indexTo = indexTo_;
}

// Returns edge weight.
double GraphEdge::getWeight() const {
	return this->weight;
}

// Sets edge weight.
void GraphEdge::setWeight(const double weight_) {
	if (weight < 0.0) {
		this->weight = 0.0;
	}
	else if (weight > 1.0) {
		this->weight = 1.0;
	}
	else {
		this->weight = weight_;
	}
}

// Returns a string with data about the object.
std::string GraphEdge::toString() const {
	std::string res = "";
	res += std::to_string(this->indexTo);
	res += ", w = ";
	res += std::to_string(this->weight);
	return res;
}

// Constructor.
SocialNetworkGraph::SocialNetworkGraph(const unsigned short maxVertices_, const unsigned short maxEdges_) {
	this->maxVertices = maxVertices_;
	this->maxEdges = maxEdges_;
	this->currentVertices = 0;
	this->currentEdges = 0;
	this->vertices = new GraphVertex * [maxVertices_];
	this->edges = new GraphEdge * [maxEdges_];
	this->indices = new unsigned short[maxVertices_ + 1];
	for (unsigned short i = 0; i < maxVertices_ + 1; i++) this->indices[i] = 0;
}

// Destructor.
SocialNetworkGraph::~SocialNetworkGraph() {
	for (unsigned short i = 0; i < this->currentEdges; i++) {
		delete this->edges[i];
	}
	delete[] this->edges;

	for (unsigned short i = 0; i < this->currentVertices; i++) {
		delete this->vertices[i];
	}
	delete[] this->vertices;
	
	delete[] indices;
}

// Add a vertex to the graph.
void SocialNetworkGraph::addVertex(const std::string& name) {
	if (getVertexByName(name) != -1) {
		std::cout << "Error: Vertex already exists.\n";
		return;
	}
	if (currentVertices >= maxVertices) {

		// Double the size of the vertices array
		maxVertices *= 2;

		// Allocate new larger arrays
		GraphVertex** newVertices = new GraphVertex * [maxVertices];
		unsigned short* newIndices = new unsigned short[maxVertices + 1];

		// Copy old data
		for (unsigned short i = 0; i < currentVertices; i++) {
			newVertices[i] = vertices[i];
			newIndices[i] = indices[i];
		}
		newIndices[currentVertices] = indices[currentVertices]; // Last index remains

		// Delete old arrays
		delete[] vertices;
		delete[] indices;

		// Assign new arrays
		vertices = newVertices;
		indices = newIndices;
	}

	this->vertices[currentVertices] = new GraphVertex(name);
	this->indices[currentVertices + 1] = this->indices[currentVertices];	// When added, no edges exist
	this->currentVertices++;
}

// Add an edge to the graph using internal indices.
void SocialNetworkGraph::addEdgeByIndex(const unsigned short fromIndex, const unsigned short toIndex, const float weight) {
	if (fromIndex >= this->currentVertices || toIndex >= this->currentVertices || fromIndex == toIndex) {
		std::cout << "Error: Invalid edge.\n";
		return;
	}

	if (currentEdges + 1 >= maxEdges) {
		// Allocate more memory
		maxEdges *= 2;
		GraphEdge** newEdges = new GraphEdge * [maxEdges];
		for (unsigned short i = 0; i < currentEdges; i++) {
			newEdges[i] = edges[i];
		}
		delete[] edges;
		edges = newEdges;
	}

	// Shift existing edges
	unsigned short startIndex = indices[fromIndex + 1];
	for (unsigned short i = currentEdges; i > startIndex; i--) {
		edges[i] = edges[i - 1];
	}

	// Insert the new edge
	edges[startIndex] = new GraphEdge(toIndex, weight);

	// Update indices for all subsequent vertices
	for (unsigned short i = fromIndex + 1; i <= currentVertices; i++) {
		indices[i]++;
	}

	// Increment edge count
	currentEdges++;
}

// Given a name, returns the index of a vertex in the internal vertices array.
// -1 if the search is unsuccessful.
int SocialNetworkGraph::getVertexByName(const std::string& name) const {
	for (short i = 0; i < currentVertices; i++) {
		if (vertices[i]->toString() == name) {
			return i;
		}
	}
	return -1;
}

// Add an edge to the graph.
void SocialNetworkGraph::addEdge(const std::string& fromName, const std::string toName, const float weight) {
	int fromIndex = this->getVertexByName(fromName);
	int toIndex = this->getVertexByName(toName);
	if (fromIndex == -1 || toIndex == -1 || edgeExists(fromIndex, toIndex)) {
		std::cout << "Error: Missing vertices.\n";
		return;
	}
	this->addEdgeByIndex(fromIndex, toIndex, weight);
}

// Returns the weight of the edge between two vertices or 0 if the edge doesn't exist.
double SocialNetworkGraph::edgeWeight(const unsigned short fromIndex, const unsigned short toIndex) const {
	unsigned short startIndex = indices[fromIndex];
	unsigned short endIndex = indices[fromIndex + 1];

	for (unsigned short i = startIndex; i < endIndex; i++) {
		if (edges[i]->getIndexTo() == toIndex) {
			return edges[i]->getWeight();
		}
	}

	return 0.0;
}

void SocialNetworkGraph::printVertices() const {
	for (unsigned short i = 0; i < currentVertices; i++) {
		std::cout << vertices[i]->toString() << " ";
	}
	std::cout << "\n";
}


// Prints all indices.
void SocialNetworkGraph::printIndices() const {
	for (unsigned short i = 0; i < currentVertices + 1; i++) {
		std::cout << indices[i] << " ";
	}
	std::cout << "\n";
}

// Prints all edges.
void SocialNetworkGraph::printEdges() const {
	for (unsigned short fromIndex = 0; fromIndex < currentVertices; fromIndex++) {
		unsigned short startIndex = indices[fromIndex];
		unsigned short endIndex = indices[fromIndex + 1];

		for (unsigned short edgeIndex = startIndex; edgeIndex < endIndex; edgeIndex++) {
			unsigned short toIndex = edges[edgeIndex]->getIndexTo();
			double weight = edges[edgeIndex]->getWeight();
			std::cout << fromIndex << "(" << vertices[fromIndex]->toString() << ")" << "->"
				<< toIndex << "(" << vertices[edges[edgeIndex]->getIndexTo()]->toString() << ")"
				<< ", w = " << weight << std::endl;
		}
	}
}

// Prints graph representation.
void SocialNetworkGraph::print() const {
	printVertices();
	printEdges();
	printIndices();
	std::cout << "Max vertices: " << maxVertices << "\n";
	std::cout << "Max edges: " << maxEdges << "\n";
	std::cout << "Current vertices: " << currentVertices << "\n";
	std::cout << "Current edges: " << currentEdges << "\n";
}

// Remove an edge from the graph using internal indices.
void SocialNetworkGraph::removeEdgeByIndex(const unsigned short fromIndex, const unsigned short toIndex) {
	unsigned short startIndex = indices[fromIndex];
	unsigned short endIndex = indices[fromIndex + 1];

	for (unsigned short i = startIndex; i < endIndex; i++) {
		if (edges[i]->getIndexTo() == toIndex) {
			delete edges[i];
			for (unsigned short j = i; j < currentEdges - 1; j++) {
				edges[j] = edges[j + 1];
			}
			currentEdges--;

			for (unsigned short k = fromIndex + 1; k <= currentVertices; k++) {
				indices[k]--;
			}

			return;
		}
	}

	std::cout << "Error: Edge not found.\n";
}

// Removes an edge from the graph.
void SocialNetworkGraph::removeEdge(const std::string& fromName, const std::string& toName) {
	int fromIndex = getVertexByName(fromName);
	int toIndex = getVertexByName(toName);
	if (fromIndex == -1 || toIndex == -1) {
		std::cout << "Error: Vertex not found.\n";
		return;
	}

	removeEdgeByIndex(fromIndex, toIndex);
}

// Removes a vertex from the graph.
void SocialNetworkGraph::removeVertex(const std::string& name) {
	int vertexIndex = getVertexByName(name);

	if (vertexIndex == -1) {
		std::cout << "Error: Vertex not found.\n";
		return;
	}

	// Remove all outgoing edges from the vertex
	unsigned short startIndex = indices[vertexIndex];
	unsigned short endIndex = indices[vertexIndex + 1];
	for (unsigned short i = startIndex; i < endIndex; i++) {
		removeEdgeByIndex(vertexIndex, edges[startIndex]->getIndexTo());
	}

	// Remove all incoming edges to the vertex
	for (unsigned short i = 0; i < currentVertices; i++) {
		if (i != vertexIndex) {
			unsigned short fromIndex = indices[i];
			unsigned short toIndex = indices[i + 1];
			for (unsigned short j = fromIndex; j < toIndex; j++) {
				if (edges[j]->getIndexTo() == vertexIndex) {
					removeEdgeByIndex(i, vertexIndex);
				}
			}
		}
	}

	delete vertices[vertexIndex];

	// Shift vertices
	for (unsigned short i = vertexIndex; i < currentVertices - 1; i++) {
		vertices[i] = vertices[i + 1];
	}

	// Adjust indices
	for (unsigned short i = vertexIndex + 1; i <= currentVertices; i++) {
		indices[i - 1] = indices[i];
	}

	currentVertices--;

	// Adjust edges
	for (unsigned short i = 0; i < currentEdges; i++) {
		if (edges[i]->getIndexTo() > vertexIndex) {
			edges[i]->setIndexTo(edges[i]->getIndexTo() - 1);
		}
	}
}

// Returns true if an edge between two vertices exists in the graph.
bool SocialNetworkGraph::edgeExists(const unsigned short fromIndex, const unsigned short toIndex) const {
	unsigned short startIndex = indices[fromIndex];
	unsigned short endIndex = indices[fromIndex + 1];
	
	for (unsigned short i = startIndex; i < endIndex; i++) {
		if (edges[i]->getIndexTo() == toIndex) {
			return true;
		}
	}

	return false;
}

// Simulates liking a post on social media, increases edge weight by 0.1. Creates new edge if it doesnt exist.
void SocialNetworkGraph::likePost(const std::string& fromName, const std::string& toName) {
	int fromIndex = this->getVertexByName(fromName);
	int toIndex = this->getVertexByName(toName);
	if (fromIndex == -1 || toIndex == -1) {
		std::cout << "Error: Missing vertices.\n";
		return;
	}
	
	unsigned short startIndex = indices[fromIndex];
	unsigned short endIndex = indices[fromIndex + 1];

	for (unsigned short i = startIndex; i < endIndex; i++) {
		if (edges[i]->getIndexTo() == toIndex) {	// Edge exists in graph
			edges[i]->setWeight(edges[i]->getWeight() + 0.1);
			return;
		}
	}

	// Edge doesn't exist in graph, add new edge
	addEdgeByIndex(fromIndex, toIndex, 0.1);
}

// Depth first search implementation.
void SocialNetworkGraph::depthFirstSearch(const std::string& startVertex) const {
	int indexToVisit = getVertexByName(startVertex);
	if (indexToVisit == -1) {
		std::cout << "Error: Starting vertex not found.\n";
		return;
	}

	bool* visit = new bool[currentVertices];
	for (unsigned short i = 0; i < currentVertices; i++) visit[i] = false;
	
	TStack<unsigned short> stack(maxVertices);
	stack.push(indexToVisit);
	while (!stack.isStackEmpty()) {
		unsigned short index = stack.pop();
		if (!visit[index]) {
			visit[index] = true;
			std::cout << index << "(" << vertices[index]->toString() << ") ";

			unsigned short startIndex = indices[index];
			unsigned short endIndex = indices[index + 1];

			// for {u, (v, u) e E}
			for (unsigned short i = endIndex; i > startIndex; i--) {
				int neighborIndex = edges[i - 1]->getIndexTo();
				if (!visit[neighborIndex]) {
					stack.push(neighborIndex);
				}
			}
		}
	}

	delete[] visit;
	std::cout << std::endl;
}

// Breadth first search implementation.
void SocialNetworkGraph::breadthFirstSearch(const std::string& startVertex) const {
	int indexToVisit = getVertexByName(startVertex);
	if (indexToVisit == -1) {
		std::cout << "Error: Starting vertex not found.\n";
		return;
	}
	
	
	bool* visit = new bool[currentVertices]();
	for (unsigned short i = 0; i < currentVertices; i++) {
		visit[i] = false;
	}

	visit[indexToVisit] = true;
    std::cout << indexToVisit << "(" << vertices[indexToVisit]->toString() << ") ";
	TQueue<unsigned short> queue(currentVertices);
	queue.enqueue(indexToVisit);

    while (!queue.isQueueEmpty()) {
        indexToVisit = queue.dequeue();

        unsigned short startIndex = indices[indexToVisit];
        unsigned short endIndex = indices[indexToVisit + 1];

        // for {u, (v, u) e E}
        for (unsigned short i = startIndex; i < endIndex; i++) {
            unsigned short neighborIndex = edges[i]->getIndexTo();
            if (!visit[neighborIndex]) {
                visit[neighborIndex] = true;
                std::cout << neighborIndex << "(" << vertices[neighborIndex]->toString() << ") ";
                queue.enqueue(neighborIndex);
            }
        }
    }
    std::cout << std::endl;

    delete[] visit;
}

// Prints the transposed graph.
void SocialNetworkGraph::printTransposedGraph() const {
	SocialNetworkGraph tr(maxVertices, maxEdges);

	// Copy vertices.
	for (unsigned short i = 0; i < maxVertices; i++) {
		tr.addVertex(vertices[i]->toString());
	}

	// Copy edges, reverse indexTo and indexFrom.
	for (unsigned short i = 0; i < maxVertices; i++) {
		for (unsigned short j = indices[i]; j < indices[i + 1]; j++) {
			tr.addEdgeByIndex(edges[j]->getIndexTo(), i, edges[j]->getWeight());
		}
	}

	tr.print();
}

// Prints the largest connected component in a graph. Kosaraju's algorithm.
void SocialNetworkGraph::largestConnectedComponent() const {
	// Prepare the DFS stack.
	bool* visit = new bool[currentVertices]();
	TStack<unsigned short> ccStack(currentVertices);
	TStack<unsigned short> dfsStack(currentVertices);
	unsigned short* postVisitedTimes = new unsigned short[currentVertices]();
	unsigned time = 1;
	//
	for (unsigned short i = 0; i < currentVertices; i++) {
		if (visit[i]) continue;
		dfsStack.push(i);
		while (!dfsStack.isStackEmpty()) {
			unsigned short j = dfsStack.top();

			if (!visit[j]) {
				visit[j] = true;
				for (unsigned short k = indices[j]; k < indices[j + 1]; k++) {
					/*
					unsigned short neighborIndex = edges[k]->getIndexTo();
					if (!visit[neighborIndex]) {
						dfsStack.push(neighborIndex);
					}
					*/
					std::cout << "j=" << j << ", k=" << k << ", indices[j]=" << indices[j] << ", indices[j+1]=" << indices[j + 1] << "\n";

					if (k >= currentEdges) {
						std::cerr << "ERROR: k (" << k << ") >= currentEdges (" << currentEdges << ")\n";
						exit(1);
					}
					if (edges[k] == nullptr) {
						std::cerr << "ERROR: edges[" << k << "] is nullptr\n";
						exit(1);
					}

					unsigned short neighborIndex = edges[k]->getIndexTo();

					std::cout << "neighborIndex = " << neighborIndex << "\n";

					if (neighborIndex >= currentVertices) {
						std::cerr << "ERROR: neighborIndex (" << neighborIndex << ") >= currentVertices (" << currentVertices << ")\n";
						exit(1);
					}

					if (!visit[neighborIndex]) {
						dfsStack.push(neighborIndex);
					}
				}
			}
			else {	// node is already visited, note finish time (if it didn't appear yet)
				dfsStack.pop();
				if (postVisitedTimes[j] == 0) {
					postVisitedTimes[j] = time;
					time++;
					ccStack.push(j);
				}
			}
		}
	}
	return;
	
	// Transpose the graph.
	SocialNetworkGraph tr(maxVertices, maxEdges);

	for (unsigned short i = 0; i < maxVertices; i++) {
		tr.addVertex(vertices[i]->toString());
	}

	for (unsigned short i = 0; i < maxVertices; i++) {
		for (unsigned short j = indices[i]; j < indices[i + 1]; j++) {
			tr.addEdgeByIndex(edges[j]->getIndexTo(), i, edges[j]->getWeight());
		}
	}

	// Pop all elements in the stack and do DFS on the transposed graph.
	// Every DFS traversal gives one connected component.
	unsigned short* largestCC = new unsigned short[currentVertices];
	unsigned short largestCCSize = 0;
	unsigned short* currentCC = new unsigned short[currentVertices];
	unsigned short currentCCSize = 0;
	bool* visitTransposed = new bool[currentVertices]();

	while (!ccStack.isStackEmpty()) {
		unsigned short indexToVisit = ccStack.pop();
		if (!visitTransposed[indexToVisit]) {
			// Start DFS on the transposed graph from the current node.
			TStack<unsigned short> stack(maxVertices);
			stack.push(indexToVisit);
			currentCCSize = 0;

			while (!stack.isStackEmpty()) {
				unsigned short node = stack.pop();
				if (!visitTransposed[node]) {
					visitTransposed[node] = true;
					currentCC[currentCCSize] = node;
					currentCCSize++;

					unsigned short startIndex = tr.indices[node];
					unsigned short endIndex = tr.indices[node + 1];

					// For the transposed graph, explore all unvisited neighbors.
					for (unsigned short i = startIndex; i < endIndex; i++) {
						int neighborIndex = tr.edges[i]->getIndexTo();
						if (!visitTransposed[neighborIndex]) {
							stack.push(neighborIndex);
						}
					}
				}
			}

			if (currentCCSize > largestCCSize) {
				largestCCSize = currentCCSize;
				for (unsigned short i = 0; i < largestCCSize; i++) {
					largestCC[i] = currentCC[i];
				}
			}
		}
	}



	std::cout << "Largest connected component, with size " << largestCCSize << ":\n";
	for (unsigned short i = 0; i < largestCCSize; i++) {
		std::cout << largestCC[i] << "(" << vertices[largestCC[i]]->toString() << ") ";
	}
	std::cout << "\n";

	delete[] visit;
	delete[] visitTransposed;
	delete[] largestCC;
	delete[] currentCC;
}

// Prints the most probable path between two vertices.
void SocialNetworkGraph::mostProbablePath(const std::string& fromName, const std::string& toName) const {
	int fromIndex = this->getVertexByName(fromName);
	int toIndex = this->getVertexByName(toName);

	if (fromIndex == -1 || toIndex == -1) {
		std::cout << "Error: Missing vertices.\n";
		return;
	}

	// Initialize the weight matrix.
	double** weightMatrix = new double* [currentVertices];
	for (unsigned short i = 0; i < currentVertices; i++) {
		weightMatrix[i] = new double[currentVertices]();
	}

	for (unsigned short i = 0; i < currentVertices; i++) {
		for (unsigned short j = indices[i]; j < indices[i + 1]; j++) {
			weightMatrix[i][edges[j]->getIndexTo()] = edges[j]->getWeight();
		}
	}

	// Initialize distances, trace, and visit arrays.
	double* distances = new double[currentVertices];
	int* trace = new int[currentVertices];
	bool* visit = new bool[currentVertices]();

	for (unsigned short i = 0; i < currentVertices; i++) {
		distances[i] = 0.0;
		trace[i] = -1;
	}
	distances[fromIndex] = 1.0;
	trace[fromIndex] = fromIndex;

	// Dijkstra's algorithm.
	for (unsigned short k = 0; k < currentVertices; k++) {
		double maxProb = 0.0;
		int i = -1;
		for (unsigned short index = 0; index < currentVertices; index++) {
			if (!visit[index] && distances[index] > maxProb) {
				maxProb = distances[index];
				i = index;
			}
		}

		// If no unvisited vertex is reachable, break.
		if (i == -1) break;
		visit[i] = true;

		// Update probabilities for adjacent vertices.
		for (unsigned short j = 0; j < currentVertices; j++) {
			if (!visit[j] && weightMatrix[i][j] > 0.0) {
				double newProb = distances[i] * weightMatrix[i][j];
				if (newProb > distances[j]) {
					distances[j] = newProb;
					trace[j] = i;
				}
			}
		}
	}

	// Print the most probable path.
	if (distances[toIndex] == 0.0) {
		std::cout << "No possible path from " << fromName << " to " << toName << ".\n";
		return;
	}

	std::cout << "Most probable path from " << fromName << " to " << toName << ", with probability " << distances[toIndex] << ":\n";

	// Trace path.
	TStack<unsigned short> traceStack(currentVertices);
	
	for (int current = toIndex; current != fromIndex; current = trace[current]) {
		if (current == -1) {
			std::cout << "Error: Path reconstruction failed.\n";
			break;
		}
		traceStack.push(current);
	}
	traceStack.push(fromIndex);

	bool first = true;
	unsigned short prevVertex = -1;
	while (!traceStack.isStackEmpty()) {
		int vertex = traceStack.pop();
		if (!first) {
			std::cout << "(" << edgeWeight(prevVertex, vertex) << ") -> ";
		}
		std::cout << vertices[vertex]->toString();
		if (!traceStack.isStackEmpty()) std::cout << " -> ";
		prevVertex = vertex;
		if (first) first = false;
	}
	std::cout << "\n";

	for (unsigned short i = 0; i < currentVertices; i++) delete[] weightMatrix[i];
	delete[] weightMatrix;
	delete[] distances;
	delete[] trace;
	delete[] visit;
}

// Prints the most probable path between two vertices.
void SocialNetworkGraph::kthMostInfluential(const unsigned short kth) const {
	// Initialize the weight matrix.
	double** weightMatrix = new double* [currentVertices];
	for (unsigned short i = 0; i < currentVertices; i++) {
		weightMatrix[i] = new double[currentVertices];
		for (unsigned short j = 0; j < currentVertices; j++) weightMatrix[i][j] = 0.0;
	}

	for (unsigned short i = 0; i < currentVertices; i++) {
		for (unsigned short j = indices[i]; j < indices[i + 1]; j++) {
			weightMatrix[i][edges[j]->getIndexTo()] = edges[j]->getWeight();
		}
	}

	// Floyd's algorithm.
	for (unsigned short k = 0; k < currentVertices; k++) {
		for (unsigned short i = 0; i < currentVertices; i++) {
			for (unsigned short j = 0; j < currentVertices; j++) {
				if (weightMatrix[i][j] < weightMatrix[i][k] * weightMatrix[k][j]) {
					weightMatrix[i][j] = weightMatrix[i][k] * weightMatrix[k][j];
				}
			}
		}
	}

	double* probSums = new double[currentVertices];
	for (unsigned short i = 0; i < currentVertices; i++) {
		probSums[i] = 0.0;
		for (unsigned short j = 0; j < currentVertices; j++) {
			probSums[i] += weightMatrix[i][j];
		}
	}

	// Sort the probability sum array and copy vertice names (sorted accordingly.).
	std::string* namesCopy = new std::string[currentVertices];
	for (unsigned short i = 0; i < currentVertices; i++) namesCopy[i] = vertices[i]->toString();

	// Bubble sort.
	for (unsigned short i = 0; i < currentVertices - 1; i++) {
		for (unsigned short j = i + 1; j < currentVertices; j++) {
			if (probSums[i] < probSums[j]) {
				double tmpProb = probSums[i];
				std::string tmpName = namesCopy[i];
				probSums[i] = probSums[j];
				namesCopy[i] = namesCopy[j];
				probSums[j] = tmpProb;
				namesCopy[j] = tmpName;
			}
		}
	}

	// Print the result, clean up memory.
	std::cout << namesCopy[kth] << "\n";

	for (unsigned short i = 0; i < currentVertices; i++) delete[] weightMatrix[i];
	delete[] weightMatrix;
	delete[] namesCopy;
	delete[] probSums;
}

unsigned short SocialNetworkGraph::getCurrentVertices() const {
	return currentVertices;
}