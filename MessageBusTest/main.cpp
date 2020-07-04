﻿#include <iostream>
#include <string>
#include "MessageBus.hpp"

MessageBus msgBus;

//
int GlobalFunc_int_int(int a)
{
	std::cout << __FUNCTION__ << " called." << std::endl;

	return a;
}
void RegisterGlobalFunc()
{
	std::cout << "向消息总线注册全局函数，GlobalFunc_int_int" << std::endl;
	msgBus.Attach(&GlobalFunc_int_int, "GlobalFunc_int_int");
}



int main()
{
	RegisterGlobalFunc();

	msgBus.SendReq<int, int>(1, "GlobalFunc_int_int");



	return 0;
}