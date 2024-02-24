#pragma once

#include "EthLayer.h"
#include "Layer.h"

/// @file

/**
 * \namespace pcpp
 * \brief The main namespace for the PcapPlusPlus lib
 */
namespace pcpp
{

	/**
	 * @struct hartiphdr
	 * Represents a HART-IP protocol header
	 */
#pragma pack(push, 1)
	struct hartiphdr
	{
		/** version */
		uint8_t version;
		/** message type */
		uint8_t msgType;
		/** message identifier */
		uint8_t msgId;
		/** status */
		uint8_t status;
		/** sequence number */
		uint16_t seqNum;
		/** byte count */
		uint16_t byteCount;
	};
#pragma pack(pop)

	/**
	 * @class HartIp
	 * Represents a HART-IP (Highway Addressable Remote Transducer over IP) protocol
	 */
	class HartIp : public Layer
	{
	  public:
		/**
		 * A constructor that creates the layer from an existing packet raw data
		 * @param[in] data A pointer to the raw data (will be casted to @ref hartip)
		 * @param[in] dataLen Size of the data in bytes
		 * @param[in] prevLayer A pointer to the previous layer
		 * @param[in] packet A pointer to the Packet instance where layer will be stored in
		 */
		HartIp(uint8_t *data, size_t dataLen, Layer *prevLayer, Packet *packet)
			: Layer(data, dataLen, prevLayer, packet)
		{
			m_Protocol = HARTIP;
		}

		/**
		 * A constructor that allocates a new HART-IP header
		 * @param[in] version Protocol version number
		 * @param[in] msgType Request(0), response(1), publish(2), NAK(15)
		 * @param[in] msgId Session Initiate(0), Session Close(1), Keep Alive(2), HART Token-Passing PDU (3)
		 * @param[in] status Indicades communication status for the HART-IP message
		 * @param[in] seqNum Unique sequence number for mapping a response to a request
		 * @param[in] byteCount Number of bytes in the message including message header and body
		 */
		HartIp(uint8_t version, uint8_t msgType, uint8_t msgId, uint8_t status, uint16_t seqNum, uint16_t byteCount);

		virtual ~HartIp() {}

		/**
		 * @return HART-IP protocol version number
		 */
		uint8_t getVersion() const;

		/**
		 * @return HART-IP reserved
		 */
		uint8_t getMsgType() const;

		/**
		 * @return HART-IP message id (request, response, publish, NAK)
		 */
		uint8_t getMsgId() const;

		/**
		 * @return HART-IP communication status for the message
		 */
		uint8_t getStatus() const;

		/**
		 * @return HART-IP unique sequence number
		 */
		uint16_t getSeqNum() const;

		/**
		 * @return HART-IP number of bytes
		 */
		uint16_t getByteCount() const;

		/**
		 * @return Size of @ref hartiphdr
		 */
		size_t getHeaderLen() const override { return sizeof(hartiphdr); }

		/**
		 * Does nothing for this layer
		 */
		void computeCalculateFields() override {}

		/**
		 * Does nothing for this layer
		 */
		void parseNextLayer() override {}

		/**
		 * A static method that checks whether a source or dest port match those associated with the HART-IP protocol
		 * @param[in] portSrc Source port number to check
		 * @param[in] portDst Dest port number to check
		 * @return True if the source or dest port match those associated with the HART-IP protocol
		 */
		static bool isHartIpPort(uint16_t port) { return port == 5094; }

		/**
		 * A static method that takes a byte array and detects whether it is a HART-IP message
		 * @param[in] data A byte array
		 * @param[in] dataSize The byte array size (in bytes)
		 * @return True if the data size is greater or equal than the size of hartiphdr
		 */
		static bool isDataValid(const uint8_t *data, size_t dataSize) { return data && dataSize >= sizeof(hartiphdr); }

		std::string toString() const override;

		OsiModelLayer getOsiModelLayer() const override { return OsiModelTransportLayer; }

	  private:
		/**
		 * Get a pointer to the HART-IP header. Data can be retrieved through the
		 * other methods of this layer. Notice the return value points directly to the data, so every change will change
		 * the actual packet data
		 * @return A pointer to the @ref hartiphdr
		 */
		hartiphdr *getHartIpHeader() const { return (hartiphdr *)m_Data; }
	};

} // namespace pcpp
