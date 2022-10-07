#include <Debug.h>
#include<sstream>
#include <fstream>
#include <string>


using namespace Core::Debug;
using namespace std;

std::fstream Log::fileType;

void Log::OpenFile(const char * fileName)
{
    fileType.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
    if (fileType)
    {
        cout << "Debug file opened succesfully." << endl;
    }
    else;
        cout << "Debug file can't be open." << endl;
}

void Log::Print(std::string message)
{
    fileType << "=========================================================================" << endl;
    fileType << message << endl;
    fileType << "=========================================================================" << endl;


}

void Log::CloseLogFile()
{
    fileType.close();
}


