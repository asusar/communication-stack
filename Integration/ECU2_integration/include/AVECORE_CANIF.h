/*
 * AVECORE_CANIF.h
 *
 *  Created on: Oct 19, 2017
 *      Author: Ahmed.Abdelmoniem
 */


/*Unit testing functions*/

/* ______________________________________________________RxIndication________________________________________________________*/

void Uninit(void); /*case uninitialized CANIF with the rest is valid*/
void invalidcanid (void); /*case invalid CAN id*/
void invalidhrh (void); /*the HRH entered is invalid*/
void invalidsdu(void); /*the sdu data entered is NULL*/
void invalidDLC(void); /*the DLC entered is invalid*/
void correctentry(void); /*the data entered is correct*/

///*UNIT test functions */
///*Bus Off test functions*/
//void BusOff_valid();
//
//void BusOff_uninitialized();
//void BusOff_inv_Contoller();
//
//void BusOff_Offline();
//void BusOff_Test();
///*Can If transmit test functions*/
//void Can_busy();

//
//void Can_free();
//
//void uninitalized();
//void NULL_pdu_inv_ptr();
//
//void Invalid_can_pdu_tx_id();
//
//void CanIf_Transmit_Test();


#ifndef AVECORE_CANIF_H_
#define AVECORE_CANIF_H_

extern uint8 arr[]={0x41}; /*payload*/

extern PduInfoType pduInfoTypeInstance = {arr,1};

///*Upper layer PDUs signaling functions*/
//void CanIfUserTxConfirmation (uint32 x);
/* ______________________________________________________RxIndication________________________________________________________*/
//void CanIfUserRxIndication (uint8 channel, uint32 pduId, const uint8 *sduPtr, uint8 dlc, Can_IdType canId);
//
/////*upper layer notification functions*/
////void CanIfBusOffNotification (uint8 Controller);
//void CanIfCtrlModeIndication (void);
//void CanIfTrcvModeIndication(void);

int main(void);
#endif /* AVECORE_CANIF_H_ */
