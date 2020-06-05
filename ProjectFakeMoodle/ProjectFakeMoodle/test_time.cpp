#include <iostream> 
#include <ctime>
#include <string>

using namespace std;

int main(){
    /* time_t now = time(0);

    tm* lmt = localtime(&now);
    cout << "year: " << 1900 + lmt->tm_year << endl;
    cout << "month: " << 1 + lmt->tm_mon << endl;
    cout << "day: " << lmt->tm_mday << endl;
    return 0; */

    time_t now = time(0);
	tm *lmt = localtime(&now);

	int stuY, stuM, stuD, stuStart_h, stuStart_m;
	string tmpY, tmpM, tmpD, tmpStart_h, tmpStart_m, tmpEnd_h, tmpEnd_m; 
	int y, m, d, start_h, start_m, end_h, end_m;

	stuY = 1900 + lmt->tm_year;
	stuM = 1 + lmt->tm_mon;
	stuD = lmt->tm_mday;
	stuStart_h = 1 + lmt->tm_hour;
	stuStart_m = 1 + lmt->tm_min;

    string a[10];
    a[1] = "2020 06 05 11:00 13:00 -1";
    

				for (int k = 0; k < 4; k++)
					tmpY += a[1][k];
                
				for (int k = 5; k < 7; k++)
					tmpM += a[1][k];
                
				for (int k = 8; k < 10; ++k)
					tmpD += a[1][k];
                    
				for (int k = 11; k < 13; ++k)
					tmpStart_h += a[1][k]; 
                
				for (int k = 14; k < 16; ++k)
					tmpStart_m += a[1][k];
                
				for (int k = 17; k < 19; ++k)
					tmpEnd_h += a[1][k];
                
				for (int k = 20; k < 22; ++k)
					tmpEnd_m += a[1][k];
			    d = stoi(tmpD);
				m = stoi(tmpM);
				y = stoi(tmpY);
				start_h = stoi(tmpStart_h);
				start_m = stoi(tmpStart_m);
				end_h = stoi(tmpEnd_h);
				end_m = stoi(tmpEnd_m);


				 if (d == stuD && m == stuM && y == stuY){
					if (stuStart_h >= start_h && stuStart_m >= start_m && stuStart_h <= end_h){
						a[1][23] = '1';
                        a[1][24] = ' ';
                        cout << "!!!!!!!" << endl;
                    }
				} 
    cout << a[1];			 
}

