#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 64
#define DAX 128

typedef struct {
    int priority;
    char task[MAX];
    char detail[DAX];
    void *next;
} Node;

Node *head = NULL;
 
// add a node to the list
void add_node(char* task)
{
    Node *new = NULL;
    
    if (head == NULL)
    {
        new = malloc(sizeof(Node));
        memset(new->detail, '\0', DAX);

        new->priority = 1;
        strcpy(new->task, task);
        head = new;
        new->next = NULL;

  } else {
        new = malloc(sizeof(Node));
        memset(new->detail, '\0', DAX);
        Node *current = head;
      // if (new == NULL){return  NULL;}
      
        while (current->next)
        {
            current = current->next;
        }
      
        new->priority = current->priority + 1;
       // new->task = task;
        strcpy(new->task, task);
        new->next = NULL;
        current->next = new; 
    }
    return;
}
// delete a node from the list
int deleteNode(int priority)
{
  Node *current = head;
  Node *prev = NULL;

    while (current)
    {
        if (current->priority == priority)
        {
            if (current == head)
            {
                head = current->next;
                
            } else {
                prev->next = current->next;
                free(current);
                current = NULL;
            }
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}
// insert a node into a position in the list
int insertNode(int priority, char* task)
{
    Node *current = head;
    Node *prev = NULL;
    Node *new = malloc(sizeof(Node));
    memset(new->detail, '\0', DAX);
    new->priority = priority;
    strcpy(new->task, task);

    while (current)
    {
        if (current->priority == priority)
        {
            if (current == head)
            {
                new->next = head;
                head = new;
                return 1;
            } else {
                new->next = current;
                prev->next = new;
                return 1;
            }
        }
        prev = current;
        current = current->next;
    }
    prev->next = new;
    new->next = NULL;
    return 0;
}

// print full list
void printList(void)
{
    Node *current = head;
    printf("\x1b[2J");
    printf("\x1b[H");
    printf("\n");
    printf("---------------------------------------------------\n");
    while (current)
    {
        // printf("|*\tTask %d:\t%s\n", current->priority, current->task);
        printf("|*\tTask %d: ---   %s\n", current->priority, current->task);
        current=current->next;
    }
    printf("---------------------------------------------------\n\n");
    return;
}

// Edit a Node
void editNode(int priority)
{
    printf("start of edit_node\n");
    Node *current = head;
    Node *prev = head;
    char edit[MAX];

    /**
    while (current)
    {
        if (current->priority != priority)
        {
            current = current->next;
        } else {
            break;
        }
    }

    ***** from insert_node *****
    while (current)
    {
        if (current->priority == priority)
        {
            if (current == head)
            {
                new->next = head;
                head = new;
                return 1;
            } else {
                new->next = current;
                prev->next = new;
                return 1;
            }
        }
        prev = current;
        current = current->next;
    }
    */
    while (current)
    {
        if (current->priority == priority)
        {
            break;
        }
        current = current->next;
    }

    if (current == NULL)
    {
        current = prev;
    }

    printf("%s\n", current->task);
    
    fgets(edit, MAX, stdin);
    edit[strcspn(edit, "\n")] = 0;
    strcpy(current->task, edit);

    return;
}

// Reorganize Priority list
void renumberList(int *length)
{
    int priority = 1;
    Node *current = head;

    while (current)
    {
        current->priority = priority;
        current=current->next;
        priority++;
    }
    *length = priority - 1;
    return;
}

/**  Reassign list
void reassign(Node *head)
{
  Node *current = head;
  Node *prev = NULL;

  while (current)
  {
    if (current == head){
      current->priority = 1;
    } else {
      current->priority = prev->priority + 1;
    }
    prev = current;
    current = current->next;
  }
}
*/

// options
void printOptions(void)
{
    printf("1. Add a task\n");
    printf("2. Insert task into list\n");
    printf("3. Delete a task\n");
    printf("4. Read List\n");
    printf("5. Edit a Task\n");
    printf("9. Quit\n");
}
// get option
void get_task(char *task)
{
    fgets(task, MAX, stdin);
    task[strcspn(task, "\n")]=0;
    
    /**
    char c;
    while((c = getchar())!= '\n' && c != EOF);
    */
    return;
}

// get priority
void get_int(int *num)
{
    scanf("%d", num);
    char c;
    while((c = getchar()) != '\n' && c != EOF);

    return;
}

int main(int argc, char** argv)
{
    
    int option = -1;
    int length = 0;
    char task[MAX]; 
    int priority;
    printf("Welcome to the To-Do app\n");
    

    while(option != 9)
    {
        print_list();        
        print_options();
        /**
        int num = scanf("%d", &option);

        char c;
        while((c = getchar())!= '\n' && c != EOF);
        */
        get_int(&option);

        if ( option > 0 && option <= 9)
        {
            switch (option) {
                case 1:
                    printf("What is your new Task?\n");
                    get_task(task);
                    add_node(task);
                    renumberList(&length);
                    break;

                case 2:
                    printf("What is your new Task\n");
                    get_task(task);
                    printf("What priority does this task have:  ");
                    get_int(&priority);
                    int done = insert_node(priority, task);
                    if (done)
                    {
                        printf("Node successfully added!\n");
                    } else {
                        printf("Noded added to end of list\n");
                    }
                    renumberList(&length);
                    break;

                case 3:
                    printf("What task have you completed?\n");
                    printf("Priority: ");
                    // scanf("%d", &priority);
                    get_int(&priority);

                    int success = delete_node(priority);
                    if (success)
                    {
                        printf("Task successfully removed from list\n");
                        renumberList(&length);
                    } else {
                        printf("No task in list had provided priority\n");
                        printf("No changes made\n");
                    }
                    break;
                case 4:
                    printList();
                    break;
                case 5:
                    printf("What priority would you like to edit:  ");
                    get_int(&priority);
                    edit_node(priority);
                    break;
                    
                case 9:
                    break;
            }
        }
    }
    return 0;
}


// staging

// clear multiple
/**
    enter clear mode
    give start number
    cycle through list to find start
    if (start not found){pri not found}
    give end
    cycle through list to find end 
    set up:
    * keep loop going until int
    * while loop 

*/


int clearSet(int *length)
{
    Node *current = head;
    int start = -1;
    while (start != 0)
    {
        scanf("%d", &start);
        getchar();
        while (current->priority != start)
        {
            current = current->next;
        }
    }

    return 0;
}


int party(void)
{
    int start = -1;
    int end = -1;

    while(1)
    {
        scanf("%d", &start);
        getchar();
        if (start ==0)
        {
            break;
        }

    }
    return 0;
}
