#include "circular_fifo.h"

void buffer_init(buffer_t *const buf)
{
	buf->carry = 0;
	buf->rx_buf_rp = buf->rx_buf_wp = buf->rx_buf;
}

bool buffer_isEmpty(const buffer_t *const buf)
{
	return (bool)((buf->rx_buf_rp >= buf->rx_buf_wp) && (buf->carry <= 0));
}

bool buffer_isFull(const buffer_t *const buf)
{
	return (bool)((buf->rx_buf_wp >= buf->rx_buf_rp) && (buf->carry > 0));
}

void buffer_forcePush(buffer_t *const buf, const buffer_element_t topush)
{
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\twp: %d cry: %d\r\n", buf->rx_buf_wp - buf->rx_buf, buf->carry);
	#endif
	*(buf->rx_buf_wp++) = (buffer_element_t)topush;
	if (buf->rx_buf_wp - buf->rx_buf >= BUFFER_SIZE) // 越过缓存边界
	{
		buf->rx_buf_wp = buf->rx_buf;
		buf->carry++;
	}
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\twp: %d cry: %d\r\n", buf->rx_buf_wp - buf->rx_buf, buf->carry);
	#endif
}

buffer_element_t buffer_forcePop(buffer_t *const buf)
{
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\trp: %d cry: %d diff: %d\r\n", buf->rx_buf_rp - buf->rx_buf, buf->carry, buf->rx_buf_wp - buf->rx_buf_rp);
	#endif
	buffer_element_t topop;
	topop = *(buf->rx_buf_rp++);
	if (buf->rx_buf_rp - buf->rx_buf >= BUFFER_SIZE) // 读指针超出缓冲区
	{
		buf->rx_buf_rp = buf->rx_buf;
		buf->carry--;
	}
	#ifdef __CIRCULAR_FIFO_DEBUG
	printf("\trp: %d cry: %d diff: %d\r\n", buf->rx_buf_rp - buf->rx_buf, buf->carry, buf->rx_buf_wp - buf->rx_buf_rp);
	#endif
	return topop;
}

bool buffer_push(buffer_t *const buf, const buffer_element_t topush)
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

bool buffer_pop(buffer_t *const buf, buffer_element_t *const p_topop)
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

char *buffer2str(char *const charbuffer, const buffer_t *const buf)
{
	sprintf(
		charbuffer,
		"buffer_t(wp=%+d, rp=%+d, cry=%d, Full=%d, Empty=%d)",
		buf->rx_buf_wp - buf->rx_buf,
		buf->rx_buf_rp - buf->rx_buf,
		buf->carry,
		buffer_isFull(buf),
		buffer_isEmpty(buf));
	return charbuffer;
}
