// async_future_get.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//�����std::launch::async�Ļ���ô��ǿ�ƿ����µ��̣߳������Ļ��͵óе���Դ���ŵ�����£���������ķ���
	//�������deferred֮�󣬲��Ὺ���µ��̣߳�ֻ�е�future�������get������ʱ��������ĺ����Ż�ִ��
	std::future<bool> fut = std::async(std::launch::deferred,is_prime,17);
#if 0
	//���ﲻ������Ļ���Ĭ����launch::async|launch::deferred ,���ֲ�����ϵͳ�������Դ�������Ƿ񿪱��߳�ȥִ�к������������̳߳أ��Դ��Ż�
	std::future<bool> fut = std::async(is_prime, 17);
#endif
	//bool ret = fut.get();//ֱ�����زŻ������ߣ�Ҳ����˵������������
	std::cout << "main thread id:" << std::this_thread::get_id()<<std::endl;
	bool ret = fut.get();//ֱ�����زŻ������ߣ�Ҳ����˵������������
	std::cin.get();
    return 0;
}

