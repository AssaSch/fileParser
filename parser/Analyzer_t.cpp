#include "Analyzer_t.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

#define KRED  "\x1B[31m"
#define KWHT  "\x1B[37m"

#define PLUS_MINUS_MAX 2

string Analyzer_t:: m_typesString[] = {"char", "short", "int", "long", "float", "double", "void"};
string Analyzer_t::	m_keyWordsString[] = {"if", "else", "for", "while", "class", "private", "public", "protected", "const", "virtual"};
string Analyzer_t::	m_delimetersString[] = {"(", ")", "[", "]", "{", "}", ";", "<", ">", "=", "+", "-", "*", "&"};

/********************************************************/
			// default CTOR
/********************************************************/
Analyzer_t:: Analyzer_t(): m_preDefinedTypes(m_typesString, m_typesString + sizeof(m_typesString)/sizeof(string)),
							m_keyWords(m_keyWordsString, m_keyWordsString + sizeof(m_keyWordsString)/sizeof(string)),
							m_delimiters(m_delimetersString, m_delimetersString + sizeof(m_delimetersString)/sizeof(string))  
{	
	m_bracesCounter = 0;
	m_bracketsCounter = 0;
	m_parenthesesCounter = 0;
	m_plusCounter = 0;
	m_minusCounter = 0;	
	m_ifFlag = false;
	m_firstToken = true;
	m_prevTokenPredefType = false;
}

/********************************************************/
			//DTOR
/********************************************************/
Analyzer_t:: ~Analyzer_t()
{
	
}

/********************************************************/
			//AnalyzeToken
/********************************************************/
void Analyzer_t:: AnalyzeToken(const string& _token, size_t _lineNum)
{
	// check for main as first token
	if (m_firstToken)
	{
		if ("main" != _token)
		{
			cout << "line " << _lineNum << ":" << KRED << "error: " << KWHT << " illegal - declaration before 'main'" << endl;
		}
		
		m_firstToken = false;
	}
	
	if ("main" == _token)
	{
		return;
	}
	
	if ("if" == _token && !m_ifFlag)
	{
		m_ifFlag = true;
		return;
	}
	
	// check for else before if
	if ("else" == _token && !m_ifFlag)
	{
		cout << "line " << _lineNum << ":" << KRED << "error: " << KWHT << " “else” without “if”" << KWHT << endl;
		return;
	}
	
	// if current token is not predefined type
	if (m_preDefinedTypes.find(_token) == m_preDefinedTypes.end())
	{
		// if previous token is predefined type
		if (m_prevTokenPredefType)
		{
			// if current token is not key word, not inside params container and a valid name - insert to param container
			if (m_keyWords.find(_token) == m_keyWords.end() && m_userParams.find(_token) == m_userParams.end() && 
				(isalpha(_token[0]) || _token[0] == '_'))
			{
				m_userParams.insert(_token);
			}
			// if current token is key word or not a valid name - print error
			else if (m_keyWords.find(_token) != m_keyWords.end() || !(isalpha(_token[0]) || _token[0] == '_'))
			{
				cout << "line " << _lineNum << ":" << KRED << "error:" << KWHT << " '" << _token << "' illegal variable name" << endl;
			}
			// if current token is allready declared param - print error
			else if (m_userParams.find(_token) != m_userParams.end())
			{
				cout << "line " << _lineNum << ":" << KRED << "error:" << KWHT << " '" << _token << "' variable already declared" << endl;
			}
		}
		// if current token is not predefined type and previous token is not predefined type and is not already declared - print error
		else if (m_userParams.find(_token) == m_userParams.end() && m_keyWords.find(_token) == m_keyWords.end() && 
				m_delimiters.find(_token) == m_delimiters.end())
		{
			cout << "line " << _lineNum << ":" << KRED << "error:" << KWHT << " '" << _token << "' variable is not declared" << endl;
		}
		
		m_prevTokenPredefType = false;
	}
	
	// check for () [] {} + -
	CheckErrorPlusMinusTokens(_token, _lineNum);
	CountOpenCloseTokens(_token);
	CheckErrorOpenCloseTokens(_token, _lineNum);
	
	// check if token is predefined type
	if (m_preDefinedTypes.find(_token) != m_preDefinedTypes.end())
	{
		// check for multiple type declaration
		if (m_prevTokenPredefType)
		{
			m_prevTokenPredefType = false;
			cout << "line " << _lineNum << ":" << KRED << "error: " << KWHT << " multiple type declaration" << endl;
		}
		else
		{
			m_prevTokenPredefType = true;		
		}
		
		return;
	}
}

/********************************************************/
			//AnalyzeToken
/********************************************************/
void Analyzer_t:: CountOpenCloseTokens(const string& _token)
{
	if (_token == "(")
	{
		++m_parenthesesCounter;
	}
	else if (_token == "[")
	{
		++m_bracketsCounter;
	}
	else if (_token == "{")
	{
		++m_bracesCounter;
	}
	else if (_token == ")")
	{
		--m_parenthesesCounter;
	}
	else if (_token == "]")
	{
		--m_bracketsCounter;
	}
	else if (_token == "}")
	{
		--m_bracesCounter;
	}
}

/********************************************************/
			//AnalyzeToken
/********************************************************/
void Analyzer_t:: CheckErrorOpenCloseTokens(const string& _token, size_t _lineNum)
{
	if (0 > m_bracesCounter)
	{
		m_bracesCounter = 0;
		cout << "line " << _lineNum << ":" << KRED << "error: " << KWHT << " “}” without “{“" << endl;
	}
	
	if (0 > m_bracketsCounter)
	{
		m_bracketsCounter = 0;
		cout << "line " << _lineNum << ":" << KRED << "error: " << KWHT << " “]” without “[“" << endl;
	}
	
	if (0 > m_parenthesesCounter)
	{
		m_parenthesesCounter = 0;
		cout << "line " << _lineNum << ":" << KRED << "error: " << KWHT << " “)” without “(“" << endl;
	}
}

/********************************************************/
			//ClearAnalyzer
/********************************************************/
void Analyzer_t:: ClearAnalyzer()
{
	m_bracesCounter = 0;
	m_bracketsCounter = 0;
	m_parenthesesCounter = 0;
	m_plusCounter = 0;
	m_minusCounter = 0;	
	m_ifFlag = false;
	m_firstToken = true;
	m_prevTokenPredefType = false;
	m_userParams.clear();

}

/********************************************************/
			//CheckErrorPlusMinusTokens
/********************************************************/
void Analyzer_t:: CheckErrorPlusMinusTokens(const string& _token, size_t _lineNum)
{
	// check for too many '+' 
	if ("+" == _token)
	{
		++m_plusCounter;
		if(PLUS_MINUS_MAX < m_plusCounter)
		{
			cout << "line " << _lineNum << ":" << KRED << "error: " << KWHT << " no operator +++" << endl;
			m_plusCounter = 0;
			return;
		}
	}
	else
	{
		m_plusCounter = 0;
	}
	
	// check for too many '-' 
	if ("-" == _token)
	{
		++m_minusCounter;
		if(PLUS_MINUS_MAX < m_minusCounter)
		{
			cout << "line " << _lineNum << ":" << KRED << "error: " << KWHT << " no operator ---" << endl;
			m_minusCounter = 0;
			return;
		}
	}
	else
	{
		m_minusCounter = 0;
	}
}

/********************************************************/
			//CheckErrorPlusMinusTokens
/********************************************************/
void Analyzer_t:: PrintEndFileErrors() const
{
	if (m_bracesCounter)
	{
		cout << KRED << " error: " << KWHT << m_bracesCounter << " '{' not closed" << endl;
	}

	if (m_bracketsCounter)
	{
		cout << KRED << " error: " << KWHT << m_bracketsCounter << " '[' not closed" << endl;
	}
	
	if (m_parenthesesCounter)
	{
		cout << KRED << " error: " << KWHT << m_parenthesesCounter << " '(' not closed" << endl;
	}
}












