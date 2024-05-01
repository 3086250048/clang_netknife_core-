#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
//去除尾部空格
char *rtrim(char *str)
{
	if (str == NULL || *str == '\0')
	{
		return str;
	}
 
	int len = strlen(str);
	char *p = str + len - 1;
	while (p >= str  && isspace(*p))
	{
		*p = '\0';
		--p;
	}
 
	return str;
}
 
//去除首部空格
char *ltrim(char *str)
{
	if (str == NULL || *str == '\0')
	{
		return str;
	}
 
	int len = 0;
	char *p = str;
	while (*p != '\0' && isspace(*p))
	{
		++p;
		++len;
	}
 
	memmove(str, p, strlen(str) - len + 1);
 
	return str;
}


//去除\n前后的empty字符
char * tidy_str(char *str){
	if(str==NULL || *str == '\0'){
		return str;
	}
	char *p = str;
    while(*p !='\0' ){
		if( *p != '\0' && *p == '\n'  &&  isspace(*(p-1))){
			memmove(p-1 , p ,strlen(p)+1);
			--p;
		}	
		if( *p != '\0' && *p == '\n'  &&  isspace(*(p+1))){
			memmove( p+1 ,p+2 ,strlen(p)+1);
		}
		++p;
	}
	return str;	
}

void remove_spaces_around_char(char *str, char ch) {
    char *read_ptr = str;
    char *write_ptr = str;
    int found_char = 0;

    while (*read_ptr) {
        if (*read_ptr == ch) {
            // Found the target char, remove spaces before it
            while (write_ptr > str && isspace(*(write_ptr - 1)) && (*(write_ptr - 1) != '\n')) {
                write_ptr--;
            }
            found_char = 1;
            *write_ptr++ = *read_ptr++;
            // Remove trailing spaces
            while (isspace(*read_ptr) && (*read_ptr != '\n')) {
                read_ptr++;
            }
        } else {
            // Copy non-target characters
            *write_ptr++ = *read_ptr++;
        }
    }

    *write_ptr = '\0'; // Null-terminate the string
}

//去除首尾空格
char *trim(char *str)
{
	str = rtrim(str);
	str = ltrim(str);
	remove_spaces_around_char(str,'\n');
	return str;
}
