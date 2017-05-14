


#include <stdlib.h>
#include <stdio.h>

int main()
{

  int number[3];
  int *pointer;


  pointer = malloc (sizeof(number));

  printf("int size is = %lu bytes\n", sizeof(int));
  printf("pointer size is = %lu bytes\n", sizeof(pointer));

  pointer[0] = 1;
  pointer[1] = 2;
  pointer[2] = 3;

  printf("pointer size after assigned value is = %lu bytes\n", sizeof(pointer));

  for(int i = 0; sizeof(pointer) > i; i++) {
    printf("pointer[%d] address = %p\n",i, &pointer+i);             // print the pointer address in hexadecimal
    printf("pointer[%d] value = %d\n", i, *(pointer + i));          // print the pointer value
    printf("pointer[%d] value = %d\n\n", i, pointer[i]);            // alternative: pointer[i]
  }


  return 0;
}
