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
	volatile buffer_element_t  array[BUFFER_SIZE];	// 接收缓冲
	volatile buffer_element_t *p_write;				// 缓冲区写指针
	volatile buffer_element_t *p_read;				// 缓冲区读指针
	volatile int               carry;				// 循环进位（写指针比读指针多多少次缓冲越界）
} buffer_t;

void buffer_init(buffer_t *const buf);

static inline bool buffer_isEmpty(const buffer_t *const buf)
{
	return (bool)((buf->p_read >= buf->p_write) && (buf->carry <= 0));
}

static inline bool buffer_isFull(const buffer_t *const buf)
{
	return (bool)((buf->p_write >= buf->p_read) && (buf->carry > 0));
}

void buffer_forcePush(buffer_t *const buf, const buffer_element_t topush);

buffer_element_t buffer_forcePop(buffer_t *const buf);


static inline bool buffer_push(buffer_t *const buf, const buffer_element_t topush)
{
	if (buffer_isFull(buf))
	{
		return false;
	}
	else
	{
		buffer_forcePush(buf, topush);
		return true;
	}
}

static inline bool buffer_pop(buffer_t *const buf, buffer_element_t *const p_topop)
{
	if (buffer_isEmpty(buf))
	{
		return false;
	}
	else
	{
		*p_topop = buffer_forcePop(buf);
		return true;
	}
}

char *buffer2str(char *const charbuffer, const buffer_t *const buf);

#endif // __CIRCULAR_FIFO_H
