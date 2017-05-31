/////////////////////////////////////////////////////////////////////
//  Display.h - Displays type table, File Dependencies and         //
//				strongly connected components ver 1.0              //
//                                                                 //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Lenovo , Windows 10      			           //
//  Application:   CodeAnalysis - CIS 687 Project 2                //
//  Author:        Sushanth Suresh SUID:987471535			       //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This displays 
-typeTable in a tabular manner a
-file dependencies in Xml format
-strongly connected in Xml format and also persists into a file

Public Interface:
=================
showTypeTable()						// Displays the type Table Generated
showDependencyTable()				//Displays the dependency database
showStronglyConnectedGraph()		//displays the strongly connected components



Build Process:
==============
Required files
TypeTable.h
StronglyConnectedComponents.h
NoSqlDb.h
XmlDocument.h
XmlElement.h
XmlWriter.h



Build commands (either one)

- devenv SCC.sln


Maintenance History:
====================
ver 2.0 : used only creation and edition
ver 1.0 : 07 Feb 17
- first release
*/


#pragma once
#include"../TypeTable/TypeTable.h"
#include "../StronglyConnectedComponents/StronglyConnectedComponents.h"
#include"../NoSqlDb/NoSqlDb.h"
#include"../XMLnew/XmlDocument/XmlDocument.h"
#include"../XMLnew/XmlElement/XmlElement.h"
#include"../XMLnew/XmlWriter/XmlWriter.h"

class Display
{
public:
	Display();
	~Display();
	void showTypeTable(std::unordered_map<std::string, std::vector<CodeAnalysis::Tuple>>& tTable); // Displays the type Table Generated
	void showDependencyTable(NoSqlDb<std::string>& depenTable);									//Displays the dependency database
	void showStronglyConnectedGraph(SCC& strongComponents);		//displays the strongly connected components
	

private:
	void showNoSQL(Element<std::string>& eachElementinDB);										//shows the element in the NoSql
	std::string showTuple(CodeAnalysis::Tuple& elementsOfTuple);								//shows the tuple values
};




