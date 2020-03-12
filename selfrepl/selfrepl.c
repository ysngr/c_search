#include <stdio.h>

char *s = "#include <stdio.h>%c%cchar *s = %c%s%c;%c%cint main(void)%c{%c%cprintf(s, 10, 10, 34, s, 34, 10, 10, 10, 10, 9, 10, 9, 10);%c%creturn 0;%c}";

int main(void)
{
	printf(s, 10, 10, 34, s, 34, 10, 10, 10, 10, 9, 10, 9, 10);
	return 0;
}