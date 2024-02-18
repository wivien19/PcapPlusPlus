#include "PnDcpLayer.h"
#include "EndianPortable.h"
#include "EthLayer.h"
#include "PayloadLayer.h"
#include <iostream>
#include <sstream>
#include <string.h>

namespace pcpp
{
	PnDcpLayer::PnDcpLayer(uint16_t frameId, uint8_t serviceId, uint8_t serviceType, uint32_t xid,
						   uint16_t responseDelay, uint16_t dcpDataLength)
	{
		m_DataLen = sizeof(pndcphdr);
		m_Data = new uint8_t[m_DataLen];
		memset(m_Data, 0, m_DataLen);
		pndcphdr *pndcpHdr = getPnDcpHeader();
		pndcpHdr->frameId = htobe16(frameId);
		pndcpHdr->serviceId = serviceId;
		pndcpHdr->serviceType = serviceType;
		pndcpHdr->responseDelay = responseDelay;
		pndcpHdr->dcpDataLength = dcpDataLength;
		m_Protocol = PNDCP;
	}

	uint16_t PnDcpLayer::getFrameId() const { return htobe16(getPnDcpHeader()->frameId); }

	uint8_t PnDcpLayer::getServiceId() const { return getPnDcpHeader()->serviceId; }

	uint8_t PnDcpLayer::getServiceType() const { return getPnDcpHeader()->serviceType; }

	uint32_t PnDcpLayer::getXid() const { return htobe32(getPnDcpHeader()->xid); }

	uint16_t PnDcpLayer::getResponseDelay() const { return htobe16(getPnDcpHeader()->responseDelay); }

	uint16_t PnDcpLayer::getDcpDataLength() const { return htobe16(getPnDcpHeader()->dcpDataLength); }

	std::string PnDcpLayer::toString() const
	{
		std::ostringstream str;
		str << "frame id: " << std::to_string(getFrameId()) << ", service id: " << std::to_string(getServiceId())
			<< ", service type: " << std::to_string(getServiceType()) << ", xid: " << std::to_string(getXid())
			<< ", response delay: " << std::to_string(getResponseDelay())
			<< ", DPC data length: " << std::to_string(getDcpDataLength());

		return "PN-DCP Layer, " + str.str();
	}

	void PnDcpLayer::parseNextLayer()
	{
		size_t headerLen = getHeaderLen();
		if (m_DataLen <= headerLen)
			return;

		uint8_t *payload = m_Data + headerLen;
		size_t payloadLen = m_DataLen - headerLen;

		m_NextLayer = new PayloadLayer(payload, payloadLen, this, m_Packet);
	}

} // namespace pcpp
