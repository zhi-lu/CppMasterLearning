//
// Created by APPLE on 2022/11/4.
// CAS(Compare And Swap)无锁队列操作
//
#include <atomic>

#include "../../common_package/macro_define/macro_.h"

template<typename E>
MAYBE_UNUSED RESULT_JUDGE compare_and_swap(E *offset, E expected, E update){
    if ((*offset = expected)){
        *offset = update;
        return true;
    }
    return false;
}

template <typename T>
class MAYBE_UNUSED atomic_{
public:

    };

int main(){
    int *value = new int(1);
    int expected = 1;
    int update = 2;
    MESSAGE_VECTOR messageVector = {"CAS operate fail,", " the value has not changed"};
    check(compare_and_swap(value, expected, update), messageVector);
    COUT << "value 值为:" << *value << END;
}

