#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main() {
    regex_t regex;
    int reti;
    char msgbuf[100];

    // 编译正则表达式
    reti = regcomp(&regex, "^a", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // 匹配字符串
    reti = regexec(&regex, "bc", 0, NULL, 0);
    if (!reti) {
        printf("Match\n");
    } else if (reti == REG_NOMATCH) {
        printf("No match\n");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // 释放正则表达式
    regfree(&regex);

    return 0;
}
