# Lithium

An imperative programming language

# About Lithium:

We have created an imperative language named "Lithium" for the programming assignments of the course titled 'Compiler Construction' (CS F363).

Every lithium code file should have a .lth extension.

Following is a list of its tokens:	

	1. Keywords: boolean, true, false, if, else, while, double, do, func, for, float, char, int, return, void, break, continue
  
	2. Operators: &, &&, |, ||, !, !=, =, ==, ^, ~, >, >>, >=, <, <<, <=, :, ?, *, \**, %, /, +, ++, -, --
  
	3. Delimiters: ',', {, }, (, ), ;, [, ]
  
	4. Integer literals: [0-9]+
  
	5. Floating point literals: [0-9]+(e|.[0-9]*e)[0-9]+
  
	6. Character literals: '([^\]|(\['?\abfnrtv]))'
  
	7. String literals: "([^\]|(\["?\abfnrtv]))*"
  
Note: Comments in Lithium should be enclosed within two '#' symbols. For example: #This is a comment#

# About the lexer:

We have created a general purpose lexer which can be run by compiling and running the 'lexer.c' file.

On running this file, the user is asked for the name of the file containing the lexer rules of the language and the name of file containing the code.

The format of the lexer rules file should be as follows:

	t (number of tokens)
  
	The next t lines contain the names of the tokens
  
	k (number of keywords)
  
	The next k lines contain the names of the keywords
  
	n (number of states in the DFA)
  
	f (number of final states)
  
	The next 2*f lines contain the state number and the corresponding token number, each on a separate line
  
	tr (number of transitions)
  
	The next 3*t lines contain the 'from' state, the 'to' state and the characters on which the transition has to be made, each on a separate line
  
	The characters indicating the beginning and end of a comment
  
	The token number of identifiers

The rule file for Lithium is "Lithium.lex". The codes are in files with extensions .lth.
