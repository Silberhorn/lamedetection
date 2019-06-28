#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "rs232.h"
#include <serial>

#define BUF_SIZE 128
/* /dev/ttyACM0 */
int main()
{
  Serial* SP = new Serial("/dev/ttyACM0");
	if (SP->IsConnected())
	{
		cout << "We're connected" << endl;
		cout << "________________" << endl;
	}
  return(0);
}

