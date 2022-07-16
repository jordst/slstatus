#include <stdio.h>
#include <string.h>
#include "../util.h"

char*
return_str(FILE *s)
{
	char *newstr;
	int ch;
	int i=0;
	while ( (ch=fgetc(s)) != EOF ) {
		newstr[i] = ch;
		i++;
	}
	return newstr;
}

const char *
cmus_status(void)
{
	FILE *s, *n;
	int ch;
	char *song_name, *cmus_status;

	s = popen("cmus-remote -C status | awk 'FNR==1 {print $2}'", "r");
	cmus_status = return_str(s);
	pclose(s);

	if (strcmp(cmus_status, "playing")) {
		n = popen("cmus-remote -C 'format_print %t - %a' | tr '\n' ' '", "r");
		song_name = return_str(n);
		pclose(n);
		return bprintf(song_name);
	}
	return bprintf("");
}
