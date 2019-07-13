/*
 * txConfirmation_unitTest.c
 *
 *  Created on: Oct 19, 2017
 *      Author: Akram.Abdalaziz
 */

#include "CanIf.h"
#include "CanIf_Cbk.h"
#include "stdio.h"

#define NUMBER_OF_TEST_CASES				((uint8)5)
#define VALID_CAN_TX_PDU_ID					((uint8)1)
#define INVALID_CAN_TX_PDU_ID				((uint8)3)
#define PRINT(_Msg)							printf(_Msg)



static void initConfig(uint8 testCaseNumber);
static void txConfirmationFirstScenario_validPduId();
static void txConfirmationSecondScenario_invalidPduId();
static void txConfirmationThirdScenario_nullUserTxConfirmPtrFn();
static void txConfirmationFourthScenario_inappropriateMode();
static void txConfirmationFifthScenario_uninitCANIF();


uint8 testNumber = 0;
typedef void (*testCasesFunctions)(void);
static const testCasesFunctions testCaseFn[NUMBER_OF_TEST_CASES] = {txConfirmationFirstScenario_validPduId,
		txConfirmationSecondScenario_invalidPduId, txConfirmationThirdScenario_nullUserTxConfirmPtrFn,
		txConfirmationFourthScenario_inappropriateMode, txConfirmationFifthScenario_uninitCANIF};

extern CanIf_ConfigType CanIf_Config_Test;

extern void CanIf_UnInit (void);

static void initConfig(uint8 testCaseNumber) {
	switch(testCaseNumber)
	{
	case 1:
		/* Prerequisites:
		 * 		Initialize txPduConfigPtr specially the PduID with at least one PDU.
		 * 		Initialize the CanIf_ConfigPtr with the default values in CanIf_Cfg.c
		 * 		Initialize CanIf_Global of this channel with the desired mode.
		 */
		CanIf_Init(&CanIf_Config);
		CanIf_SetControllerMode(CANIF_Channel_1, CAN_CS_STARTED);
		break;
	case 2:
		/* Prerequisites:
		 * 		Initialize txPduConfigPtr specially the PduID with at least one PDU.
		 * 		Initialize the CanIf_ConfigPtr with the default values in CanIf_Cfg.c
		 * 		Initialize CanIf_Global of this channel with the desired mode.
		 */
		CanIf_Init(&CanIf_Config);
		CanIf_SetControllerMode(CANIF_Channel_1, CAN_CS_STARTED);
		break;
	case 3:
		 /* Prerequisites:
		  * 	Initialize txPduConfigPtr specially the PduID with at least one PDU.
		  * 	Initialize the CanIf_ConfigPtr with the default values in CanIf_Cfg.c
		  * 	Initialize CanIf_Global of this channel with the desired mode.
		  * 	Initialize the call-out function pointer in the CanIf_ConfigPtr to NULL.
		  */
		CanIf_Init(&CanIf_Config_Test);
		CanIf_SetControllerMode(CANIF_Channel_1, CAN_CS_STARTED);
		break;
	case 4:
		/* Prerequisites:
		 * 		Initialize txPduConfigPtr specially the PduID with at least one PDU.
		 * 		Initialize the CanIf_ConfigPtr with the default values in CanIf_Cfg.c
		 * 		Initialize CanIf_Global of this channel with the desired mode.
		 * 		Change the pduMode for one of the listed Pdus to CANIF_SET_TX_OFFLINE.
		 */
		CanIf_Init(&CanIf_Config);
		CanIf_SetControllerMode(CANIF_Channel_1, CAN_CS_STARTED);
		CanIf_SetPduMode(CANIF_Channel_1, CANIF_SET_TX_OFFLINE);
		break;
	case 5:
		CanIf_UnInit();
		break;
	default:
		break;
	}
}


/*
 * Stub function for upper layer User transmit confirmation function*
 */
void CanIfUserTxConfirmationStubFn() {
	PRINT("The stub function was called");
}

/* -------------Valid PduId test case Scenario----------------------
 * Prerequisites:
 * 		Initialize txPduConfigPtr specially the PduID with at least one PDU.
 * 		Initialize the CanIf_ConfigPtr with the default values in CanIf_Cfg.c
 * 		Initialize CanIf_Global of this channel with the desired mode.
 * Test Scenario:
 * 		Call the function under test(CanIf_TxConfirmation) from the driver with a listed PduId value.
 * Expected Result
 * 		The stub will be called with printed Message "The stub function was called".
 */
static void txConfirmationFirstScenario_validPduId() {
	PRINT("\nExpected Output: The stub function was called\nActual Output: ");
	CanIf_TxConfirmation(VALID_CAN_TX_PDU_ID);

	if(1 == testNumber)
		PRINT("\n---pass---\n");
	else
		PRINT("\n---Not pass---\n");
}

/* -------------Invalid PduId test case Scenario----------------------
 * Prerequisites:
 * 		Initialize txPduConfigPtr specially the PduID with at least one PDU.
 * 		Initialize the CanIf_ConfigPtr with the default values in CanIf_Cfg.c
 * 		Initialize CanIf_Global of this channel with the desired mode.
 * Test Scenario:
 * 		Call the function under test(CanIf_TxConfirmation) from the driver with a unlisted PduId value.
 * Expected Result
 * 		The program will crash because it will try to access uninitialized memory,
 * 		but after doing some software handling the function will return with the expected result:
 * 		The stub will not be called and the validate will print an error number 18.
 */
static void txConfirmationSecondScenario_invalidPduId() {
	PRINT("\nExpected Output: API number 13(The txConfirmation API number) was fail "
			"because of the error number 18(CANIF_E_PARAM_LPDU)\nActual Output: ");
	CanIf_TxConfirmation(INVALID_CAN_TX_PDU_ID);
	if(2 == testNumber)
		PRINT("\n---pass---\n");
	else
		PRINT("\n---Not pass---\n");
}

/* -------------NULL UserTxConfirmation pointer function test case Scenario----------------------
 * Prerequisites:
 * 		Initialize txPduConfigPtr specially the PduID with at least one PDU.
 * 		Initialize the CanIf_ConfigPtr with the default values in CanIf_Cfg.c
 * 		Initialize CanIf_Global of this channel with the desired mode.
 * 		Initialize the call-out function pointer in the CanIf_ConfigPtr to NULL.
 * Test Scenario:
 * 		Call the function under test(CanIf_TxConfirmation) from the driver with a listed PduId value.
 * Expected Result
 * 		The stub will not be called and The Msg
 * 		”The txConfirmation call-out function wasn't be initialized” will be printed.
 */
static void txConfirmationThirdScenario_nullUserTxConfirmPtrFn() {
	PRINT("\nExpected Output: The txConfirmation call-out function wasn't be initialized\nActual Output: ");
	CanIf_TxConfirmation(VALID_CAN_TX_PDU_ID);
	if(4 == testNumber)
		PRINT("\n---pass---\n");
	else
		PRINT("\n---Not pass---\n");
}

/* -------------Inappropriate channel mode test case Scenario----------------------
 * Prerequisites:
 * 		Initialize txPduConfigPtr specially the PduID with at least one PDU.
 * 		Initialize the CanIf_ConfigPtr with the default values in CanIf_Cfg.c
 * 		Initialize CanIf_Global of this channel with the desired mode.
 * 		Change the pduMode for one of the listed Pdus to CANIF_SET_TX_OFFLINE.
 * Test Scenario:
 * 		Call the function under test(CanIf_TxConfirmation) from the driver with a listed PduId value that I changed its mode.
 * Expected Result
 * 		The stub will not be called and The Msg “The channel is in inappropriate mode” will be printed.
 */
static void txConfirmationFourthScenario_inappropriateMode() {
	PRINT("\nExpected Output: The channel is in inappropriate mode\nActual Output: ");
	CanIf_TxConfirmation(VALID_CAN_TX_PDU_ID);
	if(8 == testNumber)
		PRINT("\n---pass---\n");
	else
		PRINT("\n---Not pass---\n");
}

/* -------------Uninitialized CANIF test case Scenario----------------------
 * Prerequisites:
 *		Uninitialize CanIf channels.
 * Test Scenario:
 * 		Call the function under test(CanIf_TxConfirmation) without calling init function
 * 		before it from the driver with the listed PduId value.
 * Expected Result
 * 		The stub will not be called and the validate will print an error number 30.
 */
static void txConfirmationFifthScenario_uninitCANIF() {
	PRINT("\nExpected Output: API number 13(The txConfirmation API number) was fail "
			"because of the error number 30(CANIF_E_UNINIT)\nActual Output: ");
	CanIf_TxConfirmation(VALID_CAN_TX_PDU_ID);
	if(16 == testNumber)
		PRINT("\n---pass---\n");
	else
		PRINT("\n---Not pass---\n");
}

void runTxConfirmationUnitTest()
{
	uint8 testPassFlag = 0, testCase_i;

	printf("----------------------------------------------\n");
	printf("txConfirmation Test: \n");
	printf("----------------------------------------------\n");
	PRINT("Note:	The txConfirmation API number is 13\n");
	PRINT("	Error number of\n	CANIF_E_PARAM_LPDU is 18 and \n	CANIF_E_UNINIT is 30\n");
	PRINT("************************************************\n");

	for(testCase_i = 1; testCase_i <= NUMBER_OF_TEST_CASES; testCase_i++) {
		initConfig(testCase_i);
		testCaseFn[testCase_i-1]();
		CanIf_UnInit();
		testPassFlag |= testNumber;
		testNumber = 0;
	}

	if(31 == testPassFlag)
		PRINT("\nAll Test cases were passed as expected");
	else
		PRINT("\nAt least one of test cases were not passed as expected");

	PRINT("\n--------------------------------------------------------------\n");
}
