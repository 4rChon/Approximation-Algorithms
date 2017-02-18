#ifndef __UTIL_H__
#define __UTIL_H__

#include <city.h>
#include <string> // std::string

int load_tsp(std::string fileName);
float subStringToFloat(std::string line, int pos, int length);
City parse_line(std::string line);

#endif
