
 /***************************************************
 *
 * File Name: Com_helper.h

 *
 * Author: AUTOSAR COM Team
 *
 * Date Created: 17 March 2019
 *
 * Version  : 01
 *
 ****************************************************/
#ifndef COM_HELPHER_H_
#define COM_HELPER_H_

// set bit in specific bit
#define SETBIT(dest,bit)	( *( (uint8 *)dest    + (bit / 8) ) |= (uint8)(1u << (bit % 8)) )

// clear bit in specific bit
#define CLEARBIT(dest,bit)	( *( (uint8 *)dest    + (bit / 8) ) &= (uint8)~(uint8)(1u << (bit % 8)) )

// get bit value
#define CHECKBIT(source,bit)	( *( (uint8 *)source  + (bit / 8) ) &  (uint8)(1u << (bit % 8)) )


#define GET_Signal(SignalId) \
	(&(ComConfig->ComSignal[SignalId]))


#define GET_IPdu(IPduId) \
	(&(ComConfig->ComIPdu[IPduId]))


#define GET_AsuIPdu(IPduId) \
	(&(Com_Asu_Config->ComIPdu[IPduId]))

#define GET_AsuSignal(SignalId)\
	(&(Com_Asu_Config->ComSignal[SignalId]))

boolean validateSignalID (Com_SignalIdType SignalId);

#define timerDec(timer) \
	if (timer > 0) { \
		timer = timer - ComConfig->ComTimeBase.ComTxTimeBase; \
	}

uint64 power(uint8 x,uint8 y);
//boolean compare_float(uint64 f1, uint64 f2);

#endif
