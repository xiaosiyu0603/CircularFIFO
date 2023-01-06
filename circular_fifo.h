#ifndef __CIRCULAR_FIFO_H
#define __CIRCULAR_FIFO_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// #define __CIRCULAR_FIFO_DEBUG

#define CircularFIFO_SIZE	BUFSIZ
// #define CircularFIFO_SIZE	3	// ������

typedef uint16_t CircularFIFO_element_t;

// ����ṹ��
typedef volatile struct _CircularFIFO
{
	volatile CircularFIFO_element_t  buffer[CircularFIFO_SIZE];	// ���ջ���
	volatile CircularFIFO_element_t *p_write;					// ������дָ��
	volatile CircularFIFO_element_t *p_read;					// ��������ָ��
	volatile size_t                  carry;						// ѭ����λ��дָ��ȶ�ָ�����ٴλ���Խ�磩
} CircularFIFO;

void circularFIFO_init(CircularFIFO *const fifo);

/// @brief �ж��Ƿ��
/// @param fifo CircularFIFOָ��
/// @return �Ƿ�ִ�гɹ�
static inline bool circularFIFO_isEmpty(const CircularFIFO *const fifo)
{
	return (bool)((fifo->p_read >= fifo->p_write) && (fifo->carry <= 0));
}

/// @brief �ж��Ƿ���
/// @param fifo CircularFIFOָ��
/// @return �Ƿ�ִ�гɹ�
static inline bool circularFIFO_isFull(const CircularFIFO *const fifo)
{
	return (bool)((fifo->p_write >= fifo->p_read) && (fifo->carry > 0));
}

void circularFIFO_forcePush(CircularFIFO *const fifo, const CircularFIFO_element_t topush);
CircularFIFO_element_t circularFIFO_forcePop(CircularFIFO *const fifo);

/// @brief ��FIFOѹջ
/// @param fifo CircularFIFOָ��
/// @param topush Ҫѹ���ֵ
/// @return �Ƿ�ִ�гɹ�
static inline bool circularFIFO_push(CircularFIFO *const fifo, const CircularFIFO_element_t topush)
{
	if (circularFIFO_isFull(fifo))
	{
		return false;
	}
	else
	{
		circularFIFO_forcePush(fifo, topush);
		return true;
	}
}

/// @brief ��FIFO����
/// @param fifo CircularFIFOָ��
/// @param p_topop ����ֵ��ָ��
/// @return �Ƿ�ִ�гɹ�
static inline bool circularFIFO_pop(CircularFIFO *const fifo, CircularFIFO_element_t *const p_topop)
{
	if (circularFIFO_isEmpty(fifo))
	{
		return false;
	}
	else
	{
		*p_topop = circularFIFO_forcePop(fifo);
		return true;
	}
}

char *CircularFIFO2str(char *const buffer, const CircularFIFO *const fifo);

#endif // __CIRCULAR_FIFO_H
