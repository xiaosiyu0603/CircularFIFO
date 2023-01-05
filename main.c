#include <stdint.h>
#include <stdio.h>

#include "circular_fifo.h"

int main()
{
	buffer_t buf;

	char arg1[10];
	int arg2;
	char arg1_0;
	char charbuffer[100];

	buffer_init(&buf);
	printf("%s\n\n", buffer2str(charbuffer, &buf));
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
				res = buffer_push(&buf, arg2);
				if (res == false)
				{
					printf("FIFO Full.\n");
				}
				break;
			}
			case 'U':
			{
				buffer_forcePush(&buf, arg2);
				break;
			}
			case 'o':
			{
				bool res;
				buffer_element_t pop;
				res = buffer_pop(&buf, &pop);
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
				buffer_element_t pop;
				pop = buffer_forcePop(&buf);
				printf("Pop %d.\n", pop);
				break;
			}
			default:
			{
				printf("Invalid command \"%c\"\n", arg1_0);
			}
		}

		printf("%s\n\n", buffer2str(charbuffer, &buf));
	} while (!((arg1_0 == 'q') || (arg1_0 == 'Q')));

	return 0;
}
