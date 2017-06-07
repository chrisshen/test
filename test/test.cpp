// vector::begin/end
#include <iostream>
#include <vector>

// class bbb{
// public:
// 	bool operator==(const& rhs) const { return this->pos == rhs.pos;};
// 	int id;
// 	float pos;
// };
class Node{
private:
	int nodeID;
	double xLocation;
	double yLocation;

protected:
	std::vector<int> receiverSet;
	std::vector<int> interferenceSet;

public:
	void setNodeID(int id);
	void setLocation(double x, double y);
	// void setReceiverSet(std::vector<check_vehicle_los> vehicle_los_arr);
	// void setInterferenceSet(std::vector<cParticipant>& qPart);

	int getNodeID();
	double getXLocation();
	double getYLocation();
	std::vector<int> getReceiverSet();
	std::vector<int> getInterferenceSet();
};

class Graph{
public:
	// int getNumNodes();
	// void setNumNodes();
	// int getNumEdges();
	// void buildGraph();
	int getNodeSetSize();
	std::vector<Node*> nodeSet;

	Graph():nodeSet(){
		numNodes = 100;
		nodeSet = new Node*[numNodes];
		// for (int i = 0; i<100; i++){
		// 	Node node;
		// 	Node* p = &node;
		// 	nodeSet.push_back(p);
		// };
	};
private:
	
	int numNodes;
	int numEdges;
	// std::vector< std::vector<int> > adjMatrix(100, std::vector<int>(100, 0) );

};


void
Node::setNodeID(int id){
	nodeID = id;
}

void
Node::setLocation(double x, double y){
	xLocation = x;
	yLocation = y;
}

int
Node::getNodeID(){
	return nodeID;
}

double
Node::getXLocation(){
	return xLocation;
}

double
Node::getYLocation(){
	return yLocation;
}

std::vector<int>
Node::getReceiverSet(){
	return receiverSet;
}

std::vector<int>
Node::getInterferenceSet(){
	return interferenceSet;
}

int
Graph::getNodeSetSize(){
	return nodeSet.size();
}


int main ()
{
	// std::cout << "myvector contains:";
	// std::vector<bbb> myvector;
	// std::cout << "myvector contains:";

	// for (int i=1; i<=5; i++) {
	// 	bbb x;
	// 	x.id =i;
	// 	x.pos =i+0.2;
	// 	myvector.push_back(x);
	// }

	Graph x;
	int size = x.getNodeSetSize();
	std::cout << size << std::endl;
	x.nodeSet[50]->setLocation(10.0, 10.0);
	x.nodeSet[10]->setLocation(20.0, 20.0);
	int count = 0;
	for(std::vector<Node*>::iterator it = x.nodeSet.begin(); it != x.nodeSet.end(); it++){
		count++;
		(*it)->setLocation(count, count);
	}

	for(std::vector<Node*>::iterator it = x.nodeSet.begin(); it != x.nodeSet.end(); it++){
		std::cout << "address: " << &it << 
					 " Location: "<< (*it)->getXLocation() << ", "<<(*it)->getYLocation()<<std::endl;
	}
	// std::cout << "myvector contains:";
	// for (std::vector<bbb>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
	// 	std::cout << ' ' << (*it).id << ' ' << (*it).pos;
	// std::cout << '\n';

	// std::vector<bbb>::iterator it; 
	// it = std::find (myvector.begin(), myvector.end(), 3);
	// if (it != myvector.end())
	// 	std::cout << "Element found in myvector: " << (*it).id << (*it).pos << '\n';
	// else
	// 	std::cout << "Element not found in myvector\n";	

	return 0;
}