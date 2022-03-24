#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int year;
  int month;
  int day;
} date;

typedef struct {
  enum tagField {pitcher, hitter} role;
  union {
    int SO;
    int HR;
  } u;
} playerType;

typedef struct {
  char name[40];
  int age;
  float salary;
  date dob;
  playerType playerInfo;
} baseballPlayer;

void printPlayerInfo(baseballPlayer);

void main() {

  baseballPlayer person1, person2;

  strcpy(person1.name, "Hyun-Jin Ryu");
  person1.age = 32;
  person1.salary = 17900000.0;
  person1.dob.year = 1987;
  person1.dob.month = 3;
  person1.dob.day = 25;
  person1.playerInfo.role = pitcher;
  person1.playerInfo.u.SO = 163;

  strcpy(person2.name, "Shin-Soo Choo");
  person2.age = 37;
  person2.salary = 21000000.0;
  person2.dob.year = 1982;
  person2.dob.month = 7;
  person2.dob.day = 13;
  person2.playerInfo.role = hitter;
  person2.playerInfo.u.HR = 24;

  printPlayerInfo(person1);
  printPlayerInfo(person2);

  
  printf("address of name  : %p\n", &person1.name);
  printf("address of age   : %p\n", &person1.age);
  printf("address of salary: %p\n", &person1.salary);
  printf("address of year  : %p\n", &person1.dob.year);
  printf("address of month : %p\n", &person1.dob.month);
  printf("address of day   : %p\n", &person1.dob.day);
  printf("address of role  : %p\n", &person1.playerInfo.role);
  printf("address of SO    : %p\n", &person1.playerInfo.u.SO);
  printf("address of HR    : %p\n", &person1.playerInfo.u.HR);
  
}

void printPlayerInfo(baseballPlayer p) {

    printf("--------------------------------\n");
    printf(" name: %s\n", p.name);
    printf(" age : %d\n", p.age);
    printf(" salary: $ %.1f\n", p.salary);
    printf(" dob : %4d/%2d/%2d\n", p.dob.year, p.dob.month, p.dob.day);
    if(p.playerInfo.role == pitcher) {
      printf(" PITCHER SO: %d\n", p.playerInfo.u.SO);
    }
    else {
      printf(" HITTER  HR: %d\n", p.playerInfo.u.HR);
    }
    printf("--------------------------------\n");
}



