/***********************************************
 * Project Name     : Tester
 * Author           : Slavnem
 * Date             : 25/12/2024
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : A class that allows you to test whether
                      the code matches the desired results
                      or just to test the code
 ***********************************************/
#ifndef TEST_INC_H
#define TEST_INC_H

// Test
namespace Test
{
    // Text
    static inline constexpr const char* const RESULT_OUT_PASS = "[ PASSED ]";
    static inline constexpr const char* const RESULT_OUT_FAIL = "[ FAILED ]";

    // Colors
    typedef enum ecolor_s
    {
        ECOLOR_BLACK = 0,
        ECOLOR_RED,
        ECOLOR_GREEN,
        ECOLOR_YELLOW,
        ECOLOR_BLUE,
        ECOLOR_PURPLE,
        ECOLOR_TURQUOISE,
        ECOLOR_WHITE
    } ecolor_t;

    // EXPECT_EQ
    bool EXPECT_EQ(const char* const _msg, const double _value, const double _expected);

    // ASSERT_EQ
    void ASSERT_EQ(const char* const _msg, const double _value, const double _expected);
}

#endif // TEST_INC_H