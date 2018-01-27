#ifndef __ANALYZER_H__
#define __ANALYZER_H__

#include <stddef.h>	// size_t 
#include <string>
#include <set>
#include <map>

using namespace std;

/*************************************************/

class Analyzer_t 
{
public:
	
	virtual					~Analyzer_t();										// DTOR			
							Analyzer_t();										// default CTOR
	void					AnalyzeToken(const string& _token, size_t _lineNum);
	void					PrintEndFileErrors() const;
	void					ClearAnalyzer();
	
protected:
															
	void					CountOpenCloseTokens(const string& _token);
	void					CheckErrorOpenCloseTokens(const string& _token, size_t _lineNum);
	void					CheckErrorPlusMinusTokens(const string& _token, size_t _lineNum);
	
	
private:
							Analyzer_t(const Analyzer_t& _analyzer);	// copy CTOR
	const Analyzer_t& 		operator = (const Analyzer_t& _analyzer);	// asignment operator
	
	
	int 					m_bracesCounter;		// {}
	int 					m_bracketsCounter;		// []
	int 					m_parenthesesCounter;	// ()
	int 					m_plusCounter;			// +
	int 					m_minusCounter;			// -
	bool					m_firstToken;
	bool					m_ifFlag;
	bool					m_prevTokenPredefType;
	
	set<string> 			m_preDefinedTypes;
	set<string> 			m_keyWords;
	set<string> 			m_delimiters;
	set<string> 			m_userParams;
	static string			m_typesString[];
	static string			m_keyWordsString[];
	static string			m_delimetersString[];
};


#endif /* __ANALYZER_H__ */
