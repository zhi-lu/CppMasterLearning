//
// Created by APPLE on 2022/11/3.
//
#include <version.hpp>
#include <cassert>

#include "../common_package/macro_define/macro_.h"

MAYBE_UNUSED void judgeBoost(RESULT_JUDGE result, MESSAGE_VECTOR &messageVector){
    // 如果assert(false)则终止程序执行,assert(true)反之亦然.
    assert(!result);
    std::copy(messageVector.begin(), messageVector.end(),
              std::ostream_iterator<std::basic_string<char>>{ERR, " "});
}

int main(){
    COUT << "当前BOOST版本" << BOOST_VERSION << END;
    MESSAGE_VECTOR messageVector = {"error,", "boost don't 1.75 version"};
    std::basic_string<char> version = std::to_string(BOOST_VERSION);
    judgeBoost(version.starts_with("1075"), messageVector);
    return 0;
}