#include "test.h"
#include "num.h"

#include "dev.h"

class num_test : test
{
private:
    num num1;
    num num2;

public:
    // Abstract method implementation

    void setup()
    {
    }

    void teardown()
    {
    }

    // tests
    void tests()
    {
        DESCRIBE("verify instanciation");

        IT("Should instanciate with string");
        std::string number = "123456789101112131415161718192021222324252627282930";
        num1 = number;
        ASSERT(num1.to_s(), number);


        DESCRIBE("Addition");
        std::string result = "20000000000000000000000000";
        num1 = "10000000000000000000000000";
        num2 = "10000000000000000000000000";
        num1 += num2;
        ASSERT(num1.to_s(), result);
    }

       // execution
    num_test()
    {
        run();
    }

    ~num_test()
    {
    }
};
