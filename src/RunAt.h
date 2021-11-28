#ifndef	RUN_AT_H
#define RUN_AT_H

#include <Arduino.h>

#include <stdlib.h>

#define func_max_num 10

typedef struct {
  void (*function) ();
  ulong timestamp;
} function_to_run;

struct run_at_functions {
  function_to_run functions[func_max_num];
  uint8_t length = 0;
} run;

void run_at_init() {
  for (uint8_t i = 0; i < func_max_num; i++) {
    function_to_run *func_to_run = (function_to_run*) malloc(sizeof(function_to_run));
    func_to_run->function  = NULL;
    func_to_run->timestamp = 0;
    run.functions[i] = *func_to_run;
  }
}

void run_at_free() {
  for (uint8_t i = 0; i < func_max_num; i++) {
    run.functions[i].function  = NULL;
    run.functions[i].timestamp = 0;
    free(&(run.functions[i]));
  }
}

void run_at_add_function(void (*func) (), ulong timestamp) {
  if (run.length <= func_max_num - 1) {
    run.functions[run.length].function  = func;
    run.functions[run.length].timestamp = timestamp;
    run.length += 1;
  }
}

void run_function_in_millisec(void (*func) (), ulong millisec) {
  run_at_add_function(func, millis() + millisec);
}

bool run_at_if_time(function_to_run *func_to_run) {
  if (millis() >= func_to_run->timestamp) {
    func_to_run->function();
    return true;
  }
  return false;
}

void run_at_loop() {
  for (uint i = 0; i < run.length; i++) {
    if (run_at_if_time(&(run.functions[i]))) {
      for (uint j = i; j < run.length; j++) {
        run.functions[j] = run.functions[j+1];
      }
      run.length -= 1;
    }
  }
}

#endif
