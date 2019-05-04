#include <functional>
#include <iostream>
#include "enumerable.h"
#include "enumerable_generator.h"
#include "number.h"


using namespace Number;

typedef Enumerable<Factor<int> *> Fact_Enum  ;


int main(int argc, char const *argv[])
{
    Enumerable<Fact_Enum> en = Enumerable_Generator::get().range(1,21,1)
                               .map<Fact_Enum>([](const int & a) {return Number::get_factors(a);});

    Fact_Enum total_factors = Fact_Enum();
    en.each([&total_factors](Fact_Enum individualFactors){
        individualFactors.each([&total_factors](Factor<int> * possible_factor){
            bool was_there = false;
            total_factors.each([&possible_factor, &was_there](Factor<int> * answer_fact){
                if (answer_fact->factor == possible_factor->factor)
                {
                    answer_fact->repetition = answer_fact->repetition > possible_factor->repetition ? answer_fact->repetition : possible_factor->repetition;
                    was_there = true;
                }
            });
            if (!was_there)
            {
                total_factors << possible_factor;
            }        
        });
    });
    int sum = 1;
    std::cout << total_factors.inject(sum, [](int & sum, Factor<int> * fact){
        sum *= pow(fact->factor, fact->repetition);
        return sum;
    }); 
    
    return 0;
}
