#include "array.h"
#include "test.h"

class array_test : test
{
private:
    Array<int> arr1;
    Array<int> arr2;

public:

    // Abstract method implementation

    void setup()
    {
        arr1 = Array<int>();
        arr2 = Array<int>();
    }

    void teardown() {}

    // tests 

    void tests()
    {
        section("check if the array can received more than 20 value");
        static uint64_t NUMBER_OF_ELEMENT = 21;
        int * data = new int[NUMBER_OF_ELEMENT];
        for (size_t i = 0; i < NUMBER_OF_ELEMENT; i++)
        {
            arr1 << i;
            data[i] = i;
        }
        ASSERT(arr1.size(), NUMBER_OF_ELEMENT);
        assert(data, arr1.data(), NUMBER_OF_ELEMENT);


        section("test all initialization");
        arr1 = {1, 2, 3, 4};
        int data1[] = {1, 2, 3, 4};
        assert(arr1.data(), data1, 4);

        arr1 = Array<int>(30);
        int data2[] = {};
        assert(arr1.data(), data2, 0);

        arr1 = Array<int>(4, 5);
        int data3[] = {5,5,5,5,5};
        assert(arr1.data(), data3, 0);

        arr2 = arr1;
        assert(arr2.data(), data3, 0);

        section("Test the adding and the removing of item");
        arr1.push(1,2,3,4);
        assert(arr1.data(), data1, arr1.size());
        assert(arr1.pop(), 4);
        assert(arr1.size(), (uint64_t)3);
        arr2 += arr1;
        assert(arr2.data(), arr1.data(), arr1.size());
        assert(arr1.size(), arr2.size());
        Array<int> arr3 = arr1 + arr2;
        int data4[] = {1,2,3,1,2,3};
        assert(arr3.data(), data4, arr3.size());

    }

    // execution

    array_test()
    {
        run();
    }

    ~array_test()
    {}
};
