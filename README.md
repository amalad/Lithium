# Lithium
An imperative programming language

# About Lithium:

We have created an imperative language named "Lithium" for the programming assignments of the course titled 'Compiler Construction' (CS F363). Every lithium code file should have a .lth extension. Following is a list of its tokens:	
```
1. Keywords: boolean, true, false, if, else, while, double, do, func, for, float, char, int, return, void, break, continue
2. Operators: &, &&, |, ||, !, !=, =, ==, ^, ~, >, >>, >=, <, <<, <=, :, ?, *, **, %, /, +, ++, -, --
3. Delimiters: ',', {, }, (, ), ;, [, ]
4. Integer literals: [0-9]+
5. Floating point literals: [0-9]+(e|.[0-9]*e)[0-9]+
6. Character literals: '([^\]|(\['?\abfnrtv]))'
7. String literals: "([^\]|(\["?\abfnrtv]))*"
```

**Note**: Comments in Lithium should be enclosed within two '#' symbols. For example: #This is a comment#

# The lexer:
We have created a general purpose lexer which has to be fed the the name of the file containing the lexer rules of the language and the name of file containing the code.
The format of the lexer rules file should be as follows:
```
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
```
The rule file for Lithium is "Lithium.lex". The codes are in files with extensions .lth.

# The Grammar:
The grammar of Lithium is specified in "Grammar.txt"

# The Parser:
We have designed a botton-up LALR(1) parser for the grammar of Lithium. The Shift, Reduce and Go-to tables can be found in the "ParseTable" folder. In addition to these tables, the aforemetioned folder also contains a list of tokens and non-terminals in "Token_list.txt" and "NT_list.txt", respectively. A description of their formats can be found in "Description.txt". The codes for the lexer and parser can be found in "Parser.c".

We are printing the rules for an input Lithium file equivalent, the left hand side of which produces the post-order traversal of the tree.

# Tests:
The tests for the parser and lexer can be found in the subfolder "Tests"