#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

void initialize(int argc,char** argv) {

  if (argc < 2) {
    std::cout << "File path is not given" << std::endl;
    exit(1);

  }

  char* file = argv[1];
  int file_desc = open (file,O_RDWR);

  if (file_desc < 0){
      std::cerr << strerror(errno) << std::endl;
      exit (errno);
  }

  ssize_t redirect_cin = dup2(file_desc,0);
  ssize_t closed = close (file_desc);

   if (redirect_cin < 0){
     std::cerr << strerror(errno) << std::endl;
     exit(errno);
  }

  if(closed < 0 ){
      std::cerr << strerror(errno) << std::endl;
      exit(errno);
  }
}

int main(int argc, char** argv){
  initialize(argc, argv);
  std::string input;
  std::cin >> input;
  ssize_t size = input.size();
  std::string reversed(size + 1,'k');
  for(int i = 0;i <= size;++i)  {
    reversed[i] = input[size-i];
}
  reversed[size+1] = '\0';
  std::cout << reversed << std::endl;

  return 0;
}
