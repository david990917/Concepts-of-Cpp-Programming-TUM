#include "logger.h"

#include <chrono>
#include <ctime>

Logger::Logger(const std::string& filename)
    : file{}
{
    auto cwd = fs::current_path();

    if (fs::exists(filename)) {
        if (fs::exists(filename + "_old")) {
            fs::remove(filename + "_old");
        }
        fs::rename(filename, filename + "_old");
    }

    file.open(filename);
    if (not file.is_open()) {
        throw std::runtime_error("File could not be opened!");
    }

    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    file << "Commencing logging for directory: " << cwd << std::endl
         << "Current time is: " << std::ctime(&time) << std::endl;
}

Logger::~Logger()
{
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
