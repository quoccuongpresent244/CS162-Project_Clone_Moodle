#include "function.h"

using namespace std;


int main()
{
	loadStaff();
	loadLecturer();
	loadStudent();

	firstMenu();
	//login();

	delete[]lophoc;
	delete[]giaovu;
	delete[]giaovien;
	delete[]hocsinh;


	return 0;
}