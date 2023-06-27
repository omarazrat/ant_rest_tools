#ifndef __ANTHOLOGY_UTILS__
#define __ANTHOLOGY_UTILS__
#include <string>

namespace anthology{
namespace utils{
	/**
	*Sets the screen echo 
	*/
	void SetStdinEcho(bool enable = true);
	/**
	* Just because CPPRESTSDK defines wide strings auto with windows systems
	*/
	std::wstring& StoW(const std::string& str);
	/**
	* Just because CPPRESTSDK defines wide strings auto with windows systems
	*/
	std::string& WtoS(const std::wstring& str);
}//utils
}//anthology
#endif
