#include <iostream>
// #include <stdio>
#include <vector>
#include <algorithm>

using namespace std;

static int g_iTest;

class A
{
private:
	int a;
	int b;
	float c;
	int d;
	int e;

public:
	// A(): a(0), b(0), c(0.0){}
	
};

class B
{
private:
	int x;
	int y;
	float z;
	A aInstance[];
	int * p;
public:
	B(): x(0), y(0), z(0.0){}
	int getX(){
		return x;
	}

	int getY(){
		return y;
	}
};


typedef struct
{
    int m_v; //vertex
    int m_vn; //vertex of neighbor
    int m_slot_num; //slot num
}Maximum_Set;

bool comparison(Maximum_Set i, Maximum_Set j){
	return (i.m_v == j.m_v);		
}


int 
main(int argc, char const *argv[])
{
	// B bInstance;
	// A aaInstance;
	// B * pB;

	// std::cout << "sizeof(*pB): " << sizeof(pB) << std::endl;


	// std::cout << "sizeof(A): " << sizeof(A) << std::endl;
	// std::cout << "sizeof(aaInstance): " << sizeof(aaInstance) << std::endl;


	// std::cout << "sizeof(B): " << sizeof(B) << std::endl;

	// std::cout << "sizeof(bInstance): " << sizeof(bInstance) << std::endl;

	// B * pB = new B[0];

	std::vector<Maximum_Set> v;

	for (int i = 0; i < 2; i++){
		Maximum_Set tt;
		tt.m_vn = 6;
		tt.m_v = 1;
		tt.m_slot_num = 1;

		v.push_back(tt);
	}

	for (int i = 0; i < 2; i++){
		Maximum_Set tt;
		tt.m_vn = 6;
		tt.m_v = 2;
		tt.m_slot_num = 1;

		v.push_back(tt);
	}

	for (int i = 0; i < 2; i++){
		Maximum_Set tt;
		tt.m_vn = 6;
		tt.m_v = 3;
		tt.m_slot_num = 2;

		v.push_back(tt);
	}	

	// for (unsigned int i = 0; i < v.size(); i++){
	// 	std::cout << "slot#: " << v[i].m_slot_num << std::endl;
	// 	std::cout << "v: " << v[i].m_v << std::endl;
	// 	std::cout << "vn: " << v[i].m_vn << std::endl;
	// }

	std::cout <<"=============================="<<std::endl;

	std::vector<Maximum_Set>::iterator it;
	it = std::unique(v.begin(), v.end(), comparison);
	v.resize(std::distance(v.begin(), it) );

	// for (unsigned int i = 0; i < v.size(); i++){
	// 	std::cout << "slot#: " << v[i].m_slot_num << std::endl;
	// 	std::cout << "v: " << v[i].m_v << std::endl;
	// 	std::cout << "vn: " << v[i].m_vn << std::endl;
	// }

	// for (unsigned int i = 0; i < v.size(); i++ ){
	// 	std::cout << "v"<<i<<" = "
	// }

	// std::cout << "pB: " << pB->getX() << " "<< pB->getY() << std::endl;

	g_iTest = 100;

	cout << g_iTest << endl;

	g_iTest = 50;

	cout << g_iTest << endl;

	return 0;
}