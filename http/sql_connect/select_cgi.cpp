#include"sql_api.h"

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


int main()
{
	cout<<"<style type=text/css>";
	//	cout<<"body{background-image: url(../wwwroot/55.jpg);background-size:cover;}</style>";
	cout<<"<html>";

	//cout<<"<body bgcolor=FFE4E1>";


	cout<<"<font color = red>";
	cout<<"<head><title><h1>商品信息：</h1></title>\n"<<endl;
	print_style();
	cout<<"</head>\n";
	cout<<"<body>\n"<<endl;
	sql_api sql;
	sql.connect();
	sql.select();
	return 0;
	cout<<"</html>";
}
