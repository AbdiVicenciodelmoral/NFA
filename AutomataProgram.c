#include <stdio.h>
#include <stdlib.h>


int num =0;
typedef struct trans{
    int state1;
    int state2;
    char symbol;
    struct trans *Tlist;

}Transitions;

typedef struct nfa{
    int startState;
    int endState;
    Transitions *Tlist;
}NFA;


typedef struct stacker {
   NFA * nfa;
   struct stacker *next;    
}stack;


stack *push(stack **topofStack, NFA *nfaPush)  {    
    stack *newNFA =(stack*)malloc(sizeof(stack)); 
     
   //newbie = (struct stack_entry *)malloc(sizeof(struct stack_entry));
    //if(!newbie) {
     //   return 0;
   // }

    newNFA->nfa = nfaPush;

    newNFA->next = *topofStack;
    *topofStack = newNFA;
    return newNFA;
}

NFA *pop(stack *currentTop) {
    //printf("topOFStack NFA StartState = %i \n",currentTop->nfa->startState);
    stack *topOfStack = currentTop;
   if(currentTop== NULL){
        return 0;
    } 
   printf("topOFStack NFA StartState = %i \n",currentTop->nfa->startState);
    NFA *poppedNFA = (NFA*)malloc(sizeof(NFA));
    // prepare the value for return
    poppedNFA = topOfStack->nfa;
    //printf("topOFStack NFA StartState = %i \n",currentTop->nfa->startState);
   // printf("topOFStack NFA NEXT StartState = %i \n",currentTop->next->nfa->startState);
    //printf("POPPEDNFA StartState = %i \n",poppedNFA->startState);
    // remove top element and free it
    currentTop = currentTop->next;
    printf("topOFStack NFA StartState = %i \n",currentTop->nfa->startState);
    //printf("topOFStack NFA NEXT StartState = %i \n",currentTop->next->nfa->startState);
    //free(topOfStack);
    //printf("topOFStack NFA StartState = %i \n",currentTop->nfa->startState);
    return poppedNFA;
}


NFA *create(char c){
    //printf("I'm in Create \n");
    NFA *newNFA = (NFA*)malloc(sizeof(NFA));
    newNFA->startState = num;
    num++;
    newNFA->endState = num;
	num++;
    Transitions *newT = (Transitions*)malloc(sizeof(Transitions));
    newT->state1 = newNFA->startState;
    newT->state2 = newNFA->endState;
    //printf("CHAR = %c \n",c);
    newT->symbol = c;
    
    newNFA->Tlist = newT;
    return newNFA;
}


int main() {

	stack *stacker =(stack*)malloc(sizeof(stack));
    NFA *NFA1; 
    NFA *NFA2;

    FILE *fp = fopen("tester.txt","r");
   	//char c; 
	int n =0;
	char c;
  	while ((c = fgetc(fp))!=EOF){
		//c = fgetc(fp);
		// if(feof(fp)){
     	//	break ;
		//}
  		//putchar(c); 
  		//c = next character in postfix expression;
		if (c == '&') {
			n= 0;
			//nFA2 = pop();
			//nFA1 = pop();
			//push(NFA that accepts the concatenation of L(nFA1) followed by L(nFA2));
			printf("TEST & \n");
		} 
		else if (c == '|') {
			n=0;

		    NFA2 = pop(stacker);
            printf("NFA2 StartState = %i \n",NFA2->startState);
			NFA1 = pop(stacker);
            printf("NFA1 StartState = %i \n",NFA1->startState);
			//push(NFA that accepts L(nFA1) | L(nFA2));
			//printf("TEST | \n");
			//putchar(c);
		} 
		else if (c == '*') {
			n=0;
			//nFA = pop();
			//push(NFA that accepts L(nFA) star);
			//printf("TEST \n");
			//printf("Letter:%i",c);
		} 
		else if( c == 13 || c == 10){
			break;
		}
		else{
		//push(NFA that accepts a single character c);
		//printf("TEST Letter \n")
        stacker = push(&stacker,create(c));
       // n++;
		//printf("Letter:%i",c);
		//printf("TEST\n");
		}
	

  		
  	}
	//printf("First NFA StartState = %i \n",stacker->nfa->startState);
    //printf("First NFA StartState = %i \n",stacker->nfa->endState);
    //printf("First Transition Symbol = %c \n",stacker->nfa->Tlist->symbol);

	
    return(0); 
} 
  


