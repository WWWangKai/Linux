#include"sql_api.h"
using namespace std;

sql_api::sql_api()
{
	conn = mysql_init(NULL);
}

int sql_api::connect()
{
	if(NULL == mysql_real_connect(conn,"127.0.0.1","root",NULL,"web",3306,"NULL",0))
	{
		cerr<<"<h3>connect error!</h3><br/>"<<endl;
	}
	else
	{
		cout<<"<font color = red>";
		cout<<"<h2>欢迎来到商品管理网站!</h2><br/>"<<endl;
	}
}



/*static void print_style()
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


int sql_api::insert(const string &god_id,const string &god_name,const string &god_type,const string &god_price,const string &god_size)
{
	cout<<"<style type=text/css>";
	cout<<"<html>\n"<<endl;

	cout<<"<body bgcolor=FFE4E1>";

	string sql = "INSERT INTO goods (god_id,god_name,god_type,god_price,god_size) VALUES('";
	sql += god_id;
	sql += "','";
	sql += god_name;
	sql += "','";
	sql += god_type;
	sql += "','";
	sql += god_price;
	sql += "','";
	sql += god_size;
	sql += "')";
	int ret = mysql_query(conn,sql.c_str());
	if(ret == 0 )
	{
		cout<<"<font size = 5><font color = green>";
		cout<<"<h3>插入成功了，开心不!</h3><br/>"<<endl;
	}
	else
	{
		cout<<"<h3>插入失败，重试一下吧亲!</h3><br/>"<<endl;
	}

	cout<<"<font size = 5>";
	cout<<"<font color = red>";
	cout<<"<p><a href=\"../cgi_bin/select_cgi\">点击这里查看商品信息！</a></p>"<<endl;
	cout<<"</font>";
	cout<<"</font>";


	//cout<<"</head>\n";
	cout<<"<font size = 5>";
	cout<<"<font color = red>";
	cout<<"<p><a href=\"../insert.html\">点我返回上一页哦!</a></p>"<<endl;
	cout<<"</body>\n"<<"</html>\n"<<endl;
	cout<<"</font>";
	cout<<"</font>";
	cout<<"</html>";
}

void sql_api::delete_god(const string &god_name)
{
	cout<<"<style type=text/css>";
	cout<<"<html>\n"<<endl;

	cout<<"<body bgcolor=FFE4E1>";

	string sql("DELETE FROM goods WHERE god_name='");
	sql += god_name; 
	sql += "';";
	int ret = mysql_query(conn,sql.c_str());
	if(ret == 0 )
	{
		cout<<"<h3>恭喜你，删除成功了!</h3><br/>"<<endl;
	}
	else
	{
		cout<<"<h3>不好意思，您重新删一下吧!</h3><br/>"<<endl;
	}

	
	cout<<"<font size = 5>";
	cout<<"<font color = red>";
	cout<<"<p><a href=\"../cgi_bin/select_cgi\">点击这里查看商品信息！</a></p>"<<endl;
	cout<<"</font>";
	cout<<"</font>";
	


	cout<<"</head>\n";
	cout<<"<font size = 5>";
	cout<<"<font color = red>";
	cout<<"<p><a href=\"../delete.html\">点我返回上一页哦!</a></p>"<<endl;
	cout<<"</body>\n"<<"</html>\n"<<endl;
	cout<<"</font>";
	cout<<"</html>";
}

void sql_api::find(const string &god_name)
{

	cout<<"<style type=text/css>";
	cout<<"<html>\n"<<endl;


	cout<<"<body bgcolor=FFE4E1>";

	//printf("god_name\n",god_name);
	string sql("SELECT * FROM goods WHERE god_name='");
	sql += god_name; 
	sql += "';";
	int ret = mysql_query(conn,sql.c_str());
	if(ret == 0 )
	{
		cout<<"<h3>哈哈，您找的商品在呢!</h3><br/>"<<endl;

	}
	else
	{
		cout<<"<h3>哦，NO!亲，您找的商品不在哦!</h3><br/>"<<endl;
	}


	//cout<<"</font>";
	//cout<<"</font>";
	//cout<<"</font>";
	cout<<"<font size = 5>";
	cout<<"<font color = red>";
	cout<<"<p><a href=\"../cgi_bin/select_cgi\">点击这里查看商品信息！</a></p>"<<endl;
	cout<<"</font>";
	//cout<<"</font>";

	cout<<"<font size = 5>";
	cout<<"<font color = red>";
	cout<<"<p><a href=\"../find.html\">点击这里返回上一层哦!</a></p>"<<endl;
	cout<<"</body>\n"<<"</html>\n"<<endl;
	cout<<"</font>";
	cout<<"</font>";

	cout<<"</html>";
}

void sql_api::select()
{
	//cout<<"<style type=text/css>";
	//cout<<"<html>\n"<<endl;


	//cout<<"<body bgcolor=FFE4E1>";


	string sql = "SELECT * FROM goods"; /*数据库要执行的命令*/
	int ret = mysql_query(conn,sql.c_str());//这个函数用来执行mysql指令
	if(ret == 0)
	{
		//mysql的数据控制
		MYSQL_RES *res = mysql_store_result(conn);//成功返回一个指向返回集的指针
		if(res)
		{
			int lines = mysql_num_rows(res);//获取返回集中的行数
			int rows = mysql_num_fields(res);
			cout<<"<font color = green>";
			cout<<"<h3>行数=: "<<lines<<"</h3>"<<"<h3>列数=: "<<rows<<"</h3>"<<endl;
			cout<<endl<<"<br/>";
			MYSQL_FIELD *field = NULL;

			cout<<"<h2>";
			cout<<"<h4></h4>";
			cout<<"<table border=5 cellspacing=10>"<<endl;
			cout<<"<tr>";
			cout<<"<font size = 3>";
			cout<<"<font color = green>";
			cout<<"<h2>下面便是商品信息：</h2>";
			cout<<"</font>";
			for(;field = mysql_fetch_field(res);)//获得与列字段相关信息的结构指针
			{
				cout<<"<th><font size = 4><font color = black>"<<field->name<<"</font></font></th>\n";
				//cout<<field->name<<"	";
			}
			cout<<"</tr>";
			cout<<"</font>";
			cout<<endl<<"</h2><br/>";
			cout<<"</tr>";
			int i , j;
			cout<<"</tr>";
			for(i = 0 ;i < lines; i++)
			{
				cout<<"<h2>";
				MYSQL_ROW row = mysql_fetch_row(res);//从mysql_store_resul返回集中取一行  没有数据null
				//会返回一个MYSQL_ROW变量 其实就是一个char** 把其当成一个二维数组
				cout<<"<font size = 4>"<<endl;
				cout<<"<html>";
				cout<<"<font color = green>";
				cout<<"<table border=1>"<<endl;
				cout<<"<tr>";
				cout<<"</tr>";
				for(j = 0;j < rows;j++)
				{

					cout<<"<td><font size = 4><font color = black>"<<row[j]<<"</font></font></td>";
				}
				cout<<"</tr>";
				cout<<"</h2>"<<endl;
				cout<<"</table>";
				cout<<"</font>";
			}
			cout<<"</font><br/>";
		}
		
		cout<<"</head>\n";
		
		cout<<"</font>";
		cout<<"</font>";
		cout<<"<font size = 5>";
		cout<<"<font color = red>";
		cout<<"<p><a href=\"../index2.html\">点击这里，返回主页哦!</a></p>"<<endl;
		cout<<"</body>\n"<<"</html>\n"<<endl;
		cout<<"</font>";
		cout<<"</font>";
		cout<<endl;
		free(res);
	}
	//cout<<"</html>";
}


sql_api::~sql_api()
{
	mysql_close(conn);
}


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



