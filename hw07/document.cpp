#include "document.h"


Document::Document(FileContent&& content)
    : File{std::move(content)}
{}

// TODO provide file type
std::string_view Document::get_type() const
{
    return "DOC";
}

size_t Document::get_raw_size() const
{
    // TODO get the document size
    return this->content.get_size();
}

unsigned Document::get_character_count() const
{
    // TODO count non whitespace characters
    unsigned count = 0;
    for (const auto& ch : *this->content.get()) {
        if (!std::isspace(ch)) ++count;
    }
    return count;
}

// TODO content update function
void Document::update(FileContent&& new_content)
{
    content = std::move(new_content);
}