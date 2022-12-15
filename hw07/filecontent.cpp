#include "filecontent.h"

// TODO constructors
FileContent::FileContent(const std::string& content)
    : content(content)
{}
FileContent::FileContent(std::string&& content)
{
    this->content = std::move(content);
}
FileContent::FileContent(const char* content)
    : content(content)
{}

// TODO member functions
/** what's the actual storage size of the file content? */
size_t FileContent::get_size() const
{
    return content.length();
}

/** get a read-only handle to the data */
// XXX: make::shared
std::shared_ptr<const std::string> FileContent::get() const
{
    return std::make_shared<const std::string>(content);
}

// add automatic comparisons
// XXX: Define params by ourselves
bool FileContent::operator==(const FileContent& fc) const
{
    return content == fc.content;
}
