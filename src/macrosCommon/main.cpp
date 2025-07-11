#include <iostream>

#define _GET_MACRO(_1, _2, NAME, ...) NAME                                             // 选择器，仅通过参数数量来选择特定的宏
#define FOO(...)                      _GET_MACRO(__VA_ARGS__, FOO2, FOO1)(__VA_ARGS__) // (__VA_ARGS__) 的作用是把原始参数传递给被选中的宏，实现参数的“转发”
#define FOO1(a)                       std::cout << "one: " << a << std::endl
#define FOO2(a, b)                    std::cout << "two: " << a << ", " << b << std::endl

#define GL_NO_ERROR                   0
#define GL_INVALID_ENUM               1
#define GL_INVALID_VALUE              2
#define GL_INVALID_OPERATION          3
#define GL_STACK_OVERFLOW             4
#define GL_STACK_UNDERFLOW            5
#define GL_OUT_OF_MEMORY              6

// # 是字符串化操作符，用于把宏参数转换为字符串字面量
// ## 被称为连接符（token pasting operator），用于把宏参数和其他标记拼接成一个新的标记（token）

#define STR(x)                        #x
#define CONCAT(x, y)                  x##y // 连接两个标记
#define mama                          GL_NO_ERROR

// #define PER_GL_ERROR(x) \
//     case x:             \
//         return #x;

// #define PER_GL_ERROR(x) \
//     case STR(x):        \
//         return #x;

// #define PER_GL_ERROR(x) \
//     case GL_##x:        \
//         return #x;

#define PER_GL_ERROR(x)  \
    case CONCAT(GL_, x): \
        return #x;

void check_gl_error(const char *file, int line, int err = 0)
{
    if (err == GL_NO_ERROR) {
        std::cerr << file << " at line " << line << ": " << err << std::endl;
    }
}

#define MIN(x, y) ({       \
    auto __x = (x);        \
    auto __y = (y);        \
    __x < __y ? __x : __y; \
})

// in fact, the x may be function call or expression
#define CHECK_GL(x)                            \
    do {                                       \
        x;                                     \
        check_gl_error(__FILE__, __LINE__, x); \
    } while (0)

std::string opengl_errno_name(int err)
{
    switch (err) {
        PER_GL_ERROR(NO_ERROR)
        PER_GL_ERROR(INVALID_ENUM)
        PER_GL_ERROR(INVALID_VALUE)
        PER_GL_ERROR(INVALID_OPERATION)
        PER_GL_ERROR(STACK_OVERFLOW)
        PER_GL_ERROR(STACK_UNDERFLOW)
        PER_GL_ERROR(OUT_OF_MEMORY)
    }
    return "unknown error: " + std::to_string(err);
}

int main()
{
    FOO(1);    // _GET_MACRO(1, FOO2, FOO1)(1)
    FOO(1, 2); // _GET_MACRO(1, 2, FOO2, FOO1)(1, 2)

    auto res = opengl_errno_name(0);
    std::cout << "OpenGL Error: " << res << std::endl;

    check_gl_error(__FILE__, __LINE__, 0);

    if (1)
        CHECK_GL(0);

    int i = 2;
    std::cout << "Min of i and 4: " << MIN(i << 2, 4) << std::endl;

    std::cout << "Macros Common Project" << std::endl;
    return 0;
}