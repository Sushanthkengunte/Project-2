/////////////////////////////////////////////////////////////////////
// SCC.cpp - Finds the strongly connected components               //
// ver 1.0                                                         //
//-----------------------------------------------------------------//
// Language:    C++, Visual Studio 2015                            //
// Platform:    Lenovo, Windows 10                                 //
// Application: Project #2, CSE687 - Object Oriented Design, S2015 //
// Author:		sushanth suresh SUID:987471535					   //
//		       					                                   //
/////////////////////////////////////////////////////////////////////
#include"../NoSqlDb/NoSqlDb.h"
#include "StronglyConnectedComponents.h"
#include<iostream>

//---------gets the minimum of two values------------//
int Graph::min_(int a, int b) {
	if ((a) < (b))
		return a;
	return b;
}
Graph::~Graph()
{
	try
	{
		delete[] adjacency;
	}
	catch (...)
	{
		std::cout << " Memory deleted";
	}
	
}
//-----------retuns the strongly Connected graph--------------------//
std::unordered_map<int, std::vector<int>>& Graph::getAllTheSCC() {
	return allTheSCC;
}
//-------------adds an edge to the existing graph-------------------//
void Graph::addEdge(int first, int second)
{
	adjacency[first].push_back(second);
}
//----------creates the grpah with its vertex set and adjacency set--------//
void Graph::intializeGraph(int vertexSet)
{
	NumberOfVertex = vertexSet;
	adjacency = new std::list<int>[NumberOfVertex];

}
//------------finds all the strongly connected components-------------------//
void Graph::findingSCC(int startingVextex, int timeToFInd[], int foundtLow[], std::stack<int> *stpointer, bool marking[]) {
	try
	{
		static int disctime = 0;		//Counter to keep the discovery time
		static std::vector<int> temp;
		timeToFInd[startingVextex] = foundtLow[startingVextex] = ++disctime;
		stpointer->push(startingVextex);
		marking[startingVextex] = true;
		std::list<int>::iterator i;	// Recursively call to all the vertex that is reachable from stating vertex
		for (i = adjacency[startingVextex].begin(); i != adjacency[startingVextex].end(); ++i)
		{
			int reachableVertex = *i;
			if (timeToFInd[reachableVertex] == -1) //Not visited 
			{
				findingSCC(reachableVertex, timeToFInd, foundtLow, stpointer, marking);
				foundtLow[startingVextex] = min_(foundtLow[startingVextex], foundtLow[reachableVertex]);
			}
			else if (marking[reachableVertex] == true)
				foundtLow[startingVextex] = min_(foundtLow[startingVextex], timeToFInd[reachableVertex]);
		}
		int topOfStack = 0;  // To store stack extracted vertices
		if (foundtLow[startingVextex] == timeToFInd[startingVextex])
		{
			while (stpointer->top() != startingVextex)
			{
				topOfStack = (int)stpointer->top();
				temp = allTheSCC[startingVextex];
				temp.push_back(topOfStack);
				allTheSCC[startingVextex] = temp;
				marking[topOfStack] = false;
				stpointer->pop();
			}
			topOfStack = (int)stpointer->top();
			temp.push_back(topOfStack);
			allTheSCC[startingVextex] = temp;
			temp.clear();
			marking[topOfStack] = false;
			stpointer->pop();
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}
void Graph::StronglyCconnectedComponent()
{
	try
	{
		int *timeToFInd = new int[NumberOfVertex];
		int *foundtLow = new int[NumberOfVertex];
		bool *marking = new bool[NumberOfVertex];
		std::stack<int> *stpointer = new std::stack<int>();
		// set timefound to -1 and all the vertex marked not visited
		for (int i = 0; i < NumberOfVertex; i++) {
			timeToFInd[i] = -1;
			foundtLow[i] = -1;
			marking[i] = false;
		}
		//Call the findingScc recursively
		for (int firstVertex = 0; firstVertex < NumberOfVertex; firstVertex++) {
			if (timeToFInd[firstVertex] == -1)
				findingSCC(firstVertex, timeToFInd, foundtLow, stpointer, marking);
		}
		delete[] timeToFInd;
		delete[] foundtLow;
		delete[] marking;
	}
	catch (...)
	{
		std::cout << " Memory deallocated";
	}
}


SCC::~SCC()
{
}

std::unordered_map<std::string, int> SCC::getUniquetable()
{
	return uniques;
}

void SCC::BuildTheGraph()
{
	std::vector<std::string> keyOfDB;
	keyOfDB = db_SCC.keys();
	for (auto eachKey : keyOfDB) {
		int x = getID(eachKey);
		std::vector<std::string> dependencies = db_SCC.getChildren(eachKey);
		for (auto dependsOn : dependencies) {
			int y = getID(dependsOn);
			g.addEdge(x, y);
		}
	}
}

std::unordered_map<int, std::vector<int>>& SCC::getStrongCompenents()
{
	// TODO: insert return statement here
	return g.getAllTheSCC();
}

std::string SCC::getName(int i)
{
	for (auto row : uniques)
		if (uniques[row.first] == i)
			return row.first;
	return std::string();
}

int SCC::getID(std::string keyis)
{
	if (uniques.find(keyis) != uniques.end())
		return uniques[keyis];
	return 0;
}

void SCC::createUniqueID()
{
	//NoSqlDb<std::string>& tempDatabase = getDatabase();
	int i = 0;
	std::vector<std::string> keysOfDb = db_SCC.keys();
	for (auto item : keysOfDb) {
		uniques[item] = i;
		i++;
	}
}

void SCC::ComputeSCC()
{
	g.StronglyCconnectedComponent();
}
void SCC::persistsIntoXml()
{
	std::string theDocument;
	XmlWriter wrg;
	try {
		int count = 1;
		std::unordered_map<int, std::vector<int>>& sCGraph = getStrongCompenents();
		wrg.indent();
		wrg.start("Strongly Connected Components");
		for (auto vert : sCGraph) {
			wrg.start("SCC");//wrg.addAttribute("Name", "SCC");				
			std::vector<int> x = sCGraph[vert.first];
			for (auto edge : x) {
				wrg.start("files");
				wrg.addBody(getName(edge));
				wrg.end();
			}
			wrg.end();
		}
		wrg.end();
		theDocument = wrg.xml();
		std::ofstream input_file("../graphDatabase.xml");
		input_file << theDocument;
		input_file.close();
		}
	catch (const std::exception& e) {
		std::cout << "exception:" << e.what();
	}//std::cout << theDocument;
	std::cout << "\n\n<Requirement 7>Persisting the Strongly Connected Components into graphdatabase.xml file present in the location ../xmlfiles/graphdatabase.xml\n";
}
#ifdef SCC_TEST



#include"../Display/Display.h"
int main() {
	NoSqlDb<std::string> a;
	SCC sC(a);
	sC.BuildTheGraph();
	sC.ComputeSCC();
	sC.persistsIntoXml();
	Display disp;
	disp.showStronglyConnectedGraph(sC, a);
	
}
#endif // SCC_TEST