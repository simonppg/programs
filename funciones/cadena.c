	#include <stdio.h>
	#include <string.h>

	void concat(char* s1, char* s2, char* ns) {
	    ns[0] = '\0';
	    strcpy(ns, s1);
	    strcat(ns, s2);
	}

	int main(int argc, char const *argv[])
	{
		char* s1="hola";
		char* s2 =" mundo";
		char s3[strlen(s1) + strlen(s2) + 1];
		concat(s1, s2, s3);

		printf("\n%s",s3);
		printf("\n");
		return 0;
	}