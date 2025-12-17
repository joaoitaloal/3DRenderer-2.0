#ifndef RENDERER_PARSER_H
#define RENDERER_PARSER_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <raylib.h>

#include "../scene/objects/objects.h"

using namespace std;

Mesh3* ParseOBJFile(string filename);

#endif // RENDERER_PARSER_H