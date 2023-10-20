#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 10


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "File path" << std::endl;
        exit(1);
    }
    
    char* file = argv[1];
     
    int fd = open(file, O_RDONLY);

    if(fd < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    char buf[BUFFER_SIZE + 1];
    
    while(true) {
        
        ssize_t read_bytes = read(fd, buf, BUFFER_SIZE);
        if(read_bytes < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }   
        
        if(read_bytes == 0)
        {
            break;
        }
        
        buf[read_bytes] = '\0';
        std::cout << buf;      
        
    }
     int close_result = close(fd);
     if(close_result < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }  
        
    return 0;    

}