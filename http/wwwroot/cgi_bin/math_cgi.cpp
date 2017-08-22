#include <stdlib.h>
#include <strings.h>
#include<iostream>
using namespace std;

#define SIZE 1024


static void print_style()
{
	cout<<"<style type=\"text/css\">\n"<<endl;
	cout<<"body{\n"<<endl;
	cout<<" background-color:#eeffff;\n"<<endl;
	cout<<"}\n";
	cout<<"#godTable{\n";
	cout<<"border:solid;\n";
	cout<<"border-color:5b5c5e;\n";
	cout<<"border-width:1px;\n";
	cout<<"margin-left:120px;\n";
	cout<<"background-color: #eeffff;\n";
	cout<<"font-family:楷体_GB2312;\n";
	cout<<"}\n";
	cout<<".tabRow{\n";
	cout<<"border:dotted;\n";
	cout<<"border-color:#6b6c6e;\n";
	cout<<"border-width:1px;\n";
	cout<<"}\n";
	cout<<"td{\n";
	cout<<"width:70px;\n";
	cout<<"text-align: center;\n";
	cout<<"}\n";
	cout<<"#godTable a:LINK{\n";
	cout<<"color:black;\n";
	cout<<"font-family:楷体_GB2312;\n";
	cout<<"margin-bottom: 6px;\n";
	cout<<"text-decoration: none;\n";
	cout<<"}\n";
	cout<<"#godTable a:HOVER{\n";
	cout<<"color:#cc8291;\n";
	cout<<"font-family:楷体_GB2312;\n";
	cout<<"text-decoration: none;\n";
	cout<<"}\n";
	cout<<" a:VISITED{\n";
	cout<<"color:#918291;\n";
	cout<<"font-size:15px;\n";
	cout<<"font-family:楷体_GB2312;\n";
	cout<<"text-decoration:underline;\n";
	cout<<"}\n";
	cout<<"a:LINK{\n";
	cout<<"color:#6b6c6e;\n";
	cout<<"font-size:medium;\n";
	cout<<"font-family:楷体_GB2312;\n";
	cout<<"margin-bottom: 6px;\n";
	cout<<"text-decoration: none;\n";
	cout<<"}\n";
	cout<<"a:HOVER{\n";
	cout<<"color:#8c93b5;\n";
	cout<<"font-size:17px;\n";
}

void mymath(char* data_string)
{
	//printf("data_string %s\n",data_string);
	char *myargv[3];
	int number = 123456;
	int password = 654321;
	char *start = data_string;
	int i = 0;
	while(*start)
	{
		if(*start == '=')
		{
			myargv[i++] = start + 1;
		}
		if(*start == '&')
		{
			*start = '\0';
		}
		start++;
	}
	int data1 = atoi(myargv[0]);
	int data2 = atoi(myargv[1]);
	//printf("\n");
	//cout<<"data1:%d  data:%d\n",data1,data2;
	
	if(data1 == number)
	{
		if(data2 == password)
		{

			cout<<"<style type=text/css>";
			cout<<"<html>\n"<<endl;

			cout<<"<body bgcolor=FFE4E1>";
			cout<<"<font color = red>";
			cout<<"<h1>登录成功!</h1><br/>";
			cout<<"<font size = 5>";
			cout<<"<font color = green>";
			cout<<"<h2>页面正在跳转......</h2>";
			cout<<"<h2><font color = blue>三秒后未能跳转，请手动跳转!</h2>";
			cout<<"<p><a href=\"../index2.html\">点我进入主页哦!</a></p>";
			cout<<"</font>";
			cout<<"</font>";
		}
		else
		{
			cout<<"<style type=text/css>";
			cout<<"<html>\n"<<endl;

			cout<<"<body bgcolor=FFE4E1>";
			cout<<"<font color = red>";
			cout<<"<h1>密码错误，请重新登录!</h1><br/>";
			cout<<"<font size = 5>";
			cout<<"<font color = green>";
			cout<<"<h2>页面正在跳转......</h2>";
			cout<<"<h2><font color = blue>三秒后未能跳转，请手动跳转!</h2>";
			cout<<"<p><a href=\"../index.html\">点我进入重新登录哦!</a></p>";
			cout<<"</font>";
			cout<<"</font>";

		}
	}
	else
	{
		cout<<"<style type=text/css>";

		cout<<"<html>\n"<<endl;
		cout<<"<body bgcolor=FFE4E1>";
		cout<<"<font color = red>";
		cout<<"<h1>登录失败</h1><br/>";
		cout<<"</font>";
		cout<<"<font size = 5>";
		cout<<"<font color = green>";
		cout<<"<p><a href=\"../happy.html\">点击这里放松一下哦!</a></p>";
		cout<<"<p><a href=\"../index.html\">点我进入重新登录哦!</a></p>";
		cout<<"</font>";
		cout<<"</font>";

	}

	/*printf("<html>");
	printf("<h1>%d + %d = %d</h1><br/>",data1,data2,data1+data2);
	printf("<h1>%d - %d = %d</h1><br/>",data1,data2,data1-data2);
	printf("<h1>%d * %d = %d</h1><br/>",data1,data2,data1*data2);
	printf("<h1>%d / %d = %d</h1><br/>",data1,data2,data1/data2);
	printf("<h1>%d %% %d = %d</h1><br/>",data1,data2,data1%data2);
	printf("</html>");*/
	cout<<"</html>";
}


int main()
{
	char* method = getenv("METHOD");
	char* data_string = NULL;
	char buf[SIZE];
	if(strcasecmp(method,"get") == 0)
	{
		data_string = getenv("QUERY_STRING");
	}
	else
	{
		char* content_len = getenv("CONTENT_LENGTH");
		int len = atoi(content_len);
		char c;
		int i = 0;
		for(; i < len ;i++)
		{
			read(0,&c,1);
			buf[i] = c;
		}
		buf[i] = 0;
		data_string = buf;
	}
	if(data_string)
	{
		mymath(data_string);
	}
	return 0;
}







