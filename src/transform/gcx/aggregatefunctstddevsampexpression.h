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
 * 	@brief Header file for aggregatefunctstddevsampexpression.cpp.
 * 	@details Header file specifying constructors, destructor and functions for aggregatefunctstddevsampexpression.cpp.
 * 	@author Michael Schmidt
 *  @author Gunnar Jehl (multi-step paths/aggregate functions/optimizations)
 *  @version 1.01b
 * 	@license Software License Agreement (BSD License)
 */
#ifndef AGGREGATEFUNCTSTDDEVSAMPEXPRESSION_H
#define AGGREGATEFUNCTSTDDEVSAMPEXPRESSION_H

#include "aggregatefunctexpression.h"

/*! @def OUTPUT_STDDEVSAMP_ON_EMPTY_SEQUENCE
 *  @brief The value which is outputted or returned respectively if the argument of aggregate
 * 			function <tt>fn:stddev_samp</tt> contains no items, i.e. is called on an empty sequence.
 *  @details The value which is outputted or returned respectively if the argument of aggregate
 * 			function <tt>fn:stddev_samp</tt> contains no items, i.e. is called on an empty sequence.
 */
#define OUTPUT_STDDEVSAMP_ON_EMPTY_SEQUENCE ""

/*! @class AggregateFunctStdDevSampExpression
 * 	@brief Represents XQuery non-standard function <tt>fn:stddev_samp</tt>.
 * 	@details Represents XQuery non-standard function <tt>fn:stddev_samp</tt>, which takes either
 * 			a VarExpression, e.g. <tt>fn:stddev_samp(\$x)</tt>, or a VarStepExpression, e.g.
 * 			<tt>fn:stddev_samp(\$x/bib/book)</tt> or <tt>fn:stddev_samp(/bib//book)</tt> respectively,
 * 			as argument and returns the sample standard deviation of the sequence located through
 * 			the entered VarExpression or the entered VarStepExpression respectively.
 * 	@author Michael Schmidt
 *  @author Gunnar Jehl (multi-step paths/aggregate functions/optimizations)
 * 	@version 1.01b
 * 	@license Software License Agreement (BSD License)
 */
class AggregateFunctStdDevSampExpression : public AggregateFunctExpression {

public:
	/*! @brief Constructor.
	 * 	@details Constructor - creating object for a VarExpression.
	 * 	@param[in] _var Pointer to a VarExpression object.
	 */
	AggregateFunctStdDevSampExpression(VarExpression* _var);
	
	/*! @brief Constructor.
	 * 	@details Constructor - creating object for a VarStepExpression.
	 * 	@param[in] _varstep Pointer to a VarStepExpression object.
	 */
	AggregateFunctStdDevSampExpression(VarStepExpression* _varstep);
	
	/*! @brief Destructor.
	 * 	@details Destructor.
	 */
	virtual ~AggregateFunctStdDevSampExpression();
    
	/*! @fn virtual void* eval(Environment* env, unsigned modus)
	 *  @copydoc AggregateFunctExpression::eval(Environment* env, unsigned modus)
	 *  @exception Error if either the VarExpression or VarStepExpression argument in
	 * 			XQuery function <tt>fn:stddev_samp</tt> was not rewritten into a ForExpression
	 * 			or if it is not possible to cast all affected PCDATA values of an XML document
	 * 			to numeric values or some value calculation will cause an (internal) error.
	 */
    virtual void* eval(Environment* env, unsigned modus);
};

#endif // AGGREGATEFUNCTSTDDEVSAMPEXPRESSION_H
