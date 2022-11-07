cmake_minimum_required(VERSION 3.20)
project(MasterLearning)

# 设置cpp运行版本
set(CMAKE_CXX_STANDARD 20)


# 发现Boost包
set(BOOST_ROOT "/usr/local/include/boost")

#添加头文件搜索路径
include_directories(/usr/local/include/boost)
#添加库文件搜索路径
link_directories(/usr/local/lib)

add_executable(MasterLearning common_package/macro_define/macro_.h atomic/cas/no_lock_queue.cpp)
