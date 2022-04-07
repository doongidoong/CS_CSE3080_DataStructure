#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100
#define COMPARE(x, y) (x < y ? -1 : (x > y ? 1 : 0))

typedef struct {
  int coef;
  int expon;
} polynomial;

// shared memory for storing polynomials
polynomial terms[MAX_TERMS];
int avail = 0;

void polynomial_add(int, int, int, int, int*, int*);
void polynomial_print(int, int);
void attach(int, int);

void main() {

  // starta and finisha defines polynomial a
  int starta, finisha;
  int startb, finishb;
  int startc, finishc;
  //a삽입
  starta = avail; //a 시작점, terms[0]
  terms[avail].expon = 1000; terms[avail].coef = 2; 
  avail++; // terms[1]
  terms[avail].expon = 0; terms[avail].coef = 1;
  finisha = avail;
  
  //b삽입
  avail++;//tersm[2] <- b시작점
  startb = avail;
  terms[avail].expon = 4; terms[avail].coef = 1;
  avail++;//terms[3]
  terms[avail].expon = 3; terms[avail].coef = 10;
  avail++;//terms[4]
  terms[avail].expon = 2; terms[avail].coef = 3;
  avail++;//terms[5]
  terms[avail].expon = 0; terms[avail].coef = 1;
  finishb = avail; //terms[6] 까지 b
  avail++;//terms[7] <- c 시작점
  polynomial_add(starta, finisha, startb, finishb, &startc, &finishc); //뒷 부분이 포인터인 이유는 c는 add 함수로 값을 변경해야하기 때문

  polynomial_print(starta, finisha);
  polynomial_print(startb, finishb);
  polynomial_print(startc, finishc);
}

void polynomial_add(int starta, int finisha, int startb, int finishb, int *startd, int *finishd) {
  /* add A(x) and B(x) to obtain D(x) */
  float coefficient; //계수
  *startd = avail; //시작점. B가 끝나고 다음 점, 현재 7
  while(starta <= finisha && startb <= finishb) //이제 계수가 큰 순부터 차례로 넣는다
    switch(COMPARE(terms[starta].expon, terms[startb].expon)) {
      case -1: /* a expon < b expon */ 
        attach(terms[startb].coef, terms[startb].expon); //terms에 계수와 exponet를 넣고 avall++
        startb++;//만약 b가 크다면 b의 값을 넣고 b의 다음인덱스를 가르키도록 함
        break;
      case 0: /* equal exponents */
        coefficient = terms[starta].coef + terms[startb].coef;
        if(coefficient) attach(coefficient, terms[starta].expon);
        starta++; startb++;
        break;
    case 1: /* a expon > b expon */
        attach(terms[starta].coef, terms[starta].expon);
        starta++;
        }
  /* add in remaining terms of A(x) */ 
  for( ; starta <= finisha; starta++) attach(terms[starta].coef, terms[starta].expon);//만약 a가 남았을 경우
  /* add in remaining terms of B(x) */
  for( ; startb <= finishb; startb++) attach(terms[startb].coef, terms[startb].expon);//만약 b가 남았을 경우
  *finishd = avail-1;//avail은 attach를 하면 넣은 값 다음을 가르키기 때문에 -1한 값이 마지맞
}

void attach(int coefficient, int exponent) {
  /* add a new term to the polynomial */
  if(avail >= MAX_TERMS) {
    fprintf(stderr, "too many terms in the polynomial"); exit(1);
  }
  terms[avail].coef = coefficient;
  terms[avail++].expon = exponent;
}

void polynomial_print(int starta, int finisha) {
  int i;
  for(i = starta; i <= finisha; i++) {//시작부터 끝까지 끝이 포함되게 만듦
    if(i == starta) printf("%dx^%d", terms[i].coef, terms[i].expon);
    else printf(" + %dx^%d", terms[i].coef, terms[i].expon);
  }
  printf("\n");
}






