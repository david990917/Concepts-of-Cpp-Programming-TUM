#include "filedescriptor.h"
#include <unistd.h>

namespace net {
FileDescriptor::FileDescriptor(int fd)
    : fd_(fd)
{}

FileDescriptor::~FileDescriptor()
{
    close(fd_);
}


};   // namespace net