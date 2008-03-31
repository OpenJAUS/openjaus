/*****************************************************************************
 *  Copyright (c) 2006, University of Florida.
 *  All rights reserved.
 *  
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
 *  license.  See the LICENSE file for details.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
// File Name: jausIntegerPrescenceVector.c
//
// Written By: 	Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the JAUS Presence Vector class and its associated methods.  
// JausPresenceVector is to be nested with JAUS message classes that contain a Presence
// Vector field and is used to test for the presence of absence of a field of interest
//
// A JAUS Presence Vector can be a byte, an unsigned short or an unsigned integer.
//

#include "jaus.h"

JausUnsignedInteger newJausUnsignedInteger(void)
{
	JausUnsignedInteger vector;
	
	vector = newJausUnsignedInteger(0xFFFFFFFF);
	
	return vector;
}

JausBoolean jausUnsignedIntegerFromBuffer(JausUnsignedInteger *input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	return jausUnsignedIntegerFromBuffer(input, buf, bufferSizeBytes);
}

JausBoolean jausUnsignedIntegerToBuffer(JausUnsignedInteger input, unsigned char *buf, unsigned int bufferSizeBytes)
{
	return jausUnsignedIntegerToBuffer(input, buf, bufferSizeBytes);
}

JausBoolean jausUnsignedIntegerIsBitSet(JausUnsignedInteger input, int bit)
{
	return jausUnsignedIntegerIsBitSet(input, bit);
}

JausBoolean jausUnsignedIntegerSetBit(JausUnsignedInteger *input, int bit)
{
	return jausUnsignedIntegerSetBit(input, bit);
}

JausBoolean jausUnsignedIntegerClearBit(JausUnsignedInteger *input, int bit)
{
	return jausUnsignedIntegerClearBit(input, bit);
}
