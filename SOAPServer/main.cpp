#include "soapH.h" //获取自动生成的函数声明
#include "ns.nsmap"     //获取XML服务命名空间绑定

int main(int argc,char *argv[])
{
	int m,s;
	struct soap add_soap;

	soap_init(&add_soap);

	soap_set_namespaces(&add_soap,namespaces);
	
	m= soap_bind(&add_soap,NULL,123, 100);  //确定服务开放端口，NULL可改成本地ip，atoi(argv[1])是端口

	if(m < 0) 
	{
		soap_print_fault(&add_soap,stderr);
		exit(-1);
	}
	printf("Socketconnection successful: master socket = %d\n",m);

	while(1) 
	{
		s = soap_accept(&add_soap);

		if (s < 0) 
		{
			soap_print_fault(&add_soap,stderr);
			exit(-1);
		}
		printf("Socket connection successful: slave socket =%d\n",s);

		soap_serve(&add_soap);         //将该服务部署到web上以便调用

		soap_end(&add_soap);
	}

	return 0;
}

int ns__add(struct soap *add_soap,double a,double b,double *result)     //头文件中函数的具体实现
{
	*result= a + b;
	return 0;
}