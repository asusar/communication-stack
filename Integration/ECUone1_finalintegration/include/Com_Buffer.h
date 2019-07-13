/*
 * Com_Buffer.h
 *
 *  Created on: Mar 19, 2019
 *      Author: Mina Mourice
 */

#ifndef INCLUDE_COM_BUFFER_H_
#define INCLUDE_COM_BUFFER_H_


//#define isBufferLocked(IPdubufStateptr) (*(IPdubufStateptr).Locked)

#define UNLOCKBUFFER(IPdubufStateptr) \
         *IPdubufStateptr.Locked=FALSE;\
         *IPdubufStateptr.CurrentPosition=0;

#define LOCKBUFFER(IPdubufStateptr) \
		*IPdubufStateptr.Locked=TRUE;

void Com_PackSignalsToPdu(uint16 ComIPuId);

void Com_UnPackSignalsFromPdu(uint16 ComIPuId);

void Com_WriteSignalDataToPduBuffer(const uint16 signalId, const void *signalData);

void Com_ReadSignalDataFromPduBuffer(const uint16 signalId, void *signalData);

void Com_WriteSignalDataToSignalBuffer (const uint16 signalId, const void * signalData);

void Com_ReadSignalDataFromSignalBuffer (const uint16 signalId,  void * signalData);

//void inline unlockBuffer(PduIdType id)
//{
//	Com_Asu_IPdu_type *Asu_IPdu = GET_AsuIPdu(id);
//    Asu_IPdu->PduBufferState.Locked=FALSE;
//    Asu_IPdu->PduBufferState.CurrentPosition=0;
//}

//void inline lockBuffer(PduIdType id)
//{
//	Com_Asu_IPdu_type *Asu_IPdu = GET_AsuIPdu(id);
//	Asu_IPdu->PduBufferState.Locked=TRUE;
//}




#endif /* INCLUDE_COM_BUFFER_H_ */
