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

    void teardown()
    {
    }

    // tests
    void tests()
    {
        DESCRIBE("check if the array can received more than 20 value");
        static uint64_t NUMBER_OF_ELEMENT = 21;
        int *data = new int[NUMBER_OF_ELEMENT];
        for (size_t i = 0; i < NUMBER_OF_ELEMENT; i++)
        {
            arr1 << i;
            data[i] = i;
        }

        IT("Should contain the element added and be of size 21")
        ASSERT(arr1.size(), NUMBER_OF_ELEMENT);
        ASSERT_ARRAY(data, arr1.data(), NUMBER_OF_ELEMENT);

        DESCRIBE("test all initialization");
        arr1 = {1, 2, 3, 4};
        int data1[] = {1, 2, 3, 4};
        IT("Should initialize with an initializer list");
        ASSERT_ARRAY(arr1.data(), data1, 4);

        arr1 = Array<int>(30);
        int data2[] = {};
        IT("Should initialize with a given size");
        ASSERT_ARRAY(arr1.data(), data2, 0);

        arr1 = Array<int>(4, 5);
        int data3[] = {4, 5, 5, 5};
        arr1[0] = 4; // this is to make sure that the value are different
        IT("Should initialize with a default value and have a different value in each spot")
        ASSERT_ARRAY(arr1.data(), data3, 4)

        arr2 = arr1;
        IT("Should initialize by copy")
        ASSERT_ARRAY(arr2.data(), data3, 4);

        DESCRIBE("Test the adding and the removing of item")

        IT("Should be able to add multiple value")
        arr1.push(1, 2, 3, 4);
        ASSERT_ARRAY(arr1.data(), data1, arr1.size());

        IT("Should return the last value when pop and remove an item")
        ASSERT(arr1.pop(), 4);
        ASSERT(arr1.size(), (uint64_t)3);

        IT("Should add the element at the end of the array and update the size")
        arr2 += arr1;
        ASSERT_ARRAY(arr2.data(), arr1.data(), arr1.size());
        ASSERT(arr1.size(), arr2.size());

        IT("should create an array containing all the elements of the two sub array")
        Array<int> arr3 = arr1 + arr2;
        int data4[] = {1, 2, 3, 1, 2, 3};
        ASSERT_ARRAY(arr3.data(), data4, arr3.size());

        DESCRIBE("test the manipulator")
        arr1 = {1, 2, 3, 4};

        IT("Should map the value and change their type")
        Array<float> b = arr1.map<float>([](int a) { return (float)(a * 2); });
        float data5[] = {2.f, 4.f, 6.f, 8.f};
        ASSERT_ARRAY(b.data(), data5, b.size());

        IT("Should convert the value to float")
        b = arr1.cast<float>();
        float data6[] = {1.f, 2.f, 3.f, 4.f};
        ASSERT_ARRAY(b.data(), data6, b.size());

        IT("Should select the even value")
        arr2 = arr1.select([](int b) { return b % 2 == 0; });
        int data7[] = {2, 4};
        ASSERT_ARRAY(arr2.data(), data7, arr2.size());

        IT("Should return the sum using inject of the array")
        ASSERT(arr1.sum(), 1 + 2 + 3 + 4)

        IT("Should return the biggest element of the array from an inject")
        ASSERT(arr1.inject(arr1[0], [](int result, int next) { return result > next ? result : next; }), 4)
    }

    // execution
    array_test()
    {
        run();
    }

    ~array_test()
    {
    }
};
