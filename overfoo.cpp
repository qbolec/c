#include <iostream.h>

COMMAND(1)
{
	cout << "Komand jeden";
}
COMMAND(2)
{
	cout << "Komand jeden";
}
COMMAND(3)
{
	cout << "Komand jeden";
}
int main()
{
	long cmd=0;
	cin>> cmd;
	COMMAND(cmd);
	return 0;
}
