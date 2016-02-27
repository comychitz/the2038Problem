#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void convertToBinaryString( int value, char *out );
void runCurrentTime( void );
void runRightBeforeOverflow( void );
void printUsage( void );

int main( int argc, char *argv[] )
{
  int c;
  while( (c = getopt( argc, argv, "ch" )) != -1 )
  {
    switch(c)
    {
      case 'c':
	runCurrentTime();
	break;
      case 'h':
	printUsage();
	return 0;
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
  char *dateString;
  time_t tenSecondsPrior = 0xFFFFFFFF/2 - 10;

  memset( binaryString, 0, 33 );
  dateString = malloc(32);

  setvbuf(stdout, NULL, _IONBF, 0);
  system( "clear" );
  printf( "        --- The 2038 Problem ---\n\n" );
  printf( "Starting 10 seconds before the overflow..." );
  fflush(stdout);
  sleep( 2 );

  while( true )
  {
    system("clear");
    strftime( dateString, 32, "%a %Y-%m-%d %H:%M:%S", gmtime(&tenSecondsPrior) );
    convertToBinaryString( (int) tenSecondsPrior, binaryString );
    printf( "        --- The 2038 Problem ---\n\n" );
    printf( "Binary: %s\n", binaryString );
    printf( "32-bit int: %d\n", (int) tenSecondsPrior );
    printf( "UTC Time: %s\n", dateString );
    tenSecondsPrior++;
    sleep(1);
  }
  free( dateString );
}

void printUsage( void )
{
  printf("--- The 2038 Problem ---\n");
  printf("A program to illustrate the famous 2038 problem.\n");
  printf("Specifying no arguments starts the time 10 seconds\n");
  printf("prior to the overflow occuring, which occurs at\n");
  printf("19 January 2038 03:14:08 UTC.\n");
  printf("\n");
  printf("Usage: ./the2038problem [-c]\n");
  printf("\n");
  printf("Options\n");
  printf("-c                display current time\n");
  printf("-h                print this message\n");
}

void runCurrentTime( void )
{
  char binaryString[33];
  char *dateString;

  dateString = malloc( 32 );

  memset( binaryString, 0, 33 );

  while( true )
  {
    system("clear");
    time_t curTime = time(NULL);
    strftime( dateString, 32, "%a %Y-%m-%d %H:%M:%S", gmtime(&curTime));
    convertToBinaryString( curTime, binaryString );
    printf( "Binary: %s\n", binaryString );
    printf( "32-bit int: %d\n", (int) curTime );
    printf( "UTC Time: %s\n", dateString );
    sleep(1);
  }
  free( dateString );
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

