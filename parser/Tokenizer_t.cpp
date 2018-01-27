#include "Tokenizer_t.h"
#include <string>

using namespace std;


/********************************************************/
			// default CTOR
/********************************************************/
Tokenizer_t:: Tokenizer_t(): m_delimiters("()[]{};<>=+-*& \t\n\r\0") 
{	
	
}

/********************************************************/
			//DTOR
/********************************************************/
Tokenizer_t:: ~Tokenizer_t()
{
	
}

/********************************************************/
			//SplitLine
/********************************************************/
queue<string>& Tokenizer_t:: SplitLine(const string& _line)
{
	size_t pos = 0;
	size_t tempPos = 0;
	string token;
	size_t strLength = _line.length();
	
	// split to tokens acc. to delimeters
	while ((tempPos = _line.find_first_of(m_delimiters, pos)) != string::npos)
	{
		if (tempPos > pos)
		{
			token.assign(_line, pos, tempPos - pos);
			m_tokens.push(token);
			token.clear();
		}
		
		if (_line[tempPos] != ' ' && _line[tempPos] != '\t' && _line[tempPos] != '\n' && _line[tempPos] != '\0' && _line[tempPos] != '\r')
		{
			token = _line[tempPos];
			m_tokens.push(token);
			token.clear();
		}
		
		tempPos += 1;
		pos = tempPos;
	}
	
	// insert to container only if not allready at end of line
	if (strLength > pos)
	{
		token.assign(_line, pos, strLength - pos);
		m_tokens.push(token);	
	}
	
	return m_tokens;
}




















