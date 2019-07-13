import xml.etree.cElementTree as ET
#from rawanparser import *
from io import BytesIO


def indent(elem, level=0):
    i = "\n" + level * "  "
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + "  "
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
        for elem in elem:
            indent(elem, level + 1)
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i


class  create_ARXML:
    tree = ET.ElementTree
    controllers_count = 1
    HW_Count = 1

    def __init__(self, XmlFilePath):
            self.XmlFilePath = XmlFilePath

    def create(self):
        ET.register_namespace("", "http://autosar.org/4.3.0")

        root = ET.Element("AUTOSAR", {"xmlns":"http://autosar.org/4.3.0", "xmlns:xsi":"http://www.w3.org/2001/XMLSchema-instance" , "xsi:schemaLocation":"http://autosar.org/4.3.0 autosar_4-3-0.xsd" })
        AR_PACKAGES=ET.SubElement(root, "AR-PACKAGES")
        AR_PACKAGE=ET.SubElement(AR_PACKAGES,"AR-PACKAGE")
        PackageShortName = ET.SubElement(AR_PACKAGE, "SHORT-NAME")
        PackageShortName.text="EcucDefs"
        Elements=ET.SubElement(AR_PACKAGE,"ELEMENTS")
        EcucModuleDef=ET.SubElement(Elements,"ECUC-MODULE-CONFIGURATION-VALUES")
        CanShortName=ET.SubElement(EcucModuleDef,"SHORT-NAME")
        CanShortName.text="Can"
        Can_containers=ET.SubElement(EcucModuleDef, "CONTAINERS")
        ################### Can General ##########################
        Can_container_cangeneral=ET.SubElement(Can_containers, "ECUC-CONTAINER-VALUE")
        Can_container_cangeneral_shortname=ET.SubElement(Can_container_cangeneral, "SHORT-NAME")
        Can_container_cangeneral_shortname.text="CanGeneral"
        ################### Can Config set ########################
        CanConfigSetContainer=ET.SubElement(Can_containers, "ECUC-PARAM-CONF-CONTAINER-DEF")
        CanConfigSetContainerShortName=ET.SubElement(CanConfigSetContainer, "SHORT-NAME")
        CanConfigSetContainerShortName.text="CanConfigSet"
        CanConfigSetSubContainers=ET.SubElement(CanConfigSetContainer,"SUB-CONTAINERS")
        ################### Can Config set SubContainers ########################
        #CanControllerSubContainer=ET.SubElement(CanConfigSetSubContainers,"ECUC-PARAM-CONF-CONTAINER-DEF")

        self.tree = ET.ElementTree(root)
        indent(root)
        self.tree.write(self.XmlFilePath+".arxml")
        # outfile=open(self.XmlFilePath+".arxml",'w')
        # outfile.write('<?xml version="1.0" encoding="UTF-8" ?>')
        # outfile.close()

    def Add_CanGeneral(self, list_cangeneral):
        ET.register_namespace("", "http://autosar.org/4.3.0")
        root = self.tree.getroot()

        containers_list = root.findall(".//ECUC-CONTAINER-VALUE")

        for container in containers_list:
            for node in container.iter():
                if(node.tag == "SHORT-NAME" and node.text == "CanGeneral"):
                    Can_cangeneral  = container




        CanGeneral_parameters = ET.SubElement(Can_cangeneral, "PARAMETER-VALUES")   # go into the tag parameter values ####

        CanGeneralReferenceValues = ET.SubElement(Can_cangeneral, "REFERENCE-VALUES")


        ################## CanDevErrorDetect ############################

        param_1 = ET.SubElement(CanGeneral_parameters, "ECUC-NUMERICAL-PARAM-VALUE")
        can_dev_error_shortname = ET.SubElement(param_1, "SHORT-NAME")   # add short name in param1 ###
        can_dev_error_shortname.text = "CanDevErrorDetect"
        can_dev_error_value = ET.SubElement(param_1, "VALUE")
        can_dev_error_value.text = list_cangeneral[0]

        ################## CanMultiplexedTransmission ####################
        param_2 = ET.SubElement(CanGeneral_parameters,"ECUC-NUMERICAL-PARAM-VALUE")
        can_multip_trans_shortname = ET.SubElement(param_2,"SHORT-NAME")
        can_multip_trans_shortname.text = "CanMultiplexedTransmission"
        can_multip_trans_Value=ET.SubElement(param_2,"VALUE")
        can_multip_trans_Value.text = list_cangeneral[1]

        ################## CanTimeoutDuration ###########################
        param_3=ET.SubElement(CanGeneral_parameters,"ECUC-FLOAT-PARAM-DEF")
        can_timeout_shortname = ET.SubElement(param_3,"SHORT-NAME")
        can_timeout_shortname.text = "CanTimeoutDuration"
        can_timeout_Value = ET.SubElement(param_3,"VALUE")
        can_timeout_Value.text = list_cangeneral[2]

        ################## CanMainFunctionWakeupPeriod #################
        # param_4=ET.SubElement(CanGeneral_parameters,"ECUC-NUMERICAL-PARAM-VALUE")
        # can_wakeupperiod_shortname = ET.SubElement(param_4,"SHORT-NAME")
        # can_wakeupperiod_shortname.text = "CanMainFunctionWakeupPeriod"
        # can_wakeupperiod_Value = ET.SubElement(param_4,"VALUE")
        # can_wakeupperiod_Value.text = list_cangeneral[3]

        ################# CanMainFunctionModePeriod #####################
        param_5=ET.SubElement(CanGeneral_parameters, "ECUC-NUMERICAL-PARAM-VALUE")
        can_modeperiod_shortname = ET.SubElement(param_5, "SHORT-NAME")
        can_modeperiod_shortname.text = "CanMainFunctionModePeriod"
        can_modeperiod_Value = ET.SubElement(param_5, "VALUE")
        can_modeperiod_Value.text = list_cangeneral[4]

        ################# CanIndex ######################################
        param_6=ET.SubElement(CanGeneral_parameters,"ECUC-NUMERICAL-PARAM-VALUE")
        can_index_shortname=ET.SubElement(param_6,"SHORT-NAME")
        can_index_shortname.text="CanIndex"
        can_index_Value=ET.SubElement(param_6,"VALUE")
        can_index_Value.text=list_cangeneral[5]

        ################## CanVersionInfoApi ############################
        param_7=ET.SubElement(CanGeneral_parameters,"ECUC-NUMERICAL-PARAM-VALUE")
        can_version_shortname=ET.SubElement(param_7,"SHORT-NAME")
        can_version_shortname.text="CanVersionInfoApi"
        can_version_Value=ET.SubElement(param_7,"VALUE")
        can_version_Value.text=list_cangeneral[6]

        ################## CanSetBaudrateApi ###########################
        param_8=ET.SubElement(CanGeneral_parameters,"ECUC-NUMERICAL-PARAM-VALUE")
        can_BR_API_shortname=ET.SubElement(param_8,"SHORT-NAME")
        can_BR_API_shortname.text="CanSetBaudrateApi"
        can_BR_API_Value=ET.SubElement(param_8,"VALUE")
        can_BR_API_Value.text=list_cangeneral[7]

        ################# CanPublicIcomSupport ########################
        # param_9=ET.SubElement(CanGeneral_parameters,"ECUC-NUMERICAL-PARAM-VALUE")
        # can_icom_shortname=ET.SubElement(param_9,"SHORT-NAME")
        # can_icom_shortname.text="CanPublicIcomSupport"
        # can_icom_Value=ET.SubElement(param_9,"VALUE")
        # can_icom_Value.text=list_cangeneral[8]

        ################## CanLPduReceiveCalloutFunction ############################
        # param_10=ET.SubElement(CanGeneral_parameters,"ECUC-NUMERICAL-PARAM-VALUE")
        # CanLPduReceiveCalloutFunction_shortname=ET.SubElement(param_10,"SHORT-NAME")
        # CanLPduReceiveCalloutFunction_shortname.text="CanLPduReceiveCalloutFunction"
        # CanLPduReceiveCalloutFunction_value=ET.SubElement(param_10,"VALUE")
        # CanMainFunctionBusoffPeriod_value.text=list_cangeneral[10] #error will occure ,cause user dosen't provide that value in the GUI

        ################# CanMainFunctionBusoffPeriod ############################
        param_11=ET.SubElement(CanGeneral_parameters,"ECUC-NUMERICAL-PARAM-VALUE")
        CanMainFunctionBusoffPeriod_shortname=ET.SubElement(param_11,"SHORT-NAME")
        CanMainFunctionBusoffPeriod_shortname.text="CanMainFunctionBusoffPeriod"
        CanMainFunctionBusoffPeriod_value=ET.SubElement(param_11,"VALUE")
        CanMainFunctionBusoffPeriod_value.text=list_cangeneral[9]#error will occure ,cause user dosen't provide that value in the GUI

        ################## CanGeneralReferenceValues ############################

        ################## CanOsCounterRef ############################
        # param_12=ET.SubElement(CanGeneralReferenceValues,"ECUC-REFERENCE-VALUE")
        # CanOsCounterRef_shortname=ET.SubElement(param_12,"SHORT-NAME")
        # CanOsCounterRef_shortname.text="CanOsCounterRef"
        # CanOsCounterRef_value=ET.SubElement(param_12,"VALUE-REF",DEST='OsCounter')

        ################## CanSupportTTCANRef ############################
        # param_13=ET.SubElement(CanGeneralReferenceValues,"ECUC-REFERENCE-VALUE")
        # CanSupportTTCANRef_shortname=ET.SubElement(param_13,"SHORT-NAME")
        # CanSupportTTCANRef_shortname.text="CanSupportTTCANRef"
        # CanSupportTTCANRef_value=ET.SubElement(param_13,"VALUE-REF",DEST='CanIfPrivateCfg')
        # ################## CanSupportTTCANRef ############################
        # param_14=ET.SubElement(CanGeneralReferenceValues,"ECUC-REFERENCE-VALUE")
        # CanSupportTTCANRef_shortname=ET.SubElement(param_14,"SHORT-NAME")
        # CanSupportTTCANRef_shortname.text="CanSupportTTCANRef"
        # CanSupportTTCANRef_value=ET.SubElement(param_14,"VALUE-REF",DEST='CanIfPrivateCfg')


    def Add_CanController(self,CanController):
        bd_count = 1
        ET.register_namespace("", "http://autosar.org/4.3.0")
        root = self.tree.getroot()
        containers_list = root.findall('.//ECUC-PARAM-CONF-CONTAINER-DEF')
        #print(containers_list)#for testing
        #CanConfigSet_SubContainers=containers_list[0]
        #Can_configset=containers_list[0]
        for container in containers_list:
            for node in container.iter():
                if(node.tag == "SHORT-NAME" and node.text == "CanConfigSet"):
                     Can_configset = container

        for node in Can_configset:
            if(node.tag == "SUB-CONTAINERS"):
                 CanConfigSet_SubContainers=node

        CanConfigSet_sub=ET.SubElement(CanConfigSet_SubContainers, "ECUC-CONTAINER-VALUE")


        CanController_shortname=ET.SubElement(CanConfigSet_sub, "SHORT-NAME")
        CanController_shortname.text = "CanController"+str(self.controllers_count)

        CanControllerParameters=ET.SubElement(CanConfigSet_sub,"PARAMETER-VALUES")
        CanControllerSubContainers=ET.SubElement(CanConfigSet_sub,"SUB-CONTAINERS")
        CanControllerRefernces=ET.SubElement(CanConfigSet_sub,'REFERENCE-VALUES')
        ########################### CanControllerId #######################
        Param_1=ET.SubElement(CanControllerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
        can_controllerid_shortname=ET.SubElement(Param_1,"SHORT-NAME")
        can_controllerid_shortname.text="CanControllerId"
        can_controllerid_Value=ET.SubElement(Param_1,"VALUE")
        can_controllerid_Value.text=CanController[0]

        ########################## CanControllerActivation #################
        Param_2=ET.SubElement(CanControllerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
        can_controlleractivation_shortname=ET.SubElement(Param_2,"SHORT-NAME")
        can_controlleractivation_shortname.text="CanControllerActivation"
        can_controlleractivation_Value=ET.SubElement(Param_2,"VALUE")
        can_controlleractivation_Value.text=CanController[1]

        ######################### CanControllerBaseAddress #################
        Param_3=ET.SubElement(CanControllerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
        can_controlleraddress_shortname = ET.SubElement(Param_3,"SHORT-NAME")
        can_controlleraddress_shortname.text = "CanControllerBaseAddress"      #this line was missing generating none
                                                                               # the bug is here ############
        can_controlleraddress_Value=ET.SubElement(Param_3,"VALUE")
        can_controlleraddress_Value.text = CanController[2]

        # ######################### CanWakeupSupport #########################
        # Param_4=ET.SubElement(CanControllerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
        # can_controllerwakeup_shortname = ET.SubElement(Param_4,"SHORT-NAME")
        # can_controllerwakeup_shortname.text = "CanWakeupSupport"
        # can_controllerwakeup_Value=ET.SubElement(Param_4,"VALUE")
        # can_controllerwakeup_Value.text=CanController[3]
        #
        # ######################### CanWakeupFunctionalityAPI ################
        # Param_5=ET.SubElement(CanControllerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
        # can_canWakeupfunctionality_API_shortname=ET.SubElement(Param_5,"SHORT-NAME")
        # can_canWakeupfunctionality_API_shortname.text = "CanWakeupFunctionalityAPI"
        # can_canWakeupfunctionality_API_Value=ET.SubElement(Param_5, "VALUE")
        # can_canWakeupfunctionality_API_Value.text=CanController[4]

        ######################## CanTxProcessing #############################
        Param_6=ET.SubElement(CanControllerParameters,"ECUC-TEXTUAL-PARAM-VALUE")
        can_controllerTX_shortname=ET.SubElement(Param_6,"SHORT-NAME")
        can_controllerTX_shortname.text = "CanTxProcessing" + str(self.controllers_count-1)
        can_controllerTX_Value=ET.SubElement(Param_6,"VALUE")
        can_controllerTX_Value.text =  CanController[5]

        ####################### CanRxProcessing ###############################
        Param_7=ET.SubElement(CanControllerParameters,"ECUC-TEXTUAL-PARAM-VALUE")
        can_controllerRX_shortname=ET.SubElement(Param_7,"SHORT-NAME")
        can_controllerRX_shortname.text="CanRxProcessing" + str(self.controllers_count-1)
        can_controllerRX_Value=ET.SubElement(Param_7,"VALUE")
        can_controllerRX_Value.text=CanController[6]

        ###################### CanBusoffProcessing ##########################
        Param_8=ET.SubElement(CanControllerParameters,"ECUC-TEXTUAL-PARAM-VALUE")
        can_controllerbusoff_shortname=ET.SubElement(Param_8,"SHORT-NAME")
        can_controllerbusoff_shortname.text="CanBusoffProcessing"+ str(self.controllers_count-1)
        can_controllerbusoff_Value=ET.SubElement(Param_8,"VALUE")
        can_controllerbusoff_Value.text=CanController[7]

        # ####################### CanWakeupProcessing ###########################
        # Param_9=ET.SubElement(CanControllerParameters,"ECUC-TEXTUAL-PARAM-VALUE")
        # can_controllerwup_shortname=ET.SubElement(Param_9,"SHORT-NAME")
        # can_controllerwup_shortname.text="CanWakeupProcessing"
        # can_controllerwup_Value=ET.SubElement(Param_9,"VALUE")
        # can_controllerwup_Value.text=CanController[8]

        ###################### CanControllerDefaultBaudrate ####################
        #
        #this parameter should be under the tag <References> in the STANDARD
        #
        Param_10=ET.SubElement(CanControllerRefernces, "ECUC-REFERENCE-VALUE")
        can_controllerdefaultbr_shortname = ET.SubElement(Param_10, "SHORT-NAME")
        can_controllerdefaultbr_shortname.text = "CanControllerDefaultBaudrate"
        can_controllerdefaultbr_Value=ET.SubElement(Param_10, "VALUE-REF", DEST='CanControllerBaudrateConfig')
        can_controllerdefaultbr_Value.text = CanController[9]#for now

        ###################### CanCpuClockRef ####################
        Param_11=ET.SubElement(CanControllerRefernces, "ECUC-REFERENCE-VALUE")
        CanCpuClockRef_shortname = ET.SubElement(Param_11, "SHORT-NAME")
        CanCpuClockRef_shortname.text = "CanCpuClockRef"
        CanCpuClockRef_Value=ET.SubElement(Param_11, "VALUE-REF", DEST='McuClockReferencePoint')
        #CanCpuClockRef_Value.text=CanController[9]#for now

        ################### CanWakeupSourceRef ####################
        # Param_12=ET.SubElement(CanControllerRefernces, "ECUC-REFERENCE-VALUE")
        # CanCpuClockRef_shortname  =ET.SubElement(Param_12, "SHORT-NAME")
        # CanCpuClockRef_shortname.text = "CanWakeupSourceRef"
        # CanCpuClockRef_Value=ET.SubElement(Param_12, "VALUE-REF", DEST='CanWakeupSource')
        #CanCpuClockRef_Value.text=CanController[9]#for now

        ############## generating Can Controller SubContainers ############
        for i in range(10,len(CanController)):
            #CanControllerSubContainers=ET.SubElement(CanControllerParameters,"SUB-CONTAINERS")
            CanControllerSubContainerShortName = ET.SubElement(CanControllerSubContainers,"SHORT-NAME")
            CanControllerSubContainerShortName.text = "CanController"+str(self.controllers_count)+"BaudrateConfig_"+str(bd_count)
            CanControllerSubContainerParameters=ET.SubElement(CanControllerSubContainers,"PARAMETER-VALUES")

            ################ CanControllerBaudRate ###################
            Param_13=ET.SubElement(CanControllerSubContainerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
            can_BR_shortname = ET.SubElement(Param_13, "SHORT-NAME")
            can_BR_shortname.text="CanControllerBaudRate"
            can_BR_Value = ET.SubElement(Param_13, "VALUE")
            can_BR_Value.text = CanController[i][0]

            ############### CanControllerPropSeg #####################
            Param_14=ET.SubElement(CanControllerSubContainerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
            can_propseg_shortname=ET.SubElement(Param_14,"SHORT-NAME")
            can_propseg_shortname.text="CanControllerPropSeg"
            can_propseg_Value=ET.SubElement(Param_14,"VALUE")
            can_propseg_Value.text=CanController[i][1]

            ############### CanControllerSeg1 ########################
            Param_15=ET.SubElement(CanControllerSubContainerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
            can_seg1_shortname=ET.SubElement(Param_15,"SHORT-NAME")
            can_seg1_shortname.text="CanControllerSeg1"
            can_seg1_Value=ET.SubElement(Param_15,"VALUE")
            can_seg1_Value.text=CanController[i][2]

            ################ CanControllerSeg2 #######################
            Param_16=ET.SubElement(CanControllerSubContainerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
            can_seg2_shortname=ET.SubElement(Param_16,"SHORT-NAME")
            can_seg2_shortname.text="CanControllerSeg2"
            can_seg2_Value=ET.SubElement(Param_16,"VALUE")
            can_seg2_Value.text=CanController[i][3]

            ################ CanControllerSyncJumpWidth ###############
            Param_17=ET.SubElement(CanControllerSubContainerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
            can_jump_shortname=ET.SubElement(Param_17,"SHORT-NAME")
            can_jump_shortname.text="CanControllerSyncJumpWidth"
            can_jump_Value=ET.SubElement(Param_17,"VALUE")
            can_jump_Value.text=CanController[i][4]

            ################# CanControllerBaudRateConfigID #############
            Param_18=ET.SubElement(CanControllerSubContainerParameters, "ECUC-NUMERICAL-PARAM-VALUE")
            can_BR_ID_shortname=ET.SubElement(Param_18, "SHORT-NAME")
            can_BR_ID_shortname.text="CanControllerBaudRateConfigID"
            can_BR_ID_Value=ET.SubElement(Param_18, "VALUE")
            can_BR_ID_Value.text=CanController[i][5]

            ################# CanControllerFdBaudRate #############
            # Param_19=ET.SubElement(CanControllerSubContainerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
            # CanControllerFdBaudRate_shortname=ET.SubElement(Param_19,"SHORT-NAME")
            # CanControllerFdBaudRate_shortname.text="CanController"+str(self.controllers_count)+"FdBaudRate_"+str(bd_count)
            # CanControllerFdBaudRate_Value=ET.SubElement(Param_19,"VALUE")
            # #can_BR_ID_Value.text=CanController[i][5]
            #
            # ################# CanControllerFdBaudrateConfig #############
            # Param_20=ET.SubElement(CanControllerSubContainerParameters,"ECUC-NUMERICAL-PARAM-VALUE")
            # FdBaudrateConfig_shortname=ET.SubElement(Param_20,"SHORT-NAME")
            # FdBaudrateConfig_shortname.text="CanController"+str(self.controllers_count)+"FdBaudrateConfig_"+str(bd_count)
            # FdBaudrateConfig_Value=ET.SubElement(Param_20,"VALUE")
            # #can_BR_ID_Value.text=CanController[i][5]


            bd_count=bd_count+1



        self.controllers_count=self.controllers_count+1
        indent(root)
        self.tree.write(self.XmlFilePath+".arxml")

    def Add_CanHWObject(self,HWObject_List):
        Filter_Count=1
        root = self.tree.getroot()
        containers = root.findall(".//ECUC-PARAM-CONF-CONTAINER-DEF")
        for container in containers:
            for node in container:
                if(node.text == "CanConfigSet"):
                    subcontainer_config = container

        for node in subcontainer_config:
            if(node.tag == "SUB-CONTAINERS"):
                ConfigSetSubContainers=node

        subcontainer = ET.SubElement(ConfigSetSubContainers, "ECUC-CONTAINER-VALUE")
        HWObject_Name = ET.SubElement(subcontainer, "SHORT-NAME")
        HWObject_Name.text = ("CanHardwareObject"+str(self.HW_Count))
        param = ET.SubElement(subcontainer, "PARAMETER-VALUES")
        ################# can Handle type #####################
        param1=ET.SubElement(param,"ECUC-TEXTUAL-PARAM-VALUE")
        CanHandle_Name = ET.SubElement(param1, "SHORT-NAME")
        CanHandle_Name.text = ("CanHandleType")
        CanHandle_Value = ET.SubElement(param1, "VALUE")
        CanHandle_Value.text=HWObject_List[0]
        ################# can object type #####################
        param2=ET.SubElement(param, "ECUC-TEXTUAL-PARAM-VALUE")
        CanObject_Name = ET.SubElement(param2, "SHORT-NAME")
        CanObject_Name.text = ("CanObjectType")
        Canobject_Value = ET.SubElement(param2, "VALUE")
        Canobject_Value.text = str(HWObject_List[1])
        ################# can Id type #####################
        param3=ET.SubElement(param, "ECUC-TEXTUAL-PARAM-VALUE")
        CanIdType_Name=ET.SubElement(param3, "SHORT-NAME")
        CanIdType_Name.text = ("CanIdType")
        CanIdType_Value=ET.SubElement(param3, "VALUE")
        CanIdType_Value.text = HWObject_List[2]
        ################# can object id #####################
        param4=ET.SubElement(param, "ECUC-NUMERICAL-PARAM-VALUE")
        CanObjectID_Name=ET.SubElement(param4, "SHORT-NAME")
        CanObjectID_Name.text=("CanObjectId")
        CanObjectID_Value=ET.SubElement(param4, "VALUE")
        CanObjectID_Value.text=HWObject_List[3]
        ################# Can_HardwareObject_UsesPolling #####################
        # param5=ET.SubElement(param,"ECUC-NUMERICAL-PARAM-VALUE")
        # CanFdPaddingValue_Name=ET.SubElement(param5,"SHORT-NAME")
        # CanFdPaddingValue_Name.text=("CanHardwareObjectUsesPolling")
        # CanFdPaddingValue_Value=ET.SubElement(param5,"VALUE")
        # CanFdPaddingValue_Value.text = HWObject_List[4]
        ################# CanTriggerTransmitEnable #####################
        param6=ET.SubElement(param, "ECUC-NUMERICAL-PARAM-VALUE")
        CanTriggerTransmitEnable_Name = ET.SubElement(param6, "SHORT-NAME")
        CanTriggerTransmitEnable_Name.text = ("CanTriggerTransmitEnable")
        CanTriggerTransmitEnable_Value = ET.SubElement(param6, "VALUE")
        CanTriggerTransmitEnable_Value.text = HWObject_List[5]

        ################# HWobjectcount #####################

        param10 = ET.SubElement(param, "ECUC-NUMERICAL-PARAM-VALUE")
        CanTriggerTransmitEnable_Name = ET.SubElement(param10, "SHORT-NAME")
        CanTriggerTransmitEnable_Name.text = "CanHwObjectCount"
        CanTriggerTransmitEnable_Value = ET.SubElement(param10, "VALUE")
        CanTriggerTransmitEnable_Value.text = HWObject_List[7]


        ################# CanControllerRef #####################
        param7=ET.SubElement(subcontainer, "REFERENCE-VALUES")
        param8=ET.SubElement(param7, "ECUC-NUMERICAL-PARAM-VALUE")
        CanControllerRef_Name=ET.SubElement(param8, "SHORT-NAME")
        CanControllerRef_Name.text=("CanControllerRef")
        CanControllerRef_Value=ET.SubElement(param8, "VALUE", DEST='ECUC-REFERENCE-VALUE')
        CanControllerRef_Value.text=HWObject_List[6]
        ################# CanMainFunctionBusoffPeriod #####################
        # param9 = ET.SubElement(param7, "ECUC-NUMERICAL-PARAM-VALUE")
        # CanMainFunctionBusoffPeriod_Name=ET.SubElement(param9,"SHORT-NAME")
        # CanMainFunctionBusoffPeriod_-Name.text=("CanMainFunctionBusoffPeriod_"+str(self.HW_Count))
        # CanMainFunctionBusoffPeriod_Value=ET.SubElement(param9, "VALUE", DEST='CanMainFunctionBusoffPeriod')


        ############### generating Can Hardware object SubContainers #############

        if Canobject_Value.text == "RECEIVE":
            for i in range(8, len(HWObject_List)):
                CanHWObjectSubContainers = ET.SubElement(subcontainer, "SUB-CONTAINERS")
                CanHWFilter = ET.SubElement(CanHWObjectSubContainers, "ECUC-NUMERICAL-PARAM-VALUE")
                CanHWFilter_Name = ET.SubElement(CanHWFilter, "SHORT-NAME")
                CanHWFilter_Name.text = ("CanHw"+str(self.HW_Count)+"Filter_"+str(Filter_Count))
                Filter_Parameters = ET.SubElement(CanHWObjectSubContainers, "PARAMETER-VALUES")

                ############# CanHwFilterMask #####################3
                param1=ET.SubElement(Filter_Parameters, "ECUC-NUMERICAL-PARAM-VALUE")
                CanHWFilterMask_Name=ET.SubElement(param1, "SHORT-NAME")
                CanHWFilterMask_Name.text = ("CanHwFilterMask")
                CanHWFilterMask_Value=ET.SubElement(param1,  "VALUE")
                CanHWFilterMask_Value.text=HWObject_List[i][0]

                ############ CanHwFilterCode ####################
                param2 = ET.SubElement(Filter_Parameters,"ECUC-NUMERICAL-PARAM-VALUE")
                CanHWFilterCode_Name = ET.SubElement(param2,"SHORT-NAME")
                CanHWFilterCode_Name.text =("CanHwFilterCode")
                CanHWFilterCode_Value = ET.SubElement(param2,"VALUE")
                CanHWFilterCode_Value.text = HWObject_List[i][1]
                Filter_Count = Filter_Count+1
        self.HW_Count = self.HW_Count + 1


        indent(root)
        self.tree.write(self.XmlFilePath+".arxml")





















#x=create_ARXML("zz")
#x.create()
#x.Add_CanGeneral(["True","False","1","2","3","4","True","False","True"])
#x.Add_CanController(["1","True","400400","True","false","INTERRUPT","POLLING","INTERRUPT","POLLING","CanControllerBaudrateConfig_1",["500","1","2","3","4","10"],["1000","0","1","2","3","20"]])
#x.Add_CanController(["2","False","400444","False","False","POLLING","INTERRUPT","INTERRUPT","POLLING","CanControllerBaudrateConfig_2"])
#x.Add_CanHWObject(["Basic","RECEIVE","STANDARD","0","0","False","Controller0",["0","0"],["5","2"]])
#x.Add_CanHWObject(["Basic","TRANSMIT","STANDARD","0","0","False","Controller0"])
