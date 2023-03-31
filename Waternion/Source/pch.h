#pragma once

// STL
#include<set>
#include<random>
#include<limits>
#include<vector>
#include<string>
#include<bitset>
#include<cassert>
#include<sstream>
#include<istream>
#include<assert.h>
#include<iostream>
#include<algorithm>
#include<functional>
#include<unordered_map>

// Externals
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<irrKlang/irrKlang.h>
#include<ft2build.h>
#include<freetype/freetype.h>

#ifdef WATERNION_EXPORT
    #ifdef _MSC_VER
        #define WATERNION_API __declspec(dllexport)
    #else
        #define WATERNION_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _MSC_VER
        #define WATERNION_API __declspec(dllimport)
    #else
        #define WATERNION_API
    #endif
#endif