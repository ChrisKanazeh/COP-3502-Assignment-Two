/* Christopher Kanazeh
Assignment 2 COP 3502
*/

//Declare Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Linked List Declaration
struct produceItem
{   //Declare variables
    char produce[20];
    char type[20];
    char soldBy[20];
    float price;
    int quantityInStock;
    //next pointer node
    struct produceItem *next;
};

//Prototypes for Program
//add Item Prototype
void addProduceItem(struct produceItem **, char *, char *, char *, float, int);
//display Prototype
void display(struct produceItem *);
//readDataFile Prototype
void readDataFile(struct produceItem **);
//Reverse Prototype
void recursiveReverse(struct produceItem **);
//Prototype Professor showed in class to make the layout cleaner
char * CleanUp(char *clean);
//Write Data Prototype
void writeDataFile(struct produceItem *);

//add Item Function
void addProduceItem(struct produceItem **headRef, char *produce, char *type, char *soldBy, float price, int quantityInStock)
{   //Malloc to allocate a block of memory
    struct produceItem* temp = (struct produceItem*) malloc(sizeof(struct produceItem));
    //string copy each char
    strcpy(temp->produce, produce);
    strcpy(temp->type, type);
    strcpy(temp->soldBy, soldBy);
    //use temp pointers for float and int values
    temp->price = price;
    temp->quantityInStock = quantityInStock;
    //set set the pointer  where temp is equal to the headRef
    temp->next = (*headRef);
    //sets headRef equal to temp
    (*headRef) = temp;
}

//Display Function
void display(struct produceItem *headRef)
{
    struct produceItem *helper = headRef;
    //if the helper is equal to nothing, it returns because there is nothing to display.
    if(helper == NULL)
    {
        return;
    }
    else
    {   //prints out the Titles for each category for the items
        printf("==============================================================================\n");
        printf(" Item #   Produce       Type             Sold By         Price    In Stock    \n");
        printf("==============================================================================\n");
        // counter
        int counter = 1;
        // while helper is not equal to NULL
        while(helper != NULL)
        {   //prints out each item with the character or value of each line in order
            printf("%5d %3s %-13s %-16s %-13s %6.2f %8d \n", counter ++, " ", helper->produce, helper->type, helper->soldBy, helper->price, helper->quantityInStock);
            //sets helper equal to the next pointer
            helper = helper->next;
        }
    }

    printf("\n");
}
//Read Data File Function
void readDataFile(struct produceItem  **headRef)
{   //sets the constant character for comma to help remove them from the file
    const char comma[2] = ",";
    char dataLine[100];
    char *produce;
    char *type;
    char *soldBy;
    float price;
    int quantityInStock;
    //sets the file name to AssignmentTwoInput
    char *fileName = "AssignmentTwoInput.txt";
    //sets the FILE pointer ifp
    FILE *ifp;
    //sets file pointer to open the file named AssignmentTwoInput
    ifp = fopen(fileName, "r");

    if( ifp == NULL )
    {
        perror("Error while opening the file.\n");
        exit(0);
    }
    //while the data in the file is not equal to Null, we traverse through the file and add each one to the memory block
    while( ( fgets(dataLine, 100, ifp) ) != NULL)
    {   //Cleans up all the commas
        produce = CleanUp(strtok(dataLine, ","));
        type = CleanUp(strtok(NULL, ","));
        soldBy = CleanUp(strtok(NULL, ","));
        price = atof(CleanUp(strtok(NULL, ",")));
        quantityInStock = atoi(CleanUp(strtok(NULL, ",")));
        //adds each item and its values to the memory to be displayed and reversed later
        addProduceItem(headRef, produce, type, soldBy, price, quantityInStock);
    }
    //closes the file
    fclose(ifp);
}
//Function to reverse the order of the Linked List
void recursiveReverse(struct produceItem** head_ref)
{
    struct produceItem* first;
    struct produceItem* rest;
    //If there is nothing in the list, return because there is nothing to reverse
    if(*head_ref == NULL)
        return;
    //sets the first pointer equal to head_ref
    first = *head_ref;
    //set s the rest pointer equal to the next pointer of first
    rest = first->next;
    //if rest is equal to NULL, then return since it is empty
    if (rest == NULL)
        return;

    recursiveReverse(&rest);
    //sets first equal to the next next value after first
    first->next->next = first;
    //sets the next of first equal to NULL
    first->next = NULL;
    //sets headref equal to rest
    *head_ref = rest;
}
//Function to clean up the data
char * CleanUp(char *clean)
{   //i is equal to clean + the length of the string clean -1
    char * i = clean + strlen(clean) - 1;
    //increment clean by 1 while there is space
    while(*clean && isspace(*clean))
        clean++;
    //while i is greater than clean and isspace i, set i decrement equal to '\0' which is the symbol for the end of a string
    while(i > clean && isspace(*i))
        *i-- = '\0';
    //returns clean
    return clean;
}
//Function to write the data into the output file
void writeDataFile(struct produceItem *headRef)
{   //sets the fileName equal to AssignmentTwoOutput
    char *fileName = "AssignmentTwoOutput.txt";
    //file pointer
    FILE *ifp;
    //counter
    int counter = 1;
    struct produceItem *helper = headRef;


    ifp = fopen(fileName, "w");
    //if the file pointer is pointing to nothing, then print out the error and exit the program.
    if( ifp == NULL )
    {
        perror("Error while opening the file.\n");
        exit(0);
    }
    //if the helper pointer is equal to nothing, then return.
    if(helper == NULL)
    {
        return;
    }
    else
    {   //prints out the categories for the user
        fprintf(ifp, "==============================================================================\n");
        fprintf(ifp, " Item #   Produce       Type             Sold By         Price    In Stock    \n");
        fprintf(ifp, "==============================================================================\n");
        //while helper is not equal to NULL
        while(helper != NULL)
        {   //prints out each value into the file appropriately
            fprintf(ifp, "%5d %3s %-13s %-16s %-13s %6.2f %8d  \n", counter ++, " ", helper->produce, helper->type, helper->soldBy, helper->price, helper->quantityInStock);
            //sets helper equal to the next value after helper
            helper =  helper->next;
        }
    }
    //closes the file
    fclose(ifp);
}
//Main Function
int main()
{   //declare variable for choice
    int choice = 0;

    struct produceItem* head = NULL;
    //menu for user
    while(1)
    {
        printf("\n1. Stock Produce Department\n");
        printf("2. Display Produce Inventory\n");
        printf("3. Reverse Order of Produce Inventory\n");
        printf("4. Export Produce Inventory\n");
        printf("5. Exit Program\n");
        printf("Enter your choice : ");
        //scans in users choice
        if(scanf("%d", &choice) <= 0)
        {   //if the choice is not an integer then print out telling them and exit program
            printf("Enter only an Integer\n");
            exit(0);
        }
        else
        {
            switch(choice)
            {
            //case 1 to read the data file and to add it to the memory block in alphabetical order
            case 1:
                readDataFile(&head);
                break;
            //case 2 to display the data appropriately
            case 2:
                display(head);
                break;
            //reverse the items on the list to descend or re ascend.
            case 3:
                recursiveReverse(&head);
                break;
            //write the data into a file in whichever order the user wants
            case 4:
                writeDataFile(head);
                break;
            //exits the program when user choses.
            case 5:
                printf("You have chosen to Exit the Program.\n\n");
                return 0;
            //default in case user puts an invalid number
            default:
                printf("Invalid option\n");

            }
        }
    }

    return 0;

    display(head);
}
