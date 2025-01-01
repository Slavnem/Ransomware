// Slavnem @2024-12-25
// Test Src
#include <Test/Test.hpp>

#include <iostream>

// Windows
#if defined(_WIN32) || defined(_WIN64)
    #define WINDOWS_IGNORE_PACKING_MISMATCH
    #include <Windows.h>
#endif

// Test
namespace Test
{
    // Windows
    #if defined(_WIN32) || defined(_WIN64)    
        #define COLOR_BLACK 0
        #define COLOR_RED 4
        #define COLOR_GREEN 2
        #define COLOR_YELLOW 6
        #define COLOR_BLUE 1
        #define COLOR_PURPLE 5
        #define COLOR_TURQUOISE 3
        #define COLOR_WHITE 7
        #define COLOR_RESET COLOR_WHITE
    
    // Linux
    #else
        #define COLOR_BLACK "\033[30m"
        #define COLOR_RED "\033[31m"
        #define COLOR_GREEN "\033[32m"
        #define COLOR_YELLOW "\033[33m"
        #define COLOR_BLUE "\033[34m"
        #define COLOR_PURPLE "\033[35m"
        #define COLOR_TURQUOISE "\033[36m"
        #define COLOR_WHITE "\033[37m"
        #define COLOR_RESET "\033[0m"
    #endif

    // SETCOLOR
    static void SETCOLOR(const ecolor_t _color)
    {
        // Windows
        #if defined(_WIN32) || defined(_WIN64)
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            FlushConsoleInputBuffer(hConsole);

            switch (_color)
            {
                case ECOLOR_BLACK:
                    SetConsoleTextAttribute(hConsole, COLOR_BLACK);
                    break;
                case ECOLOR_RED:
                    SetConsoleTextAttribute(hConsole, COLOR_RED);
                    break;
                case ECOLOR_GREEN:
                    SetConsoleTextAttribute(hConsole, COLOR_GREEN);
                    break;
                case ECOLOR_YELLOW:
                    SetConsoleTextAttribute(hConsole, COLOR_YELLOW);
                    break;
                case ECOLOR_BLUE:
                    SetConsoleTextAttribute(hConsole, COLOR_BLUE);
                    break;
                case ECOLOR_PURPLE:
                    SetConsoleTextAttribute(hConsole, COLOR_PURPLE);
                    break;
                case ECOLOR_TURQUOISE:
                    SetConsoleTextAttribute(hConsole, COLOR_TURQUOISE);
                    break;
                case ECOLOR_WHITE:
                default:
                    SetConsoleTextAttribute(hConsole, COLOR_WHITE);
                    break;
            }

        // Linux
        #else
            switch (_color)
            {
                case ECOLOR_BLACK:
                    std::cout << COLOR_BLACK;
                    break;
                case ECOLOR_RED:
                    std::cout << RED;
                    break;
                case ECOLOR_GREEN:
                    std::cout << COLOR_GREEN;
                    break;
                case ECOLOR_YELLOW:
                    std::cout << COLOR_YELLOW;
                    break;
                case ECOLOR_BLUE:
                    std::cout << COLOR_BLUE;
                    break;
                case ECOLOR_PURPLE:
                    std::cout << COLOR_PURPLE;
                    break;
                case ECOLOR_TURQUOISE:
                    std::cout << COLOR_TURQUOISE;
                    break;
                case ECOLOR_WHITE:
                default:
                    std::cout << COLOR_WHITE;
                    break;
            }
        #endif
    }

    // RESETCOLOR
    static void RESETCOLOR()
    {
        // Windows
        #if defined(_WIN32) || defined(_WIN64)
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, COLOR_RESET);

        // Linux
        #else
            std::cout << COLOR_RESET;
        #endif
    }

    // EXPECT_EQ
    bool EXPECT_EQ(const char* const _msg, const double _value, const double _expected)
    {
        const bool result = (_value == _expected);

        SETCOLOR(result ? ECOLOR_GREEN : ECOLOR_RED);
        std::cout << (result ? RESULT_OUT_PASS : RESULT_OUT_FAIL)
            << ' ' << _msg;

        RESETCOLOR();
        std::cout << std::endl;

        return result;
    }

    // ASSERT_EQ
    void ASSERT_EQ(const char* const _msg, const double _value, const double _expected)
    {
        if (!EXPECT_EQ(_msg, _value, _expected))
            exit(EXIT_FAILURE);
    }
}