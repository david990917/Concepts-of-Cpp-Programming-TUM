#include "video.h"

Video::Video(FileContent&& content, resolution_t resolution, double duration)
    : File{std::move(content)}
    , resolution{resolution}
    , duration{duration}
{}

// TODO provide file type
std::string_view Video::get_type() const
{
    return "VID";
}

size_t Video::get_raw_size() const
{
    // TODO size of raw 30 FPS RGB color video
    return 3 * resolution[0] * resolution[1] * int(duration * 30) / 8;
}

auto Video::get_resolution() const -> resolution_t
{
    return this->resolution;
}

double Video::get_duration() const
{
    return this->duration;
}

// TODO content update function
void Video::update(FileContent&& new_content, resolution_t size, double duration)
{
    content    = std::move(new_content);
    resolution = size;
    duration   = duration;
}