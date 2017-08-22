#ifndef _SQL_API_H_
#define _SQL_API_H_

#include<iostream>
using namespace std;
#include<string>
#include<mysql.h>
#include<stdlib.h>
#include<string>
#include<unistd.h>
#include<stdio.h>
#include<cstring>


class sql_api
{
public:
	sql_api();
	int connect();//数据库的链接
	int insert(const string& god_id,const string& god_name,const string& god_type,const string& god_price,const string& god_size);//商品的添加
	void select();//商品的展示（由于较小所以是全部展示）
	void delete_god(const string &god_name);
	void find(const string &god_name);
	~sql_api();
private:
	MYSQL* conn;
	MYSQL_RES *_res;
};


#endif

