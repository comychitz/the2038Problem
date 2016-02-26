#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>

void getTime( int *seconds, char *binary );
void convertToBinaryString( int value, char *out );

int main( int argc, char *argv[] )
{
  char binaryString[32];
  int seconds;

  while( true )
  {
    system("clear");
    getTime( &seconds, binaryString );
    printf( "Binary: %s\n", binaryString );
    printf( "32-bit int: %d\n", seconds );
    sleep(1);
  }
}

void getTime( int *seconds, char *binary )
{
  struct timeval t;
  gettimeofday( &t, NULL );
  *seconds = t.tv_sec;
  convertToBinaryString( t.tv_sec, binary );
}

void convertToBinaryString( int value, char *out )
{
  if( !out )
  {
    return; // don't risk crashing the program
  }
  int i;
  for( i=31; i>=0; i-- )
  {
    if( value & 1 )
    {
      out[i] = '1';
    }
    else
    {
      out[i] = '0';
    }
    value = value >> 1;
  }
}

