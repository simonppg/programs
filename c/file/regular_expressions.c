#include <sys/types.h>
#include <regex.h>
#include <stdio.h>

int main(int argc, char *argv[]){
        regex_t regex;
        int reti;
        char msgbuf[100];

/* Compile regular expression */
        reti = regcomp(&regex, "^(.*?(\bpwm\b)[^$]*)$", 0);
        if( reti ){
        	fprintf(stderr, "Could not compile regex\n");
        }

/* Execute regular expression */
        reti = regexec(&regex, "/sys/devices/ocp.3/pwsm_test_P8_13.9/period", 0, NULL, 0);
        if( !reti ){
                puts("Match");
        }
        else if( reti == REG_NOMATCH ){
                puts("No match");
        }
        else{
                regerror(reti, &regex, msgbuf, sizeof(msgbuf));
                fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        }

/* Free compiled regular expression if you want to use the regex_t again */
	regfree(&regex);

        return 0;
}