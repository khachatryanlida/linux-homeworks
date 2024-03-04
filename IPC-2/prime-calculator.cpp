#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

// m prime number or not
bool is_prime (int m) {
 for(int i = 2; i <= m/2; i++) {
   if(m % i == 0) {
     return false;
   }
 }
  return true;
}
//Find the mth prime number
int m_prime_number(int m) {
  int count = 0;
  while(m != 0) {
    ++count;
    if(is_prime(count)) {
      --m;
    }
  }
  return count;
}

int main() {
  // Pipe file descriptors for commmunication between parent and child processes
  int pipefd_1 [2];
  int pipefd_2 [2];

// Create the pipes
int pipe_result_1 = pipe(pipefd_1);
if(pipe_result_1 < 0) {
  std::cerr << strerror(errno) << std::endl;
  exit(errno); 
}
int pipe_result_2 = pipe(pipefd_2);
if(pipe_result_2 < 0) {
  std::cerr << strerror(errno) << std::endl;
  exit(errno);
 }
//Fork to create a child process
  int pid = fork();

  if(pid < 0) {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
  }
//Child process
  if(pid == 0) {
    //Close the write end of the pipe
    close(pipefd_1[1]);
    //Close the read end of the pipe
    close(pipefd_2[0]);

    int m;
    while(true) {
      //Read the m from the pipe
      int read_result = read(pipefd_1[0], &m, sizeof(m));
      if(read_result < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
      }
     int m_prime_num = m_prime_number(m);
      //Write the mth prime number to the pipe
      int write_result = write(pipefd_2[1], &m_prime_num, sizeof(int));
      if(write_result < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
      }
    }
  }
  //Parent process
  if(pid > 0) {
    //Close the read end of the pipe
    close(pipefd_1[0]);
    //Close the write end of the pipe
    close(pipefd_2[1]);

    int m;
    while(true) {
      std::string number;
      std::cout << "Enter the number or 'exit' " << std::endl;
      std::cin >> number;
      if(number == "exit") {
        std::cout << "Exiting the program" << std::endl;
        break;
      }
      //Convert the string to integer
      m = std::stoi(number);
      //Write the m to the pipe
      int write_result = write(pipefd_1[1], &m, sizeof(int));
      if(write_result < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
      }
      int result;
      //Read the mth prime number from the pipe
      int read_result = read(pipefd_2[0], &result, sizeof(result));
      if(read_result < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
      }
      std::cout << "Received calculation result of prime(" << m << ") = " << result << std::endl;
    }
  }
  return 0;
}
