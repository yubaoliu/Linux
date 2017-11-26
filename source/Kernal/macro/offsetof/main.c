#include <stdio.h>
#ifndef offsetof
#define offsetof(TYPE,MEMBER)((size_t)&((TYPE*)0)->MEMBER)
#endif
struct ST
{
    int i;
    char c;
    int j;
};

void func (struct ST* pst)
{
    int* pi=&(pst->i); //(unsigned int)&s+0;
    int* pj=&(pst->j); //(unsigned int)&s+4;
    char* pc=&(pst->c);//(unsigned int)&s+8;

    printf("pst = %p \n",pst);
    printf("pi = %p \n",pi);
    printf("pc = %p \n",pc);
    printf("pj = %p \n",pj);
}

int main(int argc, char *argv[])
{
    struct ST s={0};
    func(&s);
    printf("--------\n");
    func(NULL);
    printf("--------\n");
    printf("offset i: %d \n",offsetof(struct ST,i));
    printf("offset c: %d \n",offsetof(struct ST,c));
    printf("offset j: %d \n",offsetof(struct ST,j));
    printf("Hello World!\n");
    return 0;
}
