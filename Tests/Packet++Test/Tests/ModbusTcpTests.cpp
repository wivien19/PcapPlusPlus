#include "../TestDefinition.h"
#include "../Utils/TestUtils.h"
#include "ModbusTcpLayer.h"
#include "Packet.h"
#include "SystemUtils.h"

using namespace std;

PTF_TEST_CASE(ModbusTcpLayerTest)
{
	timeval time;
	gettimeofday(&time, nullptr);

	READ_FILE_AND_CREATE_PACKET(1, "PacketExamples/modbus.dat");

	pcpp::Packet modbusTcpPacket(&rawPacket1);
	PTF_ASSERT_TRUE(modbusTcpPacket.isPacketOfType(pcpp::MODBUSTCP));
	auto modbusTcpLayer = modbusTcpPacket.getLayerOfType<pcpp::ModbusTcpLayer>();
	PTF_ASSERT_NOT_NULL(modbusTcpLayer);
	PTF_ASSERT_EQUAL(modbusTcpLayer->getTransactionIdentifier(), 0x57de);
	PTF_ASSERT_EQUAL(modbusTcpLayer->getProtocolIdentifier(), 0x00);
	PTF_ASSERT_EQUAL(modbusTcpLayer->getLength(), 0x0008);
	PTF_ASSERT_EQUAL(modbusTcpLayer->getUnitIdentifier(), 0xff);
	PTF_ASSERT_EQUAL(modbusTcpLayer->getFunctionCode(), 0x0f);
	PTF_ASSERT_EQUAL(modbusTcpLayer->getReferenceNumber(), 0x0005);
	PTF_ASSERT_EQUAL(modbusTcpLayer->getBitCount(), 0x0001);
	PTF_ASSERT_EQUAL(modbusTcpLayer->getByteCount(), 0x01);
	PTF_ASSERT_EQUAL(modbusTcpLayer->getData(), 0x00);
	PTF_ASSERT_EQUAL(modbusTcpLayer->toString(),
					 "MODBUS TCP/ IP ADU Layer, transaction identifier: 22494, length: 8, unit identifier: 255, "
					 "function code: 15, reference number: 5, bit count: 1, byte count: 1, data: 0");

	pcpp::ModbusTcpLayer newmodbusTcpPacket(0x56ab, 0x0009, 0xaa, 0x0b, 0x0006, 0x0003, 0x02, 0x01);
	PTF_ASSERT_EQUAL(newmodbusTcpPacket.getTransactionIdentifier(), 0x56ab);
	PTF_ASSERT_EQUAL(newmodbusTcpPacket.getProtocolIdentifier(), 0x00);
	PTF_ASSERT_EQUAL(newmodbusTcpPacket.getLength(), 0x0009);
	PTF_ASSERT_EQUAL(newmodbusTcpPacket.getUnitIdentifier(), 0xaa);

} // ModbusLayerTest
