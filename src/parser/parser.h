#ifndef RENDERER_PARSER_H
#define RENDERER_PARSER_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <raylib.h>

#include "../scene/objects/objects.h"

Mesh3* ParseOBJFile(const char* filename);

#endif // RENDERER_PARSER_H