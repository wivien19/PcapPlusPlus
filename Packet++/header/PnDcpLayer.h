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
	 * @struct pndcphdr
	 * Represents a PN-DCP protocol header
	 */
#pragma pack(push, 1)
	struct pndcphdr
	{
		/** frame id */
		uint16_t frameId;
		/** service id */
		uint8_t serviceId;
		/** service tyoe */
		uint8_t serviceType;
		/** identification of the transaction */
		uint32_t xid;
		/** response delay*/
		uint16_t responseDelay;
		/** number of bytes in subsequent blocks */
		uint16_t dcpDataLength;
	};
#pragma pack(pop)

	/**
	 * @class pndcpLayer
	 * Represents a PN-DCP (Transport Service on top of the TCP) protocol layer
	 */
	class PnDcpLayer : public Layer
	{
	  public:
		/**
		 * A constructor that creates the layer from an existing packet raw data
		 * @param[in] data A pointer to the raw data (will be casted to @ref pndcphdr)
		 * @param[in] dataLen Size of the data in bytes
		 * @param[in] prevLayer A pointer to the previous layer
		 * @param[in] packet A pointer to the Packet instance where layer will be stored in
		 */
		PnDcpLayer(uint8_t *data, size_t dataLen, Layer *prevLayer, Packet *packet)
			: Layer(data, dataLen, prevLayer, packet)
		{
			m_Protocol = PNDCP;
		}

		/**
		 * A constructor that allocates a new PN-DCP headers
		 * @param[in] frameId Reserved area for the DCP
		 * @param[in] serviceId Service id: get(1), set(2), identify(5)
		 * @param[in] serviceType Type of the service
		 * @param[in] xid Identification of the transaction
		 * @param[in] responseDelay Delay of the response
		 * @param[in] dcpDataLength Number of bytes in subsequent blocks
		 */
		PnDcpLayer(uint16_t frameId, uint8_t serviceId, uint8_t serviceType, uint32_t xid, uint16_t responseDelay,
				   uint16_t dcpDataLength);

		virtual ~PnDcpLayer() {}

		/**
		 * @return PN-DCP frame id
		 */
		uint16_t getFrameId() const;

		/**
		 * @return PN-DCP service id
		 */
		uint8_t getServiceId() const;

		/**
		 * @return PN-DCP service type
		 */
		uint8_t getServiceType() const;

		/**
		 * @return PN-DCP xid
		 */
		uint32_t getXid() const;

		/**
		 * @return PN-DCP response delay
		 */
		uint16_t getResponseDelay() const;

		/**
		 * @return PN-DCP DCP data length
		 */
		uint16_t getDcpDataLength() const;

		/**
		 * @return Size of @ref pndcphdr
		 */
		size_t getHeaderLen() const override { return sizeof(pndcphdr); }

		/**
		 * Does nothing for this layer
		 */
		void computeCalculateFields() override {}

		/**
		 * Does nothing for this layer
		 */
		void parseNextLayer() override;

		/**
		 * A static method that takes a byte array and detects whether it is a PN-DCP message
		 * @param[in] data A byte array
		 * @param[in] dataSize The byte array size (in bytes)
		 * @return True if the data size is greater or equal than the size of pndcphdr and has the right frame number
		 */
		static bool isDataValid(const uint8_t *data, size_t dataSize)
		{
			return data && data[0] == 0xfe && (data[1] == 0xfd || data[1] == 0xfe || data[1] == 0xff) &&
				   dataSize >= sizeof(pndcphdr);
		}

		std::string toString() const override;

		OsiModelLayer getOsiModelLayer() const override { return OsiModelTransportLayer; }

	  private:
		/**
		 * Get a pointer to the PN-DCP header. Data can be retrieved through the
		 * other methods of this layer. Notice the return value points directly to the data, so every change will change
		 * the actual packet data
		 * @return A pointer to the @ref pndcphdr
		 */
		pndcphdr *getPnDcpHeader() const { return (pndcphdr *)m_Data; }
	};

} // namespace pcpp
