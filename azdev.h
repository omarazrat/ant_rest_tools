#ifndef __AZURE_DEVOPS__
#define __AZURE_DEVOPS__
#include <list>
#include <string>
#include <http_client.h>

namespace anthology{
namespace azure_devops{
	/**
	* Required for most functions
	*/
	extern std::string _ado_organization_;
	/**
	* Required for most functions
	*/
	extern std::string _ado_project_;
	/**
	*Logins you via Oauth and return a web client
	*\param login
	*\param pwd Azure Devops PAT
	*\return authenticated client
	*/ 
	web::http::client::http_client * login(std::string login,std::string pwd,std::string base_path);
	
	/**
	*\param client The http client to perform the query
	*\param teamName
	*/
	std::list<std::string> boards(web::http::client::http_client & client
	,const std::string teamName);
	/**
	* Finds out the json tree for a given ticket in azure
	* \param client
	* \param ticketId
	* \return 
	*/
	web::json::value json(web::http::client::http_client & client
	,const std::string ticketId);
}//namespace azure_devops
}//namespace anthology
#endif
