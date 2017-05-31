/////////////////////////////////////////////////////////////////////
// Display.cpp - Displaying TypeTable,Strongcomponents             //
//              and dependency analysis ver 1.0                    //
//-----------------------------------------------------------------//
// Language:    C++, Visual Studio 2015                            //
// Platform:    Lenovo, Windows 10                                 //
// Application: Project #2, CSE687 - Object Oriented Design, S2015 //
// Author:		sushanth suresh SUID:987471535					   //
//		       					                                   //
/////////////////////////////////////////////////////////////////////
#include"Display.h"
Display::Display()
{
}

Display::~Display()
{
}
//--------displays the type table taking type Table Reference---------------------------//
void Display::showTypeTable(std::unordered_map<std::string, std::vector<CodeAnalysis::Tuple>>& tTable)
{
	try
	{
		std::ostringstream out;

		out.setf(std::ios::adjustfield, std::ios::left);
		out << "\n \nType Table for all the files in the folder";
		out << "\n    " << std::setw(20) << " All Elements in Type Table";
		out << "\n    " << std::setw(30) << "Key" << std::setw(18) << "Type" << std::setw(23) << "Namespace" << std::setw(10) << "File path";
		out << "\n    " << std::setw(30) << "------" << std::setw(18) << "---------" << std::setw(23) << "---------" << std::setw(10) << "---------";
		for (auto item : tTable)
			for (auto each : tTable[item.first]) {
				out << "\n    " << std::setw(25) << item.first;
				out << showTuple(each);

			}
		std::cout << out.str();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

}
//------------------Displays the dependency Table-----------------//
void Display::showDependencyTable(NoSqlDb<std::string>& depenTable)
{
	try
	{
		std::cout << "\n \nDisplaying Dependency table";
		std::cout << "\n";
		std::cout << depenTable.toXml();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	
}
//---------------displays each element----------//
void Display::showNoSQL(Element<std::string>& eachElementinDB)
{
	try
	{
		std::ostringstream out;
		out << "\n    " << std::setw(8) << "name" << " : " << eachElementinDB.name;
		std::vector<std::string> children_ = static_cast<std::vector<std::string>>(eachElementinDB.children);
		if (children_.size() > 0)
		{
			out << "\n    " << std::setw(8) << "children" << " : ";
			for (size_t i = 0; i < children_.size(); ++i)
			{
				out << children_[i];
				if (i < children_.size())
					out << "  ,   ";
			}
		}
		out << "\n";
		std::cout << out.str();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

}

//---------------Dispplays the Strongly connected graphs---------------------------------//
void Display::showStronglyConnectedGraph(SCC& strongComponents)
{
	std::cout << "\n\n Displaying all the strongly connected graph in xml format";
	std::string theDocument;
	std::unordered_map<int, std::vector<int>>& sCGraph = strongComponents.getStrongCompenents();
	std::cout << "\n\n Number Of SCC:" << sCGraph.size() << "\n\n\n";
	XmlWriter wrg;
	try {
		int count = 1;

		wrg.indent();
		wrg.start("Strongly Connected Components");
		for (auto vert : sCGraph) {
			wrg.start("SCC");//wrg.addAttribute("Name", "SCC");				
			std::vector<int> x = sCGraph[vert.first];
			for (auto edge : x) {
				wrg.start("files");
				wrg.addBody(strongComponents.getName(edge));
				wrg.end();
			}
			wrg.end();
		}
		wrg.end();
		theDocument = wrg.xml();

	}
	catch (const std::exception& e) {
		std::cout << "exception:" << e.what();
	}
	std::cout << theDocument;	
}

//-------------------Displays values of type Table--------------------------//


std::string Display::showTuple(CodeAnalysis::Tuple& elementsOfTuple)
{

	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	out<< std::setw(18) << elementsOfTuple.getType() << std::setw(23) << elementsOfTuple.getNamespace() << std::setw(10) << elementsOfTuple.getFileName()<<"\n";
	return out.str();
}


#ifdef DISPLAY_TEST
#include <fstream>
#include "../Analyzer/Executive.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <exception>
#include <iomanip>
#include <chrono>
#include <ctime>

#include "../Parser/Parser.h"
#include "../FileSystem/FileSystem.h"
#include "../FileMgr/FileMgr.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../AbstractSyntaxTree/AbstrSynTree.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"
#include "../TypeTable/TypeTable.h"
#include "../DependencyAnalysis/DependencyAnalysis.h"
#include "../NoSqlDb/NoSqlDb.h"
#include "../StronglyConnectedComponents/StronglyConnectedComponents.h"
#include"../Display/Display.h"

using Rslt = Logging::StaticLogger<0>;  // use for application results
using Demo = Logging::StaticLogger<1>;  // use for demonstrations of processing
using Dbug = Logging::StaticLogger<2>;

using namespace CodeAnalysis;
void executefuncionality1(CodeAnalysisExecutive& exec) {
	exec.setDisplayModes();
	exec.startLogger(std::cout);

	std::ostringstream tOut("CodeAnalysis - Version 1.4");
	Utils::sTitle(tOut.str(), 3, 92, tOut, '=');
	Rslt::write(tOut.str());

	//Rslt::write("\n     " + exec.getAnalysisPath());
	Rslt::write("\n     " + exec.systemTime());
	Rslt::flush();
}
void executefuncionality2(CodeAnalysisExecutive& exec) {

	exec.getSourceFiles();
	exec.processSourceCode(true);
	exec.complexityAnalysis();
	exec.dispatchOptionalDisplays();
	exec.flushLogger();
	exec.displayMetricSummary(50, 10);

	exec.flushLogger();
	Rslt::write("\n");
	std::ostringstream out;
	out << "\n  " << std::setw(10) << "searched" << std::setw(6) << exec.numDirs() << " dirs";
	out << "\n  " << std::setw(10) << "processed" << std::setw(6) << exec.numFiles() << " files";
	Rslt::write(out.str());
	Rslt::write("\n");
	exec.stopLogger();
	std::cout << "\n  Code Analysis completed";
}
int main(int argc, char* argv[])
{
	using namespace CodeAnalysis;
	CodeAnalysisExecutive exec;
	try {
		bool succeeded = exec.ProcessCommandLine(argc, argv);
		if (!succeeded)
		{
			return 1;
		}
		executefuncionality1(exec);
		exec.showCommandLineArguments(argc, argv);
		Rslt::write("\n");
		Display disp;
		DependencyAnalysis d(exec.getFileMap());
		d.doDependAnal();
		NoSqlDb<std::string> database;
		database = d.getDatabase();
		disp.showTypeTable(d.getTheTable());
		disp.showDependencyTable(database);
		database.toXml();
		SCC getSCC(database);
		getSCC.BuildTheGraph();
		getSCC.ComputeSCC();
		disp.showStronglyConnectedGraph(getSCC, database);
	}
	catch (std::exception& except)
	{
		exec.flushLogger();
		std::cout << "\n\n  caught exception in Executive::main: " + std::string(except.what()) + "\n\n";
		exec.stopLogger();
		return 1;
	}
	return 0;
}
#endif // DISPLAY_TEST