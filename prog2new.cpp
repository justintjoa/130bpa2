#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#include "prog2.h"

	void printpoints(edge a) {
		//cout << a.getfirstpoint().getx() << " " << a.getfirstpoint().gety() << ", " << a.getsecondpoint().getx() << " " << a.getsecondpoint().gety() << endl;
		//cout << "distance is" << a.getdistance() << endl;
	}

	point::point(double x, double y, int index) {
		this->x = x;
		this->y = y;
		this->index = index;
	}
	point::~point() {
	}

	double point::getx() {
		return x;
	}
	double point::gety() {
		return y;
	}


	int point::getindex() const {
		return index;
	}

		struct less_than_key3
{
    inline bool operator() (const point& struct1, const point& struct2) {
        return (struct1.getindex() < struct2.getindex());
    }
};

	edge::edge(point a, point b) {
		line.push_back(a);
		line.push_back(b);
		for (int i = 0; i < line.size(); i++) {
			std::sort(line.begin(), line.end(), less_than_key3());
		}

		distance = sqrt(pow((line.at(1).gety()-line.at(0).gety()),2) + pow((line.at(1).getx()-line.at(0).getx()),2));
	}

	edge::~edge() {
		if (line.size() > 0) {
			line.clear();
		}
	}
		
	point edge::getfirstpoint() const {
		return line.at(0);
	}

	point edge::getsecondpoint() const {
		return line.at(1);
	}
		
	double edge::getdistance() const {
		return distance;
	}




	graph::graph() {

	}
	graph::~graph() {
		if (solution.size() > 0) {
			solution.clear();
		}
	}

	
	int find(subset subsets[], int i)  {  
    // find root and make root as parent of i  
    // (path compression)  
    	if (subsets[i].parent != i)  {
        	subsets[i].parent = find(subsets, subsets[i].parent);  
    	}
  
    	return subsets[i].parent;  
	}  


	void Union(subset subsets[], int x, int y){ 
    	int xbase = find(subsets, x);  
    	int ybase = find(subsets, y);  
  
    // Attach smaller rank tree under root of high  
    // rank tree (Union by Rank)  
    	if (subsets[xbase].rank < subsets[ybase].rank)  {
        	subsets[xbase].parent = ybase;  
    	}
    	else if (subsets[xbase].rank > subsets[ybase].rank)  {
        	subsets[ybase].parent = xbase;  
    	}
  
    // If ranks are same, then make one as root and  
    // increment its rank by one  
    	else {  
        	subsets[ybase].parent = xbase;  
        	subsets[xbase].rank++;  
    	}  
	}  

	void graph::addtograph(int numberofpoints, vector<point> input, int numberofedges, vector<int> edgeindexes) {
		vector<edge> realinput;
		for (int i = 0; i < (numberofedges); i++) {
			int index1;
			index1 = edgeindexes.at(i*2);
			int index2;
			index2 = edgeindexes.at(i*2 + 1);
			edge a(input.at(index1), input.at(index2));
			realinput.push_back(a);
		}
		//for (int i = 0; i < realinput.size(); i++) {
		//	printpoints(realinput.at(i));
		//}
		std::sort(realinput.begin(), realinput.end());
		//cout << "look at me now" << endl;
		//for (int i = 0; i < realinput.size(); i++) {
		//	printpoints(realinput.at(i));
		//}
		subset *subsets = new subset[(numberofpoints*sizeof(subset))];
		 for (int v = 0; v < numberofpoints; ++v)  {  
        	subsets[v].parent = v;  
        	subsets[v].rank = 0;  
    	}	  
		
		//cout << "yeah im good" << endl;
		for (int i = 0; i < numberofedges; i++) {
			int x = find(subsets, realinput.at(i).getfirstpoint().getindex());  
        	int y = find(subsets, realinput.at(i).getsecondpoint().getindex());
			if (x != y) {  
            	solution.push_back(realinput.at(i));
            	Union(subsets, x, y);  
        	}  
		}
	}



struct less_than_key4
{
    inline bool operator() (const edge& struct1, const edge& struct2) {
    	if ((struct1.getfirstpoint().getindex() != struct2.getfirstpoint().getindex())) {
    		return (struct1.getfirstpoint().getindex() < struct2.getfirstpoint().getindex());
    	}
    	else {
    		return (struct1.getsecondpoint().getindex() < struct2.getsecondpoint().getindex());
    	}
	}
};

	


	vector<point> edge::getline() const {
		return line;
	}

	void graph::printgraph() {
		//cout << "printing solution" << endl;
		vector<edge> temp;
		for (int i = 0; i < solution.size(); i++) {
			temp.push_back(solution.at(i));
		}

		for (int i = 0; i < solution.size(); i++) {
			std::sort(temp.begin(), temp.end(), less_than_key4());
		}
		/*
		for (int i = 0; i < solution.size(); i++) {
			std::sort(temp.begin(), temp.end(), less_than_key2());
		}
		*/
		
		//cout << solution.size() << endl;
		for (int i = 0; i < temp.size(); i++) {
			cout << temp.at(i).getfirstpoint().getindex() << " " << temp.at(i).getsecondpoint().getindex() << endl;
		}
	}




