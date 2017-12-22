#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "soapStub.h"
#include "ns.nsmap"

int add(const char *server,double a,double b,double *result)
{
	struct soap add_soap;
	int res = 0;

	soap_init(&add_soap);   //初始化环境变量

	soap_set_namespaces(&add_soap,namespaces);

	soap_call_ns__add(&add_soap,server,NULL,a,b,result);   //调用ns2__add远程方法

	if (add_soap.error)
	{
		printf("soap error: %d, %s, %s\n",add_soap.error, *soap_faultcode(&add_soap), *soap_faultstring(&add_soap));

		res= add_soap.error;
	}

	soap_end(&add_soap);  //清除环境变量

	soap_done(&add_soap);

	return res;
}

int main(int argc,char *argv[])
{
	int result = -1;
	char server[128] = {0};
	double num1 = 0, num2 = 0, sum = 0;	

	gets(server);
	scanf("%lf %lf", &num1, &num2);

	result= add(server,num1,num2,&sum);

	if (result != 0)
	{
		printf("soap error, errcode=%d\n",result);
	} 
	else
	{
		printf("%f+ %f = %f\n", num1, num2, sum);
	}
	return 0;
}