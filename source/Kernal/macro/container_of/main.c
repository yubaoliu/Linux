#include <stdio.h>
#define offsetof(type, member) (size_t)&(((type*)0)->member)

struct
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
    return 0;
}
