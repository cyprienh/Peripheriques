#include "Driver_STD.h"

int String_Length(char * str){
	int i = 0;
	
	while (str[i] != 0) {
		i++;
	}
	return i;
}

char String_Compare(char* str1, char* str2) {
	char length;
	int i;
	
	if(String_Length(str1) != String_Length(str2))
		return 0;
	length = String_Length(str1);
	
	for(i = 0; i<length; i++) {
		if(str1[i] != str2[i])
			return 0;
	}
	return 1;
}
