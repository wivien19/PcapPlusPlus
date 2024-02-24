#include "HartIp.h"
#include "EndianPortable.h"
#include "PayloadLayer.h"
#include "TcpLayer.h"
#include <iostream>
#include <sstream>
#include <string.h>

namespace pcpp
{
	HartIp::HartIp(uint8_t version, uint8_t msgType, uint8_t msgId, uint8_t status, uint16_t seqNum, uint16_t byteCount)
	{
		m_DataLen = sizeof(hartiphdr);
		m_Data = new uint8_t[m_DataLen];
		memset(m_Data, 0, m_DataLen);
		hartiphdr *hartIpHdr = getHartIpHeader();
		hartIpHdr->version = version;
		hartIpHdr->msgType = msgType;
		hartIpHdr->status = status;
		hartIpHdr->seqNum = seqNum;
		hartIpHdr->byteCount = byteCount;
		m_Protocol = HARTIP;
	}

	uint8_t HartIp::getVersion() const { return getHartIpHeader()->version; }
	uint8_t HartIp::getMsgType() const { return getHartIpHeader()->msgType; }
	uint8_t HartIp::getMsgId() const { return getHartIpHeader()->msgId; }
	uint8_t HartIp::getStatus() const { return getHartIpHeader()->status; }
	uint16_t HartIp::getSeqNum() const { return be16toh(getHartIpHeader()->seqNum); }
	uint16_t HartIp::getByteCount() const { return be16toh(getHartIpHeader()->byteCount); }

	std::string HartIp::toString() const
	{
		std::ostringstream str;

		str << "HART-IP, ";
		str << "version: " << std::to_string(getVersion()) << ", message type: ";

		switch (getHartIpHeader()->msgType)
		{
		case 0x00:
			str << "request";
			break;
		case 0x01:
			str << "response";
			break;
		case 0x02:
			str << "publish";
			break;
		case 0x0f:
			str << "NAK";
			break;
		default:
			str << "unknown message type";
		}

		str << ", message id: ";

		switch (getHartIpHeader()->msgId)
		{
		case 0x00:
			str << "session initiate";
			break;
		case 0x01:
			str << "session close";
			break;
		case 0x02:
			str << "keep alive";
			break;
		case 0x0f:
			str << "HART token-passing PDU";
			break;
		default:
			str << "unknown message id";
		}
		str << ", status: ";

		str << std::to_string(getStatus()) << ", sequence number: ";
		str << std::to_string(getSeqNum());

		return str.str();
	}

} // namespace pcpp
