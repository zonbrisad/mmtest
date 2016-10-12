/* 
 * File:   main.c
 * Author: pmg
 *
 * Created on den 23 april 2012, 23:58
 */

#include <stdio.h>
#include <stdlib.h>
#include <argtable2.h>

#include <pthread.h>

#include "mmmotor.h"
#include "channel.h"
#include "alarm.h"
#include "httpThread.h"
#include "motorThread.h"



CHANNEL chns[10];

CHANNEL_MODE modes[] = {
  CHANNEL_MODE_NORMAL,
  CHANNEL_MODE_NORMAL,
  CHANNEL_MODE_NORMAL,
  CHANNEL_MODE_NORMAL,
  CHANNEL_MODE_NORMAL,
  CHANNEL_MODE_MIN,
  CHANNEL_MODE_MAX,
  CHANNEL_MODE_AVERAGE,
  CHANNEL_MODE_LIMIT,
  CHANNEL_MODE_INTEGRATE, 
};

/**
 * 
 */
int main(int argc, char** argv) {
  int nerrors;
  int i;
  
  for (i=0; i<10; i++) {
    channelInit(&chns[i]);
    channelSetMode(&chns[i], modes[i]);
  }

  struct arg_lit *help = arg_lit0("h", "help", "Print help options");
  struct arg_end *end = arg_end(20);

  void *argtable[] = {help, end};

  if (arg_nullcheck(argtable) != 0)
    printf("error: insufficient memory\n");

  nerrors = arg_parse(argc, argv, argtable);

  // Display the error details contained in the arg_end struct.
  if (nerrors > 0) {
    arg_print_errors(stdout, end, "mmmotor");
    printf("Try '%s --help' for more information.\n", "mmmotor");
    exit(0);
  }

  if (help->count) {
    printf("Testprogram for Malmberg Mini Motor\n");
    arg_print_glossary(stdout, argtable, "  %-25s %s\n");
    exit(0);
  }
  
  for (i=0; i<10; i++) {
    printf("%2d %s\n", i, channel_toString(&chns[i]));
  }
  
  
  
  // cleanup
  arg_freetable(argtable, sizeof (argtable) / sizeof (argtable[0]));
  pthread_exit(NULL);
  return (EXIT_SUCCESS);
}

