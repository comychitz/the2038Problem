#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void getTime( int *seconds, char *binary );
void convertToBinaryString( int value, char *out );
void runCurrentTime( void );
void runRightBeforeOverflow( void );
void printUsage( void );

int main( int argc, char *argv[] )
{
  int c;
  while( (c = getopt( argc, argv, "c" )) != -1 )
  {
    switch(c)
    {
      case 'c':
	runCurrentTime();
	break;
      default:
	printUsage();
	return -1;
    }
  }
  runRightBeforeOverflow();

  return 0;
}

void runRightBeforeOverflow( void )
{
  char binaryString[33];
  memset( binaryString, 0, 33 );
  int tenSecondsPrior = 0xFFFFFFFF/2 - 10;

  system( "clear" );
  printf( "        --- The 2038 Problem ---\n\n" );
  printf( "Starting 10 seconds before the overflow..." );
  fflush(stdout);
  sleep( 2 );

  while( true )
  {
    system("clear");
    printf( "        --- The 2038 Problem ---\n\n" );
    convertToBinaryString( tenSecondsPrior, binaryString );
    printf( "Binary: %s\n", binaryString );
    printf( "32-bit int: %d\n", tenSecondsPrior );
    tenSecondsPrior++;
    sleep(1);
  }
}

void printUsage( void )
{
  printf("--- The 2038 Problem ---\n");
  printf("A program to illustrate the famous 2038 problem.\n");
  printf("Specifying no arguments starts the time 10 seconds\n");
  printf("prior to the overflow occuring, which occurs at\n");
  printf("19 January 2038 03:14:08 UTC");
  printf("\n");
  printf("Usage: ./the2038problem [-c]\n");
  printf("\n");
  printf("Options\n");
  printf("-c		  display current time\n");
}

void runCurrentTime( void )
{
  char binaryString[33];
  char dateString[32];
  int seconds;

  memset( binaryString, 0, 33 );

  while( true )
  {
    system("clear");
    getTime( &seconds, binaryString );
    time_t curTime = time(NULL);
    strftime( dateString, 
	      sizeof(dateString)-1, 
	      "%Y-%m-%d %H:%M:%S", 
	      localtime(&curTime) );
    printf( "Binary: %s\n", binaryString );
    printf( "32-bit int: %d\n", seconds );
    printf( "Date: %s\n", dateString );
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

