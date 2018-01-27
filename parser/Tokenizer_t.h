#ifndef __TOKENAIZER_H__
#define __TOKENAIZER_H__

#include <stddef.h>	// size_t 
#include <string>
#include <queue>

using namespace std;

/*************************************************/

class Tokenizer_t 
{
public:

	virtual					~Tokenizer_t();							// DTOR			
							Tokenizer_t();							// default CTOR
	queue<string>&			SplitLine(const string& _line);
	
protected:
															
private:
		
							Tokenizer_t(const Tokenizer_t& _token);	// copy CTOR
	const Tokenizer_t& 		operator = (const Tokenizer_t& _token);	// asignment operator
	
	string		 			m_delimiters;
	queue<string> 			m_tokens;
	
};


#endif /* __TOKENAIZER_H__ */
