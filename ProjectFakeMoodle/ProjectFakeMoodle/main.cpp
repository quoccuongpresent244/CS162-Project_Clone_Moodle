#include "function.h"

using namespace std;


int main()
{
	loadStaff();
	loadLecturer();
	loadStudent();

	/*cout << hocsinh[0].id << endl;
	cout << hocsinh[0].password << endl;
	cout << hocsinh[1].id << endl;
	cout << hocsinh[1].password << endl;
	cout << Nstudent<<" "<<Nleave;*/
	firstMenu();
	//login();

	delete[]lophoc;
	delete[]giaovu;
	delete[]giaovien;
	delete[]hocsinh;


	return 0;
}