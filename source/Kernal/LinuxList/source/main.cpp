#include <iostream>
#include "linuxlist.h"
using namespace std;
struct Node
{
    struct list_head head;
    int value;
};

int main(int argc, char *argv[])
{
    struct Node node_test_t={0};
    struct list_head *list=(struct list_head*)&node_test_t;
    struct list_head *slider=NULL;
    INIT_LIST_HEAD(list);

    printf("Insert begin ...\n");

    for(int i=0;i<5;i++)
    {
        struct Node *n_t=(struct Node*)malloc(sizeof(struct Node));
        n_t->value=i;
        list_add_tail((struct list_head*)n_t,list);

    }
    printf("Insert end\n");
    list_for_each(slider,list)
    {
        printf("%d ", ((struct Node*)slider)->value);
    }

    cout << "\n Hello World!" << endl;
    return 0;
}
