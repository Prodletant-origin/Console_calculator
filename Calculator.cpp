#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <stack>

using namespace std;

// передача из вектора в стек
void enter(double* total, char* act, vector<char>mas, int* i, int* x) {
	int dot = 0;
	(*total) = 0;
	*x = 0;
	while ((mas[*i] >= 48 && mas[*i] <= 57) || mas[*i] == 46 || mas[*i] == '@') {
		if (mas[*i] == 46) {
			dot = 1;
			*i = *i + 1;
		}
		else if (mas[*i] == '@') {
			*i = *i + 1;
		}
		else {
			(*total) = (*total) * 10 + mas[*i] - 48;
			if (*i < (mas.size() - 1)) {
				*i = *i + 1;
			}
			*x = 1;
			dot *= 10;
		}
	}
	(*act) = mas[*i];
	if (*i < (mas.size() - 1)) {
		*i = *i + 1;
	}
	if (dot > 0) {
		(*total) = (*total) / dot;
	}
}

// приоритет
int priority(char action) {
	switch (action) {
	case '+':
		return 1;
		break;
	case '-':
		return 1;
		break;
	case '*':
		return 2;
		break;
	case '/':
		return 2;
		break;
	}
}

// вычисление
double calculating(char action, double first, double second) {
	switch (action) {
	case '+':
		return second + first;
		break;
	case '-':
		return second - first;
		break;
	case '*':
		return second * first;
		break;
	case '/':
		return second / first;
		break;
	}
}

int main() {
	vector<char>mas;
	char test, stackPriority, curentPriority, ask;
	int left = 0, right = 0, dots = 0, null = 0;
equal:
	// ввод
	while ((test = _getch()) != '=' && test != 13) {
		// сброс
		if (test == 32) {
			if (!mas.empty()) {
				cout << "\r                                                                      \r";
				mas.clear();
				left = 0;
				right = 0;
				dots = 0;
				null = 0;
			}
			else {
				system("cls");
			}
		}
		// выход
		else if (test == 27) {
			exit(0);
		}
		// backspace
		else if (test == 8) {
			if (mas.empty()) {
				continue;
			}
			else if (mas.back() == 40 || mas.back() == 41) {
				switch (mas.back()) {
				case 40:
					left--;
					break;
				case 41:
					right--;
					break;
				}
			}
			else if (mas.back() == 46) {
				dots = 0;
			}
			cout << "\b \b";
			mas.pop_back();
			if (!mas.empty()) {
				if (mas.back() == '@') {
					mas.pop_back();
					dots = 1;
				}
			}
		}
		// Ввод и контроль ввода
		else if ((test >= 40 && test <= 43) || (test >= 45 && test <= 57)) {
			// Пустой массив
			if (mas.empty()) {
				if (test == 40 || test == 45 || (test >= 48 && test <= 57)) {
					if (test == 40) {
						cout << test;
						mas.push_back(test);
						left++;
					}
					else {
						cout << test;
						mas.push_back(test);
					}
				}
				else {
					continue;
				}
			}
			// Знаки
			else if (test == 42 || test == 43 || (test >= 45 && test <= 47)) {
				if (mas.back() == 42 || mas.back() == 43 || (mas.back() >= 45 && mas.back() <= 47)) {
					continue;
				}
				else if (mas.back() == 40) {
					if (test == 42 || test == 43 || test == 46 || test == 47) {
						continue;
					}
					else {
						cout << test;
						mas.push_back(test);
					}
				}
				else if (mas.back() == 41) {
					if (test == 46) {
						continue;
					}
					else {
						cout << test;
						mas.push_back(test);
					}
				}
				else {
					if (test == 46) {
						if (dots == 0) {
							cout << test;
							mas.push_back(test);
							dots++;
						}
						else {
							continue;
						}
					}
					else {
						if (dots == 1) {
							mas.push_back('@');
						}
						cout << test;
						mas.push_back(test);
						dots = 0;
					}
				}
			}
			// Скобки
			else if (test == 40 || test == 41) {
				switch (test) {
				case 40:
					if (mas.back() == 46) {
						continue;
					}
					else if (mas.back() == 41 || (mas.back() >= 48 && mas.back() <= 57)) {
						cout << "*" << test;
						if (dots == 1) {
							mas.push_back('@');
						}
						mas.push_back('*');
						mas.push_back(test);
						left++;
						dots = 0;
					}
					else {
						cout << test;
						mas.push_back(test);
						left++;
					}
					break;
				case 41:
					if (mas.back() == 40 || mas.back() == 42 || mas.back() == 43 || (mas.back() >= 45 && mas.back() <= 47)) {
						continue;
					}
					else if (left > right) {
						cout << test;
						if (dots == 1) {
							mas.push_back('@');
						}
						mas.push_back(test);
						right++;
						dots = 0;
					}
					break;
				}
			}
			// Числа
			else {
				if (test == 48) {
					if (mas.size() == 1) {
						if (mas.back() == 48) {
							continue;
						}
						else {
							cout << test;
							mas.push_back(test);
						}
					}
					else if (null == 0) {
						if (mas.back() == 41) {
							cout << "*" << test;
							mas.push_back('*');
							mas.push_back(test);
							null = 1;
						}
						else if (mas.back() == 40 || mas.back() == 42 || mas.back() == 43 || mas.back() == 45 || mas.back() == 47) {
							cout << test;
							mas.push_back(test);
							null = 1;
						}
						else {
							cout << test;
							mas.push_back(test);
						}
					}
					else if (null == 1) {
						continue;
					}
				}
				else {
					if (mas.size() == 1 && mas.back() == 48) {
						cout << "\b \b";
						mas.pop_back();
						cout << test;
						mas.push_back(test);
					}
					else if (mas.back() == 41) {
						cout << "*" << test;
						mas.push_back('*');
						mas.push_back(test);
					}
					else {
						if (null == 1) {
							cout << "\b \b";
							mas.pop_back();
						}
						cout << test;
						mas.push_back(test);
					}
					null = 0;
				}
			}
		}
		// Отсеивание лишних символов
		else {
			continue;
		}
	}
	if (mas.empty() || mas.back() == 40 || mas.back() == 42 || mas.back() == 43 || (mas.back() >= 45 && mas.back() <= 47) || left != right) {
		goto equal;
	}
	cout << "=";
	mas.push_back('=');


	// вычисление
	stack<double>number;
	stack<char>action;
	double total, a, b, c;
	char act, stackAction;
	int i = 0, x, mark = 0;
	do {
		//передача из вектора в стек
		enter(&total, &act, mas, &i, &x);

		//ЧИСЛА
		if (x == 1) {
			if (mark == 1) {
				number.push(-total);
				mark = 0;
			}
			else if (number.empty()) {
				if (!action.empty() && action.top() == '-') {
					number.push(-total);
					action.pop();
				}
				else {
					number.push(total);
				}
			}
			else {
				number.push(total);
			}
		}

		//ЗНАКИ
		if (action.empty() && act != '=') {
			action.push(act);
		}
		else if ((act == '-') && (x == 0) && (action.top() == '(')) {
			mark = 1;
		}
		else if (act == 40) {
			action.push(act);
		}
		else if (act == 41) {
			if (action.top() == 40) {
				action.pop();
			}
			else {
				do {
					stackAction = action.top();
					action.pop();
					a = number.top();
					number.pop();
					b = number.top();
					number.pop();
					c = calculating(stackAction, a, b);
					number.push(c);
				} while (action.top() != 40);
				action.pop();
			}
		}
		else if (act == 61) {
			if (action.empty());
			else {
				do {
					stackAction = action.top();
					action.pop();
					a = number.top();
					number.pop();
					b = number.top();
					number.pop();
					c = calculating(stackAction, a, b);
					number.push(c);
				} while (!action.empty());
			}
		}
		else {
			while (true) {
				if (action.empty()) {
					action.push(act);
					break;
				}
				else if (action.top() == 40) {
					action.push(act);
					break;
				}
				else {
					stackPriority = action.top();
					curentPriority = act;
					if (priority(curentPriority) > priority(stackPriority)) {
						action.push(act);
						break;
					}
					else {
						stackAction = action.top();
						action.pop();
						a = number.top();
						number.pop();
						b = number.top();
						number.pop();
						c = calculating(stackAction, a, b);
						number.push(c);
					}
				}
			}
		}
	} while (!action.empty() || act != '=');
	cout << number.top() << endl;
	cout << "For repeat press space or start typing" << endl << "For exit press ESC";
	mas.clear();
	while (!number.empty()) {
		number.pop();
	}
	while (!action.empty()) {
		action.pop();
	}
repeat:
	ask = _getch();
	if ((ask >= 48 && ask <= 57) || ask == 40 || ask == 45) {
		cout << endl << ask;
		mas.push_back(ask);
		if (ask == 40) {
			left = 1;
		}
		else {
			left = 0;
		}
		right = 0;
		dots = 0;
		null = 0;
		goto equal;
	}
	else if (ask == ' ') {
		cout << endl;
		main();
	}
	else if (ask == 27);
	else {
		goto repeat;
	}
	return 0;
}
