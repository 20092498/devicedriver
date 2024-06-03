#include "DeviceDriver.h"
#include <stdexcept>
#include "myException.h"


DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{

}

int DeviceDriver::read(long address)
{
    int checker[5] = {};

    for (int cnt = 0; cnt < 5; cnt++)
    {
        checker[cnt] = (int)(m_hardware->read(address));
    }

    int readVal = checker[0];

    for (int cnt = 1; cnt < 5; cnt++)
    {
        if (checker[cnt] != readVal)
            throw ReadFailException("read fail");
    }

    // TODO: implement this method properly
    return readVal;
}

void DeviceDriver::write(long address, int data)
{
    int val = read(address);

    if (val != 0xFF)
    {
        throw WriteFailException("write fail");
    }

    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}