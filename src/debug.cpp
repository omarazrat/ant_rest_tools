#include <iostream>
#include <json.h>
#include <boost/program_options.hpp>
#include "utils.h"
#include "jira.h"
#include "azdev.h"
#include "json_utils.h"

using namespace std;
using namespace web::http::client;
using namespace boost::program_options;
using namespace anthology::utils;
namespace jira = anthology::jira;
namespace ado= anthology::azure_devops;
namespace po = boost::program_options;

enum PLATFORM{
	AZURE,
	JIRA
};
int dealWithParams(int argc,char** argv);
PLATFORM platform = AZURE;
string login,pwd,base_path,ticket_id;
int main (int argc,char** argv){
	int res=dealWithParams(argc,argv);
	if(res)
		return res;
	http_client * client = NULL;
	web::json::value json;
	switch(platform){
		case AZURE:
			client = ado::login(login,pwd,base_path);
			json = ado::json(*client,ticket_id);
			break;
		case JIRA:
			client = jira::login(login,pwd,base_path);
			json = jira::json(*client,ticket_id);
			break;
	
	}
	cout<<anthology::json::dump(json)<<endl;
	return 0;
}

int dealWithParams(int argc,char** argv){
	po::options_description desc("Allowed options");
	desc.add_options()
	("help", "Show this help message")
	("l", po::value<string>(), "Platform: a for Azure (default) or j for JIRA")
	("p", po::value<string>(), "Password for the system you're getting in. If not specified, we'll ask for it")
	("u", po::value<string>(), "User for the system you're getting in")
	("rp", po::value<string>(), "Root URL of the system you're getting in")
	("ao", po::value<string>(), "ADO Organization, only valid with -la")
	("ap", po::value<string>(), "ADO Project, only valid with -la")
	("t", po::value<string>(), "Ticket id")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    

	if (vm.count("help")) {
		cout << desc << endl;
		return 1;
	}
	if(vm.count("l")){
		if(vm["l"].as<string>()=="j"){
			platform = JIRA;
		}
	}

	if(!vm.count("u")){
		cerr<<"User needed (u)"<<endl;
		return 1;
	}
	login=vm["u"].as<string>();
	if(!vm.count("rp")){
		cerr<<"Base url needed (rp)"<<endl;
		return 1;
	}
	base_path=vm["rp"].as<string>();
	if(vm.count("ao")){
		switch(platform){
			case AZURE:
				ado::_ado_organization_=vm["ao"].as<string>();
				break;
			case JIRA:
				cerr<<"ADO organization only valid with Azure (la)"<<endl;
				return 1;
		}
	}
	if(vm.count("ap")){
		switch(platform){
			case AZURE:
				ado::_ado_project_=vm["ap"].as<string>();
				break;
			case JIRA:
				cerr<<"ADO project only valid with Azure (la)"<<endl;
				return 1;
		}
	}
	if(!vm.count("t")){
		cerr<<"Need ticket id"<<endl
		<<"e.g: "<<argv[0]<<" LRN-197117"<<endl;
		return 1;
	}
	ticket_id=vm["t"].as<string>();
	if(vm.count("p")){
		cout<<"[Warning] Using a password on the command line interface can be insecure."<<endl;
		pwd=vm["p"].as<string>();
	}else{
		cout<<"Enter your password and press ENTER"<<endl;
		SetStdinEcho(false);
		cin>>pwd;
		SetStdinEcho();
	}
	return 0;
}
