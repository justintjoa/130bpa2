#include <iostream>
using namespace std;

class point {

public:
	point(double x, double y, int index);
	~point();
	double getx();
	double gety();
	int getindex() const;

private:
	double x;
	double y;
	int index;

};


class edge {
	public:
		edge(point a, point b);
		~edge();
		point getfirstpoint() const;
		bool operator< (const edge &other) const {
        	return distance < other.getdistance();
    	}
		point getsecondpoint() const;
		double getdistance() const;
		vector<point> getline() const;


	private:
		vector<point> line;
		double distance;


};

class subset  {  
    public: 
    int parent;  
    int rank;  
};

class graph {
	public:
		graph();
		~graph();
		void addedge(edge a);
		bool checkforcycleutility(vector<edge> input, edge a);
		bool checkforcycle(vector<edge> input, edge a);
		void addtograph(int numberofpoints, vector<point> input, int numberofedges, vector<int> edgeindexes);
		void printgraph();


	private:
		vector<edge> solution;


};

