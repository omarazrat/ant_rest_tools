#include <base_uri.h>
#include <json.h>
#include <pplxtasks.h>
#include "azdev.h"
#include "json_utils.h"
#include "utils.h"

using namespace std;
using namespace anthology::json;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;
using namespace pplx;
using namespace anthology::utils;

string anthology::azure_devops::_ado_organization_;
string anthology::azure_devops::_ado_project_;

http_client * anthology::azure_devops::login(string login,string pwd,string base_path){
#ifdef _WIN32
	uri * location = new uri(StoW(base_path));
#else
	uri * location = new uri(base_path);
#endif
	return _login(login,pwd,*location);
}
web::json::value anthology::azure_devops::json(http_client & client
	,const string ticketId){
	string query="/"+_ado_organization_+"/"+_ado_project_+"/_apis/wit/fields?api-version=7.1-preview.3";
	return _json(client,query);
}
list<string> anthology::azure_devops::boards(http_client & client
	,const string teamName){
//GET https://dev.azure.com/{organization}/{project}/{team}/_apis/work/boards?api-version=7.1-preview.1
	list<string> resp;
	string query="/"+_ado_organization_+"/"+_ado_project_+"/"+teamName+"/_apis/work/boards?api-version=7.1-preview.1";
	web::json::value json = _json(client,query);//taskJS.get();
//	cout<<anthology::json::dump(json)<<endl;
#ifdef _WIN32
	web::json::array varray=json.at(L"value").as_array();
	for(size_t i = 0;i<json.at(L"count").as_number().to_int32();i++){
		resp.push_back(WtoS(varray[i].at(L"name").as_string()));
#else
	web::json::array varray=json.at("value").as_array();
	for(size_t i = 0;i<json.at("count").as_number().to_int32();i++){
		resp.push_back(varray[i].at("name").as_string());
#endif
	}
	return resp;
}
