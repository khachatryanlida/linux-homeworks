#include <iostream>
#include <string.h>
#include <signal.h>
#include <sys/ucontext.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>

//Signal handler for SIGUSR1
void sigusr1(int sig, siginfo_t *info, void *context) {
  
   ucontext_t *ucontext = (ucontext_t *) context;
  
  // Extract sender's UID and username
  uid_t sender_uid = info->si_uid;
  struct passwd *pw = getpwuid(sender_uid);
  char *sender_username = pw->pw_name;

  // Extract sender's PID
  pid_t sender_pid = info->si_pid;

   // Extract register values
  unsigned long eip = ucontext->uc_mcontext.gregs[REG_RIP];
  unsigned long eax = ucontext->uc_mcontext.gregs[REG_RAX];
  unsigned long ebx = ucontext->uc_mcontext.gregs[REG_RBX];

  //Print
  std::cout << "Received a SIGUSR1 signal from process " << sender_pid << " executed by " << sender_uid << " (" << sender_username << ")." << std::endl;
  std::cout << "State of the context: EIP = " << eip << ", EAX = " << eax << ", EBX = " << ebx << "." << std::endl;
   
}

int main() {
  struct sigaction action;
  memset(&action, 0, sizeof(action));
  action.sa_sigaction = sigusr1;
  action.sa_flags = SA_SIGINFO;
  
  int result = sigaction(SIGUSR1, &action, NULL);

  if (result < 0) {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
  }

  std::cout << "PID: " << getpid() << std::endl;

  while (true) {
    sleep(3);
  }
  
}
