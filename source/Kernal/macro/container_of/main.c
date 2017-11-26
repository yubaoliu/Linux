#include <stdio.h>
#define offsetof(type, member) (size_t)&(((type*)0)->member)

#ifndef container_of
#define container_of(ptr,type,member)({\
    const typeof(((type*) 0)->member)* __mptr=(ptr);    \
    (type*)((char*)__mptr-offsetof(type,member));    \
})
#endif

#ifndef container_of_simple
    #define container_of_simple(ptr,type,member)  ((type*)((char*)ptr-offsetof(type,member)))
#endif
struct ST
{
    int i;
    char c;
    int j;
};
void comma_operator_common_C()
{
    int a=0;
    int b=0;
    int r=(
                a=1,
                b=2,
                a+b
                );
    printf("r = %d \n",r);

}
void GNU_extended_C()
{
    int r=({
               int a=1;
               int b=2;
               a+b;
           });
    printf("r = %d \n",r);
}
void type_of()
{
    int i=100;
    typeof(i) j=i;
    const typeof(j)* p=&j;

    printf("sizeof(j) = %d \n",(int)sizeof(j));
    printf("j = %d\n",j);
    printf("p = %d \n", *p);
}

int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    comma_operator_common_C();
    GNU_extended_C();
    type_of();

    struct ST s={0};
    char* pc=&s.c;
    struct ST* pst=container_of(pc, struct ST,c);
    printf("&s=%p\n",&s);
    printf("pst=%p\n",pst);

    struct ST* pst_simple=container_of_simple(pc,struct ST,c);
    printf("pst_simple=%p\n",pst_simple);

    //Datatype check (unsafe)
    int e=0;
    int *pe=&e;
    struct ST* pst_error=container_of_simple(pe,struct ST,c);
    printf("pst_error=%p\n",pst_error);

    //compile warning
    struct ST* pst_error_report=container_of(pe,struct ST,c);
    printf("pst_error_report=%p\n",pst_error_report);

    return 0;
}
