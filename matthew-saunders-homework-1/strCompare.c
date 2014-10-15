#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bstsort.h"

void strCompareUsage();
int compareWithCase(char* str1, char* str2);
int compareWithOutCase(char* str1, char* str2);
int strCompare(char* string1, char* string2, int flag);

void strCompareUsage()
{
  fprintf(stderr, "usage: strCompare [-w] [string1] [string2]\n");
  exit(1);
}

int compareWithCase(char* str1, char* str2){
  while(*str1 != '\0' && *str2 != '\0'){
    if(*str1 != *str2){
      return *str1 - *str2;
    }
    str1++;
    str2++;
  }

  if(*str1 != '\0' || *str2 != '\0'){
    return -1;
  }

  /* strings match */
  return 0;
}

int compareWithOutCase(char* str1, char* str2){
  while(*str1 != '\0' && *str2 != '\0'){
    if(*str1 != *str2 && *str1 != (*str2 + 32) && *str1 != (*str2 - 32)){
      return *str1 - *str2;
    }
    str1++;
    str2++;
  }

  if(*str2 != '\0'){
    return 1; /* string1 is shorter */
  }
  else if(*str1 != '\0'){
    return -1; /* string2 is shorter */
  }

  /* strings match */
  return 0;
}

int strCompare(char* string1, char* string2, int cs){
  if(cs)
    return compareWithCase(string1, string2);
  else
    return compareWithOutCase(string1, string2);
}
