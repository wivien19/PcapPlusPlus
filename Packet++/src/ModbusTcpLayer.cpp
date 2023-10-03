#include "../header/ModbusTcpLayer.h"
#include "EndianPortable.h"
#include "ModbusTcpLayer.h"
#include <PayloadLayer.h>
#include <cstring>
#include <iostream>
#include <sstream>

namespace pcpp
{
	pcpp::ModbusTcpLayer::ModbusTcpLayer(uint16_t transactionIdentifier, uint16_t length, uint8_t unitIdentifier,
										 uint8_t functionCode, uint16_t referenceNumber, uint16_t bitCount,
										 uint8_t byteCount, uint8_t data)
	{
		const size_t headerLen = sizeof(modbustcphdr);
		m_DataLen = headerLen;
		m_Data = new uint8_t[headerLen];
		memset(m_Data, 0, headerLen);
		modbustcphdr *modbusTcpHdr = (modbustcphdr *)m_Data;
		modbusTcpHdr->transactionIdentifier = htobe16(transactionIdentifier);
		modbusTcpHdr->protocolIdentifier = 0x00;
		modbusTcpHdr->length = htobe16(length);
		modbusTcpHdr->unitIdentifier = unitIdentifier;
		modbusTcpHdr->functionCode = functionCode;
		modbusTcpHdr->referenceNumber = htobe16(referenceNumber);
		modbusTcpHdr->bitCount = htobe16(bitCount);
		modbusTcpHdr->byteCount = byteCount;
		modbusTcpHdr->data = data;
		m_Protocol = MODBUSTCP;
	}

	std::string ModbusTcpLayer::toString() const
	{
		std::ostringstream str;

		str << "MODBUS TCP/ IP ADU Layer, "
			<< "transaction identifier: " << std::to_string(getTransactionIdentifier())
			<< ", length: " << std::to_string(getLength())
			<< ", unit identifier: " << std::to_string(getUnitIdentifier())
			<< ", function code: " << std::to_string(getFunctionCode())
			<< ", reference number: " << std::to_string(getReferenceNumber())
			<< ", bit count: " << std::to_string(getBitCount())
			<< ", byte count: " << std::to_string(getByteCount())
			<< ", data: " << std::to_string(getData());

		return str.str();
	}

	uint16_t ModbusTcpLayer::getTransactionIdentifier() const
	{
		return htobe16(getModbusTcpHeader()->transactionIdentifier);
	}

	uint16_t ModbusTcpLayer::getProtocolIdentifier() const { return htobe16(0x00); }

	uint16_t ModbusTcpLayer::getLength() const { return htobe16(getModbusTcpHeader()->length); }

	uint8_t ModbusTcpLayer::getUnitIdentifier() const { return getModbusTcpHeader()->unitIdentifier; }

	uint8_t ModbusTcpLayer::getFunctionCode() const { return getModbusTcpHeader()->functionCode; }

	uint16_t ModbusTcpLayer::getReferenceNumber() const { return htobe16(getModbusTcpHeader()->referenceNumber); }

	uint16_t ModbusTcpLayer::getBitCount() const { return htobe16(getModbusTcpHeader()->bitCount); }

	uint8_t ModbusTcpLayer::getByteCount() const { return getModbusTcpHeader()->byteCount; }

	uint8_t ModbusTcpLayer::getData() const { return getModbusTcpHeader()->data; }

	void ModbusTcpLayer::setTransactionIdentifier(uint16_t transactionIdentifier) const
	{
		getModbusTcpHeader()->transactionIdentifier = transactionIdentifier;
	}
	void ModbusTcpLayer::setLength(uint16_t length) const { getModbusTcpHeader()->length = length; }
	void ModbusTcpLayer::setUnitIdentifier(uint8_t unitIdentifier) const
	{
		getModbusTcpHeader()->unitIdentifier = unitIdentifier;
	}
	void ModbusTcpLayer::setFunctionCode(uint8_t functionCode) const
	{
		getModbusTcpHeader()->functionCode = functionCode;
	}
	void ModbusTcpLayer::setReferenceNumber(uint16_t referenceNumber) const
	{
		getModbusTcpHeader()->referenceNumber = referenceNumber;
	}
	void ModbusTcpLayer::setBitCount(uint16_t bitCount) const { getModbusTcpHeader()->bitCount = bitCount; }
	void ModbusTcpLayer::setByteCount(uint8_t byteCount) const { getModbusTcpHeader()->byteCount = byteCount; }
	void ModbusTcpLayer::setData(uint8_t data) const { getModbusTcpHeader()->data = data; }

	void ModbusTcpLayer::parseNextLayer()
	{
		size_t headerLen = getHeaderLen();
		if (m_DataLen <= headerLen)
			return;

		uint8_t *payload = m_Data + headerLen;
		size_t payloadLen = m_DataLen - headerLen;

		m_NextLayer = new PayloadLayer(payload, payloadLen, this, m_Packet);
	}
} // namespace pcpp
