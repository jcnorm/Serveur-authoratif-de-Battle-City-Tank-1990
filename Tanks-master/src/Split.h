#ifndef SPLIT_H
#define SPLIT_H

#include <string>
#include <vector>

namespace Split{
    template <typename Out>
    void split(const std::string &s, char delim, Out result);

    std::vector<std::string> split(const std::string &s, char delim);
}

#endif