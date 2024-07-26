/*
 * SlipPacket.h
 *
 * Copyright (C) 2015 Martin Lundh
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef SLIPPACKET_H
#define SLIPPACKET_H

#include <memory>
#include <string.h>
#include <vector>
#include <QByteArray>


class SlipPacket
{
public:

  enum SlipControlOctets
  {
    frame_boundary_octet = 0x7E,
    frame_boundary_octet_replacement = 0x5E,
    control_escape_octet = 0x7D,
    control_escape_octet_replacement = 0x5D
  };
    /**
     * typedefed handle to a slip packet.
     */
    typedef QByteArray data_t;

    /**
     * @brief Get the Payload carried in the packet.
     * @return A pointer to the decoded payload.
     */
    data_t& GetPayload();

    /**
     * @brief Get the slip packet that contains the payload.
     * @return A pointer to the encoded packet.
     */
    data_t& GetPacket();

    /**
     * @brief destructor.
     */
    virtual ~SlipPacket();

    SlipPacket(const data_t& data, bool isPayload);
private:

    /**
     * @brief Encode the payload.
     * @return True if success.
     */
    bool Encode();

    /**
     * @brief Decode the packet.
     * @return True if success.
     */
    bool Decode();

    data_t mPayload;
    data_t mPacket;
};
#endif // SLIPPACKET_H
