#include "RdsPiBuffer.hpp"

RdsPiBuffer::RdsPiBuffer()
{
    this->clear();
}

RdsPiBuffer::State
RdsPiBuffer::add(uint16_t value,
                 bool     error)
{
    this->pos = (this->pos + 1) % BUFF_SIZE;
    this->buff[this->pos] = value;

    const uint8_t errorPos = this->pos / 8;
    const uint8_t errorBitPos = this->pos % 8;

    if (error)
    {
        this->errorBuff[errorPos] |= (1 << errorBitPos);
    }
    else
    {
        this->errorBuff[errorPos] &= ~(1 << errorBitPos);
    }

    if (this->fill < BUFF_SIZE)
    {
        this->fill++;
    }

    return this->getState(value);
}

void
RdsPiBuffer::clear()
{
    this->fill = 0;
    this->pos = (uint8_t)-1;
}

RdsPiBuffer::State
RdsPiBuffer::getState(uint16_t value)
{
    uint8_t count = 0;
    uint8_t correctCount = 0;

    for (uint8_t i = 0; i < this->fill; i++)
    {
        if (this->buff[i] == value)
        {
            count++;
            if ((this->errorBuff[i / 8] & (1 << (i % 8))) == 0)
            {
                correctCount++;
            }
        }
    }

    if (correctCount >= 2)
    {
        return STATE_CORRECT;
    }
    else if (count >= 2 && correctCount)
    {
        return STATE_VERY_LIKELY;
    }
    else if (count >= 3)
    {
        return STATE_LIKELY;
    }
    else if (count == 2 || correctCount)
    {
        return STATE_UNLIKELY;
    }

    return STATE_INVALID;
}
