#ifndef __JSON_UTILS__
#define __JSON_UTILS__
#include <base_uri.h>
#include <list>
#include <string>
#include <json.h>
namespace anthology{
namespace json{
	/**
	*Logins via simple authentication and returns a web client
	*\param login
	*\param pwd JIRA pwd
	*\param location base path of your server
	*\return authenticated client
	*/ 
	web::http::client::http_client * _login(std::string login,std::string pwd
	,web::uri &location);
	/**
	* Performs a simple GET query to the url provided
	* \param client
	* \param query
	* \return a JSON object with the result of the query
	* \throws
	*/
	web::json::value _json(web::http::client::http_client & client,
		const std::string query);
	/**
	*To show the content of any json value
	*\param json the object to display
	*\param _list inner parameter to keep track of nesting fields
	*/
	std::string dump(const web::json::value& json,std::list<std::string> &_list);
	std::string inline dump(const web::json::value& json){
		std::list<std::string> lst;
		return dump(json,lst);
	}
	/**
	*To show the content of any json object
	*\param json the object to display
	*\param _list inner parameter to keep track of nesting fields
	*/
	std::string dump(const web::json::object& obj,std::list<std::string> &_list);
	std::string inline dump(const web::json::object& obj){
		std::list<std::string> lst;
		return dump(obj,lst);
	}
	/**
	*To show the content of any json array
	*\param json the object to display
	*\param _list inner parameter to keep track of nesting fields
	*/
	std::string dump(const web::json::array& obj,std::list<std::string> &_list);
	std::string inline dump(const web::json::array& obj){
		std::list<std::string> lst;
		return dump(obj,lst);
	}
}//namespace json
}//namespace anthology
#endif
