#include "circular_fifo.h"

/// @brief ��ʼ��
/// @param fifo CircularFIFOָ��
void circularFIFO_init(CircularFIFO *const fifo)
{
	fifo->carry = 0;
	fifo->p_read = fifo->p_write = fifo->buffer;
}

/// @brief ������Ƿ�����ֱ��ѹջ
/// @param fifo CircularFIFOָ��
/// @param topush Ҫѹ�����
void circularFIFO_forcePush(CircularFIFO *const fifo, const CircularFIFO_element_t topush)
{
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\twp: %d cry: %d\r\n", fifo->p_write - fifo->buffer, fifo->carry);
	#endif
	*(fifo->p_write++) = (CircularFIFO_element_t)topush;
	if (fifo->p_write - fifo->buffer >= CircularFIFO_SIZE) // Խ������߽�
	{
		fifo->p_write = fifo->buffer;
		fifo->carry++;
	}
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\twp: %d cry: %d\r\n", fifo->p_write - fifo->buffer, fifo->carry);
	#endif
}

/// @brief ������Ƿ�գ�ֱ�ӵ���
/// @param fifo CircularFIFOָ��
/// @return �����Ľ��
CircularFIFO_element_t circularFIFO_forcePop(CircularFIFO *const fifo)
{
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\trp: %d cry: %d diff: %d\r\n", fifo->p_read - fifo->buffer, fifo->carry, fifo->p_write - fifo->p_read);
	#endif
	CircularFIFO_element_t topop;
	topop = *(fifo->p_read++);
	if (fifo->p_read - fifo->buffer >= CircularFIFO_SIZE) // ��ָ�볬��������
	{
		fifo->p_read = fifo->buffer;
		fifo->carry--;
	}
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\trp: %d cry: %d diff: %d\r\n", fifo->p_read - fifo->buffer, fifo->carry, fifo->p_write - fifo->p_read);
	#endif
	return topop;
}

/// @brief CircularFIFO״̬���ַ�������
/// @param buffer �ַ���������
/// @param fifo CircularFIFOָ��
/// @return charbuffer��ֵ
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
