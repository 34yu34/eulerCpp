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
        std::string number = "-123456789101112131415161718192021222324252627282930";
        num1 = number;
        ASSERT(num1.to_s(), number);

        IT("Should instanciate with ints");
        int z = -298374932;
        num1 = z;
        ASSERT(num1.to_s(), std::to_string(z))
        
        IT("Should instantiate with num")
        num2 = num1;
        ASSERT(num1.to_s(), num2.to_s())

        DESCRIBE("Addition");
        std::string result = "3999999999999999999999999998";
        num1 = "1999999999999999999999999999";
        num2 = "1999999999999999999999999999";
        num1 += num2;
        ASSERT(num1.to_s(), result);

        num num3 = num1 + num2;
        assert(num3.to_s(), result);
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
