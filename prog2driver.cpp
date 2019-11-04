#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <cstdlib>
#include <math.h>
using namespace std;
#include "prog2.h"



int main(int argc,  char **argv) {
	string filename;
	ifstream inputfile;
	//ofstream outfile("sum.txt");
	if (argc < 2) {
		cout << "too short" << endl;
		return 0;
	}
	filename=argv[1];
	if (argc>0) {
		fstream inputfile;
		inputfile.open(filename);
		string word;

		//if(inputfile.is_open()) {
		//	ofstream outfile("sum.txt");
		//}
		bool numberofpointsready = false;
		bool numberofedgesready = false; 
		int numberofpoints;
		int numberofedges;
		int counter1 = 0;
		vector<point> input;
		vector<int> edges;
		//while (inputfile >> word) {
		while( getline(inputfile, word) ) {
			if ((numberofpointsready == false) && (numberofedgesready == false)) {
				numberofpoints = stoi(word);
				numberofpointsready = true;
				continue;
			}
			if ((numberofpointsready == true) && (numberofedgesready == false)) {
				int index;
				index = word.find_first_of(" ");
				int length1;
				length1 = index;
				int length2;
				length2 = word.size() - length1 - 1;
				string a;
				string b;
				a = word.substr(0,length1);
				b = word.substr(index+1,length2);
				double input1 = std::stod(a);
				double input2 = std::stod(b);
				point inputpoint(input1,input2,counter1);
				input.push_back(inputpoint);
				counter1++;
				if (counter1 == numberofpoints) {
					numberofedgesready = true;
				}
				continue;
			} 
			if ((numberofedgesready == true) && (numberofpointsready == true)) {
				numberofedges = stoi(word);
				numberofpointsready = false;
				continue;
			}
			if ((numberofedgesready == true) && (numberofpointsready == false)) {
				int index;
				index = word.find_first_of(" ");
				int length1;
				length1 = index;
				int length2;
				length2 = word.size() - length1 - 1;
				string a;
				string b;
				a = word.substr(0,length1);
				b = word.substr(index+1,length2);
				int input1 = std::stod(a);
				int input2 = std::stod(b);
				edges.push_back(input1);
				edges.push_back(input2);
				continue;
			}
		}
		graph test;
		test.addtograph(numberofpoints,input,numberofedges,edges);
		test.printgraph();
	}
	else {
		cout<<"Incorrect input"<<endl;
	}
	return 0;
}

	
