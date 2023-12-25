#ifndef RDS_PI_BUFFER_H
#define RDS_PI_BUFFER_H

#include <stdint.h>

class RdsPiBuffer
{
public:
    enum State : uint8_t
    {
        STATE_CORRECT     = 0,
        STATE_VERY_LIKELY = 1,
        STATE_LIKELY      = 2,
        STATE_UNLIKELY    = 3,
        STATE_INVALID     = 4
    };

    RdsPiBuffer();
    State add(uint16_t value, bool error);
    void clear();

private:
    /* BUFF_SIZE must be a multiple of 8 */
    static constexpr uint8_t BUFF_SIZE = 64;
    uint16_t buff[BUFF_SIZE];
    uint8_t errorBuff[BUFF_SIZE/8];
    uint8_t fill;
    uint8_t pos;

    State getState(uint16_t value);
};

#endif
