#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/stack_trace.h>

#include <stdio.h>

static void func1();
static void func2();
static void func3();
static void func4();
static void func5();

void test_main()
{
    func1();
}

void func1()
{
    func2();
}

void func2()
{
    func3();
}

void func3()
{
    func4();
}

void func4()
{
    func5();
}

void func5()
{
    char buffer[1000];
    kernaux_stack_trace_snprint(buffer, sizeof(buffer));
    printf("Stack trace:\n%s", buffer);
}
