#include <stdint.h>
#include <stdio.h>

#include "circular_fifo.h"

int main()
{
	/*
		CircularFIFO_SIZE==3  ±£¨
		 ‰»Î£∫u 1 u 2 u 3 u 4 u 5 o o o o o q
	*/
	CircularFIFO fifo;

	char arg1[10];
	int arg2;
	char arg1_0;
	char charbuffer[100];

	circularFIFO_init(&fifo);
	printf("%s\n\n", CircularFIFO2str(charbuffer, &fifo));
	do
	{
		printf("Input Command \"%%c [%%d]\":\n");
		scanf("%s", arg1);
		arg1_0 = arg1[0];
		if (arg1_0 == 'U' || arg1_0 == 'u')
		{
			scanf("%d", &arg2);
			printf("Input: %c(%d) %d\n", arg1_0, arg1_0, arg2);
		}
		else
		{
			printf("Input: %c(%d)\n", arg1_0, arg1_0);
		}

		switch (arg1_0)
		{
			case 'u':
			{
				bool res;
				res = circularFIFO_push(&fifo, arg2);
				if (res == false)
				{
					printf("FIFO Full.\n");
				}
				break;
			}
			case 'U':
			{
				circularFIFO_forcePush(&fifo, arg2);
				break;
			}
			case 'o':
			{
				bool res;
				CircularFIFO_element_t pop;
				res = circularFIFO_pop(&fifo, &pop);
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
				CircularFIFO_element_t pop;
				pop = circularFIFO_forcePop(&fifo);
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

		printf("%s\n\n", CircularFIFO2str(charbuffer, &fifo));
	} while (!((arg1_0 == 'q') || (arg1_0 == 'Q')));

	return 0;
}
