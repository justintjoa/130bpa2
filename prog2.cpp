#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#include "prog2.h"

	void printpoints(edge a) {
		cout << a.getfirstpoint().getx() << " " << a.getfirstpoint().gety() << ", " << a.getsecondpoint().getx() << " " << a.getsecondpoint().gety() << endl;
		cout << "distance is" << a.getdistance() << endl;
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


	int point::getindex() {
		return index;
	}

	edge::edge(point a, point b) {
		if (a.getx() < b.getx()) {
			line.push_back(a);
			line.push_back(b);
		}
		if (a.getx() == b.getx()) {
			if (a.gety() < b.gety()) {
				line.push_back(a);
				line.push_back(b);
			}
			else {
				line.push_back(b);
				line.push_back(a);
			}
		}
		if (a.getx() > b.getx()) {
			line.push_back(b);
			line.push_back(a);
		}
		distance = sqrt(pow((line.at(1).gety()-line.at(0).gety()),2) + pow((line.at(1).getx()-line.at(0).getx()),2));
	}

	edge::~edge() {
		if (line.size() > 0) {
			line.clear();
		}
	}
		
	point edge::getfirstpoint() {
		return line.at(0);
	}

	point edge::getsecondpoint() {
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

	bool checkpoints(point a, point b) {
		if ((a.getx() == b.getx()) && (a.gety() == b.gety())) {
			return true;
		}
		else {
			return false;
		}
	}

	int checkvector(vector<point> a, point b) {
		for (int i = a.size()-1; i >= 0; i--) {
			if (checkpoints(a.at(i), b) == true) {
				return i;
			}
			else {
				continue;
			}
		}
		return -1;
	}

	bool graph::checkforcycleutility(vector<edge> input, edge a) {
		cout << "final decision" << endl;
		if (solution.size() == 0) {
			return true;
		}
		vector<point> temp;
		for (int i = 0; i < input.size(); i++) {
			temp.push_back(input.at(i).getfirstpoint());
			temp.push_back(input.at(i).getsecondpoint());
		}
		point first(a.getfirstpoint().getx(),a.getfirstpoint().gety(), a.getfirstpoint().getindex());
		if (checkvector(temp,first) != -1) {
			if (checkvector(temp,first) < (temp.size()-2)) {
				cout << "ousted" << endl;
				return false;
			}
		}
		point second(a.getsecondpoint().getx(), a.getsecondpoint().gety(), a.getsecondpoint().getindex());
		if (checkvector(temp,second) != -1) {
			if (checkvector(temp,second) < (temp.size()-2)) {
				cout << "ousted2" << endl;
				return false;
			}
		}
		return true;
	}


	bool checkedges(edge a, edge b) {
		if (checkpoints(a.getfirstpoint(), b.getfirstpoint()) == true) {
			return true;
		}
		if (checkpoints(a.getsecondpoint(), b.getfirstpoint()) == true) {
			return true;
		}
		if (checkpoints(a.getfirstpoint(), b.getsecondpoint()) == true) {
			return true;
		}
		if (checkpoints(a.getsecondpoint(), b.getsecondpoint()) == true) {
			return true;
		}
		return false;
	}

	bool comparevectortoedge(vector<edge> input, edge a) {
		for (int i = 0; i < input.size(); i++) {
			if (checkedges(input.at(i),a) == true) {
				return true;
			}
			else {
				continue;
			}
		}
		return false;
	}

	bool graph::checkforcycle(vector<edge> input, edge a) { //returns true if there is no cycle, false if there is
		cout << "entered" << endl;
		for (int i = 0; i < input.size(); i++) {
			printpoints(input.at(i));
		}
		cout << "edge in contention is ";
		printpoints(a);
		if (input.size() == 0) {
			return true;
		}
		cout << "sure" << endl;
		bool allinone;
		allinone = true;
		vector<edge> input1;
		vector<edge> input2;
		int size1;
		size1 = 0;
		input1.push_back(input.at(0));
		for (int i = 1; i < input.size(); i++) {
			if (comparevectortoedge(input1,input.at(i)) == true) {
				input1.push_back(input.at(i));
				size1++;
			}
			else {
				input2.push_back(input.at(i));
				allinone = false;
			}
		}
		if (allinone == true) {
			return checkforcycleutility(input1,a);
		}
		return (checkforcycle(input1,a) && (checkforcycle(input2,a)));
	}

	
	void graph::addedge(edge a) {
		cout << "mark" << endl;
		if (checkforcycle(solution,a) == false) {
			return;
		}
		cout << "Sure" << endl;
		edge input(a.getfirstpoint(),a.getsecondpoint());
		solution.push_back(input);
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
		for (int i = 0; i < realinput.size(); i++) {
			printpoints(realinput.at(i));
		}
		std::sort(realinput.begin(), realinput.end());
		cout << "look at me now" << endl;
		for (int i = 0; i < realinput.size(); i++) {
			printpoints(realinput.at(i));
		}
		cout << "yeah im good" << endl;
		for (int i = 0; i < numberofedges; i++) {
			addedge(realinput.at(i));
		}
	}

	void graph::printgraph() {
		cout << "printing solution" << endl;
		//cout << solution.size() << endl;
		for (int i = 0; i < solution.size(); i++) {
			cout << solution.at(i).getfirstpoint().getindex() << " " << solution.at(i).getsecondpoint().getindex() << endl;
		}
	}




