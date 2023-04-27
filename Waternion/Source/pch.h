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
#include<fstream>
#include<assert.h>
#include<iostream>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<map>
#include<stack>

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

#ifdef _DEBUG
    #define WATERNION_LOG(level, message,...)\
        fprintf(stderr, "[%s] ", level);\
        fprintf(stderr, message, ##__VA_ARGS__);\
        fprintf(stderr, "\n")

    #define WATERNION_LOG_INFO(message, ...) WATERNION_LOG("Info", message, ##__VA_ARGS__)
    #define WATERNION_LOG_ERROR(message, ...) WATERNION_LOG("Error", message, ##__VA_ARGS__)
    #define WATERNION_LOG_WARNING(message, ...) WATERNION_LOG("Warning", message, ##__VA_ARGS__)
#else
    #define WATERNION_INFO
    #define WATERNION_ERROR
    #define WATERNION_WARNING
#endif

// Dynamic runtime assert
#define WATERNION_ASSERT assert

// Static Assert
#if defined(__clang__) || defined(__gcc__)
    #define WATERNION_STATIC_ASSERT _Static_assert
#else
    #define WATERNION_STATIC_ASSERT static_assert
#endif

// Function inlining
#if defined(__clang__) || defined(__gcc__) 
    #define WATERNION_INLINE __attribute__((always_inline)) inline
    #define WATERNION_NOINLINE __attribute((noinline))
#elif defined(_MSC_VER)
    #define WATERNION_INLINE __forceinline
    #define WATERNION_NOINLINE __declspec(noinline)
#else
    #define WATERNION_INLINE inline
    #define WATERNION_NOINLINE
#endif

#define WATERNION_BIND(function) [this](auto&... args)->decltype(auto)\
    { return this->function(std::forward<decltype(args)>(args...);)}


#define WATERNION_FREE(memory) if (memory) { delete memory; memory = nullptr; }

#define GetDeltaTime() glfwGetTime()
#define GetDeltaTimeMS() glfwGetTime() * 1000

#define INVALID_ID 0
#define MAX_DELTA_TIME 0.04985f
#define MAX_DELTA_DIFF_MS 16
#define MAX_FPS 60

namespace Waternion {
    template<typename T> using Shared = std::shared_ptr<T>;
    template<typename T> using Unique = std::unique_ptr<T>;

    template<typename T, typename... Args>
    WATERNION_API WATERNION_INLINE Shared<T> MakeShared(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    
    template<typename T, typename... Args>
    WATERNION_API WATERNION_INLINE Unique<T> MakeUnique(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename To, typename From>
    WATERNION_API WATERNION_INLINE To DynamicCast(From source)
    {
        return dynamic_cast<To>(source);
    }

    template<typename To, typename From>
    WATERNION_API WATERNION_INLINE To StaticCast(From source)
    {
        return static_cast<To>(source);
    }

    template<typename To, typename From>
    WATERNION_API WATERNION_INLINE Shared<To> DyanmicPtrCast(Shared<From> source) {
        return std::dynamic_pointer_cast<To>(source);
    }

    template<typename To, typename From>
    WATERNION_API WATERNION_INLINE Shared<To> StaticPtrCast(Shared<From> source) {
        return std::static_pointer_cast<To>(source);
    }

    template<typename To, typename From>
    WATERNION_API WATERNION_INLINE To ReintepretCast(From source) {
        return reinterpret_cast<To>(source);
    }

    using UUID = size_t;
    WATERNION_API UUID GenerateUUID();

    template<typename T>
    WATERNION_INLINE UUID GetTypeID() {
        static UUID id = GenerateUUID();
        return id;
    }
}