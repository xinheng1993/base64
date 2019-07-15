#include "tools.h"

void str_uppercase(char s[]){
	size_t i;
	for(i=0;s[i]!='\0';i++)
		s[i]=toupper(s[i]);
}
