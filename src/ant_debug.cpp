#include <iostream>
#include <algorithm>
#include <iterator>
#include <web_utilities.h>
#include <pplxtasks.h>
#include <http_msg.h>
#include <json.h>
#include <boost/program_options.hpp>
#include "jira.h"
#include "azdev.h"
#include "json_utils.h"

using namespace std;
using namespace web::http::client;
using namespace web;
using namespace web::http;
using namespace pplx;
using namespace boost::program_options;

int main (int argc,char** argv){
	if(argc<2){
		cerr<<"Need ticket id"<<endl
		<<"e.g: "<<argv[0]<<" LRN-197117"<<endl;
		return 1;
	}
	string ticket_id=argv[1];
//	cout<<"Hello world of Rest services"<<endl;
	http_client* client = anthology::jira::login("narias","$Ns9hZx4M@WL","https://jira.bbpd.io");
	method mthd("GET");
	string query="issue/"+ticket_id+"?expand=changelog&fields=";
	task<http_response>  resp= client->request(mthd,query);
	cout<<"request made"<<endl;
	http_response response = resp.get();
	cout<<"status code:"<<response.status_code()<<endl<<
		/*response.to_string()<<*/endl;
	task< web::json::value > taskJS = response.extract_json();
	web::json::value json = taskJS.get();
	cout<<anthology::json::dump(json)<<endl;
	return 0;
}

