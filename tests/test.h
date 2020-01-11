#pragma once
#include <iostream>
#include <stdint.h>
#include <string.h>

#define ASSERT(a, b) \
assert(a, b);

#define ASSERT_FAIL(a) \
assert_fail(a);

#define ASSERT_ARRAY(a, b, size) \
assert(a, b, size);

#define DESCRIBE(a) \
section(a);

#define IT(a) \
comment(a);

class test
{
private:
    int count_;
    int errors_;
    int test_count_;
    bool is_first_;

protected:
    virtual void setup() = 0;
    virtual void teardown() = 0;
    virtual void tests() = 0;

    void section(std::string desc = "");
    void comment(std::string desc);

    template <class T> void assert(const T & e1,const T & e2);
    template <class T> void assert(const T e1[],const T e2[], uint64_t size);
    template <class Function> void assert_fail(Function f);
    void end();
    void run();

public:
    test();

private:  
    void case_text();
    void success();
    void fail();

    template <class T> void print_array(uint64_t size, T e1[]);
public:


};

test::test()
: count_(1), errors_(0), test_count_(1), is_first_(true) {}


void test::section(std::string desc /*= ""*/)
{
    if (!is_first_)
    {
        teardown();
        is_first_ = false;
    }
    setup();
    std::cout << "\n----------TESTS " << test_count_++ << "----------" << std::endl;
    std::cout << desc << std::endl;
}

void test::comment(std::string desc)
{
    std::cout << std::endl << desc << std::endl;
}

void test::run()
{
    tests();
    end();
}

void test::end()
{
    teardown();
    std::cout << "\n---------- END ----------\n";
    if (errors_)
    {
        std::cout << "There was a total of " << errors_ << " error(s) on " << count_ << " cases"<< std::endl;
    }
    else
    {
        std::cout << "All cases were successful!\n" << std::endl;
    }
}

void test::case_text()
{
    std::cout << "case " << count_++ << " ";
}

void test::success()
{
    case_text();
    std::cout << " was successful : ";
}

void test::fail()
{
    case_text();
    errors_++;
    std::cout << " failed : ";
}

template<class T>
void test::assert(const T & e1, const T & e2)
{
    try
    {
        if (e1 != e2)
        {
            fail();
            std::cout <<  "expected " << e1 << " to be " << e2 << std::endl;
        }
        else
        {
            success();
            std::cout << "asserted " << e1 << ", " << e2 << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        fail();
        std::cout << e.what() << std::endl;
    }
}

template <class T>
void test::assert(const T e1[], const T e2[], uint64_t size)
{
    try
    {
        // these values are just used to test if it is accessible
        // we dont want the warning there
        if (e1[size-1] == e2[size-1]) {};
    }
    catch(const std::exception& e)
    {
        fail();
        std::cout << "Arrays are not of size " << size << std::endl;
    }

    try
    {
        bool are_equal = true;
        for (uint64_t i = 0; i < size; i++)
        {
            if(e1[i] != e2[i])
            {
                are_equal = false;
                fail();
                std::cout << std::endl;
                print_array(size, e1);
                print_array(size, e2);
                break;
            }
        }
        if (are_equal)
        {
            success();
            std::cout << "Arrays match." << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        fail();
        std::cout << e.what() << '\n';
    }
}

template <class Function>
void test::assert_fail(Function f)
{
    try
    {
        f();
        fail();
        std::cout << "test didn't throw errors" << std::endl;
    }
    catch(const std::exception& e)
    {
        success();
        std::cout << "an execption was thrown" << '\n';
    }
    
}

template <class T>
void test::print_array(uint64_t size, T e1[])
{
    std::cout << "    {";
    for (uint64_t i = 0; i < size-1; i++)
    {
        std:: cout << e1[i] << ", " ;
    }
    std::cout << e1[size-1] << "}\n";
}
