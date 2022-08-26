// async_future_get.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <future>
#include <chrono>

bool is_prime(int x)
{
	std::cout << "Calcuating.Please wait...." << std::endl;
	std::cout<<"is_prime thread id:"<<std::this_thread::get_id();
	std::this_thread::sleep_for(std::chrono::seconds(5));
	for (int i = 2; i < x;++i)
	{
		if (x%i==0)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	//如果是std::launch::async的话那么会强制开辟新的线程，这样的话就得承担资源紧张的情况下，程序崩溃的风险
	//这里加了deferred之后，不会开辟新的线程，只有当future对象调用get函数的时候，这里面的函数才会执行
	std::future<bool> fut = std::async(std::launch::deferred,is_prime,17);
#if 0
	//这里不填参数的话，默认是launch::async|launch::deferred ,这种参数，系统会根据资源来决定是否开辟线程去执行函数，类似于线程池，自带优化
	std::future<bool> fut = std::async(is_prime, 17);
#endif
	//bool ret = fut.get();//直到返回才会往下走，也就是说会阻塞在这里
	std::cout << "main thread id:" << std::this_thread::get_id()<<std::endl;
	bool ret = fut.get();//直到返回才会往下走，也就是说会阻塞在这里
	std::cin.get();
    return 0;
}

