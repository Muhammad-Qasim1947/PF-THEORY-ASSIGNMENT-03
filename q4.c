#include <stdio.h>
#include <string.h>

struct books
{
    int id;
    int popularity;
    int lastaccess;
};

void addbook(struct books shelf[], int *numofbooks, int capacity, int id, int popularity, int *timestamp)
{
    int found = 0;
    for (int i = 0; i < *numofbooks; i++)
    {
        if (shelf[i].id == id)
        {
            shelf[i].popularity = popularity;
            shelf[i].lastaccess = (*timestamp)++;
            found = 1;
        }
    }

    if (!found)
    {
        // if shelf is not full
        if (*numofbooks < capacity)
        {
            shelf[*numofbooks].id = id;
            shelf[*numofbooks].popularity = popularity;
            shelf[*numofbooks].lastaccess = (*timestamp)++;
            (*numofbooks)++;
        }
        // if shelf is full
        else
        {
            int index = 0;
            for (int i = 0; i < *numofbooks; i++)
            {
                if (shelf[i].lastaccess < shelf[index].lastaccess)
                {
                    index = i;
                }
            }
            shelf[index].id = id;
            shelf[index].popularity = popularity;
            shelf[index].lastaccess = (*timestamp)++;
        }
    }
}

int access(struct books shelf[], int *numofbooks, int id, int *timestamp)
{
    for (int i = 0; i < *numofbooks; i++)
    {
        if (shelf[i].id == id)
        {
            shelf[i].lastaccess = (*timestamp)++;
            return shelf[i].popularity;
        }
    }
    return -1;
}

int main()
{
    int capacity, Q;

    printf("Enter The Capacity Of The Shelf : ");
    scanf("%d", &capacity);
    printf("\nEnter The Number Of Operations : ");
    scanf("%d", &Q);

    struct books shelf[capacity];
    int numofbooks = 0;
    int timestamp = 0;

    for (int i = 0; i < Q; i++)
    {
        char operation[10];
        printf("\nEnter The Operation You Want To Choose (ADD or ACCESS) : ");
        scanf("%s", operation);

        if (strcmp(operation, "ADD") == 0)
        {
            int id, popularity;
            printf("Enter The Book ID : ");
            scanf("%d", &id);
            printf("Enter The Book Popularity : ");
            scanf("%d", &popularity);
            addbook(shelf, &numofbooks, capacity, id, popularity, &timestamp);
        }
        else if (strcmp(operation, "ACCESS") == 0)
        {
            int id;
            printf("Enter The Book ID : ");
            scanf("%d", &id);
            int popularity = access(shelf, &numofbooks, id, &timestamp);
            printf("%d\n",popularity);
        }
    }
    return 0;
}