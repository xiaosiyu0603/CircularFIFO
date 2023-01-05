#include "circular_fifo.h"

/// @brief 初始化
/// @param buf buffer_t指针
void buffer_init(buffer_t *const buf)
{
	buf->carry = 0;
	buf->p_read = buf->p_write = buf->array;
}

/// @brief 不检查是否满，直接压栈
/// @param buf buffer_t指针
/// @param topush 要压入的数
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

/// @brief 不检查是否空，直接弹出
/// @param buf buffer_t指针
/// @return 弹出的结果
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

/// @brief buffer_t转换为字符串
/// @param charbuffer 字符串缓冲区
/// @param buf buffer_t指针
/// @return charbuffer的值
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
