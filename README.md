# fileParser
Parser & Syntax/Semantic Analyzer 

Parser is a program which reads input ASCII files and analyzes them.
Parser reads input lines and divides them into tokens. 
The delimiter between tokens can be ‘blank(s)’ or ‘tab(s)’ characters. 
All tokens are divided into 2 kinds - predefined and user-defined. 
Following is a list of predefined tokens:

Predefined Types:
 “char”, “short”, “int”, “long”, “float”, “double”, “void”
Predefined Type can be followed only by legal variable name

	Key words 
		“if”, “else”, “for” , “while”, “class”, 
		“private”, “public”, “protected”, “main”, “const”, “virtual”

	Operators:
		“++”, “--“, “==”, “->” , “=”, “+”, “-“, “*”, “&”, “<<”, “>>”

	Following predefined tokens also play a role of delimiter:
		“(“, ”), “[“, “]” , “{“ , “}” “;” “<”, “>” , “=”, “+”, “-“, “*”, “&”
 
	Example:
		if(a) really 4 tokens : 'if',  '('  ,  'a',   ')'
 
Language Rules:

1. The program has to start from "main" function.

int i;			// line 1:  error, illegal - declaration before 'main'
main {
…
}	

2. Any sequence of tokens is legal except the list of Possible Errors ( see below).

3. Possible errors:

a)  Number of open braces doesn’t match number of close braces.
([a) 	- //  one '[' not closed ( at end of file )
) ( 	- // line 10  : error,is illegal  ‘(‘ has to be before ‘)’

b)  ‘else’ without ‘if’

c)  multiple Predefined Types::
int short k;		// line 12 : error, error multiple type declaration
			// line 12 : k isn't defined
double char c;		// line 14: error, error multiple type declaration
			// line 14: c isn't defined
…
d)  illegal operators,  examples:
+++ , ---			// line 17: error, no operator +++ or ---
+
+
+				// tline 20: error, no operator +++  

e)  already declared:
int k;
float k;				// line 20 : error, variable 'k' already declared

  f) 	foo() {				// line 112 : foo is not declared
		abc			// line 113 : abc is not declared
		…
	}		

Notes: 

a)	the following code is legal:
	const virtual const const private

b)	the following code is illegal
	int virtual
