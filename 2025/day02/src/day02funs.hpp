#include <iostream>
#include <string>

bool is_invalid_id(long x) {
    std::string id{std::to_string(x)};
    int id_size = id.size();
    for (int i{0}; i < id_size / 2; i++) {
        if (id_size % (i+1) != 0 ) continue;
        std::string substring {id.substr(0, i+1)};
        std::string compare{""};
        while (compare.size() < id_size) {
            compare += substring;
        }
        if (compare == id) {
            return true;
        }
    }
    return false;
}
