#include "../cautolib.h"

using namespace std;
using namespace cautolib;

void ShowDesktop()
{
	keyboard::VirtualKeyBoard vkb;
	if (!vkb.input(2, KeyValue::KeyLWIN, KeyValue::KeyD))
		printf("error");
	system("pause");
}

int main()
{
	ShowDesktop();
	cout << "Hello CMake." << endl;
	return 0;
}
