#include "function.h"

using namespace std;


int main()
{
	loadStaff();

	/* for (int i = 0; i < Nstaff; i++) {
		cout << giaovu[i].username << endl;
		cout << giaovu[i].password << endl;
		cout << giaovu[i].fullname << endl;
		cout << giaovu[i].gender << endl;
		cout << endl;
	} */

	loadLecturer();

	/* for (int i = 0; i < Nlecturer; i++) {
		cout << giaovien[i].username << endl;
		cout << giaovien[i].password << endl;
		cout << giaovien[i].fullname << endl;
		cout << giaovien[i].gender << endl;
		cout << endl;

	} */

	loadStudent();

	/* for (int i = 0; i < Nstudent; i++) {
		cout << hocsinh[i].id << endl;
		cout << hocsinh[i].password << endl;
		cout << hocsinh[i].fullname << endl;
		cout << hocsinh[i].dob << endl;
		cout << hocsinh[i].clas << endl;
		cout << endl;
	} */

	//viewListOfClasses();

	//firstMenu();
	//viewListOfClasses();


	//importCSV();
	//addAStudenttoClass();

	//firstMenu();
	editStudent();

	//viewListOfStudentsInClass();

	//importCourseCSV();
	//addANewCourse();
	//editACourse();

	delete[]lophoc;
	delete[]giaovu;
	delete[]giaovien;
	delete[]hocsinh;


	return 0;
}