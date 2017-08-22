#include"sql_api.h"
#include<stdlib.h>
#include<strings.h>


void print_style()
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

void delete_data(char* data_string)
{
	//printf("huo que canshu\n");

	char* myargv[2];
	char* start = data_string;
	int i = 0;
	while(*start)
	{
		if(*start == '=')
		{
			myargv[i++] = start +1;
		}
		if(*start == '&')
		{
			*start = '\0';
		}
		start ++;
	}
	printf("delete_god_name\n",myargv[0]);
	sql_api s;
	s.connect();
	s.delete_god(myargv[0]);
}


void urldecode(char *p)  
{  
	int i=0;  
	while(*(p+i))  
	{  
		if ((*p=*(p+i)) == '%')  
		{  
			*p=*(p+i+1) >= 'A' ? ((*(p+i+1) & 0XDF) - 'A') + 10 : (*(p+i+1) - '0');  
			*p=(*p) * 16;  
			*p+=*(p+i+2) >= 'A' ? ((*(p+i+2) & 0XDF) - 'A') + 10 : (*(p+i+2) - '0');  
			i+=2;  
		}  
		else if (*(p+i)=='+')  
		{  
			*p=' ';  
		}  
		p++;  
	}  
	*p='\0';  
}  

int main()
{
	
	char* method = getenv("METHOD");
	char* data_string = NULL;
	char buf[1024];
	if(strcasecmp(method,"get") == 0)
	{
		data_string = getenv("QUERY_STRING");
		//printf("datastring\n");
		urldecode(data_string);
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
		delete_data(data_string);
	}
	//printf("datastring\n");
	return 0;
}
