#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <fstream>

using namespace std;

class Tokenizer_t;
class Analyzer_t;
 
/*************************************************/

class Parser_t 
{
public:

	virtual				~Parser_t();					// DTOR			
						Parser_t();						// default CTOR				
	bool				Run(const string& _pathName);
	
protected:
															
private:
	
						Parser_t(const Parser_t& _parser);		// copy CTOR
	const Parser_t& 	operator = (const Parser_t& _parser);	// asignment operator
	
	ifstream 			m_file;
	Tokenizer_t* 		m_tokenaizer;
	Analyzer_t*			m_analyzer;

};


#endif /* __PARSER_H__ */
