#include<iostream>
using namespace std;

class Train
{
private:
	char data[1000];
	int top;
public:
	Train() {
		top = -1;
	}
	void push(char c) {
		data[++top] = c;
	}
	char pop() {
		return data[top--];
	}
	char peek() {
		return data[top];
	}
	bool isEmpty() {
		return top == -1;
	}
};
bool canExit(const string& entrance, const string& exit)
{
	Train train;
	int entranceIndex = 0;
	for (char c : exit)
	{
		if (!train.isEmpty() && train.peek() == c) {
			train.pop();
		}
		else {
			while (entranceIndex < entrance.length() && entrance[entranceIndex] != c)
			{
				train.push(entrance[entranceIndex]);
				entranceIndex++;
			}
			if (entranceIndex >= entrance.length()) {
				return false;
			}
			entranceIndex++;
		}
	}
	return true;
}

int main()
{
	string entrance;
	while (cin >> entrance) {
		if (entrance == "EOF") {
			break;
		}
		string exit;
		while (cin >> exit)
		{
			if (exit == "EOF")
			{
				break;
			}
			if (canExit(entrance, exit))
			{
				cout << "yes" << endl;
			}
			else {
				cout << "no" << endl;
			}
		}
	}
	return 0;
}