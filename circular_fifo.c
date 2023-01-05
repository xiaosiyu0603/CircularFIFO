#include "circular_fifo.h"

/// @brief 初始化
/// @param fifo CircularFIFO指针
void circularFIFO_init(CircularFIFO *const fifo)
{
	fifo->carry = 0;
	fifo->p_read = fifo->p_write = fifo->buffer;
}

/// @brief 不检查是否满，直接压栈
/// @param fifo CircularFIFO指针
/// @param topush 要压入的数
void circularFIFO_forcePush(CircularFIFO *const fifo, const CircularFIFO_element_t topush)
{
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\twp: %d cry: %d\r\n", fifo->p_write - fifo->buffer, fifo->carry);
	#endif
	*(fifo->p_write++) = (CircularFIFO_element_t)topush;
	if (fifo->p_write - fifo->buffer >= CircularFIFO_SIZE) // 越过缓存边界
	{
		fifo->p_write = fifo->buffer;
		fifo->carry++;
	}
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\twp: %d cry: %d\r\n", fifo->p_write - fifo->buffer, fifo->carry);
	#endif
}

/// @brief 不检查是否空，直接弹出
/// @param fifo CircularFIFO指针
/// @return 弹出的结果
CircularFIFO_element_t circularFIFO_forcePop(CircularFIFO *const fifo)
{
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\trp: %d cry: %d diff: %d\r\n", fifo->p_read - fifo->buffer, fifo->carry, fifo->p_write - fifo->p_read);
	#endif
	CircularFIFO_element_t topop;
	topop = *(fifo->p_read++);
	if (fifo->p_read - fifo->buffer >= CircularFIFO_SIZE) // 读指针超出缓冲区
	{
		fifo->p_read = fifo->buffer;
		fifo->carry--;
	}
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\trp: %d cry: %d diff: %d\r\n", fifo->p_read - fifo->buffer, fifo->carry, fifo->p_write - fifo->p_read);
	#endif
	return topop;
}

/// @brief CircularFIFO状态的字符串描述
/// @param buffer 字符串缓冲区
/// @param fifo CircularFIFO指针
/// @return charbuffer的值
char *CircularFIFO2str(char *const buffer, const CircularFIFO *const fifo)
{
	sprintf(
		buffer,
		"CircularFIFO(wp=%+d, rp=%+d, cry=%d, Full=%d, Empty=%d)",
		fifo->p_write - fifo->buffer,
		fifo->p_read - fifo->buffer,
		fifo->carry,
		circularFIFO_isFull(fifo),
		circularFIFO_isEmpty(fifo));
	return buffer;
}
