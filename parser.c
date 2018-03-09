#include "DFA.c"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_TOKEN_NUM 100
#define MAX_TOKEN_LENGTH 20
#define MAX_KEYWORD_NUM 100
#define MAX_KEYWORD_LENGTH 16
#define MAX_FILE_LENGTH 10000
#define MAX_LEXICAL_VALUE_LENGTH 100
#define RULES_FILE "Lithium.lex"
#define INTERMEDIATE_TOKENS_LIST_FILE "tokens_list.txt"
#define TRANSLATED_TOKEN_NOS "Translate_token_no.txt"
#define NT_LIST "ParseTable/NT_list.txt"
#define TOKEN_LIST "ParseTable/Token_list.txt"
#define SHIFT_TABLE "ParseTable/ShiftTable.txt"
#define REDUCE_TABLE "ParseTable/ReduceTable.txt"
#define GOTO_TABLE "ParseTable/GotoTable.txt"
#define no_states 164
#define n_terminals 56
#define n_non_terminals 40


int rules[500][500];
char nt_look[n_terminals][30], t_look[n_non_terminals][30];
int shift_table[no_states][n_terminals], reduce_table[no_states][n_terminals], goto_table[no_states][n_non_terminals];


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


void generate_pairs(lexer *l, char* code, FILE* f, FILE* token_translate, int* count)
{
/**
 *	@brief Scans through the code and prints the lexeme-token pairs along with their respective line numbers to a file
 *	@param lexer *l The pointer to the lexer
 *	@param char* code The pointer to the character array containing the code
 *      @param FILE* f The file to which the tokens list is to be printed
 */
	int beg = 0, end = 0, last_token = -1, last_token_pos = -1, curr_state, line = 1, i;
	int translated_token_nos[l->n_tokens];
	for(i=0; i<(l->n_tokens); i++)
		translated_token_nos[i] = get_int(token_translate);
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
			end++;
		}
		else
		{
			int token_i = l->to_token[last_token];
			char str[100] = {'\0'}; i=0;
			while(beg<=last_token_pos)
				str[i++] = code[beg++];
			str[i] = '\0';
			if(token_i==(l->id_token_num))
			{
				for(i=0; i<l->n_keywords; i++)
					if(!strcmp(str, l->keyword_list[i]))
					{
						token_i = i;
						break;
					}
			}
			fprintf(f, "%d %s %s %d\n", translated_token_nos[token_i], l->token_list[token_i], str, line);
			*count += 1;
		}
	}
	fprintf(f, "55 $ $ %d\n", line+1);
	*count+=1;
}


/////////////////////////////////////////////////////////////////////////////////////////


typedef struct node{
	int id_no;
	int is_state;
	int is_terminal;
	struct node* next;
}node;


typedef struct stack{
	node* head;
}stack;


stack* get_stack()
{
	stack* st = (stack*)malloc(sizeof(stack));
	st->head = NULL;
	return st;
}


node* get_node(int id_no, int is_state, int is_terminal)
{
	node* nd = (node*)malloc(sizeof(node));
	nd->id_no = id_no;
	nd->is_state = is_state;
	nd->is_terminal = is_terminal;
	nd->next = NULL;
	return nd;
}


int is_empty(stack* st)
{
	if(st->head==NULL)
		return 1;
	return 0;
}


void push(stack* st, node* nd)
{
	nd->next = st->head;
	st->head = nd;
}


node* pop(stack* st)
{
	node* temp = st->head;
	st->head = (st->head)->next;
	return temp;
}


node* top(stack *st)
{
    return st->head;
}


void print_stack(stack *st)
{
    node *temp = st->head;
    while(temp!=NULL)
    {
        printf("%d %d %d\n", temp->id_no, temp->is_state, temp->is_terminal);
        temp=temp->next;
    }
}


node* get_next(FILE* Token_list, int* ln)
{
	int id=0, l=0;
	char x[100], y[100];
	FILE *fc = Token_list;
	if(fscanf(Token_list, " %d %s %s %d\n", &id, x, y, &l)==EOF)
		return NULL;
	*ln = l;
	return get_node(id, 0, 1);
}


int handle_error1(stack *st, FILE* code_tokens_list, node** lookahead)
{
	int l;
	while((*lookahead)!=NULL && strcmp(t_look[(*lookahead)->id_no], ";") && strcmp(t_look[(*lookahead)->id_no], "}") && strcmp(t_look[(*lookahead)->id_no], ")") && strcmp(t_look[(*lookahead)->id_no], "]"))
	{
		*lookahead = get_next(code_tokens_list, &l);
	}
	if(*lookahead==NULL)
		return 1;
	while(!is_empty(st))
	{
		if(top(st)->is_state)
		{
			if(shift_table[top(st)->id_no][(*lookahead)->id_no]==-1 && reduce_table[top(st)->id_no][(*lookahead)->id_no]==-1)
				pop(st);
			else
				return 0;	
		}
		else pop(st);
	}
	return 1;
}


void print_rule(int rr)
{
	int num=rules[rr][0];
	printf("%s -> ", nt_look[rules[rr][1]]);
	int i;
	for(i=num; i>=2; i--)
	{
		int id=rules[rr][2*i-1];
		int is_t=rules[rr][2*i];
		printf("%s ", is_t?t_look[id]:nt_look[id]);
	}
	printf("\n");
}


void parser(FILE* code_tokens_list, FILE* NT_list, FILE* Token_list, FILE* Shift_table, FILE* Reduce_table, FILE* Goto_table, int n_tokens)
{
	
	int i,j;
	//read NT_list and Token_list
	for(i=0; i<n_non_terminals; i++)
	{
		fscanf(NT_list, "%d %s\n", &j, nt_look[i]);
	}
	for(i=0; i<n_terminals; i++)
	{
		fscanf(Token_list, "%d %s\n", &j, t_look[i]);
	}
	//read tables
	for(i=0; i<no_states; i++)
	{
		for(j=0; j<n_terminals; j++)
		{
			char temp[3];
			get_line(Shift_table, temp);
			shift_table[i][j] = strcmp(temp, "cc")?atoi(temp):-2;
			get_line(Reduce_table, temp);
			reduce_table[i][j] = strcmp(temp, "cc")?atoi(temp):-2;
		}
		for(j=0; j<n_non_terminals; j++)
		{
			goto_table[i][j] = get_int(Goto_table);
		}
	}
	//Stack running code
	char buf[100];
	int ln;
	stack *stk=get_stack();
	node *start=get_node(0,1,0);
	push(stk,start);
	node * lookahead = get_next(code_tokens_list, &ln);
	while(1)
	{
		
		node* tp = top(stk);
		if(tp->is_state)
		{
			int ss=shift_table[tp->id_no][lookahead->id_no];
			int rr=reduce_table[tp->id_no][lookahead->id_no];
			if((ss==-2)||(rr==-2))
			{
				printf("Succesfully parsed.\n");
				return;
			}
			else if((ss==-1)&&(rr==-1))
			{
				printf("A syntax error has occured at line %d... Trying to handle.\n", ln);
				int flag=handle_error1(stk, code_tokens_list, &lookahead);
				if(flag==0)
				{
					printf("Handled\n");
				}
				if(flag==1)
				{
					printf("Unable to handle the error\n");
					return;
				}
			}
			else if(ss!=-1)
			{
				push(stk, lookahead);
				printf("TERMINAL: %s\n", t_look[lookahead->id_no]);
				lookahead=get_next(code_tokens_list, &ln);
				push(stk, get_node(ss, 1, 0));
			}
			else
			{
				int num=rules[rr][0];
				int i;
				node* lhs=get_node(rules[rr][1], 0, 0);
				for(i=2; i<=num; i++)
				{
					int id=rules[rr][2*i-1];
					int is_t=rules[rr][2*i];
					pop(stk);
					if(is_empty(stk))
					{
						printf("Irrecoverable error occured at line %d\n", ln);
						return;
					}
					node* x=pop(stk);
					if((x->id_no == id) && (x->is_terminal == is_t))
					{
						continue;
					}
					else
					{
						printf("Irrecoverable error occured at line %d\n", ln);
						return;
					}
				}
				push(stk, lhs);
				print_rule(rr);
			}
		}
		else
		{
			node* ter=pop(stk);
			node* st=pop(stk);
			int new_id=goto_table[st->id_no][ter->id_no];
			if(new_id==-1)
			{
				printf("Irrecoverable error occured at line %d\n", ln);
				return;
			}
			node* nst=get_node(new_id, 1, 0);
			push(stk, st);
			push(stk, ter);
			push(stk, nst);
		}

	}
			
}


int main()
{
	FILE* f=fopen(RULES_FILE, "r");
	FILE* tokens_list = fopen(INTERMEDIATE_TOKENS_LIST_FILE, "w");
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
	f = fopen(TRANSLATED_TOKEN_NOS, "r");
	printf("Scanning...\n");
	int count_;
	int* count=&count_;
	*count = 0;
	generate_pairs(l, code, tokens_list, f, count);
	fclose(tokens_list);
	fclose(f);
	FILE* jj=fopen("rules.txt","r");
	int x,num,i=0,j=0;
	fscanf(jj,"%d",&x);
	for(i=0;i<x;i++)
        {
        	fscanf(jj,"%d",&num);
        	rules[i][0]=num;
        	for(j=1;j<=2*num;j+=2)
            	    fscanf(jj,"%d %d",&rules[i][j],&rules[i][j+1]);
        }
	printf("Parsing...\n");
	parser(fopen(INTERMEDIATE_TOKENS_LIST_FILE, "r"), fopen(NT_LIST, "r"), fopen(TOKEN_LIST, "r"), fopen(SHIFT_TABLE, "r"), fopen(REDUCE_TABLE, "r"), fopen(GOTO_TABLE, "r"), *count);
	return 0;
}
