#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 64

typedef struct {
    int priority;
    char task[MAX];
    void *next;
} Node;

Node *head = NULL;
 
// strcspn
// add a node to the list
void addNode(char* task)
{
    Node *new = NULL;
    
    if (head == NULL)
    {
        new = malloc(sizeof(Node));
        // if (new == NULL){return NULL;}

        new->priority = 1;
        // new->task = task;
        strcpy(new->task, task);
        head = new;
        new->next = NULL;

  } else {
      new = malloc(sizeof(Node));
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
int deleteNode(int pri)
{
  Node *current = head;
  Node *prev = NULL;

    while (current)
    {
        if (current->priority == pri)
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
int insertNode(int pri, char* task)
{
    Node *current = head;
    Node *prev = NULL;
    Node *new = malloc(sizeof(Node));
    // if (new == NULL) {return NULL;}

    new->priority = pri;
    // new->task = task;
    strcpy(new->task, task);

    while (current)
    {
        if (current->priority == pri)
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
    while (current)
    {
        printf("Task %d:\t%s\n", current->priority, current->task);
        current=current->next;
    }
    return;
}

// Reorganize Priority list
void renumberList(void)
{
    int pri = 1;
    Node *current = head;

    while (current)
    {
        if (current->priority!=pri)
        {
            current->priority = pri;
        }
        current=current->next;
        pri++;
    }
    return;
}

// Reassign list
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

// options
void printOptions(void)
{
    printf("\t1. Add a task\n");
    printf("\t2. Insert task into list\n");
    printf("\t3. Delete a task\n");
    printf("\t4. Read List\n");
    // printf("\t5. Add a task\n");
    printf("\t9. Quit\n");
}

int main(int argc, char** argv)
{
    
    int option = -1;
    char task[MAX];
    int pri;
    printf("Welcome to the To-Do app\n");
    

    while(option != 9)
    {
        printList();        
        printOptions();
        int num = scanf("%d", &option);
        getchar(); 
        if (num == 1 && option > 0 && option <= 9)
        {
            switch (option) {
                case 1:
                    printf("What is your new Task?\n");
                    fgets(task, MAX, stdin);
                    task[strcspn(task, "\n")] = 0;
                    
                    addNode(task);
                    printf("added\n");
                    reassign(head);
                    // option = -1;
                    break;
                case 2:
                    printf("What is your new Task\n");
                    scanf("%s", task);
                    printf("What priority does this task have:  ");
                    scanf("%d", &pri);
                    int done = insertNode(pri, task);
                    if (done)
                    {
                        printf("Node successfully added!\n");
                    } else {
                        printf("Noded added to end of list\n");
                    }
                    reassign(head);
                    break;
                case 3:
                    printf("What task have you completed?\n");
                    printf("Priority: ");
                    scanf("%d", &pri);
                    int success = deleteNode(pri);
                    if (success)
                    {
                        printf("Task successfully removed from list\n");
                        reassign(head);
                    } else {
                        printf("No task in list had provided priority\n");
                        printf("No changes made\n");
                    }
                    break;
                case 4:
                    printList();
                    break;
                case 9:
                    break;
            }
        }
    }
    return 0;
}
