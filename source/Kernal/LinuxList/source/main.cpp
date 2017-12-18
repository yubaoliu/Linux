#include <iostream>
#include "linuxlist.h"
using namespace std;

void list_demo_1()
{
    struct Node
    {
        struct list_head head;
        int value;
    };

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

    printf("\n delete one node (value==3): \n");
    list_for_each(slider,list)
    {
        if(((struct Node*)slider)->value==3)
        {
            list_del(slider);
            free(slider);
            break;
        }
    }

    printf("After delete \n");
    list_for_each(slider,list)
    {
        printf("%d ", ((struct Node*)slider)->value);
    }
}
void list_demo_2()
{
    struct Node
    {
        int value;
        struct list_head head;
    };

    struct Node node_test_t={0};
    struct list_head *list=&node_test_t.head;
    struct list_head *slider=NULL;
    INIT_LIST_HEAD(list);

    printf("Demo 2\n");
    printf("Insert begin ...\n");

    for(int i=0;i<5;i++)
    {
        struct Node *n_t=(struct Node*)malloc(sizeof(struct Node));
        n_t->value=i;
        list_add(&n_t->head,list);

    }
    printf("Insert end\n");
    list_for_each(slider,list)
    {
        printf("%d ",list_entry(slider,struct Node,head)->value);
    }

    printf("\n delete one node (value==3): \n");
    list_for_each(slider,list)
    {
        if(list_entry(slider,struct Node,head)->value ==3)
        {
            list_del(slider);
            free(list_entry(slider,struct Node,head));
            break;
        }
    }

    printf("After delete \n");
    list_for_each(slider,list)
    {
        printf("%d ", list_entry(slider,struct Node,head)->value);
    }

}

int main(int argc, char *argv[])
{
   // list_demo_1();
    list_demo_2();
    cout << "\n Hello World!" << endl;
    return 0;
}
