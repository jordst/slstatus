#include <stdio.h>
#include <string.h>
#include "../util.h"

const char *
cmus_status(void)
{
	char song[64];
	char status[64];
	//char nerr[7] = "playing";
	char songname[512], cmusstatus[512];
	FILE  *s,*n;

	sprintf(status, "cmus-remote -C status | awk 'FNR==1 {print $2}' > /tmp/cstatus");
	s = popen(status, "r");
	pclose(s);
	pscanf("/tmp/cstatus", "%s", cmusstatus);

	if (cmusstatus[1] == 'l') {
		sprintf(song, "cmus-remote -C 'format_print \"%%t - %%a\"' > /tmp/csong");
		n = popen(song, "r");
		pclose(n);
		pscanf("/tmp/csong", "%[^\n]", songname);
		return bprintf("%s", songname);
	}
	return bprintf("");
}
