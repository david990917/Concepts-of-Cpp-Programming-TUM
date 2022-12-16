#include "filecontent.h"

// TODO constructors
FileContent::FileContent(const std::string& content)
    : content{std::make_shared<std::string>(content)}
{}
FileContent::FileContent(std::string&& content)
    : content{std::make_shared<std::string>(std::move(content))}
{}
FileContent::FileContent(const char* content)
    : content{std::make_shared<std::string>(content)}
{}

// TODO member functions
/** what's the actual storage size of the file content? */
size_t FileContent::get_size() const
{
    return this->content->size();
}

/** get a read-only handle to the data */
// XXX: make::shared
std::shared_ptr<const std::string> FileContent::get() const
{
    return this->content;
}

// add automatic comparisons
// XXX: Define params by ourselves
bool FileContent::operator==(const FileContent& fc) const
{
    return content == fc.content;
}
