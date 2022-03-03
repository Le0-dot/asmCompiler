//////////////////////////////////////////////////////////////////////
//
//  stmt -> op endline
//
//  op -> add_op  |
//	  and_op  |
//	  ld_op   |
//	  ldi_op  |
//	  ldr_op  |
//	  lea_op  |
//	  not_op  |
//	  st_op   |
//	  sti_op  |
//	  str_op  |
//	  jmp_op  |
//	  jsr_op  |
//	  br_op   |
//	  trap_op |
//	  halt_op
//
//  add_op -> add reg reg reg |
//	      add reg reg num5
//
//  and_op -> and reg reg reg |
//	      and reg reg num5
//
//  ld_op -> ld reg num9
//
//  ldi_op -> ldi reg num9
//
//  ldr_op -> ldr reg num3 num6
//
//  lea_op -> lea reg num9
//
//  not_op -> not reg reg
//
//  st_op -> st reg num9
//
//  sti_op -> sti reg num9
//
//  str_op -> str reg num3 num6
//
//  jmp_op -> jmp num3
//
//  jsr_op -> jsr num11 |
//	      jsrr num3
//
//  br_op -> br num3 num9
//
//  trap_op -> trap trapvect
//
//  halt_op -> halt
//
///////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <memory>

#include "word/words.hpp"
#include "logging_queue.hpp"

template<typename bits>
class parser
{
    private:
	using iqueue = logging_queue<std::shared_ptr<word>>;
	using oqueue = logging_queue<bits>;

	iqueue& input_queue;
	oqueue& output_queue;

    public:
	parser(iqueue& input_queue, oqueue& output_queue) :
	    input_queue{input_queue}, output_queue{output_queue} {}

	void run()
	{

	}
};
