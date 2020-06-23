#include <iostream>
#include <string>
#include "IocContainer.hpp"


class Base
{
public:
	Base(const std::string& str, int n, int* p) : m_str(str) {}
	virtual ~Base(){}

	virtual void DoJob(const std::string& str) = 0;

protected:
	std::string m_str;
};

class Derived_0 : public Base
{
public:
	using Base::Base;

	virtual void DoJob(const std::string& str) override
	{
		std::cout << "Derived_0::DoJob called." << std::endl;
		std::cout << m_str << std::endl;
		std::cout << str << std::endl;
	}
};

class Derived_1 : public Base
{
public:
	using Base::Base;

	virtual void DoJob(const std::string& str) override
	{
		std::cout << "Derived_1::DoJob called." << std::endl;
		std::cout << m_str << std::endl;
		std::cout << str << std::endl;
	}
};


void InitIocContainer()
{
	//��ʼ����������
	IocContainerAgent::Instance();

	//ע��������ҵ�����͵�������ϵ ʹ��IOC��ô�������Ŀ���Ȩ
	//ʵ�ֿ��Ƶķ�ת
	IocContainerAgent::GetInstance()->RegisterType<Base, Derived_0, const std::string&, int, int*>("BS,0");
	IocContainerAgent::GetInstance()->RegisterType<Base, Derived_1, const std::string&, int, int*>("BS,1");
}

void BusinessProcess(int nProType, const std::string& strConstructParam, const std::string& strJobParam, int nParam)
{
	std::string strIocKey = std::string("BS,") + std::to_string(nProType);
	//���ݲ�ͬ��ҵ�����ʹ�����ͬ������������ҵ��ʵ�ִ���ĵط����������ֻ���������IOC������ʵ�ֿ��Ʒ�ת
	//����const std::string&�������͵Ĳ�����Ҫ��ʽָ��ģ����������ͣ�
	//������int��int*���ƵĲ���������ʽ��ָ��ģ����������ͣ������Զ��Ƶ�
	//��Ȼ��Ҳ������ʽ��ָ������������
	auto pBase = IocContainerAgent::GetInstance()->ResolveShared<Base, const std::string&>(strIocKey, strConstructParam, nParam, &nParam);
	if (pBase)
	{
		pBase->DoJob(strJobParam);
	}
	else
	{
		std::cout << "�޷�������ҵ������Base[" << strIocKey << "]" << std::endl;
	}
}


int main()
{
	//��ʼ�� IOC ����
	InitIocContainer();

	//����ҵ��
	BusinessProcess(0, "ConstructParam : for test constructor param.", "JobParam : for test base class IF param.", 0);
	BusinessProcess(1, "ConstructParam : for test constructor param.", "JobParam : for test base class IF param.", 0);
	BusinessProcess(2, "ConstructParam : for test constructor param.", "JobParam : for test base class IF param.", 0);


	return 0;
}