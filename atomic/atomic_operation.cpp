//
// Created by APPLE on 2022/11/3.
//
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

// 设置一个全局变量为0
int global_variable = 0;

// 设置一个原子全局变量为0,
std::atomic<int> atomic_global_variable = 0;
// 上面写法可替代下面写法 std::atomic_uint32_t atomicUint32 = 0;

// 设置互斥锁.
typedef std::mutex lock;

// 并给线程执行设置同一把锁.
static lock mutex;

// 设置一个常量,大小为100000(用作循环)
constexpr static int LOOP_NUMBER = 100000;

// 设置一个宏,设置重新定义noexcept;
#define NOEXCEPT_ noexcept

// 设置一个宏,表示某些字段,函数,类,结构体...的未使用.
#define MAYBE_UNUSED  __attribute__((unused))

/**
 * 对全局变量进行操场,触发线程安全问题.
 */
void MAYBE_UNUSED myThread(){
    for (int i = 0; i < LOOP_NUMBER; ++i) {
        global_variable++;
    }
}

void MAYBE_UNUSED myThreadUsingAtomic(){
    for (int i = 0; i < LOOP_NUMBER; ++i) {
        atomic_global_variable++;
    }
}
/**
 * 对全局变量进行操场,触发线程安全问题.
 * <p>
 * 解决:设置互斥锁解决线程安全问题.
 */
void MAYBE_UNUSED myThreadUsingMutexLock(){
    for (int i = 0; i < LOOP_NUMBER; ++i) {
       // 加锁, lock add 指令就是计算机硬件底层提供的原子性支持
       mutex.lock();
       global_variable++;
       // 释放锁
       mutex.unlock();
    }
}

class AtomicOperation{
public:
    /**
     * 非原子操作,展现线程安全问题.
     *
     * @param functionPoint 传递一个函数指针
     */
    MAYBE_UNUSED static void noAtomicOperation(auto functionPoint) NOEXCEPT_;

    /**
     * 互斥锁解决线程安全问题.
     */
    MAYBE_UNUSED static void mutexLockOperation() NOEXCEPT_;

    /**
     * 通过原子操作解决线程安全问题.
     */
    MAYBE_UNUSED static void atomicOperation() NOEXCEPT_;
};

void __attribute__((unused)) AtomicOperation::noAtomicOperation(auto functionPoint) NOEXCEPT_{
    // 使用高分辨的时钟.
    auto begin = std::chrono::high_resolution_clock::now();
    // 传递函数指针.
    std::thread threadOne(functionPoint);
    std::thread threadTwo(functionPoint);
    // 线程执行.
    threadOne.join();
    threadTwo.join();
    auto end   = std::chrono::high_resolution_clock::now();
    std::cout << "输出全局变量--global_variable的值为: " << global_variable << std::endl;
    std::cout << "输出全局变量--atomic_global_variable的值为: " << atomic_global_variable << std::endl;
    // 对线程执行进行计时器.
    std::cout << "time: " << static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) * 1e-6 << "s" << std::endl;
}

void __attribute__((unused)) AtomicOperation::mutexLockOperation() NOEXCEPT_ {
    noAtomicOperation(myThreadUsingMutexLock);
}

void __attribute__((unused)) AtomicOperation::atomicOperation() NOEXCEPT_ {
    noAtomicOperation(myThreadUsingAtomic);
}

int main(){
    AtomicOperation::atomicOperation();
}