#include "types.h"
#include "stat.h"
#include "user.h"

volatile int sink;

static void do_work(int iters){
  for(int i = 0; i < iters; i++)
    sink += i;
}

static void run_child(int t){
  settickets(t);
  for(int k = 0; k < 200; k++)
    do_work(200000);
  printf(1, "[PID %d] child tickets=%d done\n", getpid(), t);
  exit();
}

int
main(void)
{
  int pid;

  pid = fork();
  if(pid == 0) run_child(10);

  pid = fork();
  if(pid == 0) run_child(5);

  pid = fork();
  if(pid == 0) run_child(1);

  while(wait() > 0) { }
  printf(1, "all done\n");
  exit();
}