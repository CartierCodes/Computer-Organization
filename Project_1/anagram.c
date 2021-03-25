/* Add the complete description of the program here */

#include <stdio.h>
#include <string.h> 

/* Swap function: It takes the pointers of two distinct charcaters as inputs and swap their contents     */ 
void swap(char *i, char *j) {
   char temp = *i;
   *i = *j;
   *j = temp;
}

void change(char * str, int len, int end){
  if(len == end) { printf("%s\n", str); }
  else {
    for(int i = len; i <= end; i++) {
      swap((str + len), (str + i));
      change(str, len + 1, end);
      swap((str + len), (str + i));
    }
  }
}

int main(int argc, char** argv) {
  change(argv[1], 0, strlen(argv[1]) - 1);
  return 0;
}