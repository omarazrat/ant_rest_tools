#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>
#include <sstream>
#include <json.h>
#include <http_msg.h>
#include <http_client.h>
#include <pplxtasks.h>
#include "utils.h"
#include "json_utils.h"

using namespace std;
using namespace pplx;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;
using namespace anthology::utils;

http_client * anthology::json::_login(string login,string pwd
	,uri &location){
	http_client_config * config = new http_client_config();
#ifdef _WIN32
	credentials cred(StoW(login),StoW(pwd));
#else
	credentials cred(login,pwd);
#endif
	config->set_credentials(cred);
        http_client * client = new http_client(location,*config);
	return client;	
}
value anthology::json::_json(http_client & client,
		const string query){
	http_request req;
	req.set_method(methods::GET);
#ifdef _WIN32
	req.set_request_uri(StoW(query));
#else
	req.set_request_uri(query);
#endif
	http_response response= client.request(req).get();
#ifdef _WIN32
	response.headers().set_content_type(L"application/json");
#else
	response.headers().set_content_type("application/json");
#endif
//	cout<<"request made"<<endl;
//	cout<<"status code:"<<response.status_code()<<endl;//<<
//		response.to_string()<<endl;
	task< web::json::value > taskJS = response.extract_json();
	web::json::value json = taskJS.get();
	
	return json;
}
string anthology::json::dump(const value& json,list<string> &_list){
	stringstream out;
	string last;
	switch(json.type()){
		case value::Number:
		case value::Boolean:
		case value::String:
		case value::Null:
			last = _list.back();
			_list.pop_back();
			copy(_list.begin(),_list.end(),ostream_iterator<string>(out,">"));
			out<<last<<" ";
			_list.push_back(last);
			break;
		default:
			break;
	}
	switch(json.type()){
		case value::Number:
			out<<json.as_number().to_double()<<":Number"<<endl;
			break;
		case value::Boolean:
			out<<json.as_bool()<<":Bool"<<endl;
			break;
		case value::String:
#ifdef _WIN32
			out<<WtoS(json.as_string())<<":String"<<endl;
#else
			out<<json.as_string()<<":String"<<endl;
#endif
			break;
		case value::Object:
			out<<"{"<<anthology::json::dump(json.as_object(),_list);
			out<<"}"<<endl;
			break;
		case value::Array:
			out<<"{"<<anthology::json::dump(json.as_array(),_list);
			out<<"}"<<endl;
			break;
		case value::Null:
			out<<":Null"<<endl;
			break;
	}
	if(!_list.empty())
		_list.pop_back();
	return out.str();
}
string anthology::json::dump(const object& obj,list<string> &_list){	
	stringstream out;
	object::const_iterator it = obj.begin();
	while(it!=obj.end()){
#ifdef _WIN32
		_list.push_back(WtoS(it->first));
#else
		_list.push_back(it->first);
#endif
		out<<anthology::json::dump(it->second,_list);
		advance(it,1);
	}
	return out.str();
}
string anthology::json::dump(const web::json::array& obj,list<string> &_list){
	stringstream out;
	web::json::array::const_iterator it = obj.begin();
	size_t counter=0;
	while(it!=obj.end()){
		stringstream buffer;
		buffer<<"["<<counter++<<"]";
		_list.push_back(buffer.str());
		out<<anthology::json::dump(*it,_list);
		advance(it,1);
	}
	return out.str();
}
