#ifndef MY_STD_THREAD_H_
#define MY_STD_THREAD_H_


#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <future>
#include <sys/time.h>
#include <unistd.h>

/**
 * 异步调用
 * @tparam F 模板
 * @tparam Args 模板
 * @param f
 * @param args 可变参数
 * @return
 */
template <typename F, typename... Args>
auto RealAsync(F&& f, Args&&... args)-> std::future<typename std::result_of<F(Args...)>::type>
{
    using _Ret = typename std::result_of<F(Args...)>::type;
    auto _func = std::bind(std::forward<F>(f),std::forward<Args>(args)...);
    std::packaged_task<_Ret()> tsk(std::move(_func));
    auto _fut = tsk.get_future();
    std::thread thd(std::move(tsk));
    thd.detach();
    return _fut;
}
//void RealAsyncDemo()
//{
//    int file_name_=0;
//    std::string client="";
//    RealAsync([/* this,*/ file_name_, client](){
//        file_name_ = 1;
//    });
//}


class MyStdThread
{
public:
    /** 定义线程锁 */
    typedef void*  Mutex;
    /**
     * 创建一把线程锁
     * @param[out] m 线程锁
     */
    void CreateMutex(Mutex& m)
    {
        if(m == NULL)
        {
            std::mutex* temp = new std::mutex();
            m = (Mutex)temp;
        }

    }
    /**
     * 锁住资源
     * @param[in] m 线程锁
     */
    void Lock(Mutex m)
    {
        if(m!= NULL)
            ((std::mutex*)m)->lock();
        else
        {
            std::cerr<<"error,the mutex is NULL!"<<std::endl;
        }
    }
    /**
     * 释放资源
     * @param m 线程锁
     */
    void UnLock(Mutex m)
    {
        if(m!= NULL)
            ((std::mutex*)m)->unlock();
        else
            std::cerr<<"error,the mutex is NULL!"<<std::endl;
    }
    /**
     * 销毁一把线程锁
     * @param m 线程锁
     */
    void DestoryMutex(Mutex m)
    {
        if(m != NULL)
            delete ((std::mutex*)m);
    }
    /** 定义线程句柄 */
    typedef void* Thread; //定义多线程指针

    /**
     * 创建一个线程，并线程分离
     * @tparam T
     * @param[out] thread 线程句柄
     * @param[in] func_thread 线程回调函数
     * @param[in] self 函数指针，一般在类中调用写this
     * @param[in] arg 线程启动的函数指针所需要的输入参数
     */
    template <typename T>
    void CreateThread(Thread& thread, void (T::*func_thread)(void* arg),T* self,void* arg){
        if(thread == NULL)
        {
            std::thread* temp = new std::thread(func_thread, self, arg);
            thread = (Thread)temp;
            ((std::thread*)thread)->detach();///< 线程分离，线程退出后系统自动回收资源
        }
    }
    /**
     * 销毁一个线程
     * @param[in] thread
     */
    void DestoryThread(Thread thread){

        if(thread != NULL){
        	//((std::thread*)thread)->join();
            delete (std::thread*)thread;
        }
    }


    /**
     * 创建一个线程，并线程分离
     * @tparam T
     * @param[in] func_thread 线程回调函数
     * @param[in] self 函数指针，一般在类中调用写this
     * @param[in] arg 线程启动的函数指针所需要的输入参数
     */
    template <typename T>
    void CreateThreadNew( void (T::*func_thread)(void* arg),T* self,void* arg){
        SetThreadExitFlag(0);
        std::thread* temp = new std::thread(func_thread, self, arg);
        cur_thread_id_ = (Thread)temp;
        ((std::thread*)cur_thread_id_)->detach();///< 线程分离，线程退出后系统自动回收资源

    }
    /**
     * 销毁一个线程
     * @param[in] thread
     * @param[in] timeout 超时时间，单位ms
     */
    void DestoryThreadNew(int timeout=3000){
        if(cur_thread_id_ != NULL){

            SetThreadExitFlag(1);
            long long last_time = GetCurTimeMs();
            long long cur_time=0;
            while(1){
                cur_time = GetCurTimeMs();
                if(cur_time-last_time>timeout || last_time>cur_time){
                    break;
                }
                if(GetThreadExitFlag()>=2){
                    break;
                }
                usleep(500);
            }
            usleep(500);

            //((std::thread*)thread)->join();
            delete (std::thread*)cur_thread_id_;
            cur_thread_id_ = NULL;
        }
    }
    /**
     * 线程是否要退出
     * @return true：是，false：否
     */
    bool ThreadIsDestory() {
        bool ret = false;

        if(GetThreadExitFlag()!=0){
            ret = true;
        }

        return ret;
    }
    /**
     * 线程return前调用
     */
    void ThreadDestoryFinish(){
        SetThreadExitFlag(2);
    }
    /**
     * 线程是否完全退出
     * @return true：是，false：否
     */
    bool ThreadIsDestoryFinish() {
        bool ret = false;

        if(GetThreadExitFlag()==2){
            ret = true;
        }

        return ret;
    }
private:
    int thread_exit_flag=2;/// 线程退出标志,0：线程正在使用，1：线程要退出，2线程退出完毕
    std::mutex thread_exit_flag_mutex;
    Thread cur_thread_id_=NULL;
private:
    /**
     * 设置线程退出标志
     * @param[in] flag
     */
    void SetThreadExitFlag(int flag){
        thread_exit_flag_mutex.lock();
        thread_exit_flag = flag;
        thread_exit_flag_mutex.unlock();
    }
    /**
     * 获取线程退出标志
     * @return
     */
    int GetThreadExitFlag(){
        int ret=-1;
        thread_exit_flag_mutex.lock();
        ret = thread_exit_flag ;
        thread_exit_flag_mutex.unlock();

        return ret;
    }
    /**
     * 获取当前ms值
     * @return
     */
    long long GetCurTimeMs(void) {
        struct timeval tv;
        long long ms=0;

        gettimeofday(&tv,NULL);
        ms=tv.tv_sec;
        return (ms*1000+tv.tv_usec/1000);
    }
};


#endif /* MY_STD_THREAD_H_ */
