#include "../TestDefinition.h"
#include "../Utils/TestUtils.h"
#include "EndianPortable.h"
#include "HartIp.h"
#include "Packet.h"
#include "SystemUtils.h"
#include <iostream>

PTF_TEST_CASE(HartIpTests)
{
	timeval time;
	gettimeofday(&time, nullptr);

	READ_FILE_AND_CREATE_PACKET(1, "PacketExamples/HartIp.dat");

	pcpp::Packet HartIpTest(&rawPacket1);
	PTF_ASSERT_TRUE(HartIpTest.isPacketOfType(pcpp::HARTIP));
	auto hartIp = HartIpTest.getLayerOfType<pcpp::HartIp>();
	PTF_ASSERT_NOT_NULL(hartIp);

	PTF_ASSERT_EQUAL(hartIp->getVersion(), 1);
	PTF_ASSERT_EQUAL(hartIp->getMsgType(), 0);
	PTF_ASSERT_EQUAL(hartIp->getMsgId(), 0);
	PTF_ASSERT_EQUAL(hartIp->getStatus(), 0);
	PTF_ASSERT_EQUAL(hartIp->getSeqNum(), 2);
	PTF_ASSERT_EQUAL(hartIp->getByteCount(), 13);

	PTF_ASSERT_EQUAL(
		hartIp->toString(),
		"HART-IP, version: 1, message type: request, message id: session initiate, status: 0, sequence number: 2");

} // HartIpTests
