#include <base_uri.h>
#include <json.h>
#include <pplxtasks.h>
#include "jira.h"
#include "json_utils.h"

using namespace web::http::client;
using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace http::client;
using namespace pplx;
using namespace anthology::json;

http_client * anthology::jira::login(string login,string pwd,string base_path){
	uri * location = new uri(base_path+"/rest/api/2");
	return _login(login,pwd,*location);
}
web::json::value anthology::jira::json(http_client & client
	,const string ticketId){
	string query="issue/"+ticketId+"?expand=changelog&fields=";
	return _json(client,query);
}
