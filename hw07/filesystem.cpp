#include "filesystem.h"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>

Filesystem::Filesystem() {}

bool Filesystem::register_file(const std::string& name, const std::shared_ptr<File>& file)
{
    // TODO: Something needs to be done here
    if (name == "" or file == nullptr) {
        return false;
    }

    auto it = files.find(name);
    if (it != files.end()) {
        return false;
    }

    auto thisptr = this->shared_from_this();

    // TODO: You need some checks here
    if (file->filesystem != nullptr) {
        return false;
    }

    file->filesystem = std::move(thisptr);

    // TODO: More updates you need to do!
    files[name] = file;

    // TODO register a new file here
    file->isRegistered = true;
    return true;
}

bool Filesystem::remove_file(std::string_view name)
{
    // TODO file removal

    // name not exists -> false
    auto it = files.find(std::string(name));
    if (it == files.end()) {
        return false;
    }

    files.erase(it);
    return true;
}

bool Filesystem::rename_file(std::string_view source, std::string_view dest)
{
    // TODO file renaming

    // source not exists -> false
    auto it = files.find(std::string(source));
    if (it == files.end()) {
        return false;
    }

    // dest exists -> false
    auto it2 = files.find(std::string(dest));
    if (it2 != files.end()) {
        return false;
    }

    files[std::string(dest)] = files[std::string(source)];
    files.erase(it);
    return true;
}

std::shared_ptr<File> Filesystem::get_file(std::string_view name) const
{   // TODO
    auto it = files.find(std::string(name));
    if (it == files.end()) {
        return nullptr;
    }
    return it->second;
}

size_t Filesystem::get_file_count() const
{
    // TODO
    return files.size();
}

size_t Filesystem::in_use() const
{
    // TODO sum up all real file sizes
    size_t total_size = 0;
    for (const auto& [name, file] : files) {
        total_size += file->get_size();
    }
    return total_size;
}

// convenience function so you can see what files are stored
std::string Filesystem::file_overview(bool sort_by_size)
{
    std::ostringstream output;
    // this function is not tested, but it may help you when debugging.

    output << "files in filesystem: " << std::endl;

    // for (auto&& entry : this->files) {
    //     // TODO: fix printing name, type and size
    //     output << entry.get_name << std::endl;
    // }
    return std::move(output).str();
}

std::vector<std::shared_ptr<File>> Filesystem::files_in_size_range(size_t max, size_t min) const
{
    // TODO: find the matching files and return them
    std::vector<std::shared_ptr<File>> matching_files;
    for (const auto& [name, file] : files) {
        size_t size = file->get_size();
        if (size >= min && size <= max) {
            matching_files.push_back(file);
        }
    }
    return matching_files;
}
