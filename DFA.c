#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DFA
{
	int n_states;
	int *transitions;
	int *final_states;
	int init_state;
} DFA;

void init_DFA(DFA* d, int n_states, int init_state)
{
/**
 *	@brief Initializes the DFA
 *	@param DFA* d The DFA to be initialized
 *	@param int n_states The number of states in the DFA
 *	@param int init_state The initial state
 */
	d->n_states=n_states;
	d->transitions=(int*)malloc(sizeof(int)*n_states*128);
	d->final_states=(int*)malloc(sizeof(int)*n_states);
	d->init_state=init_state;
	int i,j;
	for(i=0;i<n_states;i++)
	{
		for(j=0;j<128;j++)
		{
			d->transitions[i*128+j]=-1;
		}
		d->final_states[i]=0;
	}
}

void free_DFA(DFA* d)
{
/**
 *	@brief Deallocates the memory assigned to a DFA
 *  @param DFA* d The DFA to be freed
 */
	free(d->transitions);
	free(d->final_states);
	free(d);
}

void add_transition_DFA(DFA* d, int from, int to, char on)
{
/**
 *	@brief Adds a transition to the DFA
 *	@param DFA* d The DFA
 *  @param int from The "from" state number
 *	@param int to The "to" state number
 *	@param char on The character on which the transition happens
 */
	d->transitions[from*128 + (int)on] = to;
}

void add_final_DFA(DFA* d, int state)
{
/**
 *	@brief Adds a final state to the DFA
 *	@param DFA* d The DFA
 *	@param int state The state to be added as a final state
 */
	d->final_states[state]=1;
}

void remove_final_DFA(DFA* d, int state)
{
/**
 *	@brief Makes a final state not-final
 * 	@param DFA* d The DFA
 *	@param int state The state to be made un-final
 */
	d->final_states[state]=0;
}

int get_next_state(DFA* d, int curr, char c)
{
/**
 *	@brief Given the current state and the character read, gets the next state
 *	@param DFA* d The DFA to be run
 *	@param int curr The current state
 *	@param char c The character read
 *	@return Returns the next state
 */
	return (d->transitions)[curr*128 + (int)c];
}

int is_final(DFA* d, int state)
{
/**
 *	@brief Given a state and a DFA, checks if the state is final
 *	@param DFA* d The DFA
 *	@param int state The state to be checked
 *	@return Returns 1 if final, 0 otherwise
 */
	if (state==-1)
		return 0;
	return d->final_states[state]==1;
}

int run_DFA(DFA* d, char* s)
{
/** @brief Runs the DFA on the given string and returns the final state.
 *	@param DFA* d The DFA to be run
 *	@param char* s The string
 *	@return int curr_state The final state
 */
	int length=strlen(s);
	int i;
	int curr_state=d->init_state;
	for(i=0;i<length;i++)
	{
		curr_state=d->transitions[curr_state*128 + (int)s[i]];
		if (curr_state==-1)
			break;
	}
	return curr_state;
}


void get_reachables(int* count_states, int* reachables, int* transitions, int current)
{
/**
 *	@brief Performs a DFS to get the reachable states. Convenience method
 *	@param int* count_states The pointer to a variable which keeps the counter for reachables
 *	@param int* reachables A 0-1 array which keeps a track of whether the state is reachable or not
 *	@param int* transitions The transition array to be followed.
 *	@param int current The state on which the recursion is at right now. When first calling, use initial state.
 */
	reachables[current]=1;
	(*count_states)++;
	int i;
	for(i=0; i<128; i++)
	{
		if (transitions[current*128 + i]==-1 || reachables[transitions[current*128 + i]]==1)
			continue;
		get_reachables(count_states, reachables, transitions,  transitions[current*128 + i]);
	}
}
DFA* remove_unreachable_DFA(DFA* d)
{
/**
 *  @brief Removes the unreachable states from the DFA.
 *  @param DFA* d The pointer to the DFA
 *  @return DFA* x The DFA with states removed.
 */
	int reachables[d->n_states];
	int count_states=0;
	int i, j;
	for(i=0; i<d->n_states; i++)
		reachables[i]=0;
	get_reachables(&count_states, reachables, d->transitions, d->init_state);
	int index=0;
	int *final_states=(int*)malloc(sizeof(int)*count_states);
	int *transitions=(int*)malloc(sizeof(int)*128*count_states);
	for(i=0; i<d->n_states; i++)
	{
		if (reachables[i]!=0)
		{
			for(j=0; j<128; j++)
			{
				transitions[index*128+j]=d->transitions[i*128+j];
			}
			final_states[index]=d->final_states[i];
			index++;
		}
	}
	DFA* x=(DFA*)malloc(sizeof(DFA));
	x->init_state=d->init_state;
	x->transitions=transitions;
	x->final_states=final_states;
	x->n_states=count_states;
	return x;
}

int max(int* arr, int n)
{
/**
 *  @brief Convenience method. Returns max of an integer array.
 *  @param int* arr The array
 *  @param int n The size of the array
 *  @return int max The maximum element
 */
	int max=0;
	int i;
	for(i=0; i<n; i++)
	{
		if (arr[i]>max)
			max=arr[i];
	}
	return max;
}
	
				
DFA* reduce_DFA(DFA* dfa)
{
/**
 *  @brief This function minimizes the given DFA using Moore's algorithm. Also removes
 *		   unreachable states. Note: This is not used anywhere due to some complications
 *		   in the way a lexer works. Running time complexity is O(n^2) for n states (worst).
 *  @param DFA* dfa The pointer to the DFA to be minimized
 *  @return DFA* x The reduced DFA
 */
	DFA* d=remove_unreachable_DFA(dfa);
	int groups[d->n_states];
	int i,j,k;
	for(i=0; i<d->n_states; i++)
	{
		groups[i]=d->final_states[i];
	}
	int curr=max(groups, d->n_states);
	int prev=0;
	int new_groups[d->n_states];
	int new_transitions[d->n_states*128];
	while(curr!=prev)
	{
		prev=curr;
		curr=1;
		for(i=0; i<d->n_states; i++)
		{
			for(j=0; j<128; j++)
			{
				if (d->transitions[i*128+j]==-1)
					new_transitions[i*128+j]=-1;
				else
					new_transitions[i*128 + j]=groups[d->transitions[i*128+j]];
				
			}
		}
		new_groups[0]=0;
		for(i=1; i<d->n_states; i++)
		{
			for(j=0; j<i; j++)
			{
				if (groups[i]!=groups[j])
				{
					continue;
				}
				for(k=0; k<128; k++)
				{
					if (new_transitions[i*128+k]!=new_transitions[j*128+k])
						break;
				}
				if (k==128)
				{
					new_groups[i]=new_groups[j];
					break;
				}
			}
			if (j==i)
			{
				new_groups[i]=curr++;
			}
		}
		for(i=0; i<d->n_states; i++)
		{
			groups[i]=new_groups[i];
		}
	}
	int temp[curr];
	int *final_states=(int*)malloc(sizeof(int)*curr);
	for(i=0; i<curr; i++)
	{
		final_states[i]=0;
	}
	int init=-1;
	for(i=0; i<d->n_states; i++)
	{
		temp[groups[i]]=i;
		final_states[groups[i]]=d->final_states[i];
		if(d->init_state==i)
			init=groups[i];
	}
	int *transitions=(int*)malloc(sizeof(int)*128l*curr);
	
	for(i=0; i<curr; i++)
	{
		for(j=0; j<128; j++)
		{
			transitions[i*128+j]=new_transitions[temp[i]*128+j];
		}
	}
	DFA* x=(DFA*)malloc(sizeof(DFA));
	x->n_states=curr;
	x->transitions=transitions;
	x->final_states=final_states;
	x->init_state=init;
	free_DFA(d);
	return x;
}

void to_file_DFA(DFA* d, FILE* f)
{
/**	
 *  @brief This function serializes a DFA to a file
 *  @param DFA* d The pointer to the DFA
 *  @param FILE* f The pointer to the file to be written into
 */
	fprintf(f, "%d\n", d->n_states);
	fprintf(f, "%d\n", d->init_state);
	int i, j;
	for(i=0; i<d->n_states; i++)
	{
		fprintf(f, "%d\n", d->final_states[i]);
	}
	for(i=0; i<d->n_states; i++)
	{
		for(j=0; j<128; j++)
		{
			fprintf(f, "%d\n", d->transitions[i*128 + j]);
		}
	}
}

DFA* from_file_DFA(FILE* f)
{
/**
 *  @brief This function deserializes a DFA from a file.
 *  @param FILE* f The pointer to the file.
 *  @return DFA* d The created DFA
 */
	int n_states;
	fscanf(f, "%d[^\n]%*c", &n_states);
	int init_state;
	fscanf(f, "%d[^\n]%*c", &init_state);
	int* final_states=(int*)malloc(sizeof(int)*n_states);
	int i, j;
	for(i=0; i<n_states; i++)
	{
		fscanf(f, "%d[^\n]%*c", &final_states[i]);
	}
	int* transitions=(int*)malloc(sizeof(int)*128*n_states);
	for(i=0; i<n_states; i++)
	{
		for(j=0; j<128; j++)
		{
			fscanf(f, "%d[^\n]%*c", &transitions[i*128 + j]);
		}
	}
	DFA* d=(DFA*)malloc(sizeof(DFA));
	d->n_states=n_states;
	d->init_state=init_state;
	d->final_states=final_states;
	d->transitions=transitions;
	return d;
}
