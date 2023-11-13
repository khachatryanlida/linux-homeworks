#include <iostream>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>

void do_command (char** argv) {
  //Get the starting time.
  struct tms time_start;
  clock_t start_of_time;
  start_of_time = times(&time_start);

  pid_t pid = fork();
  if(pid < 0) {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
  }
  //Child process.
  if(pid == 0) {
    execvp(argv[0], argv);
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
  }
  //Parent process.
  if(pid > 0) {
    int status;
    //Parent process waits for child process to finish.
    waitpid(pid, &status, 0);
    //Get the ending time.
    struct tms time_end;
    clock_t end_of_time;
    end_of_time = times(&time_end);
    //Calculate the elapsed time.
    double elapsed_time = (double)(end_of_time - start_of_time);
    std::cout << "Command completed with exit code " << WEXITSTATUS(status)
      << " and took " << elapsed_time << " seconds." << std::endl;
  }
}
int main(int argc, char** argv) {
    if (argc < 2) {
         std::cerr << strerror(errno) << std::endl;
         exit(errno);
    }

    // Allocate memory.
    char** args_vec = new char*[argc];
    for (int i = 1; i < argc; i++) {
        args_vec[i - 1] = argv[i];
    }
    args_vec[argc - 1] = nullptr;

    // Call do_command.
    do_command(args_vec);

    delete[] args_vec;

    return 0;
}
