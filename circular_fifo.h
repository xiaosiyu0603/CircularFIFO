#ifndef __CIRCULAR_FIFO_H
#define __CIRCULAR_FIFO_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// #define __CIRCULAR_FIFO_DEBUG

#define CircularFIFO_SIZE	BUFSIZ
// #define CircularFIFO_SIZE	3	// 调试用

typedef uint16_t CircularFIFO_element_t;

// 缓存结构体
typedef volatile struct _CircularFIFO
{
	volatile CircularFIFO_element_t  buffer[CircularFIFO_SIZE];	// 接收缓冲
	volatile CircularFIFO_element_t *p_write;					// 缓冲区写指针
	volatile CircularFIFO_element_t *p_read;					// 缓冲区读指针
	volatile size_t                  carry;						// 循环进位（写指针比读指针多多少次缓冲越界）
} CircularFIFO;

void circularFIFO_init(CircularFIFO *const fifo);

/// @brief 判断是否空
/// @param fifo CircularFIFO指针
/// @return 是否执行成功
static inline bool circularFIFO_isEmpty(const CircularFIFO *const fifo)
{
	return (bool)((fifo->p_read >= fifo->p_write) && (fifo->carry <= 0));
}

/// @brief 判断是否满
/// @param fifo CircularFIFO指针
/// @return 是否执行成功
static inline bool circularFIFO_isFull(const CircularFIFO *const fifo)
{
	return (bool)((fifo->p_write >= fifo->p_read) && (fifo->carry > 0));
}

void circularFIFO_forcePush(CircularFIFO *const fifo, const CircularFIFO_element_t topush);
CircularFIFO_element_t circularFIFO_forcePop(CircularFIFO *const fifo);

/// @brief 向FIFO压栈
/// @param fifo CircularFIFO指针
/// @param topush 要压入的值
/// @return 是否执行成功
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

/// @brief 从FIFO弹出
/// @param fifo CircularFIFO指针
/// @param p_topop 弹出值的指针
/// @return 是否执行成功
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
