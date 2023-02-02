#include "monitor.h"

#include <thread>

FileMonitor::FileMonitor(const std::string& targetpath, std::chrono::milliseconds interval,
                         const std::string& logfilename)
    : targetpath{targetpath}
    , logger{logfilename}
    , interval{interval}
{
    for (auto&& file : fs::recursive_directory_iterator(targetpath)) {
        paths[file.path().string()] = fs::last_write_time(file);
    }
}

// Monitor the targetpath for changes and pass information to the logger in case of differences
void FileMonitor::start(std::chrono::seconds timeout)
{
    bool running = true;
    auto start   = std::chrono::system_clock::now();
    while (running) {
        std::this_thread::sleep_for(interval);

        auto it = paths.begin();
        while (it != paths.end()) {
            if (not fs::exists(it->first)) {
                logger.log(it->first, status::removed);
                it = paths.erase(it);
            }
            else {
                it++;
            }
        }

        for (auto&& file : fs::recursive_directory_iterator(targetpath)) {
            auto write_time = fs::last_write_time(file);
            auto name       = file.path().string();

            if (not paths.contains(name)) {
                paths[name] = write_time;
                logger.log(name, status::added);
            }
            else {
                if (paths[name] != write_time) {
                    paths[name] = write_time;
                    logger.log(name, status::changed);
                }
            }
        }

        auto current = std::chrono::system_clock::now();
        if (current - start > timeout) {
            running = false;
        }
    }
}
