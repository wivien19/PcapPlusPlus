#include "../TestDefinition.h"
#include "../Utils/TestUtils.h"
#include "EndianPortable.h"
#include "Packet.h"
#include "PnDcpLayer.h"
#include "SystemUtils.h"
#include <iostream>

PTF_TEST_CASE(PnDcpTest)
{
	timeval time;
	gettimeofday(&time, nullptr);

	READ_FILE_AND_CREATE_PACKET(1, "PacketExamples/PnDcp.dat");

	pcpp::Packet PnDcpPacket(&rawPacket1);
	PTF_ASSERT_TRUE(PnDcpPacket.isPacketOfType(pcpp::PNDCP));
	auto pnDcpLayer = PnDcpPacket.getLayerOfType<pcpp::PnDcpLayer>();
	PTF_ASSERT_NOT_NULL(pnDcpLayer);

	PTF_ASSERT_EQUAL(pnDcpLayer->getFrameId(), 65278);
	PTF_ASSERT_EQUAL(pnDcpLayer->getServiceId(), 5);
	PTF_ASSERT_EQUAL(pnDcpLayer->getServiceType(), 0);
	PTF_ASSERT_EQUAL(pnDcpLayer->getXid(), 16777217);
	PTF_ASSERT_EQUAL(pnDcpLayer->getResponseDelay(), 1);
	PTF_ASSERT_EQUAL(pnDcpLayer->getDcpDataLength(), 4);
	PTF_ASSERT_EQUAL(pnDcpLayer->toString(), "PN-DCP Layer, frame id: 65278, service id: 5, service type: 0, xid: "
											 "16777217, response delay: 1, DPC data length: 4");

} // PnDcpTest
