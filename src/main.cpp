#include "PUD.h"

using namespace std;

int main(int argc, char* argv[])
{
	PUD reader("data/puds/ICEBRDGE.PUD", 0x0);
	reader.Load();

	return 0;
}
