#ifndef __JIRA_H__
#define __JIRA_H__
#include <http_client.h>

namespace anthology{
namespace jira{
	/**
	*Logins you via simple authentication and returns a web client
	*\param login
	*\param pwd JIRA pwd
	*\param base_path base path of your JIRA server
	*\return authenticated client
	*/ 
	web::http::client::http_client * login(std::string login,std::string pwd,std::string base_path);
	/**
	* Finds out the json tree for a given ticket in JIRA 
	* \param client
	* \param ticketId
	* \return 
	*/
	web::json::value json(web::http::client::http_client & client
	,const std::string ticketId);
}//namespace jira
}//namespace anthology
#endif
