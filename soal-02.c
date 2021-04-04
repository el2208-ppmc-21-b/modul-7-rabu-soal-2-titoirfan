#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
/* DESKRIPSI PROGRAM */
/*Program menerima masukan berupa perintah insert, delete, undo dan redo  */
/*Insert : Masukan data berupa integer*/
/*delete : Menghapus data tertentu pada stack */
/*undo   : Mengembalikan kondisi sebelum aksi */
/*redo   : Mengembalikan kondisi setelah redo */

struct StackNode { 
	char* url; 
	struct StackNode* next; 
}; 

struct StackNode* newNode(char * new_url) 
{ 
	struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode)); 
	//memory allocation for new url
    stackNode->url = (char*)malloc(strlen(new_url));
    //copy to url
    strcpy(stackNode->url, new_url);
	stackNode->next = NULL; 
	return stackNode; 
} 

int isEmpty(struct StackNode* root) 
{ 
	return !root; 
} 

void push(struct StackNode** root, char * new_url) 
{ 
	struct StackNode* stackNode = newNode(new_url); 
	stackNode->next = *root; 
	*root = stackNode; 
	// printf("%s pushed to stack\n", new_url); 
} 

char * pop(struct StackNode** root) 
{ 
	if (isEmpty(*root)) 
		return "EMPTY"; 
	struct StackNode* temp = *root; 
	*root = (*root)->next;

    //memory allocation for popped url
	char* popped = (char*)malloc(strlen(temp->url));
    //copy url
    strcpy(popped, temp->url); 
	free(temp); 

	return popped; 
} 

char * peek(struct StackNode* root) 
{ 
	if (isEmpty(root)) 
		return "EMPTY"; 
	return root->url; 
} 

void printStack(struct StackNode * root){
    //create temporary node
    struct StackNode*temp;
    temp = root;
    //check for stack underflow
    if (temp == NULL){
        // printf("\nStack is EMPTY");
    } 

    while ((temp) != NULL){
        printf("%s->", temp->url);
        //next
        temp = temp-> next;
    }
    printf("\n");
}

//function to clear the stack
void clearStack( struct StackNode ** root){
    while((*root) != NULL){
        pop(root);
    }
}

//function to go back the previous URL
void undo(struct StackNode ** backStack, struct StackNode ** forwardStack){
    if (isEmpty(*backStack)){
        printf("Can't Go Back!");
    }
    else {
        push(forwardStack,pop(backStack));
    }
}
//function to go back to the left URL when after activate back fiture
void redo(struct StackNode ** backStack, struct StackNode ** forwardStack){
    if (isEmpty(*forwardStack)){
        printf("Can't Go Forward!");
    }
    else {
        push(backStack,pop(forwardStack));
    }
}

void printCurrentSite(struct StackNode * root){
    if (isEmpty(root)){
        printf("\nNothing to found ..\n");
    }
    else
    {
        printf("\nCurrent Site : %s\n", peek(root));
    }
    
}
//function to perform undo task
int main() 
{ 
	//stack declaration
    struct StackNode* backStack = NULL;
    struct StackNode* forwardStack = NULL;

    //variables
    char instruction;
    char url [256];
    char junk;
    //Print Initial
    printf("----------Mozarella Firefly----------");
    do {
        printf("\nInstruction : ");
        fflush(stdin);
        scanf("%c", &instruction);
        switch (instruction)
        {
        case 'I':
            //insert url
            printf("Insert URL : ");
            scanf(" %s", url);

            //push it to the backStack
            push(&backStack, url);

            //clear forward stack
            clearStack(&forwardStack);
            break;
        case 'U' : //Undo
            undo(&backStack, &forwardStack);
            break;
        case 'R' : //redo
            redo(&backStack, &forwardStack);
            break;
        default:
            break;
        }
        
        getchar();

        //print current location
        if ( instruction != 'E'){
            printCurrentSite(backStack);
        }
        // printStack(backStack);
    } while (instruction != 'E');
    
    //exit message
    printf("... Exit\n");
  
	return 0; 
} 
