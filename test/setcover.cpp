#include"setcover.h"

//
/*
Node Class:
*/
//
void
Node::setNodeID(int id){
	nodeID = id;
}

void
Node::setLocation(double x, double y){
	xLocation = x;
	yLocation = y;
}

void
Node::setReceiverSet(std::vector<check_vehicle_los> vehicle_los_arr){
	for (std::vector<check_vehicle_los>::iterator it = vehicle_los_arr.begin(); it != vehicle_los_arr.end(); it++){
		if (nodeID == (*it).m_v){
			// push back the neighbor ID
			receiverSet.push_back((*it).m_nv);
		}
	}
}

void
Node::setInterferenceSet(std::vector<cParticipant>& qPart){
	// iterate all nodes of the graph, via index
	for(unsigned int i = 0; i < qPart.size(); i++){
		// check it is not my node
		if ( i != nodeID ){
			// check it is not in my receiverSet, if it's in, set flag false
			bool flag = true;
			for(std::vector<int>::iterator w = receiverSet.begin(); w != receiverSet.end(); w++){
				if ( i == (*w).nodeID ){
					flag = false;
				}
			}
			// flag = ture
			if ( flag ){
				// iterate receiverSet to calculate the angle
				for(std::vector<int>::iterator j = receiverSet.begin(); j != receiverSet.end(); j++){
					// sender's position
					double sender_x = qPart[nodeID].GetCoord().x;
					double sender_y = qPart[nodeID].GetCoord().y;
					// reciver's position
					double receiver_x = qPart[(*j)->nodeID].GetCoord().x;
					double receiver_y = qPart[(*j)->nodeID].GetCoord().y;
					// possible interference node's position
					double interference_x = qPart[i].GetCoord().x;
					double interference_y = qPart[i].GetCoord().y;
					// inner product:a dot times b
					double inner_product = ((receiver_x - sender_x) * (interference_x - sender_x) + 
											(receiver_y - sender_y) * (interference_y - sender_y));
					// distance from sender to receiver
					double distance_to_receiver = sqrt( pow((sender_x - receiver_x), 2) + 
														pow((sender_y - receiver_y), 2));
					// distance from sender to possible interference node
					double distance_to_interference = sqrt( pow((sender_x - interference_x), 2) + 
															pow((sender_y - interference_y), 2));
					// two vectors' angle
					double cos_theta = inner_product / (distance_to_receiver * distance_to_interference);

					// if the angle is less than 45/2 = 22.5 and distance is less than 2 times of transmission range, then it's interference
					if( (cos_theta >= cos(22.5 * 0.0175)) && ( distance_to_interference <= (2 * distance_to_receiver) ) ){

						interferenceSet.push_back( i );

						std::cout<<"============================================"<<std::endl;
						std::cout<<"sender: "<<qPart[nodeID].GetVehicleID()<<std::endl;
						std::cout<<"receiver: "<<qPart[(*j)->nodeID].GetVehicleID()<<std::endl;
						std::cout<<"interference: "<<qPart[i].GetVehicleID()<<std::endl<<std::endl;

					}
				}
			}
		}
	}
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

//
/*
// Graph Class:
*/
//

int
Graph::getNumNodes(){
	return numNodes;
}

void
setNumNodes(int num){
	numNodes = num;
}

int
Graph::getNumEdges(){
	return numEdges;
}

void
Graph::buildGraph(){

	
	for (int i = 0; i < numNodes; i++){
		Node node;
		Node* p;
		p = &node;
		nodeSet.push_back(p);
	}
}

//
/*
// CSetCover Class:
*/
//
void
CSetCover::setVertex(int v){ //To insert a vehicle size
	m_vertex_size = v;
}


void
CSetCover::Greedy_Set_Cover(vector<cParticipant>& qPart, vector<check_vehicle_los> vehicle_los_arr){
	Maximum_Set in_set;
	std::vector<Maximum_Set> temp_v_s;

	setVertex(qPart.size()); //To insert a vehicle size

	edge_init(qPart,vehicle_los_arr); //To create both Reception set and Reception set

	while(!edge_count == NULL){
		temp_v_s = Search_Maximum_Compatible_Set(); //maximum set search
		set_count++; //increase the slot, in order to separate the slot

		for(unsigned int i=0; i<temp_v_s.size(); i++){
			check_adj_mat[temp_v_s[i].m_v][temp_v_s[i].m_vn] = NULL; //maximum edge node matrix remove
			in_set.m_v = temp_v_s[i].m_v;
			in_set.m_vn = temp_v_s[i].m_vn;
			in_set.m_slot_num = set_count;
			v_MS.push_back(in_set);   //To insert the array about sender and receiver
			edge_count--;
		}
		temp_v_s.clear();
	}

	if(v_MS.size() != 0){
		//Show_Set_Cover(qPart);
		edge_delete();
	}
}

vector<Maximum_Set>
CSetCover::Search_Maximum_Compatible_Set(){
    int max = 0;
    vector<Maximum_Set> v_maximal_set;
    vector<Maximum_Set> v_temp_maximal_set;

    for(int i = 0; i < m_vertex_size; i++){
        //v_maximal_set = Make_Maximal_ComPatible_Set(i); //To connect all vertex Maximal_ComPatible_Set return

        v_maximal_set = Make_Maximal_ComPatible_Set_Plus(i);

        if(v_maximal_set.size() > max){  //To search a maximal compatible set
            max = v_maximal_set.size();
            v_temp_maximal_set = v_maximal_set;
        }
    }
    return v_temp_maximal_set;
}


vector<Maximum_Set>
CSetCover::Make_Maximal_ComPatible_Set(int v){

	Node *w;
	vector<Maximum_Set> v_s;
	Maximum_Set ms;
	int i_ut=0, i_ui=0, i_ur=0, i_flag=0;
	queue<int> Q;
	int overlap_check[MAX_VERTICES];

	for(int i=0; i<MAX_VERTICES; i++){
		overlap_check[i]=UNVISITED;
		visited[i]=UNVISITED;
	}

	Q.push(v);

	while (!Q.empty()){
		i_ut=Q.front();
		Q.pop();

		for(w=g.l_Reception_set[i_ut]; w; w = w->link){
			if((visited[w->vertex] == UNVISITED) && (visited[i_ut] == UNVISITED) && (check_adj_mat[i_ut][w->vertex])){
				ms.m_v = i_ut; //정점과 정점 이웃을 vector 에다 넣기
				ms.m_vn = w->vertex;
				v_s.push_back(ms);
				visited[w->vertex] = VISITED;
				i_flag=CHECKED;
			}
		}
		if(i_flag==CHECKED){
			overlap_check[i_ut]=VISITED;
			visited[i_ut]=VISITED;
			i_flag=NULL;
		}
		w=NULL;

		for(w=g.l_Interference_set[i_ut]; w; w = w->link) {
			if((visited[w->vertex] == UNVISITED) && (overlap_check[i_ui] == UNVISITED)){
				i_ui=w->vertex;
				Q.push(i_ui);
				overlap_check[i_ui]=VISITED;
			}
		}
		w=NULL;
	}
	return v_s;
}


vector<Maximum_Set>
CSetCover::Make_Maximal_ComPatible_Set_Plus(int s){

	return v_s;
}