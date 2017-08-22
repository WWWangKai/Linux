#include"sql_api.h"
#include<stdlib.h>
#include<strings.h>

/*void print_style()
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
	cout<<"font-family:楷体_GB2312;\n";
	cout<<"text-decoration:underline;\n";
	cout<<"margin-bottom: 6px;\n";
	cout<<"}\n";
	cout<<"#quickMenu a:VISITED{\n";
	cout<<"color:#81838e;\n";
	cout<<"font-size:medium;\n";
	cout<<"font-family:楷体_GB2312;\n";
	cout<<"text-decoration:underline;\n";
	cout<<"margin-bottom: 6px;\n";
	cout<<"}\n";
	cout<<"#oper{\n";
	cout<<"magin-top:20px;\n";
	cout<<"margin-bottom:20px;\n";
	cout<<"margin-left:120px;\n";
	cout<<"}\n";
	cout<<"</style>\n";
}
*/

void insert_data(char* data_string)
{
	//cout<<"data_string"<<data_string<<endl;
	char* myargv[6];

	char* start = data_string;
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
	//print_style();
	sql_api sql;
	sql.connect();
	//cout<<"why   mmmmm";
	cout<<"<h3>Check your information!</h3><br/>"<<endl;
	cout<<"<h4>"<<"god_id: "<<myargv[0]<<"<br/>"<<endl;
	cout<<"god_name: "<<myargv[1]<<"<br/>"<<endl;
	cout<<"god_type: "<<myargv[2]<<"<br/>"<<endl;
	cout<<"god_price: "<<myargv[3]<<"<br/>"<<endl;
	cout<<"god_size: "<<myargv[4]<<"</h4><br/>"<<endl;
	//cout<<"connect success!"<<endl;
	cout<<myargv[0]<<" ";
	cout<<myargv[1]<<" ";
	cout<<myargv[2]<<" ";
	cout<<myargv[3]<<" ";
	cout<<myargv[4]<<" ";
	sql.insert(myargv[0],myargv[1],myargv[2],myargv[3],myargv[4]);
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
		insert_data(data_string);
	}
	cout<<data_string<<"";
	return 0;
}

