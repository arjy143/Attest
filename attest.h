#ifndef ATTEST_H
#define ATEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
    extern "C" {
#endif

/*  Attest - a minimal unit testing framework for C and C++
*/

typedef void (*attest_func_t)(void);

//representation of a testcase
typedef struct attest_testcase
{
    const char* name;
    attest_func_t func;
    struct attest_testcase *next;
} attest_testcase_t;

extern attest_testcase_t *attest_head;

//macro for registering tests
#define REGISTER_TEST(name) \
        static void name(void); \
        static attest_testcase_t name##_case = {#name, name, NULL}; \
        __attribute((constructor)) static void register_##name(void) \
        { \
            name##_case.next = attest_head; \
            attest_head = &name##_case; \
        } \
        static void name(void)

//basic assertion macros

#define ASSERT_TRUE(condition) do \
        { \
            if (!(condition)) \
            { \
                fprintf(stderr, "[FAIL] %s:%d: ASSERT_TRUE(%s)\n", __FILE__, __LINE__, #condition); \
                exit(1); \
            } \
        } while (0)

#define ASSERT_EQ(a, b) do \
        { \
            if (!((a) == (b))) \
            { \
                fprintf(stderr, "[FAIL] %s:%d: ASSERT_EQ(%s, %s) - found %lld vs %lld\n", __FILE__, __LINE__, #a, #b, (long long)(a), (long long)(b)); \
                exit(1); \
            } \
        } while (0)

#define ASSERT_STR_EQ(a, b) do \
        { \
            if (strcmp((a), (b)) != 0) \
            { \
                fprintf(stderr, "[FAIL] %s:%d: ASSERT_STR_EQ(%s, %s)\n", __FILE__, __LINE__, #a, #b); \
                exit(1); \
            } \
        } while (0)

#ifdef __cplusplus
    }
#endif

#endif //ATTEST_H