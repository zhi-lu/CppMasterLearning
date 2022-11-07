//
// Created by APPLE on 2022/11/3.
//

#ifndef MASTERLEARNING_MACRO__H
#define MASTERLEARNING_MACRO__H

#include <iostream>
#include <vector>

#define COUT std::cout
#define CLOG std::clog
#define END  std::endl
#define ERR  std::cerr

#define MAYBE_UNUSED __attribute__((unused))
#define RESULT_JUDGE bool

using MESSAGE_VECTOR = std::vector<std::basic_string<char>>;

/**
 * 检查相当于断言,如果传入为false则输出失败结果.传入为true则反之亦然.
 *
 * @param result 传入的结果
 * @param messageVector 信息向量,存放失败结果.
 */
MAYBE_UNUSED void check(RESULT_JUDGE result, const MESSAGE_VECTOR &messageVector){
    if (!result){
        std::copy(messageVector.begin(), messageVector.end(),
                  std::ostream_iterator<std::basic_string<char>>(ERR, " "));
    }
}

#endif //MASTERLEARNING_MACRO__H
