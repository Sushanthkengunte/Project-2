/////////////////////////////////////////////////////////////////////
//  SCC.h - Finds the strongly connected components                //
//  ver 1.0                                                        //
//                                                                 //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Lenovo , Windows 10      			           //
//  Application:   CodeAnalysis - CIS 687 Project 2                //
//  Author:        Sushanth Suresh SUID:987471535			       //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
It defines two classes Graph database class and an SCC class
*SCC works as a container class finding all the strongly connected
components using the Tarjan's algorithm
*Graph class creates a graph containing a vertex set and a adjacency
list at run time.


Public Interface:
=================
SCC class contains
getUniquetable()
BuildTheGraph()							// builds the graph of all the files
getStrongCompenents()					//returns all the strongly connected components
getName()								//returns file name for its ID
getID()							       // returns the ID of a file
createUniqueID()					   //creates a unique ID for each file
persistsIntoXml()						//save the SCC into XML

Graph Class contains

intializeGraph(int V)			// set the number of vertices
getAllTheSCC()					//all the strongly connected components
void addEdge(int v, int w)    // function to add an edge to graph
StronglyCconnectedComponent() //public interface to find the SCC


Build Process:
==============
Required files
-NoSqlDb.h
-XmlDocument.h
-XmlElement.h
-XmlWriter.h


Build commands (either one)

- devenv SCC.sln


Maintenance History:
====================
ver 2.0 : used only creation and edition
ver 1.0 : 07 Feb 17
- first release
*/
#pragma once
#include<iostream>
#include<list>
#include<stack>

#include"../NoSqlDb/NoSqlDb.h"
#include"../XMLnew/XmlDocument/XmlDocument.h"
#include"../XMLnew/XmlElement/XmlElement.h"
#include"../XMLnew/XmlWriter/XmlWriter.h"

class Graph
{
private:
	int NumberOfVertex;    // count of vertex set
	std::list<int> *adjacency;    // adjacency list created in run time
	std::unordered_map<int, std::vector<int>> allTheSCC;	//stores all the Strongly connected components
	void findingSCC(int startingVextex, int timeToFInd[], int foundtLow[],std::stack<int> *stpointer, bool marking[]);
	int min_(int a, int b);

public:
	void intializeGraph(int V);    
	std::unordered_map<int, std::vector<int>>& getAllTheSCC();
	void addEdge(int v, int w);   // function to add an edge to graph
	void StronglyCconnectedComponent();    
	~Graph();
};

class SCC
{
public:
	SCC(NoSqlDb<std::string>& database) :db_SCC(database) {
		g.intializeGraph(db_SCC.count());
		createUniqueID();
	};
	~SCC();
	std::unordered_map<std::string, int> getUniquetable();	
	void BuildTheGraph();									// builds the graph of all the files
	std::unordered_map<int, std::vector<int>>& getStrongCompenents();	//returns all the strongly connected components
	std::string getName(int i);								//returns file name for its ID
	int getID(std::string);									// returns the ID of a file
	void createUniqueID();									//creates a unique ID for each file
	void ComputeSCC();
	void persistsIntoXml();
private:
	NoSqlDb<std::string> db_SCC;
	Graph g;
	std::unordered_map<std::string, int> uniques;
	
};

