#pragma once

#include <string>
using namespace std;

// http get
string URL_LOGIN = "http://dibang.zz91.com/api/loginsave.html?username=<USERNAME>&pwd=<PASSWORD>&clientid=<CLIENTID>";
string URL_GET_SELLER = "http://dibang.zz91.com/api/searchsuppliers.html?iccode=<iccode>";
string URL_DATA_UPDATE_LOG = "http://dibang.zz91.com/api/datatable_update.html?maxid=<MAXID>&datatable=<DATATABLE>&company_id=<COMPANY_ID>";
string URL_GET_AUTH = "http://dibang.zz91.com/api/getauth.html?user_selfid=<USER_SELFID>&company_id=<COMPANY_ID>";

// http post
string URL_DATA_GET_STORAGE_LASTTIME = "http://dibang.zz91.com/api/getstoragedate.html?company_id=<COMPANY_ID>";
string URL_DATA_UPLOAD_STORAGE_DOMAIN = "dibang.zz91.com";
string URL_DATA_UPLOAD_STORAGE_URL = "/api/updatestorage.html";							// 批量上传入库单
string URL_DATA_UPLOAD_STORAGE_PARAM = "company_id=<COMPANY_ID>&storelist=<DATA>";
string URL_DATA_GET_SUPPLIERS_LASTTIME = "http://dibang.zz91.com/api/getsuppliersdate.html?company_id=<COMPANY_ID>";
string URL_DATA_UPLOAD_SUPPLIERS_DOMAIN = "dibang.zz91.com";
string URL_DATA_UPLOAD_SUPPLIERS_URL = "/api/updatesuppliers.html";						// 批量上传本地供应商
string URL_DATA_UPLOAD_SUPPLIERS_PARAM = "company_id=<COMPANY_ID>&supplierlist=<DATA>";

// local properties
char LOGIN_USERNAME[50];				// 登录用户名
char LOGIN_SELFID[50];					// 登录的selfid信息
char LOGIN_GROUPID[50];
char LOGIN_COMPANYID[50];

// sql 语句统一堆放处
/*
select
*/
string SQL_USERS_SELECT_BY_CLIENTID		= "select top 1 id,selfid,username,group_id,company_id from users where clientid = '<CLIENTID>'";
string SQL_USERS_BY_UAP					= "select count(*) as hasExist from users where username='<USERNAME>' and pwd='<PWD>' ";

string SQL_V_SUPPLIERS_FOR_NOPAY	= "select * from v_suppliers where ispay = 0 and company_id = <COMPANY_ID> order by id desc";
string SQL_V_SUPPLIERS_FOR_PAY		= "select * from v_suppliers where ispay > 0 and company_id = <COMPANY_ID> order by id desc";

string SQL_SUPPLIERS_BY_ICCODE	= "select top 1 * from suppliers	where isdel=0 and company_id = <COMPANY_ID> and iccode = '<ICCODE>' order by id desc";
string SQL_SUPPLIERS_BY_MOBILE	= "select * from suppliers			where isdel=0 and company_id = <COMPANY_ID> and mobile = '<MOBILE>' order by id desc";
string SQL_SUPPLIERS_BY_CONTACT = "select * from suppliers			where isdel=0 and company_id = <COMPANY_ID> and contact like '%<CONTACT>%' order by id desc";
string SQL_SUPPLIERS_FOR_PAGE	= "SELECT * FROM suppliers			where isdel=0 and company_id = <COMPANY_ID> <WHERECLAUSE> and id  between (select min(id) from(select top <MIN> id from suppliers where  isdel = 0 and company_id = <COMPANY_ID> <WHERECLAUSE> order by id desc)) and (select min(id) from(select top <MAX> id from suppliers where isdel = 0 and company_id = <COMPANY_ID> <WHERECLAUSE> order by id desc)) order by id desc";
string SQL_SUPPLIERS_FOR_PAGE_COUNT = "SELECT count(0) as total_records FROM suppliers where isdel = 0 and company_id = <COMPANY_ID> <WHERECLAUSE> ";
string SQL_SUPPLIERS_FOR_TOP1		= "select top 1 id from suppliers order by id desc";
string SQL_SUPPLIERS_FOR_TOP1_ALL	= "select top 1 * from suppliers order by id desc";
string SQL_SUPPLIERS_FOR_UPLOAD		= "select * from suppliers where gmt_modified >#<GMT_MODIFIED># and company_id=<COMPANY_ID>";
string SQL_SUPPLIERS_BY_SELFID		= "select  count(0) as hasExist  from suppliers where selfid = '<SELFID>'";
string SQL_SUPPLIERS_BY_CID			= "select * from suppliers where company_id=<COMPANY_ID> order by id desc";

string SQL_STORAGE_FOR_UPLOAD = "select * from storage where gmt_modified >#<GMT_MODIFIED># and company_id=<COMPANY_ID>";

string SQL_V_STORAGELIST_BY_ICCODE = "select * from v_storagelist where iccode = '<ICCODE>' and company_id = <COMPANY_ID> order by id desc";
string SQL_V_STORAGELIST_FOR_SINGLE = "select * from v_storagelist where company_id = <COMPANY_ID> <WHERECALUSE>  order by id desc";

string SQL_STORAGE_BY_ID			= "select * from storage where id = <ID>";
string SQL_STORAGE_BY_SELFID		= "select * from storage where selfid = '<SELFID>'";
string SQL_STORAGE_BY_CODE			= "select * from storage where code = '<CODE>'";

string SQL_STORAGE_FOR_LAST_PRICE	= "select * from storage where company_id = <COMPANY_ID> and products_selfid = '<PRODUCTS_SELFID>' and price > 0 and status=4 order by id desc";

string SQL_UPDATE_LOG = "select * from update_log";

string SQL_PRODUCTS_SELECT_BY_SELFID = "select count(0) as hasExist from products where selfid = '<SELFID>'";

string SQL_CATEGORY_PRODUCTS_SELECT_BY_SELFID		= "select count(0) as hasExist from category_products where selfid = '<SELFID>'";
string SQL_CATEGORY_PRODUCTS_SELECT_BY_COMPANY_ID	= "select * from category_products where company_id = <COMPANY_ID> order by id desc";
string SQL_CATEGORY_PRODUCTS_SELECT_BY_NAME			= "select * from category_products where name = '<NAME>' order by id desc";

string SQL_PRODUCTS_SELECT_BY_COMPANY_ID = "select top 1 * from products where company_id = <COMPANY_ID> <CAULSE> order by id desc";

string SQL_EQSET_SELECT_ALL					= "select * from eqset";
string SQL_EQSET_SELECT_HASEXIST			= "select count(0) as hasExist from eqset where eq_type = '<EQ_TYPE>' ";

string SQL_COMPANY_CTYPE_BY_ID				= "select ctype from company where id = <ID>";

/*
insert
*/
string SQL_STORAGE_INSERT			= "INSERT INTO `storage` (`selfid`,`group_id`,`company_id`,`code`,`suppliers_selfid`,`gw`,`status`,`price_users_selfid`,`ispay`,`eqtype`) VALUES ('<SELFID>',<GROUP_ID>,<COMPANY_ID>,'<CODE>','<SUPPLIERS_SELFID>',<GW>,<STATUS>,'<PRICE_USERS_SELFID>',<ISPAY>,'<EQTYPE>')";
string SQL_STORAGE_INSERT_ALL		= "INSERT INTO `storage`(`selfid`,`group_id`,`company_id`,`stype`,`licence`,`code`,`products_selfid`,`suppliers_selfid`,`price`,`gw`,`nw`,`tare`,`total`,`status`,`price_users_selfid`,`price_time`,`out_time`,`ispay`,`scorecheck`,`pay_users_selfid`,`bz`) VALUES('<SELFID>',<GROUP_ID>,<COMPANY_ID>,'<STYPE>','<LICENCE>','<CODE>','<PRODUCTS_SELFID>','<SUPPLIERS_SELFID>',<PRICE>,<GW>,<NW>,<TARE>,<TOTAL>,<STATUS>,'<PRICE_USERS_SELFID>',<PRICE_TIME>,<OUT_TIME>,<ISPAY>,<SCORECHECK>,'<PAY_USERS_SELFID>','<BZ>')";

string SQL_SUPPLIERS_INSERT_GUEST	= "INSERT INTO `suppliers`(`selfid`,`iccode`,`name`,`contact`,`company_id`,`group_id`,`ctype`,`isdel`) VALUES('<SELFID>','<ICCODE>','<NAME>','<CONTACT>','<COMPANY_ID>',<GROUP_ID>,<CTYPE>,0)";
string SQL_SUPPLIERS_INSERT_ALL		= "INSERT INTO `suppliers`(`selfid`,`iccode`,`name`,`contact`,`company_id`,`group_id`,`ctype`,`htype`,`mobile`,`address`,`bz`,`isdel`) VALUES('<SELFID>','<ICCODE>','<NAME>','<CONTACT>',<COMPANY_ID>,<GROUP_ID>,<CTYPE>,<HTYPE>,'<MOBILE>','<ADDRESS>','<BZ>',0)";

string SQL_USERS_INSERT				= "INSERT INTO  users (selfid,group_id,company_id,clientid,username,pwd) VALUES ('<SELFID>',<GROUP_ID>,<COMPANY_ID>,'<CLIENTID>','<USERNAME>','<PWD>')";
string SQL_PRODUCTS_INSERT			= "INSERT INTO `products`(`selfid`,`group_id`,`company_id`,`name`,`name_py`,`category_selfid`,`spec`,`unit`,`stock`,`bz`)VALUES ('<SELFID>',<GROUP_ID>,<COMPANY_ID>,'<NAME>','<NAME_PY>','<CATEGORY_SELFID>','<SPEC>','<UNIT>',<STOCK>,'<BZ>')";
string SQL_CATEGORY_PRODUCTS_INSERT = "INSERT INTO `category_products`(`selfid`,`sub_selfid`,`company_id`,`name`) VALUES ('<SELFID>','<SUB_SELFID>',<COMPANY_ID>,'<NAME>')";
string SQL_EQSET_INSERT				= "INSERT INTO  eqset (eq_name,eq_type,eq_com,eq_btl,eq_sjw,eq_jyw,eq_tzw) values ('<EQ_NAME>','<EQ_TYPE>','<EQ_COM>','<EQ_BTL>','<EQ_SJW>','<EQ_JYW>','<EQ_TZW>')";
string SQL_UPDATE_LOG_INSERT		= "INSERT INTO  update_log (maxid,bz,tablename) values (<MAXID>,'<BZ>','<TABLENAME>')";

/*
update
*/
string SQL_STORAGE_UPDATE_TO_PRICE_OVER =			"update `storage` set gmt_modified = now(),status = 2,price_time = <PRICE_TIME>,price=<PRICE>,products_selfid = '<PRODUCTS_SELFID>',price_users_selfid = '<PRICE_USERS_SELFID>' ,total=<TOTAL> where id = <ID>";
string SQL_STORAGE_UPDATE_TO_WEIGHT_OVER =			"update `storage` set gmt_modified = now(),status = 3,tare_check=1,nw=<NW>,total=<TOTAL>,tare=<TARE> where id = <ID>";
string SQL_STORAGE_UPDATE_TO_TRADE_OVER =			"update `storage` set gmt_modified = now(),status = 4,pay_time = now(),ispay=1 , pay_users_selfid = '<PAY_USERS_SELFID>' where id = <ID>";
string SQL_STORAGE_UPDATE_TO_TRADE_OVER_ONLINE =	"update `storage` set gmt_modified = now(),status = 4,pay_time = now(),ispay=2 , pay_users_selfid = '<PAY_USERS_SELFID>' where id = <ID>";
string SQL_STORAGE_UPDATE_TO_FAIL =					"update `storage` set gmt_modified = now(),status = 99 where id = <ID>";

string SQL_EQSET_UPDATE =							"update eqset set eq_com = '<EQ_COM>' , eq_btl = '<EQ_BTL>' where eq_type = '<EQ_TYPE>' ";

string SQL_UPDATE_LOG_MAXID_CHANGE =				"update update_log set maxid = <MAXID> where tablename = '<TABLENAME>'";

string SQL_SUPPLIERS_TO_DEL_BY_IC =					"update suppliers set gmt_modified=now(),isdel=1 where iccode='<ICCODE>'";
string SQL_SUPPLIERS_FOR_EDIT =						"update suppliers set gmt_modified=now(),ctype=<CTYPE>,name='<NAME>',htype='<HTYPE>',contact='<CONTACT>',mobile='<MOBILE>',address='<ADDRESS>',bz='<BZ>' where iccode= '<ICCODE>'";

/*
	table listview head
	表格，头部配置参数 
*/

// 选择供应商 表头 
string LISTVIEW_TITLE_SUPPLIERS_CHOOSE[6] = { "序号","供货人编号","供货人","联系电话","供货商类型","地址" };
int LISTVIEW_WIDTH_SUPPLIERS_CHOOSE[6] = { 60,90,120,90,90,180 };

// 磅单界面，供应商表头 
string LISTVIEW_TITLE_STORAGE_SUPPLIERS[6] = { "序号","供货人编号","供货人", "联系电话","供应商类型","地址" };
int LISTVIEW_WIDTH_STORAGE_SUPPLIERS[6] = { 60, 120, 80, 100, 80, 160 };

// 磅单界面， 过磅单列表表头 
string LISTVIEW_TITLE_STORAGE_LIST[12] = { "序号", "磅", "供货人编号", "供货人", "进场时间", "毛重", "皮重", "品名", "单价", "净重", "总额", "状态" };
int LISTVIEW_WIDTH_STORAGE_LIST[12] = { 60,60,90,60,120,50,50,60,60,80,80,80 };

// 供应商管理界面列表 表头
string LISTVIEW_TITLE_SUPPLIERS_LIST[9] = { "公司类型","IC编号","公司名称","合作关系","联系人","手机号码","地址","备注","添加时间" };
int LISTVIEW_WIDTH_SUPPLIERS_LIST[9] = { 65,130,80,65 ,70 ,100 ,120 ,80 ,150 };

string LISTVIEW_TITLE_STORAGE_SINGLE[14] = { "流水号 ","出入库","车牌号","进场时间","送货人","货名","毛重","皮重","净重","毛重时间","司机","备注","状态" };
int LISTVIEW_WIDTH_STORAGE_SINGLE[14] = {100,55,80,145,80,80,80,80,80,145,80,80,80};