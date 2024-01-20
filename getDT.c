#include "types.h"
#include "stat.h"
#include "user.h"
#include "date.h"

int main (int argc, char *argv[])
{
	struct rtcdate s;
	
	if(datetime(&s)==-1)
	{
		printf(2, "Failed To Obtain Date/Time");
		exit(); 
	}
	
	printf(1, "Date Is: %d/%d/%d And Time Is: %d:%d:%d", s.day, s.month, s.year, (s.hour + 2), s.minute, s.second); 
	exit(); 
}
