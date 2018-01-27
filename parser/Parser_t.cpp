#include "Parser_t.h"
#include "Tokenizer_t.h"
#include "Analyzer_t.h"
#include <string.h>
#include <fstream>
#include <stddef.h>	// size_t 

using namespace std;


/********************************************************/
			// CTOR from char*
/********************************************************/
Parser_t:: Parser_t(): m_tokenaizer(0), m_analyzer(0)
{	
	try
	{
		m_tokenaizer = new Tokenizer_t;
		m_analyzer = new Analyzer_t;	
	}
	catch (bad_alloc& ba)
	{
		delete m_analyzer;
		delete m_tokenaizer;
		throw;
	}
}

/********************************************************/
			//DTOR
/********************************************************/
Parser_t:: ~Parser_t()
{
	m_file.close();
	
	if (m_analyzer)
	{
		delete m_analyzer;
		m_analyzer = 0;	
	}
	
	if (m_tokenaizer)
	{
		delete m_tokenaizer;
		m_tokenaizer = 0;	
	}
}


/********************************************************/
			//GetLine
/********************************************************/
bool Parser_t:: Run(const string& _pathName)
{
	string line;
	string token;
	size_t lineNum = 1;
	
	m_file.open(_pathName.c_str());
	if (!m_file.good())
	{
		return false;
	}
	
	while (getline(m_file, line))
	{
		// split line into tokens and insert into m_tokens container
		queue<string>& tokensContainer = m_tokenaizer->SplitLine(line);
		
		// send tokens to analayzer one by one until container is empty
		while (!tokensContainer.empty())
		{
			token = tokensContainer.front();
			tokensContainer.pop();
			m_analyzer->AnalyzeToken(token, lineNum);
		}
		
		++lineNum;
	}
	
	m_analyzer->PrintEndFileErrors();
	m_analyzer->ClearAnalyzer();
	m_file.close();
	
	return true;
}















