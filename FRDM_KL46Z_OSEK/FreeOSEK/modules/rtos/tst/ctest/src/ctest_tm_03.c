/* Copyright 2008, 2009 Mariano Cerdeiro
 * Copyright 2014, ACSE & CADIEEL
 *      ACSE: http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *      CADIEEL: http://www.cadieel.org.ar
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief FreeOSEK Os Conformance Test for the Task Managment, Test Sequence 3
 **
 ** \file FreeOSEK/Os/tst/ctest/src/ctest_tm_03.c
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT Conformance Test
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT_TM Task Management
 ** @{ */
/** \addtogroup FreeOSEK_Os_CT_TM_03 Test Sequence 3
 ** @{ */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090413 v0.1.0 MaCe initial version based on old moduletest
 */

/*==================[inclusions]=============================================*/
#include "os.h"            /* include os header file */
#include "ctest_tm_03.h"   /* include test header file */
#include "ctest.h"         /* include ctest header file */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
const uint32f SequenceCounterOk = MAX_SEQUENCE;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int main
(
   void
)
{
   /* start OS in AppMode 1 */
   StartOS(AppMode1);

   /* shall never return */
   while(1);

   return 0;
}

TASK(Task1)
{
   StatusType ret;

   ASSERT(OTHER, 0);

   Sequence(0);
   /* \treq TM_03 mf B1B2E1E2 se Call ActivateTask() from preemptive
    * task on suspend basic task which has higher priority than running
    * task
    *
    * \result Runnin task is preempted. Activated task becomes ready.
    * Service returns E_OK
    */
   ret = ActivateTask(Task3);
   ASSERT(TM_03, ret != E_OK);

   Sequence(4);

   /* evaluate conformance tests */
   ConfTestEvaluation();

   /* finish the conformance test */
   ConfTestFinish();
}

TASK(Task2)
{
   Sequence(3);
   TerminateTask();
}

TASK(Task3)
{
   StatusType ret;

   Sequence(1);
   /* \treq TM_04 mf B1B2E1E2 se Call ActivateTask() from preemptive
    * task on suspend basic task which has lower priority than running
    * task
    *
    * \result Non preemption of running task. Activated task becomes ready.
    * Service returns E_OK
    */
   ret = ActivateTask(Task2);
   ASSERT(TM_04, ret != E_OK);

   Sequence(2);
   TerminateTask();
}

/* This task is not used, only to change the scheduling police */
TASK(Task4)
{
   TerminateTask();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

