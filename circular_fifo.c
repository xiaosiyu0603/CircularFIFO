#include "circular_fifo.h"

void buffer_init(buffer_t *const buf)
{
	buf->carry = 0;
	buf->p_read = buf->p_write = buf->array;
}

void buffer_forcePush(buffer_t *const buf, const buffer_element_t topush)
{
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\twp: %d cry: %d\r\n", buf->p_write - buf->array, buf->carry);
	#endif
	*(buf->p_write++) = (buffer_element_t)topush;
	if (buf->p_write - buf->array >= BUFFER_SIZE) // 越过缓存边界
	{
		buf->p_write = buf->array;
		buf->carry++;
	}
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\twp: %d cry: %d\r\n", buf->p_write - buf->array, buf->carry);
	#endif
}

buffer_element_t buffer_forcePop(buffer_t *const buf)
{
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\trp: %d cry: %d diff: %d\r\n", buf->p_read - buf->array, buf->carry, buf->p_write - buf->p_read);
	#endif
	buffer_element_t topop;
	topop = *(buf->p_read++);
	if (buf->p_read - buf->array >= BUFFER_SIZE) // 读指针超出缓冲区
	{
		buf->p_read = buf->array;
		buf->carry--;
	}
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\trp: %d cry: %d diff: %d\r\n", buf->p_read - buf->array, buf->carry, buf->p_write - buf->p_read);
	#endif
	return topop;
}

char *buffer2str(char *const charbuffer, const buffer_t *const buf)
{
	sprintf(
		charbuffer,
		"buffer_t(wp=%+d, rp=%+d, cry=%d, Full=%d, Empty=%d)",
		buf->p_write - buf->array,
		buf->p_read - buf->array,
		buf->carry,
		buffer_isFull(buf),
		buffer_isEmpty(buf));
	return charbuffer;
}
