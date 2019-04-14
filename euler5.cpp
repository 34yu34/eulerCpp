#include <functional>
#include <iostream>
#include "enumerable.h"
#include "enumerable_generator.h"
#include "number.h"


using namespace Number;

typedef Enumerable<Factor<int> *> FactEnum  ;


int main(int argc, char const *argv[])
{
    Enumerable<FactEnum> en = Enumerable_Generator::get().range(1,21,1)
                               .map<FactEnum>([](const int & a) {return Number::getFactors(a);});

    FactEnum totalFactors = FactEnum();
    en.each([&totalFactors](FactEnum individualFactors){
        individualFactors.each([&totalFactors](Factor<int> * nbFact){
            bool wasThere = false;
            totalFactors.each([&nbFact, &wasThere](Factor<int> * fact){
                if (fact->factor == nbFact->factor)
                {
                    fact->repetition = fact->repetition > nbFact->repetition ? fact->repetition : nbFact->repetition;
                    wasThere = true;
                }
            });
            if (!wasThere)
            {
                totalFactors << nbFact;
            }        
        });
    });
    int sum = 1;
    std::cout << totalFactors.inject(sum, [](int & sum, Factor<int> * fact){
        sum *= pow(fact->factor, fact->repetition);
        return sum;
    }); 
    
    return 0;
}
