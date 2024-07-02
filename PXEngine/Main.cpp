//#define TEST
#define CREATESETTINGS
#ifdef  TEST
#include "TestEngine.h"
#include "Utilities/ArgumentParser.h"
#include <iostream>
int main(int argc, const char* argv[])
{
	ArgumentParser parser(argc, argv);
	TestEngine engine(parser);
	return engine.Run();
}
#endif //  TEST

#ifdef  CREATESETTINGS
#include "Settings/SettingsSerializer.h"
int main()
{

}
#endif //  CREATESETTINGS