#ifndef __CIRCULAR_FIFO_H
#define __CIRCULAR_FIFO_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// #define __CIRCULAR_FIFO_DEBUG

// #define BUFFER_SIZE	BUFSIZ
#define BUFFER_SIZE	3

typedef uint16_t buffer_element_t;

typedef volatile struct
{
	volatile buffer_element_t  rx_buf[BUFFER_SIZE];				// ���ջ���
	volatile buffer_element_t *rx_buf_wp;						// ������дָ��
	volatile buffer_element_t *rx_buf_rp;						// ��������ָ��
	volatile int               carry;							// ѭ����λ��дָ��ȶ�ָ�����ٴλ���Խ�磩
} buffer_t;

void buffer_init(buffer_t *const buf);

// TODO: extern inline

bool buffer_isEmpty(const buffer_t *const buf);
bool buffer_isFull(const buffer_t *const buf);

bool buffer_push(buffer_t *const buf, const buffer_element_t topush);
bool buffer_pop(buffer_t *const buf, buffer_element_t *const p_topop);

void buffer_forcePush(buffer_t *const buf, const buffer_element_t topush);
buffer_element_t buffer_forcePop(buffer_t *const buf);

char *buffer2str(char *const charbuffer, const buffer_t *const buf);

#endif // __CIRCULAR_FIFO_H
