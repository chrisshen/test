#include<iostream>
#include<queue>
#include<vector>
// #include<cParticipant.h>
// #include<cTimeSlot.h>
// using namespace std;

#define UNVISITED	0
#define CHECKED		1
#define VISITED		1
#define MARK		1

#define WHITE		0
#define GRAY		1
#define BLACK		2

#define MAX_VERTICES 300 //In TMAC, the number of vehicles is 300

using namespace std;
#pragma once

// struct check_vehicle_los
// {
//     int m_v;//vertex
//     int m_nv;//neighbor
// };

// Node class
class Node{
private:
	int nodeID;
	double xLocation;
	double yLocation;

protected:
	std::vector<int> receiverSet;
	std::vecotr<int> interferenceSet;

public:
	void setNodeID(int id);
	void setLocation(double x, double y);
	void setReceiverSet(std::vector<check_vehicle_los> vehicle_los_arr);
	void setInterferenceSet(std::vector<cParticipant>& qPart);

	int getNodeID();
	double getXLocation();
	double getYLocation();
	std::vector<int> getReceiverSet();
	std::vector<int> getInterferenceSet();
};

// Graph class
class Graph{
public:
	int getNumNodes();
	void setNumNodes();
	int getNumEdges();
	void buildGraph();
	Graph(){
		// adjMatrix[].clear();

	};
private:
	Node node;
	std::vector<Node*> nodeSet[numNodes];
	int numNodes;
	int numEdges;
	std::vector< std::vector<int> > adjMatrix(MAX_VERTICES, std::vector<int>(MAX_VERTICES, 0) );

};

// Setcover class
class CSetCover
{
	private:
		Graph g;
		int m_vertex_size;
		int edge_count;
		int set_count;
		int check_adj_mat[MAX_VERTICES][MAX_VERTICES];
		int visited[MAX_VERTICES];

	protected:
		void graph_init();
		void set_vertex(int v);

		// define struct for maximum set:
		typedef struct{
			int m_v; 			//myID
			int m_vn; 			//ID of neighbor
			int m_slot_num; 	//number of slot
		}Maximum_Set;

		typedef struct{
			int m_visit; 		//Is it visit?
			int m_flag;
			int m_QueueOverlapCheck;
		}Search_Maximal_compatible;

		typedef struct{
			Search_Maximal_compatible arr[MAX_VERTICES];
		}Maxmal_Set;


		Maxmal_Set Init_Maxmal_Set();
		vector<Maximum_Set> Search_Maximum_Compatible_Set();  		//In TMAC paper, algorithm 2
		vector<Maximum_Set> Make_Maximal_ComPatible_Set(int v);  	//In TMAC paper, algorithm 3

		vector<Maximum_Set> Make_Maximal_ComPatible_Set_Plus(int v); //Update Algorithm3

	public:
		vector<Maximum_Set> v_MS;
		void Greedy_Set_Cover(vector<cParticipant>& qPart, vector<check_vehicle_los> vehicle_los_arr);
		void Show_Set_Cover(vector<cParticipant>& qPart);
		int GetMaxSetSize() { return v_MS.size(); }

		int GetNthSlot(int n , vector<Maximum_Set>& set){
			int cnt = 0;
			for(unsigned int i = 0 ; i < v_MS.size() ; i++){
				if(v_MS[i].m_slot_num == n){
					cnt++;
					set.push_back(v_MS[i]);
				}
			}
			return cnt;
		}

		int GetSlotSize(){
			int pre = 0;
			int cnt = 0;
			for(unsigned int i = 0 ; i < v_MS.size() ; i++){
				if(v_MS[i].m_slot_num != pre){
					pre = v_MS[i].m_slot_num;
					cnt++;
				}
			}
			return cnt;
		}

		Maximum_Set& GetNthNode(int n){
			return v_MS[n];
		}

		int GetVertexSize() { return m_vertex_size; }
};