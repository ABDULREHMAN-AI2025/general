#include <stdio.h>
#include<string.h>

typedef struct student{
    char name[20];
    int age;

}st;

int main(){

    st st1;
    strcpy(st1.name,"abdul");
    st1.age=20;
    st *ptr =&st1;

    printf("%s %d\n ",ptr->name,ptr->age);

    
    return 0;
}