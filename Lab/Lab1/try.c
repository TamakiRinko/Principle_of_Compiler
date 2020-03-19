#include <stdio.h>


int main(){
	char str[20] = "0x12";
    printf("%d", strtol(str, NULL, 0));
	return 0;
}