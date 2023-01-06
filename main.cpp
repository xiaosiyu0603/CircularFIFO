#include <cstdio>
#include <iostream>
#include "circular_fifo"

using namespace std;

int main()
{
	/*
		 ‰»Î£∫u 1 u 2 u 3 u 4 u 5 o o o o o q
	*/

	string arg1;
	char arg1_0;
	int arg2;

	CircularFIFO<uint8_t, int8_t, 3> fifo;

	cout << fifo << endl;
	do
	{
		printf("Input Command \"%%c [%%d]\":\n");
		cin >> arg1;
		arg1_0 = arg1.c_str()[0];
		if (arg1_0 == 'U' || arg1_0 == 'u')
		{
			cin >> arg2;
			printf("Input: %c %d\n", arg1_0, arg2);
		}
		else
		{
			printf("Input: %c\n", arg1_0);
		}

		switch (arg1_0)
		{
			case 'u':
			{
				bool res;
				res = fifo.push(arg2);
				if (res == false)
				{
					printf("FIFO Full.\n");
				}
				break;
			}
			case 'U':
			{
				fifo.forcePush(arg2);
				break;
			}
			case 'o':
			{
				bool res;
				uint8_t pop;
				res = fifo.pop(&pop);
				if (res == false)
				{
					printf("FIFO Empty.\n");
				}
				else
				{
					printf("Pop %d.\n", pop);
				}
				break;
			}
			case 'O':
			{
				uint8_t pop;
				pop = fifo.forcePop();
				printf("Pop %d.\n", pop);
				break;
			}
			case 'q':
			case 'Q':
				break;
			default:
			{
				printf("Invalid command \"%c\"\n", arg1_0);
			}
		}
		cout << fifo << endl << endl;
	} while (!((arg1_0 == 'q') || (arg1_0 == 'Q')));



	return 0;
}
