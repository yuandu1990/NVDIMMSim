/*********************************************************************************
*  Copyright (c) 2011-2012, Paul Tschirhart
*                             Peter Enns
*                             Jim Stevens
*                             Ishwar Bhati
*                             Mu-Tien Chang
*                             Bruce Jacob
*                             University of Maryland
*                             pkt3c [at] umd [dot] edu
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*     * Redistributions of source code must retain the above copyright notice,
*        this list of conditions and the following disclaimer.
*
*     * Redistributions in binary form must reproduce the above copyright notice,
*        this list of conditions and the following disclaimer in the documentation
*        and/or other materials provided with the distribution.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
*  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*********************************************************************************/

//Block.cpp
//Block functions

#include "Block.h"

using namespace std;
using namespace NVDSim;

Block::Block(uint block)
{
	block_num = block;
}

Block::Block()
{

}

void *Block::read(uint page_num)
{
	if (page_data.find(page_num) == page_data.end())
	{
		DEBUG("Request to read page "<<page_num<<" failed: nothing has been written to that address");
		return (void *)0x0;
	}
	else
	{
		return page_data[page_num];
	}
}

void Block::write(uint page_num, void *data)
{
	if (page_data.find(page_num) == page_data.end())
	{
		page_data[page_num]= data;
	}
	else
	{
		if(GARBAGE_COLLECT == 1)
		{
			ERROR("Request to write page "<<page_num<<" failed: page has been written to and not erased");
			exit(1);
		}
		else
		{
			page_data[page_num]= data;
		}
	}
}

void Block::erase()
{
	page_data.clear();
}



