/*
 | Author: Michael Schmidt;
 |         Gunnar Jehl (multi-step paths/aggregate functions/optimizations) 
 ===========================================================================
 ===========================================================================
 | Software License Agreement (BSD License)
 | 
 | Copyright (c) 2006-2007, Saarland University Database Group 
 | All rights reserved.
 |
 | Redistribution and use of this software in source and binary forms,
 | with or without modification, are permitted provided that the following
 | conditions are met:
 | 
 | * Redistributions of source code must retain the above
 |   copyright notice, this list of conditions and the
 |   following disclaimer.
 |
 | * Redistributions in binary form must reproduce the above
 |   copyright notice, this list of conditions and the
 |   following disclaimer in the documentation and/or other
 |   materials provided with the distribution.
 |
 | * Neither the name the of Saarland University Database Group nor the names 
 |   of its contributors may be used to endorse or promote products derived 
 |   from this software without specific prior written permission of the
 |   Saarland University Database Group.
 | 
 | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 | AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 | IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 | ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 | LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 | CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 | SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 | INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 | CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 | ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 | POSSIBILITY OF SUCH DAMAGE.
*/
/*! @file
 * 	@brief Implementations of header file constexpression.h.
 * 	@details Implementations of constructors, destructor and functions of the corresponding header file constexpression.h.
 * 	@author Michael Schmidt
 *  @author Gunnar Jehl (multi-step paths/aggregate functions/optimizations)
 * 	@version 1.01b
 * 	@license Software License Agreement (BSD License)
 */
#include "constexpression.h"

ConstExpression::ConstExpression(const char* _text) :
Expression(et_const) {

	// we replace special signs, namely: < -> &lt and > -> &gt;
	ostringstream s;
	for (unsigned i=0;i<strlen(_text);i++) {
		if (_text[i]=='<') {
			s << "&lt;";
		} else if (_text[i]=='>') {
			s << "&gt;";
		} else {
			s << _text[i];
		}
	}
	text=strdup(s.str().c_str());
	delete[] _text;
}

ConstExpression::~ConstExpression() {
	free((char*)text);
}

void ConstExpression::print(ostream& o) const {
	o << "\"" << text << "\"";
}

void* ConstExpression::eval(Environment* env, unsigned modus) {

	switch (modus) {
		case EVAL_QUERY:
			cout << text;
			break;

		case EVAL_QUERY_SILENT:
			return (void*)text;
			break;

		case EVAL_SIGNOFF: // nothing to do here
			break;	
	}
	
	return NULL; 
}
