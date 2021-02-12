#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int main()
{
	int total_traffic;                              // Общий трафик
	int actual_remaining_traffic;                   // Фактически оставшийся трафик
	int recommended_remaining_traffic;              // Рекомендованный остаток трафика
	int start_day;                                  // День начала отчетного периода
	int day_use;                                    // Ежедневная норма потребления трафика
	int year;                                       // Текущий год
	int month;                                      // Текущий месяц
	int month_days;                                 // Количество дней в текущем месяце
	int day;                                        // Текущий день

	time_t current_time = time(nullptr);
	tm *cur_time_struct = localtime(&current_time);

	fstream fin;

	fin.open(".preferences.txt");

	cout << "Maxim Pochinskiy - Traffic Calculator 1.0 - 29.10.20\n" << endl;

	if (!fin.fail())
	{
		cout << "Hello!\n" << endl
			 << "You can find out if you have overreached your\n"
			 << "recommended month traffic use with this application.\n" << endl;

		fin >> total_traffic >> start_day;

		cout << "Enter actual remaining traffic (MB): ";
		cin >> actual_remaining_traffic;

		year = cur_time_struct->tm_year;
		day = cur_time_struct->tm_mday;

		if (day >= start_day)
			month = cur_time_struct->tm_mon;
		else
			month = cur_time_struct->tm_mon - 1;

		if ((month == 0) || (month == 2) || (month == 4) || (month == 6) ||
			(month == 7) || (month == 9) || (month == 11))
			month_days = 31;
		else if ((month == 3) || (month == 5) || (month == 8) || (month == 10))
			month_days = 30;
		else if (!(year % 4) && ((year % 100) || !(year % 400)))
			month_days = 29;
		else
			month_days = 28;

		day_use = total_traffic / month_days;

		if (day > start_day)
			recommended_remaining_traffic = total_traffic - day_use * (day - start_day);
		else
			recommended_remaining_traffic = total_traffic - day_use * (month_days - start_day + day);

		cout << endl
			 << "Total traffic: " << total_traffic << " MB.\n"
			 << "Recommended day traffic use for this month: " << day_use << " MB.\n"
			 << "Actual remaining traffic: " << actual_remaining_traffic << " MB.\n"
			 << "Recommended remaining traffic: " << recommended_remaining_traffic << " MB.\n"
			 << endl;

		if (actual_remaining_traffic < recommended_remaining_traffic)
			cout << "Warning! It's strongly recommended to you to reduce your daily traffic use!\n"
				 << "You have overreached recommended traffic use by "
				 << recommended_remaining_traffic - actual_remaining_traffic << " MB.\n";
		else
			cout << "You have not overreached recommended traffic use.\n"
				 << "You can also spend over "
				 << actual_remaining_traffic - recommended_remaining_traffic << " MB.\n";

		fin.close();
	}
	else
		cout << "Preferences file opening error!\n";

	cout << endl
		 << "Goodbye!\n";

	return 0;
}