#include <iostream>
#include <vector>
using namespace std;

class process
{
private:
	int start_time;
	int burst;
	int queue;
	char status;	
public:
	int number;
	void set_start_time(int t)
	{
		start_time = t;
	}
	void set_burst(int b)
	{
		burst = b;
	}
	void set_queue(int q)
	{
		queue = q;
	}
	void set_status(char s)
	{
		status = s;
	}
	int get_start_time()
	{
		return start_time;
	}
	int get_burst()
	{
		return burst;
	}
	int get_queue()
	{
		return queue;
	}
	char get_status()
	{
		return status;
	}

	void run(int q)
	{
		burst -= q;
		status = 'A';
	}

	void wait()
	{
		status = 'W';
	}

	void out()
	{
		status = ' ';
	}
};

void show(process* p, int n, int time)
{
	
	cout << time << "\t";
	for (int i = 0; i < n; i++)
	{

		cout << p[i].get_status() << "\t";
	}
	cout << endl;	
}

void make_process(process* p, int i)
{
	process new_process;
	int temp;	
	cout << "введите стартовое время " << i + 1 << "-го процесса ";
	cin >> temp;
	while (temp < 1)
	{
		cout << "неверные данные, повторите ввод ";
		cin >> temp;
	}
	new_process.set_start_time(temp);
	cout << "введите длительность " << i + 1 << "-го процесса ";
	cin >> temp;
	while (temp < 0)
	{
		cout << "неверные данные, повторите ввод ";
		cin >> temp;
	}
	new_process.set_burst(temp);
	new_process.set_status(' ');
	new_process.set_queue(0);
	new_process.number = i + 1;
	p[i] = new_process;
}

int main()
{
	setlocale(LC_ALL, "ru");
	int n;
	int quant = 1;
	process* p;
	cout << "введите кол-во процессов" << endl;
	cin >> n;
	while (n < 1)
	{
		cout << "неверные данные, повторите ввод ";
		cin >> n;
	}	
	p = new process[n];
	for (int i = 0; i < n; i++)
	{
		make_process(p, i);
	}	

	for (int i = 0; i < n - 1; i++) 
	{
		for (int j = 0; j < n - i - 1; j++) 
		{
			if (p[j].get_start_time() > p[j + 1].get_start_time())
			{
				process temp;
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}

	cout << "\t";
	for (int i = 0; i < n; i++)
	{
		cout << p[i].number << "\t";
	}	
	cout << endl;
	int all_burst = 0;
	for (int i = 0; i < n; i++)
	{
		all_burst += p[i].get_burst();
	}
	int time = 1;
	bool free = true;
	int k = 1;
	while (all_burst > 0)
	{
		for (int i = 0; i < n; i++)
		{
			if (time >= p[i].get_start_time())
			{
				if (p[i].get_burst() > 0)
				{
					p[i].wait();
				}
				else
				{
					p[i].out();
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (time >= p[i].get_start_time() && p[i].get_burst() > 0 && p[i].get_queue() == 0)
			{
				if (free == true)
				{
					k = 1;
					p[i].run(quant);
					all_burst -= quant;
					free = false;	
					p[i].set_queue(1);
				}				
			}			
		}

		for (int i = 0; i < n; i++)
		{
			if (time >= p[i].get_start_time() && p[i].get_burst() > 0 && p[i].get_queue() == 1)
			{
				if (free == true)
				{
					k = 0;
					for (int j = 0; j < 2; j++)
					{
						if (p[i].get_burst() > 0)
						{
							p[i].run(quant);
							all_burst -= quant;
							k++;
						}
					}
					free = false;
					p[i].set_queue(2);
				}				
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (time >= p[i].get_start_time() && p[i].get_burst() > 0 && p[i].get_queue() == 2)
			{
				if (free == true)
				{
					k = 0;
					for (int j = 0; j < 4; j++)
					{
						if (p[i].get_burst() > 0)
						{
							p[i].run(quant);
							all_burst -= quant;
							k++;
						}
					}
					free = false;
					p[i].set_queue(3);
				}				
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (time >= p[i].get_start_time() && p[i].get_burst() > 0 && p[i].get_queue() == 3)
			{
				if (free == true)
				{
					k = 0;
					for (int j = 0; j < p[i].get_burst(); j++)
					{
						
						p[i].run(quant);
						all_burst -= quant;
						k++;						
					}
					free = false;					
				}
			}
		}

		for (int i = 0; i < k; i++)
		{
			show(p, n, time);
			time++;
		}
		free = true;
		k = 1;
	}

	delete[] p;
	return 0;
}