/*
 * SlipPacket.cpp
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

#include "slippacket.h"

#include <iostream>
#include <sstream>
#include <string>


#define SLIP_MAX_LENGTH (512)



SlipPacket::SlipPacket(const data_t& data, bool isPayload)
{
    if(isPayload)
    {
        mPayload = data;
        mPacket.reserve(SLIP_MAX_LENGTH);
        Encode();
    }
    else
    {
        if((data[0] == frame_boundary_octet) && (data[data.size() - 1] == frame_boundary_octet))
        {
            mPacket = data;
            mPayload.reserve(SLIP_MAX_LENGTH);
            Decode();
        }
        else
        {
            throw std::runtime_error("Not a valid slip packet.");
        }
    }

}

SlipPacket::~SlipPacket()
{
}

SlipPacket::data_t& SlipPacket::GetPayload()
{
    return mPayload;
}
SlipPacket::data_t& SlipPacket::GetPacket()
{
    return mPacket;
}

bool SlipPacket::Encode()
{
    if(mPacket.size() != 0)
    {
        throw std::runtime_error("Packet not empty when encoding!");
    }
    mPacket.push_back(SlipControlOctets::frame_boundary_octet);

    uint16_t i;
    for ( i = 0; i < (mPayload.size()); i++)
    {
        if ( mPayload[i] == frame_boundary_octet )
        {
            mPacket.push_back(control_escape_octet);
            mPacket.push_back(frame_boundary_octet_replacement);
        }
        else if ( mPayload[i] == control_escape_octet )
        {
            mPacket.push_back(control_escape_octet);
            mPacket.push_back(control_escape_octet_replacement);
        }
        else
        {
            mPacket.push_back(mPayload[i]);
        }
    }
    mPacket.push_back(frame_boundary_octet);

    return true;
}

bool SlipPacket::Decode()
{
    uint16_t k;
    if(mPacket[0] != SlipControlOctets::frame_boundary_octet)
    {
        throw std::runtime_error("Not a valid Slip Packet");
    }
    if(mPayload.size() != 0)
    {
        throw std::runtime_error("Payload not empty when decoding!");
    }
    for (k = 1; k < (mPacket.size() - 1); k++ )
    {
        if ( mPacket[k] == control_escape_octet )
        {
            k++;
            if ( mPacket[k] == control_escape_octet_replacement )
            {
                mPayload.push_back(control_escape_octet);
            }
            else if ( mPacket[k] == frame_boundary_octet_replacement )
            {
                mPayload.push_back(frame_boundary_octet);
            }
            else
            {
                throw std::runtime_error("Not a valid Slip Packet");
            }
        }
        else
        {
            mPayload.push_back(mPacket[k]);
        }
    }
    return true;
}
