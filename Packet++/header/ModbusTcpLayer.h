#ifndef PCAPPLUSPLUS_MODBUSLAYER_H
#define PCAPPLUSPLUS_MODBUSLAYER_H

#include "Layer.h"

namespace pcpp
{

/**
 * @struct modbustcphdr
 * Represents a MODBUS TCP/IP ADU protocol header
 */
#pragma pack(push, 1)
	typedef struct
	{
		/** Identification of a MODBUS Request / Response transaction */
		uint16_t transactionIdentifier;
		/** Protocol identifier, in this case the value is alway 0x00 */
		uint16_t protocolIdentifier;
		/** Number of following bytes */
		uint16_t length;
		/** Identification of a remote slave connected on a serial line or on other buses */
		uint8_t unitIdentifier;
		/** Function code */
		uint8_t functionCode;
		/** Reference number */
		uint16_t referenceNumber;
		/** Bit count */
		uint16_t bitCount;
		/** Byte count */
		uint8_t byteCount;
		/** Data */
		uint8_t data;

	} modbustcphdr;
#pragma pack(pop)

	/**
	 * @class ModbusTcpLayer
	 * Represents a MODBUS TCP/IP ADU
	 */
	class ModbusTcpLayer : public Layer
	{
	  public:
		/**
		 * A constructor that creates the layer from an existing packet raw data
		 * @param[in] data A pointer to the raw data (will be casted to @ref modbustcphdr)
		 * @param[in] dataLen Size of the data in bytes
		 * @param[in] prevLayer A pointer to the previous layer
		 * @param[in] packet A pointer to the Packet instance where layer will be stored in
		 */
		ModbusTcpLayer(uint8_t *data, size_t dataLen, Layer *prevLayer, Packet *packet)
			: Layer(data, dataLen, prevLayer, packet)
		{
			m_Protocol = MODBUSTCP;
		}

		/**
		 * A constructor that allocates a new MODBUS TCP/IP header
		 * @param[in] transactionIdentifier Identification of a MODBUS Request / Response transaction
		 * @param[in] length Number of following bytes
		 * @param[in] unitIdentifier Identification of a remote slave connected on a serial line or on other buses
		 * @param[in] functionCode Function code
		 * @param[in] referenceNumber Reference number
		 * @param[in] bitCount Bit count
		 * @param[in] byteCount Byte count
		 * @param[in] data Data
		 */
		ModbusTcpLayer(uint16_t transactionIdentifier, uint16_t length, uint8_t unitIdentifier, uint8_t functionCode,
					   uint16_t referenceNumber, uint16_t bitCount, uint8_t byteCount, uint8_t data);

		virtual ~ModbusTcpLayer() {}

		/**
		 * @return MODBUS TCP/IP Identification of a MODBUS Request / Response transaction
		 */
		uint16_t getTransactionIdentifier() const;

		/**
		 * @return MODBUS TCP/IP Protocol identifier
		 */
		uint16_t getProtocolIdentifier() const;

		/**
		 * @return MODBUS TCP/IP Number of following bytes
		 */
		uint16_t getLength() const;

		/**
		 * @return MODBUS TCP/IP Identification of a remote slave connected on a serial line or on other buses
		 */
		uint8_t getUnitIdentifier() const;

		/**
		 * @return MODBUS TCP/IP Function code
		 */
		uint8_t getFunctionCode() const;

		/**
		 * @return MODBUS TCP/IP Reference number
		 */
		uint16_t getReferenceNumber() const;

		/**
		 * @return MODBUS TCP/IP Bit count
		 */
		uint16_t getBitCount() const;

		/**
		 * @return MODBUS TCP/IP Byte count
		 */
		uint8_t getByteCount() const;

		/**
		 * @return MODBUS TCP/IP Data
		 */
		uint8_t getData() const;

		/**
		 * @return Size of @ref modbustcphdr
		 */
		size_t getHeaderLen() const override { return sizeof(modbustcphdr); }

		/**
		 * Set the value of the transaction identifier
		 * @param[in] transactionIdentifier The value of the transaction identifier
		 */
		void setTransactionIdentifier(uint16_t transactionIdentifier) const;

		/**
		 * Set the value of the length
		 * @param[in] length The value of the length
		 */

		void setLength(uint16_t length) const;

		/**
		 * Set the value of the unit identifier
		 * @param[in] unitIdentifier The value of the unit identifier
		 */
		void setUnitIdentifier(uint8_t unitIdentifier) const;

		/**
		 * Set the value of the function code
		 * @param[in] functionCode The value of the function code
		 */
		void setFunctionCode(uint8_t functionCode) const;

		/**
		 * Set the value of the reference number
		 * @param[in] referenceNumber The value of the reference number
		 */
		void setReferenceNumber(uint16_t referenceNumber) const;

		/**
		 * Set the value of the bit count
		 * @param[in] bitCount The value of the bit count
		 */
		void setBitCount(uint16_t bitCount) const;

		/**
		 * Set the value of the byte count
		 * @param[in] byteCount The value of the byte count
		 */
		void setByteCount(uint8_t byteCount) const;

		/**
		 * Set the value of the data
		 * @param[in] data The value of the data
		 */
		void setData(uint8_t data) const;

		/**
		 * A static method that checks whether a source or dest port match those associated with the MODBUS TCP/IP ADU
		 * protocol
		 * @param[in] portSrc Source port number to check
		 * @param[in] portDst Dest port number to check
		 * @return True if the source or dest port match those associated with the MODBUS TCP/IP ADU protocol
		 */
		static bool isModbusTcpPort(uint16_t portSrc, uint16_t portDst) { return portSrc == 502 || portDst == 502; }

		/**
		 * A static method that takes a byte array and detects whether it is a MODBUS TCP/IP ADU message
		 * @param[in] data A byte array
		 * @param[in] dataSize The byte array size (in bytes)
		 * @return True if the data size is greater or equal than the size of tpkthdr
		 */
		static bool isDataValid(const uint8_t *data, size_t dataSize)
		{
			return data && dataSize >= sizeof(modbustcphdr);
		}
		/**
		 * Does nothing for this layer
		 */
		void computeCalculateFields() override {}

		/**
		 * Currently parses the rest of the packet as a generic payload (PayloadLayer)
		 */
		void parseNextLayer() override;

		std::string toString() const override;

		OsiModelLayer getOsiModelLayer() const override { return OsiModelTransportLayer; }

	  private:
		modbustcphdr *getModbusTcpHeader() const { return (modbustcphdr *)m_Data; }
	};

} // namespace pcpp

#endif // PCAPPLUSPLUS_MODBUSLAYER_H
