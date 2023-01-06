#include "circular_fifo.h"

/// @brief ��ʼ��
/// @param buf buffer_tָ��
void buffer_init(buffer_t *const buf)
{
	buf->carry = 0;
	buf->p_read = buf->p_write = buf->array;
}

/// @brief ������Ƿ�����ֱ��ѹջ
/// @param buf buffer_tָ��
/// @param topush Ҫѹ�����
void buffer_forcePush(buffer_t *const buf, const buffer_element_t topush)
{
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\twp: %d cry: %d\r\n", buf->p_write - buf->array, buf->carry);
	#endif
	*(buf->p_write++) = (buffer_element_t)topush;
	if (buf->p_write - buf->array >= BUFFER_SIZE) // Խ������߽�
	{
		buf->p_write = buf->array;
		buf->carry++;
	}
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\twp: %d cry: %d\r\n", buf->p_write - buf->array, buf->carry);
	#endif
}

/// @brief ������Ƿ�գ�ֱ�ӵ���
/// @param buf buffer_tָ��
/// @return �����Ľ��
buffer_element_t buffer_forcePop(buffer_t *const buf)
{
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\trp: %d cry: %d diff: %d\r\n", buf->p_read - buf->array, buf->carry, buf->p_write - buf->p_read);
	#endif
	buffer_element_t topop;
	topop = *(buf->p_read++);
	if (buf->p_read - buf->array >= BUFFER_SIZE) // ��ָ�볬��������
	{
		buf->p_read = buf->array;
		buf->carry--;
	}
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\trp: %d cry: %d diff: %d\r\n", buf->p_read - buf->array, buf->carry, buf->p_write - buf->p_read);
	#endif
	return topop;
}

/// @brief buffer_tת��Ϊ�ַ���
/// @param charbuffer �ַ���������
/// @param buf buffer_tָ��
/// @return charbuffer��ֵ
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
