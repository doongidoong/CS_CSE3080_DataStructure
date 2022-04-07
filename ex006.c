#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

/*
typedef struct {
  char name[10];
  int age;
  float salary;
} humanBeing;
*/

struct humanBeing {
  char name[10];
  int age;
  float salary;
};

int humans_equal(struct humanBeing, struct humanBeing);

void main() {

  struct humanBeing person1, person2;
  int rv;
 
  strcpy(person1.name, "James"); //string을 넣어야하므로 strcopy를 사용함.
  person1.age = 10;
  person1.salary = 35000;

  strcpy(person2.name, "James");
  person2.age = 10;
  person2.salary = 350000;
  struct humanBeing person3;
  strcpy(person3.name,"James");
  person3.age = 10;
  person3.salary = 35000;
  //if(person1==person2) printf("에러가 남");
  if(humans_equal(person1, person2))
    printf("The two human beings are the same.\n");
  else
    printf("The two human beings are NOT the same.\n");
  if(humans_equal(person1, person3))
    printf("The two human beings are the same.\n");
  else
    printf("The two human beings are NOT the same.\n");
}
  
int humans_equal(struct humanBeing person1, struct humanBeing person2) {
  /* returns TRUE if person1 and person2 are the same human being, 
     otherwise return FALSE */
  if(strcmp(person1.name, person2.name))//이때문에 요소 하나하나씩 비교함
    return FALSE;
  if(person1.age != person2.age)
    return FALSE;
  if(person1.salary != person2.salary)
    return FALSE;
  return TRUE;
}


