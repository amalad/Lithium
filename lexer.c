/**
 *	This is a general purpose lexer. 
 *	It takes the lexer rules as input from a file that has to be specified by the user. 
 *	The name of the code file is also taken as input from the user. 
 *	The lexer rules file should be in the following format:
 *		t (number of tokens)
 *		The next t lines contain the names of the tokens
 *		k (number of keywords)
 *		The next k lines contain the names of the keywords
 *		n (number of states in the DFA)
 *		f (number of final states)
 *		The next 2*f lines contain the state number and the corresponding token number, each on a separate line
 *		tr (number of transitions)
 *		The next 3*t lines contain the 'from' state, the 'to' state and the characters on which the transition
 *				has to be made, each on a separate line
 *		The characters indicating the beginning and end of a comment
 *		The token number of identifiers
*/

#include "DFA.c"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_TOKEN_NUM 100
#define MAX_TOKEN_LENGTH 20
#define MAX_KEYWORD_NUM 100
#define MAX_KEYWORD_LENGTH 16
#define MAX_FILE_LENGTH 10000


typedef struct lexer
{
	DFA* d;
	char token_list[MAX_TOKEN_NUM][MAX_TOKEN_LENGTH];
	char keyword_list[MAX_KEYWORD_NUM][MAX_KEYWORD_LENGTH];
	int n_tokens;
	int n_keywords;
	int *to_token;
	int n_final_states;
	char comm_delim;
	int id_token_num;
} lexer;

void get_line(FILE *f, char str[])
{
/**
 *	@brief Reads a line from the input file and stores it in a character array
 *	@param FILE *f The pointer to the file
 *	@param char str[] The character array to be written to
 */
	char ch;
	int i = 0;
	while((ch=fgetc(f))!=EOF && ch!='\n')
	{
		str[i++] = ch;
	}
	str[i] = '\0';
}

int get_int(FILE* f)
{
/**
 *	@brief Reads an integer from a file and returns it
 *	@param FILE *f The pointer to the file
 */
	char buffer[50];
	get_line(f, buffer);
	return atoi(buffer);
}

void read_file(FILE *f, char* code)
{
/**
 *	@brief Reads and stores the contents of a file in a character array
 *	@param FILE *f The pointer to the file
 *	@param char* code The pointer to the character array to be written to
 */
	int i = 0;
	char ch;
	while((ch = fgetc(f))!=EOF)
	{
		code[i++] = ch;
	}
	code[i] = '\0';
}

lexer* get_lexer_from_rules(FILE* f)
{
/**
 *	@brief Creates and initializes the lexer
 *	@param FILE *f The pointer to the file containing the lexical rules
 */
	lexer* lex=(lexer*)malloc(sizeof(lexer));
	lex->d=(DFA*)malloc(sizeof(DFA));
	int n_states;
	int n_final_states;
	int i;
	char discard;
	lex->n_tokens=get_int(f);
	for(i=0; i<lex->n_tokens; i++)
	{
		get_line(f, lex->token_list[i]);
	}
	lex->n_keywords=get_int(f);
	for(i=0; i<lex->n_keywords; i++)
	{
		get_line(f, lex->keyword_list[i]);
	}
	n_states=get_int(f);
	init_DFA(lex->d, n_states, 0);
	lex->to_token=(int*)malloc(sizeof(int)*n_states);
	lex->n_final_states=get_int(f);
	for(i=0; i<lex->n_final_states; i++)
	{
		int temp;
		temp=get_int(f);
		lex->to_token[temp]=get_int(f);
		add_final_DFA(lex->d, temp);
	}
	char temp[200];
	int n_transitions=get_int(f);
	for(i=0; i<n_transitions; i++)
	{
		int from=get_int(f);
		int to=get_int(f);
		get_line(f, temp);
		int j;		
		int len=strlen(temp);
		for (j=0; j<len; j++)
		{
			add_transition_DFA(lex->d, from, to, temp[j]);
		}
	}
	lex->comm_delim=fgetc(f);
	fgetc(f);
	lex->id_token_num=get_int(f);
	return lex;
}

void generate_pairs(lexer *l, char* code)
{
/**
 *	@brief Scans through the code and prints the lexeme-token pairs along with their respective line numbers
 *	@param lexer *l The pointer to the lexer
 *	@param char* code The pointer to the character array containing the code
 */
	int beg = 0, end = 0, last_token = -1, last_token_pos = -1, curr_state, line = 1, i;
	while(1)
	{
		curr_state = 0;
		if(code[end]==l->comm_delim)
		{
			int comm_beg = line;
			end++;
			while(code[end]!=l->comm_delim)
			{
				if(code[end]=='\n')
					line++;
				if(code[end]=='\0')
				{
					printf("Comment not ended properly, line number %d\n", comm_beg);
					break;
				}
				end++;
				beg = end;
			}
			if(code[end]==l->comm_delim)
			{
				end++;
				beg = end;
			}
			continue;
		}
		else if(code[end]==' ' || code[end]=='\n' || code[end]=='\t')
		{
			if(code[end]=='\n') line++;
			end++;
			beg = end;
			continue;
		}
		else if(code[end]=='\0')
			break;

		while(1)
		{
			curr_state = get_next_state(l->d, curr_state, code[end]);
			if(is_final(l->d, curr_state))
			{
				last_token_pos = end;
				last_token = curr_state;
			}
			else if(curr_state==-1)
				break;
			end++;
		}
		if(last_token_pos<beg)
		{
			printf("Invalid, string ");
			while(beg<=end)
				printf("%c", code[beg++]);
			printf(", line number %d\n", line);
			end++;
		}
		else
		{
			int token = l->to_token[last_token];
			char str[100] = {'\0'}; i=0;
			while(beg<=last_token_pos)
				str[i++] = code[beg++];
			str[i] = '\0';
			if(token==(l->id_token_num))
			{
				for(i=0; i<l->n_keywords; i++)
					if(!strcmp(str, l->keyword_list[i]))
					{
						token = i;
						break;
					}
			}
			printf("Token %d, string %s, line number %d\n", token, str, line);
		}
	}
}


int main()
{
	char rules_file[20];
	printf("Enter rules file: ");
	scanf("%s", rules_file);
	FILE* f=fopen(rules_file, "r");
	printf("Generating lexer from file...\n");
	lexer* l=get_lexer_from_rules(f);
	printf("Lexer generated.\n");
	fclose(f);
	char code_file[20];
	printf("Enter code file: ");
	scanf("%s", code_file);
	f = fopen(code_file, "r");
	char* code=(char*)malloc(sizeof(char)*MAX_FILE_LENGTH);
	read_file(f, code);
	fclose(f);
	printf("Scanning...\n");
	generate_pairs(l, code);
	return 0;	
}
