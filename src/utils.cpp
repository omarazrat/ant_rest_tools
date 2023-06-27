#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
#include "utils.h"

using namespace std;
/**
*From https://stackoverflow.com/questions/1413445/reading-a-password-from-stdcin
*/
void anthology::utils::SetStdinEcho(bool enable)
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode );

#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}
wstring& anthology::utils::StoW(const string& str){
	wstring resp(str.begin(),str.end());
	return resp;
}
string& anthology::utils::WtoS(const wstring& str){
	string resp(str.begin(),str.end());
	return resp;
}