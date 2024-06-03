#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include "../Project1/deviceDriver.cpp"
#include "../Project1/flashmemorydevice.h"
#include "test.h"
#include "../Project1/myException.h"
#include <stdexcept>

#define interface struct;



using namespace testing;
using namespace std;



class FlashMemoryMock :public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), ());
	MOCK_METHOD(void, write, (long address, unsigned char data), ());
	
};

TEST(Testdevicedriver, TestRead_Normal) {
	FlashMemoryDevice * flashM = new FlashMemoryMock();
	DeviceDriver dev(flashM);

	EXPECT_CALL(*(FlashMemoryMock*)flashM, read(1)).WillRepeatedly(Return(0));
	int ret = dev.read(1);
	EXPECT_EQ(ret, 0);
}

TEST(Testdevicedriver, TestRead_5timesCall) {
	FlashMemoryDevice* flashM = new FlashMemoryMock();

	EXPECT_CALL(*(FlashMemoryMock *)flashM, read(1)).Times(5).WillRepeatedly(Return(0));
	
	DeviceDriver dev(flashM);
	int ret = dev.read(1);
	EXPECT_EQ(ret, 0);
}

TEST(Testdevicedriver, TestRead_failRead) {
	FlashMemoryDevice* flashM = new FlashMemoryMock();

	EXPECT_CALL(*(FlashMemoryMock*)flashM, read(1)).WillOnce(Return(3)).WillRepeatedly(Return(0));


	DeviceDriver dev(flashM);
	EXPECT_THROW(dev.read(1), ReadFailException);
}


TEST(Testdevicedriver, TestWrite_normal) {
	FlashMemoryDevice* flashM = new FlashMemoryMock();

	EXPECT_CALL(*(FlashMemoryMock*)flashM, read(1)).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(*(FlashMemoryMock*)flashM, write(1, 4)).Times(1);

	DeviceDriver dev(flashM);
	dev.write(1, 4);
}

TEST(Testdevicedriver, TestWrite_failWrite) {
	FlashMemoryDevice* flashM = new FlashMemoryMock();

	EXPECT_CALL(*(FlashMemoryMock*)flashM, read(1)).WillRepeatedly(Return(3));
	EXPECT_CALL(*(FlashMemoryMock*)flashM, write(1, 4)).Times(0);

	DeviceDriver dev(flashM);
	EXPECT_THROW(dev.write(1, 4), WriteFailException);
}