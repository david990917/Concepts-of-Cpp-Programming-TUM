#include "logger.h"

#include <chrono>
#include <ctime>

#include <filesystem>
namespace fs = std::filesystem;


Logger::Logger(const std::string& filename)
    : file{fs::current_path() / filename}
    , filename(filename)
{
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    file << "Commencing logging for directory: "
         << "TODO: insert current path here.." << std::endl
         << "Current time is: " << std::ctime(&time) << std::endl;
}

Logger::~Logger()
{
    auto dir         = fs::current_path();
    auto orgfilename = dir / filename;
    if (fs::exists(orgfilename)) {
        if (fs::exists(orgfilename + "_old")) {
            fs::remove(orgfilename + "_old");
        }
        fs::rename(orgfilename, orgfilename / "_old");
    }

    file.open(orgfilename);
    if (!file.is_open()) {
        throw std::runtime_error("File could not be opened!");
    }
    // explicit file closing needed in Windows
}

void Logger::log(const std::string& path, status what) const
{
    if (not file.is_open()) {
        throw std::runtime_error("File could not be opened!");
    }

    switch (what) {
    case status::added: file << "+ File was added:    " << path << std::endl; break;
    case status::changed: file << "! File was modified: " << path << std::endl; break;
    case status::removed: file << "~ File was deleted:  " << path << std::endl; break;
    default: file << "? Error! Unknown file status detected for: " << path << std::endl; break;
    }
}
