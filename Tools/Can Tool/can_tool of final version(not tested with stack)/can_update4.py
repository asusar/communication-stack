from PyQt4 import QtCore, QtGui
from PyQt4.QtGui import QIcon
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import sys,time
from PyQt4.QtCore import *
import xml.etree.ElementTree as ET
import json
import os
from ParserGenerate import *





class Module:

    Containers = []

    def __init__(self, XmlFilePath):
        self.XmlFilePath = XmlFilePath
    def GetModuleName(self):#editted to meet the standard tree
        tree = ET.parse(self.XmlFilePath)   #parse the file
        for node in tree.iter():    #iterate on all tree nodes
            if(node.tag == "{http://autosar.org/4.3.0}ECUC-MODULE-CONFIGURATION-VALUES"):
                for child in node:
                    if(child.tag == "{http://autosar.org/4.3.0}SHORT-NAME"):
                        return child.text



    def GetContainerName(self):#editted to met the standard
        tree = ET.parse(self.XmlFilePath)   #parse the file
        Containers = []
        for node in tree.iter():    #iterate on all tree nodes
            if(node.tag == "{http://autosar.org/4.3.0}CONTAINERS"):
                for child in node:
                    if(child.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF" or child.tag=="{http://autosar.org/4.3.0}ECUC-CONTAINER-VALUE"):
                        for grandchild in child:
                            if(grandchild.tag == "{http://autosar.org/4.3.0}SHORT-NAME"):
                                Containers.append(grandchild.text)
        return Containers

    def GetSubContainerName(self,Container):#editted to meet standard
        tree = ET.parse(self.XmlFilePath)   #parse the file
        SubContainers = []
        for node in tree.iter():    #iterate on all tree node
                if(node.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF"):
                    flag=False
                    for child in node:
                        if((child.tag == "{http://autosar.org/4.3.0}SHORT-NAME") and (flag == False)):
                            if(child.text == Container):
                                flag =True
                                continue

                        if((child.tag == "{http://autosar.org/4.3.0}PARAMETERS-VALUES") and (flag == True)) :
                            for grandchild in child:
                                if(grandchild.tag == "{http://autosar.org/4.3.0}SUB-CONTAINERS"):
                                    for subContainerName in grandchild:
                                        if(subContainerName.tag == "{http://autosar.org/4.3.0}SHORT-NAME"):
                                            SubContainers.append(subContainerName.text)
        return SubContainers

    def GetParam(self,Container):#editted
        #parser = ET.XMLParser(recover=True)
        # parser = ET.XMLParser(encoding="utf-8")
        # #tree = ET.fromstring(self.XmlFilePath, parser=parser)   #parse the file

        tree = ET.parse(self.XmlFilePath)
        # root = tree.getroot()

        # with open(self.XmlFilePath) as fd:
        #  parse = xmltodict.parse(fd.read())
        # print(parse)

        tree = ET.parse(self.XmlFilePath)
        Parameters = []
        values = []
        # for node in tree.iter():    #iterate on all tree node
        #         print(node.tag)
        #         if(node.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF"):
        #             flag=False
        #             print(flag)

        for node in tree.iter():    # iterate on all tree node
                # print(node.tag)

                if(node.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF" or node.tag == "{http://autosar.org/4.3.0}ECUC-CONTAINER-VALUE"):
                    flag = False
                    #print(flag)
                    for child in node:
                        #print(child.tag)
                        if((child.tag == "{http://autosar.org/4.3.0}SHORT-NAME") and (flag == False)):
                            if(child.text == Container):
                                flag =True
                                #print(flag)
                                continue
                        elif(child.tag=="{http://autosar.org/4.3.0}PARAMETER-VALUES" and flag==True):
                            for el in child:
                                #print(el.tag)
                                if(el.tag=="{http://autosar.org/4.3.0}ECUC-NUMERICAL-PARAM-VALUE" or el.tag=="{http://autosar.org/4.3.0}ECUC-TEXTUAL-PARAM-VALUE"
                                or el.tag=="{http://autosar.org/4.3.0}ECUC-FLOAT-PARAM-DEF" ):
                                    for grandchild in el:
                                            if(grandchild.tag == "{http://autosar.org/4.3.0}SHORT-NAME" ):
                                                Parameters.append(grandchild.text)
                                            elif(grandchild.tag=="{http://autosar.org/4.3.0}VALUE"):
                                                values.append(grandchild.text)
        #print(Parameters)
        return Parameters,  values


    def Modify(self,param,value):
        ET.register_namespace("", "http://autosar.org/4.3.0")

        tree = ET.parse(self.XmlFilePath)   #parse the file
        for node in tree.iter():
            if(node.tag == "{http://autosar.org/4.3.0}Param"):
                flag=False

                for child in node:
                    if((child.tag == "{http://autosar.org/4.3.0}Short_Name") and (child.text == param) and (flag == False)):
                        flag = True
                        continue

                    if((child.tag == "{http://autosar.org/4.3.0}Value") and (flag == True)):
                        child.text=value
        tree.write('can_xml_1.xml')

    def GetValue(self,param):
        ET.register_namespace("", "http://autosar.org/4.3.0")

        tree = ET.parse(self.XmlFilePath)   #parse the file
        for node in tree.iter():
            if(node.tag == "{http://autosar.org/4.3.0}Param"):
                flag = False

                for child in node:
                    if((child.tag == "{http://autosar.org/4.3.0}Short_Name") and (child.text == param) and (flag == False)):
                        flag = True
                        continue

                    if((child.tag == "{http://autosar.org/4.3.0}Value") and (flag == True)):
                        return child.text





################ controller parameters ->working properly #####################

    def controller_param(self,controller):
     tree = ET.parse(self.XmlFilePath)
     param_name = []
     param_value = []
     index = 0
     controller_found_flag = False
     for GrandGrandparent in tree.iter():
                    if GrandGrandparent.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF":
                        #print(GrandGrandparent.tag)
                        for Grandparent in GrandGrandparent:
                            for parent in Grandparent:
                                for GrandGrandchild in parent:
                                        if GrandGrandchild.text == "CanController"+str(controller):
                                            controller_found_flag = True
                                        elif GrandGrandchild.tag == "{http://autosar.org/4.3.0}PARAMETER-VALUES" and controller_found_flag == True:
                                            controller_found_flag = False
                                            for Grandchild in GrandGrandchild:
                                                #print(Grandchild.tag)
                                                for child in Grandchild:
                                                       if child.tag == "{http://autosar.org/4.3.0}SHORT-NAME":
                                                        param_name.append(child.text)
                                                        index += 1
                                                        string=child.text
                                                       elif child.tag == "{http://autosar.org/4.3.0}VALUE":
                                                         if "Processing" in string:
                                                             if child.text == "INTERRUPT":
                                                                param_value.append("0U")
                                                             elif child.text == "MIXED":
                                                                 param_value.append("1U")
                                                             elif child.text == "POLLING":
                                                                 param_value.append("2U")
                                                         else:
                                                           param_value.append(child.text)

     print(param_name), print(param_value)
     return param_name, param_value


    def controller_no(self, subContainer):  # edited to match the new standard xml file

        tree = ET.parse(self.XmlFilePath)
        count = 0
        for element in tree.iter():
            if(element.tag=="{http://autosar.org/4.3.0}ECUC-CONTAINER-VALUE"):
                found = False
                for child in element:
                    if((child.tag=="{http://autosar.org/4.3.0}SHORT-NAME")and(found==False)):

                        if(subContainer in child.text):

                            count = count+1

        print(count)
        return count

 ################### BR no. ##########################

    def baud_rate_no(self, controller):
        tree = ET.parse(self.XmlFilePath)
        controller_found_flag = False
        count = 1
        for GrandGrandparent in tree.iter():
                if GrandGrandparent.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF":
                    print(GrandGrandparent.tag)
                    for Grandparent in GrandGrandparent:  # go in sub-containers
                        for parent in Grandparent:       # go in ecu-c container value
                            for GrandGrandchild in parent:
                                    if GrandGrandchild.text == "CanController"+str(controller):
                                        controller_found_flag = True
                                    elif GrandGrandchild.tag == "{http://autosar.org/4.3.0}SUB-CONTAINERS" and controller_found_flag == True:
                                        for Grandchild in GrandGrandchild:
                                            if Grandchild.text == "CanController"+str(controller)+"BaudrateConfig_"+str(count):
                                               count += 1
        #print(count-1)
        return count

################### BR param ################################
    def baud_rate_param(self, controller, baud_rate_config_no):
      tree = ET.parse(self.XmlFilePath)
      param_name = []
      param_value = []
      baud_rate_config_flag = False
      controller_found_flag = False
      x = 1
      for GrandGrandparent in tree.iter():
            if GrandGrandparent.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF":
                print(GrandGrandparent.tag)
                for Grandparent in GrandGrandparent:  # go in sub-containers
                    for parent in Grandparent:       # go in ecu-c container value
                        for GrandGrandchild in parent:
                                if GrandGrandchild.text == "CanController"+str(controller):
                                    controller_found_flag = True
                                elif GrandGrandchild.tag == "{http://autosar.org/4.3.0}SUB-CONTAINERS" and controller_found_flag == True:
                                    for Grandchild in GrandGrandchild:
                                        if Grandchild.text == "CanController" + str(controller) + "BaudrateConfig_" + str(baud_rate_config_no):
                                            baud_rate_config_flag = True
                                        elif Grandchild.tag == "{http://autosar.org/4.3.0}PARAMETER-VALUES" and  baud_rate_config_flag == True:
                                             baud_rate_config_flag = False
                                             for child in Grandchild:
                                                   for el in child:
                                                         if el.tag == "{http://autosar.org/4.3.0}SHORT-NAME":
                                                          param_name.append(el.text)
                                                         elif el.tag == "{http://autosar.org/4.3.0}VALUE":
                                                          param_value.append(el.text)
      print(param_name), print(param_value)
      return param_name, param_value

 ######## hardware object paramters ###################

    def HW_object_params(self, object_no):

        tree = ET.parse(self.XmlFilePath)
        param_name = []
        param_value = []
        object_found_flag = False

        for GrandGrandparent in tree.iter():
         if GrandGrandparent.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF":
            print(GrandGrandparent.tag)
            for Grandparent in GrandGrandparent:  # go in sub-containers
                for parent in Grandparent:       # go in ecu-c container value
                    for GrandGrandchild in parent:
                            if GrandGrandchild.text == "CanHardwareObject"+str(object_no):
                                object_found_flag = True
                            elif GrandGrandchild.tag == "{http://autosar.org/4.3.0}PARAMETER-VALUES" and object_found_flag == True:
                                object_found_flag = False
                                for Grandchild in GrandGrandchild:
                                    for child in Grandchild:
                                                     if child.tag == "{http://autosar.org/4.3.0}SHORT-NAME":
                                                      param_name.append(child.text)
                                                     elif child.tag == "{http://autosar.org/4.3.0}VALUE":
                                                      param_value.append(child.text)
        return param_name, param_value




 #### number on HOHS ##################
    def HW_objects_no(self):

     tree = ET.parse(self.XmlFilePath)
     count = 1

     for GrandGrandparent in tree.iter():
         if GrandGrandparent.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF":
            print(GrandGrandparent.tag)
            for Grandparent in GrandGrandparent:  # go in sub-containers
                for parent in Grandparent:       # go in ecu-c container value
                    for GrandGrandchild in parent:
                            if GrandGrandchild.text == "CanHardwareObject"+str(count):
                                count += 1
     return count

    ###### filter parameters of receive objects ###########
    def filter_params(self, object_no):
        tree = ET.parse(self.XmlFilePath)
        param_name = []
        param_value = []
        object_flag = False
        for GrandGrandparent in tree.iter():
         if GrandGrandparent.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF":
            print(GrandGrandparent.tag)
            for Grandparent in GrandGrandparent:  # go in sub-containers
                for parent in Grandparent:       # go in ecu-c container value
                    for GrandGrandchild in parent:
                            if GrandGrandchild.text == "CanHardwareObject"+str(object_no):
                                object_flag = True
                            elif GrandGrandchild.tag == "{http://autosar.org/4.3.0}SUB-CONTAINERS" and object_flag == True:
                                object_flag = False
                                for Grandchild in GrandGrandchild:
                                    if Grandchild.tag == "{http://autosar.org/4.3.0}PARAMETER-VALUES":
                                        for child in Grandchild:
                                            for el in child:
                                                     if el.tag == "{http://autosar.org/4.3.0}SHORT-NAME":
                                                       param_name.append(el.text)
                                                     elif el.tag == "{http://autosar.org/4.3.0}VALUE":
                                                       param_value.append(el.text)
            return param_name, param_value



########### ref of HOH'controller #################
    def HOH_controller_ref(self,HOH_no):
        tree = ET.parse(self.XmlFilePath)
        object_flag = False
        for GrandGrandparent in tree.iter():
            if GrandGrandparent.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF":
                print(GrandGrandparent.tag)
                for Grandparent in GrandGrandparent:  # go in sub-containers
                    for parent in Grandparent:       # go in ecu-c container value
                        for GrandGrandchild in parent:
                                if GrandGrandchild.text == "CanHardwareObject"+str(HOH_no):
                                    object_flag = True
                                elif GrandGrandchild.tag == "{http://autosar.org/4.3.0}REFERENCE-VALUES" and object_flag == True:
                                    object_flag = False
                                    for Grandchild in GrandGrandchild:  # go in ECUC-NUMERICAL-PARAM-VALUE ####
                                        for child in Grandchild:
                                                if child.tag == "{http://autosar.org/4.3.0}VALUE" and "Controller" in child.text:
                                                     string = child.text
                                                     x = int(string[-1:])
                                                     return x

##### default baud_rate no #############
    def default_BR_no(self, controller_no):

        tree = ET.parse(self.XmlFilePath)
        controller_found_flag = False

        for GrandGrandparent in tree.iter():
            if GrandGrandparent.tag == "{http://autosar.org/4.3.0}ECUC-PARAM-CONF-CONTAINER-DEF":
                print(GrandGrandparent.tag)
                for Grandparent in GrandGrandparent:
                    for parent in Grandparent:
                        for GrandGrandchild in parent:
                                if GrandGrandchild.text == "CanController"+str(controller_no):
                                    controller_found_flag = True
                                elif GrandGrandchild.tag == "{http://autosar.org/4.3.0}REFERENCE-VALUES" and controller_found_flag == True:
                                    controller_found_flag = False
                                    for Grandchild in GrandGrandchild:
                                        print(Grandchild.tag)
                                        for child in Grandchild:  # textual param-val ro numerical param-val
                                               if "BaudRate Config" in child.text:
                                                 string = child.text
                                                 x = int(string[-1:])
                                                 print(x)
                                                 return x





    def MaxNumOfBaudRates(self):
        NumOFCanControllers=self.Subcontainer_no('CanController')
        baudrates=[]
        for i in range(1,NumOFCanControllers+1):
            baudrates.append(self.Subsubcontainer_no("CanController"+str(i)+"BaudrateConfig_"))
        #print(baudrates)
        return max(baudrates)


    def no_HTH_HRH(self,Type):
        tree=ET.parse(self.XmlFilePath)
        count=0
        for element in tree.iter():
            if(element.tag=="{http://autosar.org/4.3.0}subContainer"):
                found=False
                for child in element:
                    if((child.tag=="{http://autosar.org/4.3.0}Short_Name")and(found==False)):
                        if('CanHardwareObject' in child.text):
                            found=True
                            continue
                    if((child.tag=="{http://autosar.org/4.3.0}Param")and(found==True)):
                        for grandchild in child:
                            if((grandchild.tag=="{http://autosar.org/4.3.0}Value") and (grandchild.text==Type)):
                                count =count+1


        return count

    def HW_object_Type(self,HW_Object):
        tree=ET.parse(self.XmlFilePath)
        for element in tree.iter():
            if(element.tag=="{http://autosar.org/4.3.0}subContainer"):
                found=False
                for child in element:
                    if((child.tag=="{http://autosar.org/4.3.0}Short_Name")and(found==False)):
                        if(child.text==HW_Object):
                            found=True
                            continue
                    if((child.tag=="{http://autosar.org/4.3.0}Param")and(found==True)):
                        for grandchild in child:
                            if((grandchild.tag=="{http://autosar.org/4.3.0}Value") and (grandchild.text=='TRANSMIT' or grandchild.text=='RECEIVE')):
                                return grandchild.text



def check(value):
        if(value == 'True'):
            return True
        else:
            return False


def get_selected(index):
        return index.model().itemFromIndex(index).text()


data = root = [

    ("Can", [

        ("Can General", []),

        ("Can Configuration Set", [

            ("Can Controllers", []),
            ("Can Hardware Objects", []),

        ])

        ])]


try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_CanTool(object):
    path_1 = ""
    generation_flag = False

    counter = 0
    Can_Controllers_Count = 1
    Can_Hardware_Objects_Count = 1
    controllers_count =0
    # controllers_for_HWobject = []
    Can_Baudrates_Count = []
    controller_Baudrates_Count=[]
    removed_hw_object_index =0
    removed_br_index = 0
    remove_baud_rates_container=[]
    hw_object_to_remove_filter_from=[]
    for i in range(0,100):
       controller_Baudrates_Count.append(0)

    # Can_Baudrates_Count [1][1] =0
    # Can_Baudrates_Count [2][1] =0

    # Can_Baudrates_Count[0][1] = 0

    num_of_generated_controllers=0

    Can_HW_Filters_Count = []

    CanControllers_gb = []
    CanHardwareObjects_gb = []

    CanBaudrates_gb = []

    CanHWFilter_gb = []


    def setupUi(self, CanTool):

        CanTool.setObjectName(_fromUtf8("CanTool"))
        CanTool.resize(1058, 700)
        self.centralwidget = QtGui.QWidget(CanTool)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))

        self.treeView = QtGui.QTreeView(self.centralwidget)
        self.treeView.setGeometry(QtCore.QRect(0, 0, 260, 800))
        self.treeView.setObjectName(_fromUtf8("treeView"))
        self.treeView.setContextMenuPolicy(Qt.CustomContextMenu)

        # creation of left barr requests ############
        self.treeView.customContextMenuRequested.connect(self.openMenu)

        self.groupBox = QtGui.QGroupBox(self.centralwidget)
        self.groupBox.setGeometry(QtCore.QRect(270, 0, 780, 700))
        self.groupBox.setStyleSheet(_fromUtf8("background-image: url(back_1.png);"))
        self.groupBox.setAutoFillBackground(True)
        self.groupBox.setObjectName(_fromUtf8("groupBox"))
        self.groupBox.setVisible(False)
        self.label = QtGui.QLabel(self.groupBox)
        self.label.setGeometry(QtCore.QRect(30, 70, 71, 21))
        self.label.setObjectName(_fromUtf8("label"))
        self.label_2 = QtGui.QLabel(self.groupBox)
        self.label_2.setGeometry(QtCore.QRect(30, 120, 190, 16))
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.label_3 = QtGui.QLabel(self.groupBox)
        self.label_3.setGeometry(QtCore.QRect(30, 170, 190, 16))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.label_4 = QtGui.QLabel(self.groupBox)
        self.label_4.setGeometry(QtCore.QRect(30, 220, 290, 16))
        self.label_4.setObjectName(_fromUtf8("label_4"))

        self.label_11 = QtGui.QLabel(self.groupBox)
        self.label_11.setGeometry(QtCore.QRect(30, 270, 290, 16))
        self.label_11.setObjectName(_fromUtf8("label_11"))

        self.label_5 = QtGui.QLabel(self.groupBox)
        self.label_5.setGeometry(QtCore.QRect(30, 320, 190, 16))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.label_6 = QtGui.QLabel(self.groupBox)
        self.label_6.setGeometry(QtCore.QRect(30, 370, 270, 16))
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.label_7 = QtGui.QLabel(self.groupBox)
        self.label_7.setGeometry(QtCore.QRect(30, 420, 190, 16))
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.label_8 = QtGui.QLabel(self.groupBox)
        self.label_8.setGeometry(QtCore.QRect(30, 470, 190, 16))
        self.label_8.setObjectName(_fromUtf8("label_8"))
        self.label_9 = QtGui.QLabel(self.groupBox)
        self.label_9.setGeometry(QtCore.QRect(30, 520, 190, 16))
        self.label_9.setObjectName(_fromUtf8("label_9"))
 #must be edited for RWperiodsss ###########################






        self.Can_Index = QtGui.QLineEdit(self.groupBox)
        self.Can_Index.setGeometry(QtCore.QRect(320, 70, 113, 20))
        self.Can_Index.setObjectName(_fromUtf8("Can_Index"))

        self.Can_main_fn_Mode_period = QtGui.QLineEdit(self.groupBox)
        self.Can_main_fn_Mode_period.setGeometry(QtCore.QRect(320, 120, 113, 20))
        self.Can_main_fn_Mode_period.setObjectName(_fromUtf8("Can_main_fn_Mode_period"))

        self.Can_Timeout_Duration = QtGui.QLineEdit(self.groupBox)
        self.Can_Timeout_Duration.setGeometry(QtCore.QRect(320, 170, 113, 20))
        self.Can_Timeout_Duration.setObjectName(_fromUtf8("Can_Timeout_Duration"))

        self.Can_Main_Fn_Wakeup = QtGui.QLineEdit(self.groupBox)
        self.Can_Main_Fn_Wakeup.setGeometry(QtCore.QRect(320, 220, 113, 20))
        self.Can_Main_Fn_Wakeup.setObjectName(_fromUtf8("Can_Main_Fn_Wakeup"))

        self.Can_busoff_processing = QtGui.QLineEdit(self.groupBox)
        self.Can_busoff_processing.setGeometry(QtCore.QRect(320, 270, 113, 20))
        self.Can_busoff_processing.setObjectName(_fromUtf8("Can_busoff_processing"))

        self.Can_mul_transmission = QtGui.QCheckBox(self.groupBox)
        self.Can_mul_transmission.setGeometry(QtCore.QRect(290, 320, 70, 17))
        self.Can_mul_transmission.setText(_fromUtf8(""))
        self.Can_mul_transmission.setObjectName(_fromUtf8("Can_mul_transmission"))

        self.Can_Public_icom_support = QtGui.QCheckBox(self.groupBox)
        self.Can_Public_icom_support.setGeometry(QtCore.QRect(290, 370, 70, 17))
        self.Can_Public_icom_support.setText(_fromUtf8(""))
        self.Can_Public_icom_support.setObjectName(_fromUtf8("Can_Public_icom_support"))

        self.Can_version_info = QtGui.QCheckBox(self.groupBox)
        self.Can_version_info.setGeometry(QtCore.QRect(290, 420, 70, 17))
        self.Can_version_info.setText(_fromUtf8(""))
        self.Can_version_info.setObjectName(_fromUtf8("Can_version_info"))

        self.Can_Set_baudrate_API = QtGui.QCheckBox(self.groupBox)
        self.Can_Set_baudrate_API.setGeometry(QtCore.QRect(290, 470, 70, 17))
        self.Can_Set_baudrate_API.setText(_fromUtf8(""))
        self.Can_Set_baudrate_API.setObjectName(_fromUtf8("Can_Set_baudrate_API"))

        # a bug was here label was not aligned correctly with checkbox ################

        self.Can_Dev_error = QtGui.QCheckBox(self.groupBox)
        self.Can_Dev_error.setGeometry(QtCore.QRect(290, 520, 70, 17))
        self.Can_Dev_error.setText(_fromUtf8(""))
        self.Can_Dev_error.setObjectName(_fromUtf8("Can_Dev_error"))








        ##################################################################################CanHWFilter_1
        self.groupBox_5 = QtGui.QGroupBox(self.centralwidget)
        self.groupBox_5.setGeometry(QtCore.QRect(270, 0, 780, 700))
        self.groupBox_5.setStyleSheet(_fromUtf8("background-image: url(back_1.png));"))
        self.groupBox_5.setObjectName(_fromUtf8("groupBox_5"))
        self.groupBox_5.setVisible(False)

        self.label_100000_1 = QtGui.QLabel(self.groupBox_5)
        self.label_100000_1.setGeometry(QtCore.QRect(30, 70, 181, 21))
        self.label_100000_1.setObjectName(_fromUtf8("label_100000_1"))
        self.label_200000_1 = QtGui.QLabel(self.groupBox_5)
        self.label_200000_1.setGeometry(QtCore.QRect(30, 120, 111, 16))
        self.label_200000_1.setObjectName(_fromUtf8("label_200000_1"))
        self.Can_Hw_Filter_Mask_1= QtGui.QLineEdit(self.groupBox_5)
        self.Can_Hw_Filter_Mask_1.setGeometry(QtCore.QRect(290, 70, 113, 20))
        self.Can_Hw_Filter_Mask_1.setObjectName(_fromUtf8("Can_Hw_Filter_Mask_1"))
        self.Can_Hw_Filter_Code_1 = QtGui.QLineEdit(self.groupBox_5)
        self.Can_Hw_Filter_Code_1.setGeometry(QtCore.QRect(290, 120, 113, 20))
        self.Can_Hw_Filter_Code_1.setObjectName(_fromUtf8("Can_Hw_Filter_Code_1"))
        #####################################################################################################




        CanTool.setCentralWidget(self.centralwidget)

        self.menubar = QtGui.QMenuBar(CanTool)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 751, 21))
        self.menubar.setObjectName(_fromUtf8("menubar"))
        self.menuFile = QtGui.QMenu(self.menubar)
        self.menuFile.setObjectName(_fromUtf8("menuFile"))
        self.menuEdit = QtGui.QMenu(self.menubar)
        self.menuEdit.setObjectName(_fromUtf8("menuEdit"))
        CanTool.setMenuBar(self.menubar)

        self.statusbar = QtGui.QStatusBar(CanTool)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        CanTool.setStatusBar(self.statusbar)
        self.actionNew = QtGui.QAction(CanTool)
        self.actionNew.setObjectName(_fromUtf8("actionNew_Project"))
        self.actionNew.triggered.connect(self.new)
        self.actionOpen = QtGui.QAction(CanTool)
        self.actionOpen.setObjectName(_fromUtf8("actionOpen"))

        self.actionOpen.triggered.connect(self.file_open)

        self.actionSave_Changes = QtGui.QAction(CanTool)
        self.actionSave_Changes.setObjectName(_fromUtf8("actionSave_Changes"))
        self.actionSave_Changes.setEnabled(False)


        self.actionSave_Changes.triggered.connect(self.get_controllers_parameters)
        self.actionSave_Changes.triggered.connect(self.get_canGeneral_parameters)
        self.actionSave_Changes.triggered.connect(self.generate_ARXML)



        self.actionExit = QtGui.QAction(CanTool)
        self.actionExit.setObjectName(_fromUtf8("actionExit"))
        self.actionExit_2 = QtGui.QAction(CanTool)
        self.actionExit_2.setObjectName(_fromUtf8("actionExit_2"))
        #self.actionExit_2.triggered.connect(self.Create_new_task)
        #self.actionExit_2.triggered.connect(self.addChildClick)
        self.actionGenerate_Header_file = QtGui.QAction(CanTool)
        self.actionGenerate_Header_file.setObjectName(_fromUtf8("actionGenerate_Header_file"))
        self.actionGenerate_Header_file.setEnabled(False)
        self.actionGenerate_Header_file.triggered.connect(self.generate_ARXML)
        self.actionGenerate_Header_file.triggered.connect(self.Generate_header)

        self.menuFile.addAction(self.actionNew)
        self.menuFile.addAction(self.actionOpen)
        self.menuFile.addAction(self.actionSave_Changes)
        self.menuFile.addSeparator()
        self.menuFile.addAction(self.actionExit_2)
        self.menuEdit.addAction(self.actionGenerate_Header_file)
        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuEdit.menuAction())


        ############################ dialog box ########################
        self.dlg =QtGui.QInputDialog()
        self.dlg.setInputMode(QtGui.QInputDialog.TextInput)
        self.dlg.setLabelText("Please enter can object name")
        self.dlg.setWindowTitle('Warning')
        self.dlg.resize(300, 200)


        #self.treeWidget.connect(self.treeWidget, SIGNAL("itemClicked(QTreeWidgetItem*, int)"),self.choose)

        self.retranslateUi(CanTool)
        QtCore.QMetaObject.connectSlotsByName(CanTool)


    def display_error(self,string):

          self.error_window = QtGui.QWizard()
          self.error_window.setWindowTitle("error")
          self.error_window.resize(800, 200)
          message = QtGui.QLabel(self.error_window)
          message.setGeometry(QtCore.QRect(20, 70, 800, 70))
          message.setText(string)
          self.error_window.exec()

    def retranslateUi(self, CanTool):
        CanTool.setWindowTitle(_translate("CanTool", "Can Tool", None))
        #self.treeWidget.headerItem().setText(0, _translate("CanTool", "", None))
        #__sortingEnabled = self.treeWidget.isSortingEnabled()
        #self.treeWidget.setSortingEnabled(False)

        self.groupBox.setTitle(_translate("CanTool", "Can General", None))
        self.label.setText(_translate("CanTool", "Can Index", None))
        self.label_2.setText(_translate("CanTool", "Can Main Function Mode Period", None))
        self.label_3.setText(_translate("CanTool", "Can TimeOut Duration", None))
        self.label_4.setText(_translate("CanTool", "Can Main Function WakeUp Period(not supported)", None))
        self.label_11.setText(_translate("CanTool", "Can MainFunction Busoff Period", None))
        self.label_5.setText(_translate("CanTool", "Can Multiplexed Transmission", None))
        self.label_6.setText(_translate("CanTool", "Can Public Icom Support(not supported)", None))
        self.label_7.setText(_translate("CanTool", "Can Version Info API", None))
        #  the set baud_rate API  was not aligned correctly with its checkbox #####################3
        self.label_8.setText(_translate("CanTool", "Can Set BaudRate API", None))
        self.label_9.setText(_translate("CanTool", "Can Dev Error Detect", None))



        self.model = QStandardItemModel()

        self.addItems(self.model, data)
        self.treeView.setModel(self.model)

        self.model.setHorizontalHeaderLabels(["Modules"])

        self.treeView.connect(self.treeView, QtCore.SIGNAL('clicked(QModelIndex)'), self.choose)


        self.menuFile.setTitle(_translate("CanTool", "File", None))
        self.menuEdit.setTitle(_translate("CanTool", "Generate", None))
        self.actionNew.setText(_translate("CanTool", "New Project", None))
        self.actionOpen.setText(_translate("CanTool", "Open Project", None))
        self.actionSave_Changes.setText(_translate("CanTool", "Save", None))
        self.actionExit.setText(_translate("CanTool", "Exit", None))
        self.actionExit_2.setText(_translate("CanTool", "Exit", None))
        self.actionGenerate_Header_file.setText(_translate("CanTool", "Generate Files", None))

        #########################################################################################CanHWFilter_1
        self.groupBox_5.setTitle(_translate("MainWindow", "Can Hw Filter", None))
        self.label_100000_1.setText(_translate("MainWindow", "Can Hw Filter Mask", None))
        self.label_200000_1.setText(_translate("MainWindow", "Can Hw Filter Code", None))
        #############################################################################################



    def new(self):
        #self.dlg_2.exec_()
        self.path_1 = QtGui.QFileDialog.getSaveFileName(None,'new File')
        self.actionSave_Changes.setEnabled(True)
        self.actionGenerate_Header_file.setEnabled(True)
        os.makedirs(self.path_1)
        os.makedirs(os.path.join(self.path_1, "ARXML"))
        os.makedirs(os.path.join(self.path_1, "Header"))


    def file_open(self):
        self.actionSave_Changes.setEnabled(True)
        self.actionGenerate_Header_file.setEnabled(True)
        path = QtGui.QFileDialog.getExistingDirectory(None,'Open project')
        self.path_1 =path
        '''
        parser = Module(path)
        self.read_inputs(parser.GetValue('CanIndex'),parser.GetValue('CanMainFunctionModePeriod'),\
        parser.GetValue('CanMainFunctionWakeupPeriod'),parser.GetValue('CanTimeoutDuration'),\
        check(parser.GetValue('CanMultiplexedTransmission')),check(parser.GetValue('CanPublicIcomSupport')),\
        check(parser.GetValue('CanSetBaudrateApi')),check(parser.GetValue('CanVersionInfoApi')),\
        check(parser.GetValue('CanDevErrorDetect')),parser.GetValue('CanControllerId_1'),\
        parser.GetValue('CanControllerBaseAddress_1'),parser.GetValue('CanTxProcessing_1'),\
        parser.GetValue('CanRxProcessing_1'),parser.GetValue('CanBusoffProcessing_1'),parser.GetValue('CanWakeupProcessing_1'),\
        check(parser.GetValue('CanControllerActivation_1')),check(parser.GetValue('CanWakeupSupport_1')),\
        check(parser.GetValue('CanWakeupFunctionalityAPI_1')),parser.GetValue('CanControllerId_2'),\
        parser.GetValue('CanControllerBaseAddress_2'),parser.GetValue('CanTxProcessing_2'),\
        parser.GetValue('CanRxProcessing_2'),parser.GetValue('CanBusoffProcessing_2'),parser.GetValue('CanWakeupProcessing_2'),\
        check(parser.GetValue('CanControllerActivation_2')),check(parser.GetValue('CanWakeupSupport_2')),\
        check(parser.GetValue('CanWakeupFunctionalityAPI_2')),parser.GetValue('CanControllerBaudRateConfigID_1'),\
        parser.GetValue('CanControllerBaudRate_1'),parser.GetValue('CanControllerPropSeg_1'),\
        parser.GetValue('CanControllerSeg1_1'),parser.GetValue('CanControllerSeg2_1'),parser.GetValue('CanControllerSyncJumpWidth_1'),\
        parser.GetValue('CanControllerBaudRateConfigID_2'),parser.GetValue('CanControllerBaudRate_2'),\
        parser.GetValue('CanControllerPropSeg_2'),parser.GetValue('CanControllerSeg1_2'),parser.GetValue('CanControllerSeg2_2'),\
        parser.GetValue('CanControllerSyncJumpWidth_2'),parser.GetValue('CanObjectId_1'),parser.GetValue('CanFdPaddingValue_1'),\
        parser.GetValue('CanObjectType_1'),parser.GetValue('CanHandleType_1'),parser.GetValue('CanIdType_1'),\
        check(parser.GetValue('CanTriggerTransmitEnable_1')),parser.GetValue('CanControllerRef_1'),parser.GetValue('CanObjectId_2'),parser.GetValue('CanFdPaddingValue_2'),\
        parser.GetValue('CanObjectType_2'),parser.GetValue('CanHandleType_2'),parser.GetValue('CanIdType_2'),\
        check(parser.GetValue('CanTriggerTransmitEnable_2')),parser.GetValue('CanControllerRef_2'),parser.GetValue('CanObjectId_3'),parser.GetValue('CanFdPaddingValue_3'),\
        parser.GetValue('CanObjectType_3'),parser.GetValue('CanHandleType_3'),parser.GetValue('CanIdType_3'),\
        check(parser.GetValue('CanTriggerTransmitEnable_3')),parser.GetValue('CanControllerRef_3'),parser.GetValue('CanObjectId_4'),parser.GetValue('CanFdPaddingValue_4'),\
        parser.GetValue('CanObjectType_4'),parser.GetValue('CanHandleType_4'),parser.GetValue('CanIdType_4'),\
        check(parser.GetValue('CanTriggerTransmitEnable_4')),parser.GetValue('CanControllerRef_4'),parser.GetValue('CanHwFilterMask_1'),parser.GetValue('CanHwFilterCode_1'),\
        parser.GetValue('CanHwFilterMask_2'),parser.GetValue('CanHwFilterCode_2'),parser.GetValue('CanHwFilterMask_3'),\
        parser.GetValue('CanHwFilterCode_3'),parser.GetValue('CanHwFilterMask_4'),parser.GetValue('CanHwFilterCode_4'))
        '''




    def choose(self):

        selected_item = self.treeView.selectedIndexes()
        base_node = selected_item[0]

        getchild = get_selected(base_node)

        if(getchild == "Can General"):
            self.groupBox.setVisible(True)
            for i in range(0, len(self.CanControllers_gb)):
                self.CanControllers_gb[i].setVisible(False)

            for i in range(0, len(self.CanBaudrates_gb)):
                for j in range(0, len(self.CanBaudrates_gb[i])):
                    self.CanBaudrates_gb[i][j].setVisible(False)

            for i in range(0, len(self.CanHWFilter_gb)):
                for j in range(0, len(self.CanHWFilter_gb[i])):
                    self.CanHWFilter_gb[i][j].setVisible(False)

            for i in range(0, len(self.CanHardwareObjects_gb)):
                self.CanHardwareObjects_gb[i].setVisible(False)


        if "Can Controller_" in getchild :

            for i in range(0, len(self.CanControllers_gb)):
                if(i==int(getchild[-1:])-1):
                    self.CanControllers_gb[i].setVisible(True)
                    self.done([i], "Controller")

                else:
                    self.CanControllers_gb[i].setVisible(False)
            for i in range(0, len(self.CanHardwareObjects_gb)):
                self.CanHardwareObjects_gb[i].setVisible(False)
            for i in range(0, len(self.CanBaudrates_gb)):
                for j in range(0, len(self.CanBaudrates_gb[i])):
                    self.CanBaudrates_gb[i][j].setVisible(False)
            for i in range(0, len(self.CanHWFilter_gb)):
                for j in range(0, len(self.CanHWFilter_gb[i])):
                    self.CanHWFilter_gb[i][j].setVisible(False)
                #self.CanHWFilter_gb[i].setVisible(False)
            self.groupBox.setVisible(False)



         # flag = False
        if("Can Hardware Object_" in getchild):

            z = len(getchild)  # solving the bug of GUI ######################
            y = 0
            x = 1
            for i in range(0, len(getchild)):

               char = getchild[z-1-i]
               if char == '_':

                  value = y
                  break
               else:
                       y = y + (x*int(char))
                       x = x*10
            counter=0
            for i in range(0, len(self.CanHardwareObjects_gb)):
                counter+=1
                if i == value-1:
                   self.CanHardwareObjects_gb[i].setVisible(True)
                   self.hw_object_remove_button([i], i)
                   # flag = True
                else:
                   self.CanHardwareObjects_gb[i].setVisible(False)

            type=self.CanHardwareObjects_gb[value-1].findChildren(QtGui.QComboBox, "Can_Object_Type")
            object_type = str(type[0].currentText())
            if object_type == "TRANSMIT" :
               # self.Can_HW_Filters_Count[value-1]=1
               if self.Can_HW_Filters_Count[value-1]==2:
                   self.hw_object_to_remove_filter_from[value-1].removeRow(0)
                   self.Can_HW_Filters_Count[value-1]=1




            for i in range(0, len(self.CanControllers_gb)):
                self.CanControllers_gb[i].setVisible(False)

            for i in range(0, len(self.CanBaudrates_gb)):
                for j in range(0, len(self.CanBaudrates_gb[i])):
                    self.CanBaudrates_gb[i][j].setVisible(False)

            for i in range(0, len(self.CanHWFilter_gb)):
                for j in range(0, len(self.CanHWFilter_gb[i])):
                    self.CanHWFilter_gb[i][j].setVisible(False)
            self.groupBox.setVisible(False)


        if("Filter_" in getchild):
            for i in range(0, len(self.CanHWFilter_gb)):
                for j in range(0, len(self.CanHWFilter_gb[i])):
                    if((i == (int(getchild[6])-1) ) and (j==int(getchild[-1:])-1)):
                        self.CanHWFilter_gb[i][j].setVisible(True)
                    else:
                        self.CanHWFilter_gb[i][j].setVisible(False)
            for i in range(0, len(self.CanControllers_gb)):
                self.CanControllers_gb[i].setVisible(False)
            for i in range(0, len(self.CanHardwareObjects_gb)):
                self.CanHardwareObjects_gb[i].setVisible(False)
            self.groupBox.setVisible(False)

            for i in range(0, len(self.CanBaudrates_gb)):
                for j in range(0, len(self.CanBaudrates_gb[i])):
                    self.CanBaudrates_gb[i][j].setVisible(False)

        if("Baudrate config_" in getchild):

            z = len(getchild)   # solving the bug of GUI ######################
            y = 0
            x = 1
            for i in range(0, len(getchild)):

               char = getchild[z-1-i]
               if char == '_':

                  value = y
                  break
               else:
                       y = y + (x*int(char))
                       x = x*10

            for i in range(0, len(self.CanBaudrates_gb)):
                for j in range(0, len(self.CanBaudrates_gb[i])):
                    if i == int(getchild[3])-1 and j == value-1:
                        self.CanBaudrates_gb[i][j].setVisible(True)
                        self.done([i, j], "BD")
                        self.baudrate_remove_button([i, j],i,j)
                    else:
                        self.CanBaudrates_gb[i][j].setVisible(False)

            for i in range(0, len(self.CanControllers_gb)):
                self.CanControllers_gb[i].setVisible(False)
            for i in range(0, len(self.CanHardwareObjects_gb)):
                self.CanHardwareObjects_gb[i].setVisible(False)
            for i in range(0, len(self.CanHWFilter_gb)):
                for j in range(0,  len(self.CanHWFilter_gb[i])):
                    self.CanHWFilter_gb[i][j].setVisible(False)
            self.groupBox.setVisible(False)




    def save_xml(self):
        parser = Module(self.path_1)
        parser.Modify("CanIndex",str(self.Can_Index.text()))
        parser.Modify("CanMainFunctionModePeriod",str(self.Can_main_fn_Mode_period.text()))
        parser.Modify("CanTimeoutDuration",str(self.Can_Timeout_Duration.text()))
        parser.Modify("CanMainFunctionWakeupPeriod",str(self.Can_Main_Fn_Wakeup.text()))
        parser.Modify("CanMultiplexedTransmission",str(self.Can_mul_transmission.isChecked()))
        parser.Modify("CanPublicIcomSupport",str(self.Can_Public_icom_support.isChecked()))
        parser.Modify("CanSetBaudrateApi",str(self.Can_Set_baudrate_API.isChecked()))
        parser.Modify("CanVersionInfoApi",str(self.Can_version_info.isChecked()))
        parser.Modify("CanDevErrorDetect",str(self.Can_Dev_error.isChecked()))

        ########################## save in Can controller_1_XML_region ################################
        parser.Modify("CanControllerId_1",str(self.Can_Controller_ID.text()))
        parser.Modify("CanControllerActivation_1",str(self.can_controller_activation.isChecked()))
        parser.Modify("CanControllerBaseAddress_1",str(self.Can_Controller_Base_Address.text()))
        parser.Modify("CanWakeupSupport_1",str(self.can_wakeup_support.isChecked()))
        parser.Modify("CanWakeupFunctionalityAPI_1",str(self.can_wakeup_API.isChecked()))
        parser.Modify("CanTxProcessing_1",str(self.Can_Tx_Processing.currentText()))
        parser.Modify("CanRxProcessing_1",str(self.Can_Rx_Processing.currentText()))
        parser.Modify("CanBusoffProcessing_1",str(self.can_bus_off.currentText()))
        parser.Modify("CanWakeupProcessing_1",str(self.can_wakeup.currentText()))

        ##########################save in CanContollerBaudRate_1_XML_region#################################
        parser.Modify("CanControllerBaudRate_1",str(self.BaudRate.text()))
        parser.Modify("CanControllerPropSeg_1",str(self.Prop_seg.text()))
        parser.Modify("CanControllerSeg1_1",str(self.Prop_seg1.text()))
        parser.Modify("CanControllerSeg2_1",str(self.Prop_seg2.text()))
        parser.Modify("CanControllerSyncJumpWidth_1",str(self.Sync_jumpwidth.text()))
        parser.Modify("CanControllerBaudRateConfigID_1",str(self.BaudRate_config_ID.text()))

        ########################## save in Can controller_2_XML_region ####################################
        parser.Modify("CanControllerId_2",str(self.Can_Controller_ID_2.text()))
        parser.Modify("CanControllerActivation_2",str(self.can_controller_activation_2.isChecked()))
        parser.Modify("CanControllerBaseAddress_2",str(self.Can_Controller_Base_Address_2.text()))
        parser.Modify("CanWakeupSupport_2",str(self.can_wakeup_support_2.isChecked()))
        parser.Modify("CanWakeupFunctionalityAPI_2",str(self.can_wakeup_API_2.isChecked()))
        parser.Modify("CanTxProcessing_2",str(self.Can_Tx_Processing_2.currentText()))
        parser.Modify("CanRxProcessing_2",str(self.Can_Rx_Processing_2.currentText()))
        parser.Modify("CanBusoffProcessing_2",str(self.can_bus_off_2.currentText()))
        parser.Modify("CanWakeupProcessing_2",str(self.can_wakeup.currentText()))

        ##########################save in CanContollerBaudRate_2_XML_region#################################
        parser.Modify("CanControllerBaudRate_2",str(self.BaudRate_2.text()))
        parser.Modify("CanControllerPropSeg_2",str(self.Prop_seg_2.text()))
        parser.Modify("CanControllerSeg1_2",str(self.Prop_seg1_2.text()))
        parser.Modify("CanControllerSeg2_2",str(self.Prop_seg2_2.text()))
        parser.Modify("CanControllerSyncJumpWidth_2",str(self.Sync_jumpwidth_2.text()))
        parser.Modify("CanControllerBaudRateConfigID_2",str(self.BaudRate_config_ID_2.text()))

        ##########################save in CanHWObject_1_XML_region##########################################
        parser.Modify("CanHandleType_1",str(self.Can_HandleType_1.currentText()))
        parser.Modify("CanObjectType_1",str(self.Can_Object_Type_1.currentText()))
        parser.Modify("CanIdType_1",str(self.Can_Id_Type_1.currentText()))
        parser.Modify("CanObjectId_1",str(self.Can_Object_Id_1.text()))
        parser.Modify("CanFdPaddingValue_1",str(self.Can_Fd_Padding_Value_1.text()))
        parser.Modify("CanTriggerTransmitEnable_1",str(self.Can_Trigger_Transmit_Enable_1.isChecked()))
        parser.Modify('CanControllerRef_1',str(self.Can_Controller_ref_1.currentText()))

        ##########################save in CanHWFilter_1_XML_region##########################################
        parser.Modify("CanHwFilterMask_1",str(self.Can_Hw_Filter_Mask_1.text()))
        parser.Modify("CanHwFilterCode_1",str(self.Can_Hw_Filter_Code_1.text()))

        ##########################save in CanHWObject_2_XML_region##########################################
        parser.Modify("CanHandleType_2",str(self.Can_HandleType_2.currentText()))
        parser.Modify("CanObjectType_2",str(self.Can_Object_Type_2.currentText()))
        parser.Modify("CanIdType_2",str(self.Can_Id_Type_2.currentText()))
        parser.Modify("CanObjectId_2",str(self.Can_Object_Id_2.text()))
        parser.Modify("CanFdPaddingValue_2",str(self.Can_Fd_Padding_Value_2.text()))
        parser.Modify("CanTriggerTransmitEnable_2",str(self.Can_Trigger_Transmit_Enable_2.isChecked()))
        parser.Modify('CanControllerRef_2',str(self.Can_Controller_ref_2.currentText()))


        ##########################save in CanHWFilter_2_XML_region##########################################
        parser.Modify("CanHwFilterMask_2",str(self.Can_Hw_Filter_Mask_2.text()))
        parser.Modify("CanHwFilterCode_2",str(self.Can_Hw_Filter_Code_2.text()))

        ##########################save in CanHWObject_3_XML_region##########################################
        parser.Modify("CanHandleType_3",str(self.Can_HandleType_3.currentText()))
        parser.Modify("CanObjectType_3",str(self.Can_Object_Type_3.currentText()))
        parser.Modify("CanIdType_3",str(self.Can_Id_Type_3.currentText()))
        parser.Modify("CanObjectId_3",str(self.Can_Object_Id_3.text()))
        parser.Modify("CanFdPaddingValue_3",str(self.Can_Fd_Padding_Value_3.text()))
        parser.Modify("CanTriggerTransmitEnable_3",str(self.Can_Trigger_Transmit_Enable_3.isChecked()))
        parser.Modify('CanControllerRef_3',str(self.Can_Controller_ref_3.currentText()))

        ##########################save in CanHWFilter_3_XML_region##########################################
        parser.Modify("CanHwFilterMask_3",str(self.Can_Hw_Filter_Mask_3.text()))
        parser.Modify("CanHwFilterCode_3",str(self.Can_Hw_Filter_Code_3.text()))

        ##########################save in CanHWObject_4_XML_region##########################################
        parser.Modify("CanHandleType_4",str(self.Can_HandleType_4.currentText()))
        parser.Modify("CanObjectType_4",str(self.Can_Object_Type_4.currentText()))
        parser.Modify("CanIdType_4",str(self.Can_Id_Type_4.currentText()))
        parser.Modify("CanObjectId_4",str(self.Can_Object_Id_4.text()))
        parser.Modify("CanFdPaddingValue_4",str(self.Can_Fd_Padding_Value_4.text()))
        parser.Modify("CanTriggerTransmitEnable_4",str(self.Can_Trigger_Transmit_Enable_4.isChecked()))
        parser.Modify('CanControllerRef_4',str(self.Can_Controller_ref_4.currentText()))

        ##########################save in CanHWFilter_4_XML_region##########################################
        parser.Modify("CanHwFilterMask_4",str(self.Can_Hw_Filter_Mask_4.text()))
        parser.Modify("CanHwFilterCode_4",str(self.Can_Hw_Filter_Code_4.text()))


################################################ Generation ########################################################

    # def Generate_Arxml(self):
    #     arxml=open(os.path.join(self.path_1, "ARXML/Can.arxml"), 'w')
    #     print("Edited ARXML file",file=arxml)
    def display_warining(self):
          self.warining_window= QtGui.QWizard()
          self.warining_window.setWindowTitle("warining")
          self.warining_window.resize(800, 200)
          message = QtGui.QLabel(self.warining_window)
          message.setGeometry(QtCore.QRect(20, 70, 800, 70))
          message.setText("Make sure you filled all boxes and created 2 controllers at least other wise generation will not occur")
          self.warining_window.exec()

    def Generate_header(self):
        self.display_warining()
        if self.generation_flag:

            self.dlg.exec_()
            generated_file = open(os.path.join(self.path_1, "Header/Can_Cfg.h"), 'w')
            parser = Module(os.path.join(self.path_1, "ARXML/Can_ARXML.arxml"))
            parameters, values = parser.GetParam("CanGeneral")
            hrh=0
            hth=0
            max_hwcount = 0
            max_bdr_no = 0
            pp_counter = 0
            # pp_string[0] = "xxxxx"
            # pp_value[0] = "xxxxx"


            # print(values)

            # values[8] = 'False'
            # values[9] = 'False'
            print("#ifndef INCLUDES_CAN_CFG_H_  " , file=generated_file)
            print("#define INCLUDES_CAN_CFG_H_  " , file=generated_file)
            print('\n\n', file=generated_file)
            print("#define False 0U  " , file=generated_file)
            print("#define True  1U " , file=generated_file)
            i=0
            for value in values:

                if value == "True":
                    values[i] = "1U"
                elif value == "False":
                     values[i] = "0U"
                i+=1


            print("#define  " + parameters[6] + " " + values[6], file=generated_file)
            print("#define  " + parameters[5] + " " + values[5], file=generated_file)
            # print("#define  " + parameters[2] + " " + values[2]+'U', file=generated_file) #wake up parameter
            print("#define  " + parameters[4] + " " + values[4]+'U', file=generated_file)
            print("#define  " + parameters[1] + " " + values[1], file=generated_file)
            # print("#define  " + parameters[8] + " " + values[8], file=generated_file)
            # print("#define  " + parameters[7] + " " + values[7], file=generated_file) ### ICOM support####
            print("#define  " + parameters[7] + " " + values[7]+'U', file=generated_file)
            print("#define  " + parameters[0] + " " + values[0], file=generated_file)
            print("#define  " + parameters[2] + " " + values[2]+'U', file=generated_file)
            print("#define  " + parameters[3] + " " + values[3]+'U', file=generated_file)






            # print("#define general \\"+"\n"+"{.CanGeneral=\\", file=generated_file)  # edition required  here ############3
            # print("." + parameters[5] + "=" + values[5]+'\\', file=generated_file)
            # print("." + parameters[4] + "=" + values[4]+'\\', file=generated_file)
            # print("." + parameters[2] + "=" + values[2]+'\\', file=generated_file)
            # print("." + parameters[3] + "=" + values[3]+'\\', file=generated_file)
            # print("." + parameters[1] + "=" + values[1]+'\\', file=generated_file)
            # print("." + parameters[8] + "=" + values[8]+'\\', file=generated_file)
            # print("." + parameters[7] + "=" + values[7]+'\\', file=generated_file)
            # print("." + parameters[6] + "=" + values[6]+'\\', file=generated_file)
            # print("." + parameters[0] + "=" + values[0]+'\\', file=generated_file)
            # print("};\n\n", file=generated_file)


            ###################################################################

            # print("#define NUM_OF_CanControllers " + str(parser.Subcontainer_no('CanController'))+'U', file=Generated_file)
            # print("#define Max_no_of_baudRates "+str(parser.MaxNumOfBaudRates())+'U', file=Generated_file)
            # print("#define NUM_OF_HTH " + str(parser.no_HTH_HRH('TRANSMIT'))+'U', file=Generated_file)
            # print("#define NUM_OF_HRH " + str(parser.no_HTH_HRH('RECEIVE'))+'U', file=Generated_file)
            # print("#define size_MAP_HOH_2_CANObj " + str(parser.Subcontainer_no('CanHardwareObject'))+'U', file=Generated_file)
            pp_string = []
            pp_value = []
            print('\n\n\n\n', file=generated_file)

            print("#define UserCANCfg \\", file=generated_file)
            print("{.CanConfigSet.CanController =\\"+"\n"+"    {\\" , file=generated_file)

            for k in range(1, 3):
                print("{\\", file=generated_file)
                controller_params, controller_values = parser.controller_param(k)

                for j in range(0, 6):
                 string = controller_params[j]
                 if string[-1:] >= '0':
                   if string[-1:] <= '9':
                     pp_string.append(controller_params[j])
                     pp_value.append(controller_values[j])
                     pp_counter+=1
                   else :
                    string = controller_values[j]
                    if controller_params[j] == "CanControllerBaseAddress":  # CanControllerBaseAddress
                        print("." + controller_params[j] + " = 0x" + controller_values[j] + "U,\\", file=generated_file)
                    else:
                        if string[-1:] >= '0':
                          if string[-1:] <= '9':
                           print("." + controller_params[j] + " = " + controller_values[j] + "U,\\", file=generated_file)
                          else :
                            print("." + controller_params[j] + " = " + controller_values[j] + ",\\", file=generated_file)
                        else:
                          print("." + controller_params[j] + " = " + controller_values[j] + ",\\", file=generated_file)


                 else :
                    string = controller_values[j]
                    if controller_params[j] == "CanControllerBaseAddress":  # CanControllerBaseAddress
                        print("." + controller_params[j] + " = 0x" + controller_values[j] + "U,\\", file=generated_file)
                    else:
                        if string[-1:] >= '0':
                          if string[-1:] <= '9':
                           print("." + controller_params[j] + " = " + controller_values[j] + "U,\\", file=generated_file)
                          else :
                            print("." + controller_params[j] + " = " + controller_values[j] + ",\\", file=generated_file)
                        else:
                          print("." + controller_params[j] + " = " + controller_values[j] + ",\\", file=generated_file)

                print(".CanCpuClockRef=&McuPerClockConfigData,\\", file=generated_file)

                x = parser.default_BR_no(k)
                print(".CanControllerDefaultBaudrate = &"+self.dlg.textValue()+".CanConfigSet.CanController["+str(k-1)+"U].CanControllerBaudrateConfig["+str(x-1)+"U],\\",
                        file =generated_file)

                print(".CanControllerBaudrateConfig=\\", file=generated_file)
                print("{\\", file=generated_file)

                no_bd = parser.baud_rate_no(k)  # getting no. of baud-rate configs in controller ############
                if k == 1:
                    max_bdr_no = no_bd
                else:
                      if max_bdr_no<no_bd :
                           max_bdr_no =no_bd
                for n in range(1, no_bd):
                    baud_rate_params, baud_rate_values = parser.baud_rate_param(k, n)  # passing no of controller and no. of BR ####
                    print(" {\\", file=generated_file)
                    for param in range(0, 6):
                        print("." + baud_rate_params[param] + " = " + baud_rate_values[param] + "U,\\", file=generated_file)

                    if param == 5:
                        if n == no_bd-1:
                         print("        }\\", file=generated_file)  # end of a baud rate config
                         print("       }\\", file=generated_file)  # end of all baud rate configs on controller
                         if k == 1:
                          print("      },\\", file=generated_file)   # end of controller
                         else:
                              print(" }\\", file=generated_file)
                              print(" },\\", file=generated_file)  # end of all controllers #####
                        else:
                               print("        },\\", file=generated_file)

            print(".CanConfigSet.CanHardwareObject =\\"+"\n"+" {\\", file=generated_file)

            hoh_no = parser.HW_objects_no()
            for i in range(1, hoh_no):
                receive_flag = False
                print("  {\\", file=generated_file)
                param_name, param_value = parser.HW_object_params(i)
                for j in range(0, 6):
                 string = param_value[j]

                 if param_value[j] == "RECEIVE":
                     receive_flag = True
                     param_value[j]="receive"
                     hrh += 1
                 if param_value[j] == "TRANSMIT":
                        hth += 1
                        param_value[j] = "transmit"

                 if param_name[j] == "CanHwObjectCount":
                     if j==0 :
                         max_hwcount= int(param_value[j])
                     else:
                          if int(param_value[j])> max_hwcount :
                              max_hwcount = int(param_value[j])


                 if string[-1:] >= '0':
                    if string[-1:] <= '9':
                       print("." + param_name[j] + " = " + param_value[j] + "U,\\", file=generated_file)
                    else:
                            print("." + param_name[j] + " = " + param_value[j] + ",\\", file=generated_file)
                 else:
                                print("." + param_name[j] + " = " + param_value[j] + ",\\", file=generated_file)

                controller_ref = parser.HOH_controller_ref(i)
                print(".CanControllerRef = &CanContainer.CanConfigSet.CanController["+str(controller_ref-1)+"],\\", file=generated_file)
                if receive_flag == True:
                    filter_param_name, filter_param_value = parser.filter_params(i)
                    print(" .CanHwFilter=\\", file=generated_file)
                    print(" {\\", file=generated_file)
                    print("." + filter_param_name[0] + " =0x" + filter_param_value[0] + "U,\\", file=generated_file)
                    print("." + filter_param_name[1] + " =0x" + filter_param_value[1] + "U,\\", file=generated_file)
                    print(" }\\", file=generated_file)
                    if i == hoh_no-1:
                         print(" }\\", file=generated_file)
                         print(" }\\", file=generated_file)
                         print("};", file=generated_file)   # terminating the container
                    else:
                         print(" },\\", file=generated_file)

                else:
                     if i == hoh_no-1:
                         print(" }\\", file=generated_file)
                         print(" }\\", file=generated_file)
                         print("};", file=generated_file)   # terminating the container

                     else:
                            print(" },\\", file=generated_file)

            print("#define  "+"NUM_OF_HTH  " +str(hth)+"U", file=generated_file)
            print("#define  "+"NUM_OF_HRH  " +str(hrh)+"U", file=generated_file)
            print("#define  "+"NUM_OF_HOH  " + str(hth+hrh)+"U", file=generated_file)
            print("#define  "+"Max_CanHwObjectCount  " +str(max_hwcount)+"U" , file=generated_file)
            print("#define  "+"Max_num_of_baudrates  " +str(max_bdr_no-1)+"U", file=generated_file)
            print("#define  "+"NUM_OF_CAN_CONTROLLERS  2U", file=generated_file)
            print('\n\n\n\n', file=generated_file)
            print("#define INTERRUPT 0U  " , file=generated_file)
            print("#define  POLLING 2U " , file=generated_file)

            for p in range(0, pp_counter):

                print("#define  " + pp_string[p] + " " + pp_value[p], file=generated_file)


            print('\n\n', file=generated_file)

            print("#endif", file=generated_file)




             # check if it is receive to get fitler
             # terminate hoh
             # check if it is the last one to close container




    ################################### Tree View ####################################
    def addItems(self, parent, elements):

        for text, children in elements:
            item = QStandardItem(text)
            parent.appendRow(item)
            if children:
                self.addItems(item, children)



    ################################ Right Click Menu #################################

    def addChildClick(self):

        selection = self.treeView.selectedIndexes()
        base_node = selection[0]
        getchild = get_selected(base_node)


        if(getchild=="Can Controllers"):
            text = "Can Controller_"+str(self.Can_Controllers_Count)
            self.Can_Controllers_Count = self.Can_Controllers_Count+1
            self.Can_Baudrates_Count.append(2)
            self.CanBaudrates_gb.append([])
            self.Create_new_CanController()
            item = QStandardItem(text)
            s = selection[0]    # Handling multiple selectons
            parent = self.model.itemFromIndex(s)
            parent.appendRow(item)
            self.remove_baud_rates_container.append(item)
            item.appendRow(QStandardItem("Can"+str(self.Can_Controllers_Count-1)+" Baudrate config_1"))
            self.Create_new_Baudrate(self.Can_Controllers_Count-1)
            if("Can Controller Baudrate config_1" in getchild):
                self.CanBaudrates_gb[0].setVisible(True)

        if("Controller_" in getchild):
            text = "Can"+str(getchild[-1:])+" Baudrate config_"+str(self.Can_Baudrates_Count[int(getchild[-1:])-1])
            self.Can_Baudrates_Count[int(getchild[-1:])-1] = self.Can_Baudrates_Count[int(getchild[-1:])-1]+1
            self.Create_new_Baudrate(int(getchild[-1:]))
            item = QStandardItem(text)
            s = selection[0]    # Handling multiple selectons
            parent = self.model.itemFromIndex(s)
            parent.appendRow(item)


        if(getchild=="Can Hardware Objects"):
            text = "Can Hardware Object_"+str(self.Can_Hardware_Objects_Count)
            self.Can_Hardware_Objects_Count = self.Can_Hardware_Objects_Count+1
            self.counter += 1
            self.Can_HW_Filters_Count.append(1)
            self.CanHWFilter_gb.append([])
            self.Create_new_HardwareObject()
            item = QStandardItem(text)
            s = selection[0]    # Handling multiple selectons
            parent = self.model.itemFromIndex(s)
            parent.appendRow(item)
            self.hw_object_to_remove_filter_from.append(item)
            self.hw_objects_container=parent
        if("Object_" in getchild):
            type=self.CanHardwareObjects_gb[int(getchild[-1:])-1].findChildren(QtGui.QComboBox, "Can_Object_Type")
            object_type = str(type[0].currentText())
            if object_type == "TRANSMIT":
                string = "Receive hardware objects only have hw_filter container"
                self.display_error(string)

            elif self.Can_HW_Filters_Count[int(getchild[-1:])-1] > 1:
                string = "Receive hardware objects shall contain one filter container only"
                self.display_error(string)

            else:
                text = "Object"+str(getchild[-1:])+" Filter_"+str(self.Can_HW_Filters_Count[int(getchild[-1:])-1])
                self.Can_HW_Filters_Count[int(getchild[-1:])-1] = self.Can_HW_Filters_Count[int(getchild[-1:])-1]+1
                self.create_new_HWfilter(int(getchild[-1:]))
                item = QStandardItem(text)
                s = selection[0]
                parent = self.model.itemFromIndex(s)
                parent.appendRow(item)

        # item = QStandardItem(text)

        # if nothing selected parent is model
        if selection == []:
            parent = self.model

        # else: # Otherwise parent is what is selected
        #     s = selection[0]    # Handling multiple selectons
        #     parent = self.model.itemFromIndex(s)
        #
        # parent.appendRow(item)
        # print(type(self.model))
        # parent.r
        # if(item.text()=="Can Controller_"+str(self.Can_Controllers_Count-1)):
        #     item.appendRow(QStandardItem("Con"+str(self.Can_Controllers_Count-1)+" Baudrate config_1"))
        #     # self.Can_Baudrates_Count=self.Can_Baudrates_Count+1
        #     self.Create_new_Baudrate(self.Can_Controllers_Count-1)
        #     if("Can Controller Baudrate config_1" in getchild):
        #         self.CanBaudrates_gb[0].setVisible(True)


        #cleanup
        #self.treeView.expandAll()
        self.treeView.clearSelection()



######### the following function is responsible for generating the menu when u right click any container ##########
    def openMenu(self, position):

        indexes = self.treeView.selectedIndexes()
        base_node = indexes[0]
        node_text = get_selected(base_node)

        menu = QMenu()
        if (node_text == "Can Controllers"):

            menu.addAction("Create New Contoller", self.addChildClick)

        elif (node_text == "Can Hardware Objects"):

            menu.addAction("Create New Hardware Object", self.addChildClick)

        elif ("Can Controller_" in node_text):
            menu.addAction("Add New BaudRate Config", self.addChildClick)

        elif("Can Hardware Object_" in node_text):
            menu.addAction("Add New HW Filter", self.addChildClick)


        menu.exec_(self.treeView.viewport().mapToGlobal(position))

    def hw_object_remove_button(self,object_no,number):
        x = self.CanHardwareObjects_gb[object_no[0]].findChildren(QtGui.QPushButton, "pushButton_HardwareObject_remove")
        try:
                x[0].clicked.disconnect()
        except:
                pass

                x[0].clicked.connect(self.remove_HW_object)
                self.removed_hw_object_index = number

    def remove_HW_object(self):
        self.CanHardwareObjects_gb[self.removed_hw_object_index].setVisible(False)
        # hw_object = self.model.findChild(QtGui.QStandardItemModel, 'Can Hardware Objects')
        # hw_object.removeRows()
        self.hw_objects_container.removeRow(self.Can_Hardware_Objects_Count-2)

        self.Can_Hardware_Objects_Count = self.Can_Hardware_Objects_Count-1
        self.CanHardwareObjects_gb.pop(self.removed_hw_object_index)
        if self.removed_hw_object_index<self.Can_Hardware_Objects_Count-1:
         if self.Can_HW_Filters_Count[self.removed_hw_object_index+1] == 2 and self.Can_HW_Filters_Count[self.removed_hw_object_index] == 1 :
          self.Can_HW_Filters_Count[self.removed_hw_object_index+1]=1
          # self.Can_HW_Filters_Count[self.removed_hw_object_index]=1
        self.hw_object_to_remove_filter_from.pop(self.removed_hw_object_index)
        self.Can_HW_Filters_Count.pop(self.removed_hw_object_index)
        self.CanHWFilter_gb.pop(self.removed_hw_object_index)

    def baudrate_remove_button(self,baudrate_in_controller,controller_no,br_no):
        x = self.CanBaudrates_gb[baudrate_in_controller[0]][baudrate_in_controller[1]].findChildren(QtGui.QPushButton,"pushButton_Baudrate_remove")
        try:
                x[0].clicked.disconnect()
        except:
                pass

                x[0].clicked.connect(self.remove_baude_rate)
                self. removed_br_index = br_no
                self.controller_to_remove_br_from=controller_no

    def remove_baude_rate(self):
        if self.Can_Baudrates_Count[self.controller_to_remove_br_from] == 2:
            string =" Each can controller must have at least one Baud-rate configuration"
            self.display_error(string)
        else:
            self.remove_baud_rates_container[self.controller_to_remove_br_from].removeRow(self.Can_Baudrates_Count[self.controller_to_remove_br_from]-2)
            self.CanBaudrates_gb[self.controller_to_remove_br_from][self. removed_br_index].setVisible(False)
            self.CanBaudrates_gb[self.controller_to_remove_br_from].pop(self. removed_br_index)
            self.Can_Baudrates_Count[self.controller_to_remove_br_from]-=1

    def done(self,ind,name):

        if name == "Controller":

            x = self.CanControllers_gb[ind[0]].findChildren(QtGui.QPushButton, "pushButton_controller_done")
            self.index = ind

            try:
                x[0].clicked.disconnect()
            except:
                pass
              # x[0].clicked.connect(self.Controller_Ref)

        elif name == "BD":

            x = self.CanBaudrates_gb[ind[0]][ind[1]].findChildren(QtGui.QPushButton, "pushButton_Baudrate_done")
            self.index=ind

            try:
                x[0].clicked.disconnect()


            except:
                pass
            # x[0].clicked.connect(self.BD_Ref)

    def BD_Ref(self):
        ID = self.CanBaudrates_gb[self.index[0]][self.index[1]].findChildren(QtGui.QLineEdit, "BaudRate_config_ID")
        ID[0].setEnabled(False)
        Baud_ID = ID[0].text
        cb = self.CanControllers_gb[self.index[0]].findChildren(QtGui.QComboBox, "Baud_rate_config")
        cb[0].addItem("BaudRate Config"+str(self.index[1]+1))

    def Controller_Ref(self):
        ID = self.CanControllers_gb[self.index[0]].findChildren(QtGui.QLineEdit, "Can_Controller_ID")
        ID[0].setEnabled(False)
        Controller_ID=ID[0].text
        for obj in self.CanHardwareObjects_gb:

            cb = obj.findChildren(QtGui.QComboBox, "Can_Controller_ref")
            cb[0].addItem("Controller"+str(self.index[0]+1))

    def Create_new_CanController(self):
        self.groupBox_2 = QtGui.QGroupBox(self.centralwidget)
        self.groupBox_2.setGeometry(QtCore.QRect(270, 0, 780, 700))
        self.groupBox_2.setStyleSheet(_fromUtf8("background-image: url(back_1.png);"))
        self.groupBox_2.setObjectName(_fromUtf8("groupBox"))
        self.label_10 = QtGui.QLabel(self.groupBox_2)
        self.label_10.setText(_translate("MainWindow", "Can Controller ID", None))
        self.label_10.setGeometry(QtCore.QRect(30, 70, 200, 21))
        self.label_10.setObjectName(_fromUtf8("label"))
        self.label_20 = QtGui.QLabel(self.groupBox_2)
        self.label_20.setText(_translate("MainWindow", "Can Controller Base Address(hexa)", None))
        self.label_20.setGeometry(QtCore.QRect(30, 120, 200, 16))
        self.label_20.setObjectName(_fromUtf8("label_2"))
        self.label_30 = QtGui.QLabel(self.groupBox_2)
        self.label_30.setText(_translate("MainWindow", "Can Tx Processing", None))
        self.label_30.setGeometry(QtCore.QRect(30, 170, 200, 16))
        self.label_30.setObjectName(_fromUtf8("label_3"))
        self.label_40 = QtGui.QLabel(self.groupBox_2)
        self.label_40.setText(_translate("MainWindow", "Can Rx Processing", None))
        self.label_40.setGeometry(QtCore.QRect(30, 220, 200, 16))
        self.label_40.setObjectName(_fromUtf8("label_4"))
        self.label_50 = QtGui.QLabel(self.groupBox_2)
        self.label_50.setText(_translate("MainWindow", "Can Bus Off Processing", None))
        self.label_50.setGeometry(QtCore.QRect(30, 270, 200, 16))
        self.label_50.setObjectName(_fromUtf8("label_5"))
        self.label_60 = QtGui.QLabel(self.groupBox_2)
        self.label_60.setText(_translate("MainWindow", "Can Wakeup Processing(not supported)", None))
        self.label_60.setGeometry(QtCore.QRect(30, 320, 240, 16))
        self.label_60.setObjectName(_fromUtf8("label_6"))
        self.label_70 = QtGui.QLabel(self.groupBox_2)
        self.label_70.setText(_translate("MainWindow", "Can Controller Activation", None))
        self.label_70.setGeometry(QtCore.QRect(30, 370, 200, 16))
        self.label_70.setObjectName(_fromUtf8("label_7"))
        self.label_80 = QtGui.QLabel(self.groupBox_2)
        self.label_80.setText(_translate("MainWindow", "Can Wakeup support(not supported)", None))
        self.label_80.setGeometry(QtCore.QRect(30, 420, 240, 16))
        self.label_80.setObjectName(_fromUtf8("label_8"))
        self.label_90 = QtGui.QLabel(self.groupBox_2)
        self.label_90.setText(_translate("MainWindow", "Can Wakeup FunctionalityAPI(not supported)", None))
        self.label_90.setGeometry(QtCore.QRect(30, 470, 260, 16))
        self.label_90.setObjectName(_fromUtf8("label_9"))
        self.Can_Controller_ID = QtGui.QLineEdit(self.groupBox_2)
        self.Can_Controller_ID.setGeometry(QtCore.QRect(290, 70, 200, 20))
        self.Can_Controller_ID.setObjectName(_fromUtf8("Can_Controller_ID"))
        self.Can_Controller_Base_Address = QtGui.QLineEdit(self.groupBox_2)
        self.Can_Controller_Base_Address.setGeometry(QtCore.QRect(290, 120, 200, 20))
        self.Can_Controller_Base_Address.setObjectName(_fromUtf8("Can_Controller_Base_Address"))
        self.Can_Tx_Processing = QtGui.QComboBox(self.groupBox_2)
        self.Can_Tx_Processing.setGeometry(QtCore.QRect(290, 170, 200, 22))
        self.Can_Tx_Processing.setObjectName(_fromUtf8("Can_Tx_Processing"))
        self.Can_Tx_Processing.addItem('INTERRUPT')
        self.Can_Tx_Processing.addItem('POLLING')
        # self.Can_Tx_Processing.addItem('MIXED')
        self.Can_Rx_Processing = QtGui.QComboBox(self.groupBox_2)
        self.Can_Rx_Processing.setGeometry(QtCore.QRect(290, 220, 200, 22))
        self.Can_Rx_Processing.setObjectName(_fromUtf8("Can_Rx_Processing"))
        self.Can_Rx_Processing.addItem('INTERRUPT')
        self.Can_Rx_Processing.addItem('POLLING')
        # self.Can_Rx_Processing.addItem('MIXED')
        self.can_bus_off = QtGui.QComboBox(self.groupBox_2)
        self.can_bus_off.setGeometry(QtCore.QRect(290, 270, 200, 22))
        self.can_bus_off.setObjectName(_fromUtf8("can_bus_off"))
        self.can_bus_off.addItem('INTERRUPT')
        self.can_bus_off.addItem('POLLING')
        self.can_wakeup = QtGui.QComboBox(self.groupBox_2)
        self.can_wakeup.setGeometry(QtCore.QRect(290, 320, 200, 22))
        self.can_wakeup.setObjectName(_fromUtf8("can_wakeup"))
        self.can_wakeup.addItem('INTERRUPT')
        self.can_wakeup.addItem('POLLING')
        self.can_controller_activation = QtGui.QCheckBox(self.groupBox_2)
        self.can_controller_activation.setGeometry(QtCore.QRect(290, 370, 200, 17))
        self.can_controller_activation.setText(_fromUtf8(""))
        self.can_controller_activation.setObjectName(_fromUtf8("can_controller_activation"))
        self.can_wakeup_support = QtGui.QCheckBox(self.groupBox_2)
        self.can_wakeup_support.setGeometry(QtCore.QRect(290, 420, 200, 17))
        self.can_wakeup_support.setText(_fromUtf8(""))
        self.can_wakeup_support.setObjectName(_fromUtf8("can_wakeup_support"))
        self.can_wakeup_API = QtGui.QCheckBox(self.groupBox_2)
        self.can_wakeup_API.setGeometry(QtCore.QRect(290, 470, 200, 17))
        self.can_wakeup_API.setText(_fromUtf8(""))
        self.can_wakeup_API.setObjectName(_fromUtf8("can_wakeup_API"))


        self.pushButton_controller_done = QtGui.QPushButton(self.groupBox_2)
        self.pushButton_controller_done.setText(_translate("MainWindow", "Done", None))
        self.pushButton_controller_done.setGeometry(QtCore.QRect(600, 600, 200, 30))
        self.pushButton_controller_done.setObjectName(_fromUtf8("pushButton_controller_done"))


        self.combo = QtGui.QComboBox(self.groupBox_2)
        self.combo.setGeometry(QtCore.QRect(290, 520, 200, 22))
        self.combo.setObjectName(_fromUtf8("Baud_rate_config"))
        self.label_100 = QtGui.QLabel(self.groupBox_2)
        self.label_100.setGeometry(QtCore.QRect(30, 520, 200, 16))
        self.label_100.setObjectName(_fromUtf8("label_100"))
        self.label_100.setText(_translate("MainWindow", "Default BaudRate Config ref.", None))

        self.CanControllers_gb.append(self.groupBox_2)


    def Create_new_HardwareObject(self):

        self.groupBox_4 = QtGui.QGroupBox(self.centralwidget)
        self.groupBox_4.setGeometry(QtCore.QRect(270, 0, 780, 700))
        self.groupBox_4.setStyleSheet(_fromUtf8("background-image: url(back_1.png);"))
        self.groupBox_4.setObjectName(_fromUtf8("groupBox_4"))
        self.label_10000_1 = QtGui.QLabel(self.groupBox_4)
        self.label_10000_1.setText(_translate("MainWindow", "Can Object ID", None))
        self.label_10000_1.setGeometry(QtCore.QRect(30, 70, 200, 21))
        self.label_10000_1.setObjectName(_fromUtf8("label"))
        self.label_20000_1 = QtGui.QLabel(self.groupBox_4)
        self.label_20000_1.setText(_translate("MainWindow", "CanHardwareObjectUsesPolling(not supported)", None))
        self.label_20000_1.setGeometry(QtCore.QRect(30, 120, 280, 16))
        self.label_20000_1.setObjectName(_fromUtf8("label_2"))
        self.label_30000_1 = QtGui.QLabel(self.groupBox_4)
        self.label_30000_1.setText(_translate("MainWindow", "Can Object Type", None))
        self.label_30000_1.setGeometry(QtCore.QRect(30, 170, 200, 16))
        self.label_30000_1.setObjectName(_fromUtf8("label_3"))
        self.label_40000_1 = QtGui.QLabel(self.groupBox_4)
        self.label_40000_1.setText(_translate("MainWindow", "Can Handle Type", None))
        self.label_40000_1.setGeometry(QtCore.QRect(30, 220, 200, 16))
        self.label_40000_1.setObjectName(_fromUtf8("label_4"))
        self.label_50000_1 = QtGui.QLabel(self.groupBox_4)
        self.label_50000_1.setText(_translate("MainWindow", "Can ID Type", None))
        self.label_50000_1.setGeometry(QtCore.QRect(30, 270, 200, 16))
        self.label_50000_1.setObjectName(_fromUtf8("label_5"))
        self.label_60000_1 = QtGui.QLabel(self.groupBox_4)
        self.label_60000_1.setText(_translate("MainWindow", "Can Trigger Transmit Enable(not supported)", None))
        self.label_60000_1.setGeometry(QtCore.QRect(30, 320, 260, 16))
        self.label_60000_1.setObjectName(_fromUtf8("label_6"))
        self.label_70000_1 = QtGui.QLabel(self.groupBox_4)
        self.label_70000_1.setText(_translate("MainWindow", "Can Controller Ref", None))
        self.label_70000_1.setGeometry(QtCore.QRect(30, 370, 141, 16))
        self.label_70000_1.setObjectName(_fromUtf8("label_7"))
        self.label_80000_1 = QtGui.QLabel(self.groupBox_4)
        self.label_80000_1.setText(_translate("MainWindow", "HWobjectcount", None))
        self.label_80000_1.setGeometry(QtCore.QRect(30, 470, 141, 16))
        self.label_80000_1.setObjectName(_fromUtf8("label_8"))

         # end of labels #################################

        self.Can_Object_Id_1 = QtGui.QLineEdit(self.groupBox_4)
        self.Can_Object_Id_1.setGeometry(QtCore.QRect(290, 70, 113, 20))
        self.Can_Object_Id_1.setObjectName(_fromUtf8("Can_Object_Id"))
        self.Can_HardwareObject_UsesPolling_1 = QtGui.QCheckBox(self.groupBox_4)
        self.Can_HardwareObject_UsesPolling_1.setGeometry(QtCore.QRect(320, 120, 113, 20))
        self.Can_HardwareObject_UsesPolling_1.setObjectName(_fromUtf8("Can_HardwareObject_UsesPolling"))
        self.Can_Object_Type_1 = QtGui.QComboBox(self.groupBox_4)
        self.Can_Object_Type_1.setGeometry(QtCore.QRect(290, 170, 111, 22))
        self.Can_Object_Type_1.setObjectName(_fromUtf8("Can_Object_Type"))
        self.Can_Object_Type_1.addItem('TRANSMIT')
        self.Can_Object_Type_1.addItem('RECEIVE')
        self.Can_HandleType_1= QtGui.QComboBox(self.groupBox_4)
        self.Can_HandleType_1.setGeometry(QtCore.QRect(290, 220, 111, 22))
        self.Can_HandleType_1.setObjectName(_fromUtf8("Can_HandleType"))
        self.Can_HandleType_1.addItem('BASIC')
        self.Can_HandleType_1.addItem('FULL')
        self.Can_Id_Type_1 = QtGui.QComboBox(self.groupBox_4)
        self.Can_Id_Type_1.setGeometry(QtCore.QRect(290, 270, 111, 22))
        self.Can_Id_Type_1.setObjectName(_fromUtf8("Can_Id_Type"))
        self.Can_Id_Type_1.addItem('STANDARD')
        self.Can_Id_Type_1.addItem('EXTENDED')
        self.Can_Id_Type_1.addItem('MIXED')
        self.Can_Trigger_Transmit_Enable_1 = QtGui.QCheckBox(self.groupBox_4)
        self.Can_Trigger_Transmit_Enable_1.setGeometry(QtCore.QRect(320, 320, 70, 17))
        self.Can_Trigger_Transmit_Enable_1.setText(_fromUtf8(""))
        self.Can_Trigger_Transmit_Enable_1.setObjectName(_fromUtf8("Can_Trigger_Transmit_Enable"))

        self.Can_Controller_ref_1 = QtGui.QComboBox(self.groupBox_4)
        self.Can_Controller_ref_1.setGeometry(QtCore.QRect(290, 370, 113, 20))
        self.Can_Controller_ref_1.setObjectName(_fromUtf8("Can_Controller_ref"))
        self.Can_Controller_ref_1.addItem("Controller"+str(1))
        self.Can_Controller_ref_1.addItem("Controller"+str(2))

        self.HW_object_count = QtGui.QLineEdit(self.groupBox_4)
        self.HW_object_count.setGeometry(QtCore.QRect(290, 470, 113, 20))
        self.HW_object_count.setObjectName(_fromUtf8("HW_Object_count"))



        self.pushButton_HardwareObject_remove = QtGui.QPushButton(self.groupBox_4)
        self.pushButton_HardwareObject_remove.setText(_translate("MainWindow", "remove object", None))
        self.pushButton_HardwareObject_remove.setGeometry(QtCore.QRect(600, 600, 150, 30))
        self.pushButton_HardwareObject_remove.setObjectName(_fromUtf8("pushButton_HardwareObject_remove"))
        self.CanHardwareObjects_gb.append(self.groupBox_4)


        #self.Controller_Ref()

    def Create_new_Baudrate(self, controller_num):
        self.controller_Baudrates_Count[controller_num-1] += 1
        self.groupBox_3 = QtGui.QGroupBox(self.centralwidget)
        self.groupBox_3.setGeometry(QtCore.QRect(270, 0, 780, 700))
        self.groupBox_3.setStyleSheet(_fromUtf8("background-image: url(back_1.png);"))
        self.groupBox_3.setObjectName(_fromUtf8("groupBox_3"))
        self.label_2000 = QtGui.QLabel(self.groupBox_3)
        self.label_2000.setText(_translate("MainWindow", "Can Controller Baudrate (kbps)", None))
        self.label_2000.setGeometry(QtCore.QRect(30, 120, 200, 16))
        self.label_2000.setObjectName(_fromUtf8("label_2000"))
        self.label_3000 = QtGui.QLabel(self.groupBox_3)
        self.label_3000.setText(_translate("MainWindow", "Can Controller Prop Seg", None))
        self.label_3000.setGeometry(QtCore.QRect(30, 170, 200, 16))
        self.label_3000.setObjectName(_fromUtf8("label_3000"))
        self.label_4000 = QtGui.QLabel(self.groupBox_3)
        self.label_4000.setText(_translate("MainWindow", "Can Controller Seg1", None))
        self.label_4000.setGeometry(QtCore.QRect(30, 220, 200, 16))
        self.label_4000.setObjectName(_fromUtf8("label_4000"))
        self.label_5000 = QtGui.QLabel(self.groupBox_3)
        self.label_5000.setText(_translate("MainWindow", "Can Controller Seg2", None))
        self.label_5000.setGeometry(QtCore.QRect(30, 270, 200, 16))
        self.label_5000.setObjectName(_fromUtf8("label_5000"))
        self.label_1000 = QtGui.QLabel(self.groupBox_3)
        self.label_1000.setText(_translate("MainWindow", "Can Controller Baudrate Config ID", None))
        self.label_1000.setGeometry(QtCore.QRect(30, 70, 200, 21))
        self.label_1000.setObjectName(_fromUtf8("label_1000"))
        self.label_6000 = QtGui.QLabel(self.groupBox_3)
        self.label_6000.setText(_translate("MainWindow", "Can Controller Sync JumpWidth", None))
        self.label_6000.setGeometry(QtCore.QRect(30, 320, 200, 16))
        self.label_6000.setObjectName(_fromUtf8("label_6000"))
        self.BaudRate_config_ID = QtGui.QLineEdit(self.groupBox_3)
        self.BaudRate_config_ID.setGeometry(QtCore.QRect(290, 70, 150, 20))
        self.BaudRate_config_ID.setObjectName(_fromUtf8("BaudRate_config_ID"))
        self.BaudRate = QtGui.QLineEdit(self.groupBox_3)
        self.BaudRate.setGeometry(QtCore.QRect(290, 120, 150, 20))
        self.BaudRate.setObjectName(_fromUtf8("BaudRate"))
        self.Prop_seg = QtGui.QLineEdit(self.groupBox_3)
        self.Prop_seg.setGeometry(QtCore.QRect(290, 170, 150, 20))
        self.Prop_seg.setObjectName(_fromUtf8("Prop_seg"))
        self.Prop_seg1 = QtGui.QLineEdit(self.groupBox_3)
        self.Prop_seg1.setGeometry(QtCore.QRect(290, 220, 150, 20))
        self.Prop_seg1.setObjectName(_fromUtf8("Prop_seg1"))
        self.Prop_seg2 = QtGui.QLineEdit(self.groupBox_3)
        self.Prop_seg2.setGeometry(QtCore.QRect(290, 270, 150, 20))
        self.Prop_seg2.setObjectName(_fromUtf8("Prop_seg2"))
        self.Sync_jumpwidth = QtGui.QLineEdit(self.groupBox_3)
        self.Sync_jumpwidth.setGeometry(QtCore.QRect(290, 320, 150, 20))
        self.Sync_jumpwidth.setObjectName(_fromUtf8("Sync_jumpwidth"))

        ################# push_button for Baud_rate ######################
        self.pushButton_Baudrate_remove = QtGui.QPushButton(self.groupBox_3)
        self.pushButton_Baudrate_remove.setText(_translate("MainWindow", "remove object", None))
        self.pushButton_Baudrate_remove.setGeometry(QtCore.QRect(600, 600, 110, 30))
        self.pushButton_Baudrate_remove.setObjectName(_fromUtf8("pushButton_Baudrate_remove"))

        self.CanBaudrates_gb[controller_num - 1].append(self.groupBox_3)
        controller = self.CanControllers_gb[controller_num - 1].findChildren(QtGui.QComboBox, "Baud_rate_config")
        controller[0].addItem("BaudRate Config"+str(self.controller_Baudrates_Count[controller_num-1]))

    def create_new_HWfilter(self, filters_num):
        self.groupBox_5 = QtGui.QGroupBox(self.centralwidget)
        self.groupBox_5.setGeometry(QtCore.QRect(270, 0, 780, 700))
        self.groupBox_5.setStyleSheet(_fromUtf8("background-image: url(back_1.png);"))
        self.groupBox_5.setObjectName(_fromUtf8("groupBox_5"))
        self.label_100000_1 = QtGui.QLabel(self.groupBox_5)
        self.label_100000_1.setText(_translate("MainWindow", "Can HW Filter Mask(hexa)", None))
        self.label_100000_1.setGeometry(QtCore.QRect(30, 70, 200, 21))
        self.label_100000_1.setObjectName(_fromUtf8("label_100000_1"))
        self.label_200000_1 = QtGui.QLabel(self.groupBox_5)
        self.label_200000_1.setText(_translate("MainWindow", "Can HW Filter Code(hexa)", None))
        self.label_200000_1.setGeometry(QtCore.QRect(30, 120, 150, 16))
        self.label_200000_1.setObjectName(_fromUtf8("label_200000_1"))
        self.Can_Hw_Filter_Mask_1= QtGui.QLineEdit(self.groupBox_5)
        self.Can_Hw_Filter_Mask_1.setGeometry(QtCore.QRect(290, 70, 113, 20))
        self.Can_Hw_Filter_Mask_1.setObjectName(_fromUtf8("Can_Hw_Filter_Mask_1"))
        self.Can_Hw_Filter_Code_1 = QtGui.QLineEdit(self.groupBox_5)
        self.Can_Hw_Filter_Code_1.setGeometry(QtCore.QRect(290, 120, 113, 20))
        self.Can_Hw_Filter_Code_1.setObjectName(_fromUtf8("Can_Hw_Filter_Code_1"))
        self.pushButton_HWFilter_done = QtGui.QPushButton(self.groupBox_5)
        self.pushButton_HWFilter_done.setText(_translate("MainWindow", "Done", None))
        self.pushButton_HWFilter_done.setGeometry(QtCore.QRect(600, 600, 110, 30))
        self.pushButton_HWFilter_done.setObjectName(_fromUtf8("pushButton_HWFilter_done"))

        self.CanHWFilter_gb[filters_num -1].append(self.groupBox_5)

########## getting parameters from GUI #########################

    def get_controllers_parameters(self):
        controllers_parameters = []
        i = 0
        flag=False
        Can_ID_error=[]
        for controller in self.CanControllers_gb:

            controller_parameters = []

            con_ID=controller.findChildren(QtGui.QLineEdit,"Can_Controller_ID")
            Can_ID_error.append(int(con_ID[0].text()))
            con_base_address=controller.findChildren(QtGui.QLineEdit,"Can_Controller_Base_Address")
            con_TX=controller.findChildren(QtGui.QComboBox,"Can_Tx_Processing")
            Con_RX=controller.findChildren(QtGui.QComboBox,"Can_Rx_Processing")
            con_busoff=controller.findChildren(QtGui.QComboBox,"can_bus_off")
            con_wu=controller.findChildren(QtGui.QComboBox,"can_wakeup")
            con_activation = controller.findChildren(QtGui.QCheckBox,"can_controller_activation")

            con_wu_support= controller.findChildren(QtGui.QCheckBox,"can_wakeup_support")
            con_wu_API=controller.findChildren(QtGui.QCheckBox,"can_wakeup_API")
            con_default_BR=controller.findChildren(QtGui.QComboBox,"Baud_rate_config")
            if i==0:
              if Can_ID_error[0]!=0 :
                 string = "Can ID parameter in controllers must start with zero and continue without any gaps "
                 self.display_error(string)
              else:
                   flag = True
            else :
                    if   Can_ID_error[i-1]== Can_ID_error[i]-1 :
                        flag=True
                    else:
                         flag=False
                         string = "Can ID parameter in controllers must start with zero and continue without any gaps "
                         self.display_error(string)
            if flag==True:
                controller_parameters.append(con_ID[0].text())
                controller_parameters.append(str(con_activation[0].isChecked()))

                controller_parameters.append(con_base_address[0].text())
                controller_parameters.append(str(con_wu_support[0].isChecked()))
                controller_parameters.append(str(con_wu_API[0].isChecked()))
                controller_parameters.append(str(con_TX[0].currentText()))
                controller_parameters.append(str(Con_RX[0].currentText()))
                controller_parameters.append(str(con_busoff[0].currentText()))
                controller_parameters.append(str(con_wu[0].currentText()))
                controller_parameters.append(str(con_default_BR[0].currentText()))
                br=0
                br_id_error=[]
                for baudrate in self.CanBaudrates_gb[i]:
                    bauderate_parameters = []
                    br+=1
                    bd_ID=baudrate.findChildren(QtGui.QLineEdit,"BaudRate_config_ID")
                    br_id_error.append(int(bd_ID[0].text()))

                    bd_bd=baudrate.findChildren(QtGui.QLineEdit,"BaudRate")
                    baudrate_value=int(bd_bd[0].text())

                    bd_prop_seg=baudrate.findChildren(QtGui.QLineEdit,"Prop_seg")
                    bd_seg1=baudrate.findChildren(QtGui.QLineEdit,"Prop_seg1")
                    bd_seg2=baudrate.findChildren(QtGui.QLineEdit,"Prop_seg2")
                    bd_jump=baudrate.findChildren(QtGui.QLineEdit,"Sync_jumpwidth")
                    propseg = int(bd_prop_seg[0].text())
                    controllerseg1 = int(bd_seg1[0].text())
                    controllerseg2 =  int(bd_seg2[0].text())
                    SyncJumpWidth  =  int(bd_jump[0].text())
                    if propseg<1 :
                        string = "propseg in controller"+str(i+1)+"  baud_rate_config no."+str(br)+\
                            " must not be greater than 8 or less than 1"
                        self.display_error(string)
                    elif propseg>8:
                        string = "propseg in controller"+str(i+1)+" baud_rate_config no."+str(br)+\
                                " must not be greater than 8 or less than 1"
                        self.display_error(string)
                    elif controllerseg1>controllerseg2:
                           string = "controllerseg1 in controller"+str(i+1)+" baud_rate_config no."+str(br)+\
                                " must not be greater than controllerseg2"
                           self.display_error(string)
                    elif SyncJumpWidth  >controllerseg1:
                           string = "syncJumoWidth in controller"+str(i+1)+" baud_rate_config no."+str(br)+\
                                " must not be greater controllerseg1"
                           self.display_error(string)
                    elif controllerseg1<1 :
                        string = "controllerseg1 in controller"+str(i+1)+" baud_rate_config no."+str(br)+\
                            " must not be greater than 8 or less than 1"
                        self.display_error(string)
                    elif controllerseg1>8:
                        string = "controllerseg1 in controller"+str(i+1)+" baud_rate_config no."+str(br)+\
                                " must not be greater than 8 or less than 1"
                        self.display_error(string)
                    elif controllerseg2<1 :
                        string = "controllerseg2 in controller"+str(i+1)+" baud_rate_config no."+str(br)+\
                            " must not be greater than 8 or less than 1"
                        self.display_error(string)
                    elif controllerseg2>8:
                        string = "controllerseg2 in controller"+str(i+1)+"  baud_rate_config no."+str(br)+\
                                " must not be greater than 8 or less than 1"
                        self.display_error(string)
                    elif  SyncJumpWidth>4:
                        string = "syncJumoWidth in controller"+str(i+1)+" baud_rate_config no."+str(br)+\
                                " must not be greater than 4 or less than 1"
                        self.display_error(string)
                    elif (controllerseg2+controllerseg1+propseg)>24 :
                        string = "summation of (controllerseg2+controllerseg1+propseg) in controller"+str(i+1)\
                                 +" baud_rate_config no."+str(br)+" must not exceed 24"
                        self.display_error(string)
                    elif controllerseg2>(controllerseg1+1) :
                        string = "controllerseg2 in controller"+str(i+1)\
                                 +" baud_rate_config no."+str(br)+" must not exceed (controllerseg1+1)"
                        self.display_error(string)
                    elif br_id_error[0] != 0:
                        string = "BaudRate_config_ID parameters in Baudrate configurations in controller"+str(i+1)+\
                               " must start with zero and continue without any gaps"
                        self.display_error(string)
                    elif br > 1 and (br_id_error[br-2]!=br_id_error[br-1]-1) :
                        string = "BaudRate_config_ID parameters in Baudrate configurations in controller"+str(i+1)+\
                               " must start with zero and continue without any gaps"
                        self.display_error(string)
                    elif baudrate_value>1000 :
                         string = " Baudrate configuration"+str(br) +" in controller"+str(i+1)+\
                               " ,Baudrate value is invalid, values accepted from (1 to 1000)"
                         self.display_error(string)
                    elif baudrate_value == 0:
                         string = " Baudrate configuration"+str(br) +" in controller"+str(i+1)+\
                               " ,Baudrate value is invalid, values accepted from (1 to 1000)"
                         self.display_error(string)

                    else:

                        bauderate_parameters.append(bd_bd[0].text())
                        bauderate_parameters.append(bd_prop_seg[0].text())
                        bauderate_parameters.append(bd_seg1[0].text())
                        bauderate_parameters.append(bd_seg2[0].text())
                        bauderate_parameters.append(bd_jump[0].text())
                        bauderate_parameters.append(bd_ID[0].text())

                    controller_parameters.append(bauderate_parameters)
            if i<2 :

             if con_activation[0].isChecked():
                 self.num_of_generated_controllers+=1
             controllers_parameters.append(controller_parameters)
            i = i+1
            flag = False
        return controllers_parameters


    def get_canGeneral_parameters(self):
        CanGeneral = []

        gen_index = self.groupBox.findChildren(QtGui.QLineEdit,"Can_Index")
        gen_main_period = self.groupBox.findChildren(QtGui.QLineEdit,"Can_main_fn_Mode_period")
        gen_timeout = self.groupBox.findChildren(QtGui.QLineEdit,"Can_Timeout_Duration")
        gen_main_wakeup = self.groupBox.findChildren(QtGui.QLineEdit,"Can_Main_Fn_Wakeup")
        gen_mul_trans = self.groupBox.findChildren(QtGui.QCheckBox,"Can_mul_transmission")
        gen_icom = self.groupBox.findChildren(QtGui.QCheckBox,"Can_Public_icom_support")
        gen_BD_API = self.groupBox.findChildren(QtGui.QCheckBox,"Can_Set_baudrate_API")
        gen_version = self.groupBox.findChildren(QtGui.QCheckBox,"Can_version_info")
        gen_dev_error = self.groupBox.findChildren(QtGui.QCheckBox,"Can_Dev_error")
        bus_off_processing=self.groupBox.findChildren(QtGui.QLineEdit,"Can_busoff_processing")

        CanGeneral.append(str(gen_dev_error[0].isChecked()))
        CanGeneral.append(str(gen_mul_trans[0].isChecked()))
        CanGeneral.append(gen_timeout[0].text())
        CanGeneral.append(gen_main_wakeup[0].text())
        CanGeneral.append(gen_main_period[0].text())
        CanGeneral.append(gen_index[0].text())
        CanGeneral.append(str(gen_version[0].isChecked()))
        CanGeneral.append(str(gen_BD_API[0].isChecked()))
        CanGeneral.append(str(gen_icom[0].isChecked()))
        CanGeneral.append(bus_off_processing[0].text())


        # print(CanGeneral)
        return CanGeneral




    def get_Hardware_parameters(self):
        count = 0
        hw_object_error = []
        Hardware_Objects = []

        gen_mul_trans = self.groupBox.findChildren(QtGui.QCheckBox,"Can_mul_transmission")
        for HW_Object in self.CanHardwareObjects_gb:
            HW_Object_Parameters = []
            Can_Object_Id = HW_Object.findChildren(QtGui.QLineEdit, "Can_Object_Id")
            hw_object_error.append(int(Can_Object_Id[0].text()))

            Can_HardwareObject_UsesPolling = HW_Object.findChildren(QtGui.QCheckBox, "Can_HardwareObject_UsesPolling")
            HW_object_count = HW_Object.findChildren(QtGui.QLineEdit, "HW_Object_count")
            hw_count = int(HW_object_count[0].text())

            Can_Object_Type = HW_Object.findChildren(QtGui.QComboBox, "Can_Object_Type")
            object_type =str(Can_Object_Type[0].currentText())


            Can_HandleType = HW_Object.findChildren(QtGui.QComboBox, "Can_HandleType")
            handle_type =str(Can_HandleType[0].currentText())

            Can_Id_Type = HW_Object.findChildren(QtGui.QComboBox, "Can_Id_Type")
            Can_Trigger_Transmit_Enable = HW_Object.findChildren(QtGui.QCheckBox, "Can_Trigger_Transmit_Enable")
            Can_Controller_ref = HW_Object.findChildren(QtGui.QComboBox, "Can_Controller_ref")


            if hw_object_error [0]!=0:
                string="hardware object ID paramters in hardware objects must begin with zero " \
                       "and continue without any gaps"
                self.display_error(string)
                self.generation_flag=False
            elif count>0 and hw_object_error[count-1]!=hw_object_error[count]-1 :
                   string="hardware object ID paramters in hardware objects must begin with zero " \
                       "and continue without any gaps"
                   self.display_error(string)
                   self.generation_flag = False

            elif hw_count<1:
                 string ="HW objectcount paramter in hardware object"+str(count+1)+" shall be greater than zero"
                 self.display_error(string)
                 self.generation_flag=False

            elif hw_count<2 and handle_type == "BASIC":
                 string ="HW objectcount paramter in hardware object"+str(count+1)+" shall be greater than 1 for " \
                         "a Basic type object"
                 self.display_error(string)
                 self.generation_flag = False
            elif object_type =="RECEIVE" and self.Can_HW_Filters_Count [count] != 2:
                string="In hardware object"+str(count+1)+" a receive object shall have a filter container"
                self.display_error(string)
                self.generation_flag = False
            elif  handle_type == "BASIC"  and gen_mul_trans[0].isChecked()==True and Can_Object_Type =="TRANSMIT" and hw_count < 2:
                   string="In hardware object"+str(count+1)+" in case of Multiplexed Transmission is set" \
                           " value  of hwobjectcount shall be at least 2"
                   self.display_error(string)
                   self.generation_flag = False

            else:
                        self.generation_flag=True
                        HW_Object_Parameters.append(str(Can_HandleType[0].currentText()))
                        HW_Object_Parameters.append(str(Can_Object_Type[0].currentText()))
                        HW_Object_Parameters.append(str(Can_Id_Type[0].currentText()))
                        HW_Object_Parameters.append(Can_Object_Id[0].text())
                        HW_Object_Parameters.append(str(Can_HardwareObject_UsesPolling[0].isChecked()))
                        HW_Object_Parameters.append(str(Can_Trigger_Transmit_Enable[0].isChecked()))
                        HW_Object_Parameters.append(str(Can_Controller_ref[0].currentText()))
                        HW_Object_Parameters.append(str(HW_object_count[0].text()))
            for HW_Filter in self.CanHWFilter_gb[count]:
                    HW_Filter_Parameters=[]
                    Can_Hw_Filter_Mask=HW_Filter.findChildren(QtGui.QLineEdit,  "Can_Hw_Filter_Mask_1")
                    Can_Hw_Filter_Code=HW_Filter.findChildren(QtGui.QLineEdit,"Can_Hw_Filter_Code_1")
                    HW_Filter_Parameters.append(Can_Hw_Filter_Mask[0].text())
                    HW_Filter_Parameters.append(Can_Hw_Filter_Code[0].text())
                    if handle_type == "FULL" and str(Can_Hw_Filter_Mask[0].text()) != "FFFFFFFF":
                        string="In hardware object"+str(count+1)+" in case of FUll handle type"\
                           " mask must be equal to FFFFFFFF"
                        self.display_error(string)
                        self.generation_flag = False
                    elif handle_type == "BASIC" and (str(Can_Hw_Filter_Mask[0].text()) == str(Can_Hw_Filter_Code[0].text())):
                        string="In hardware object"+str(count+1)+" in case of BASIC handle type"\
                           " filter code and mask must (not) be equal"
                        self.display_error(string)
                        self.generation_flag = False
                    else:
                        HW_Object_Parameters.append(HW_Filter_Parameters)

            Hardware_Objects.append(HW_Object_Parameters)
            count = count+1
        return Hardware_Objects



    def generate_ARXML(self):
        x = create_ARXML(os.path.join(self.path_1, "ARXML/Can_ARXML"))
        x.create()
        general_list = []
        controllers_list = []
        HW_Objects_list = []
        general_list = self.get_canGeneral_parameters()
        controllers_list = self.get_controllers_parameters()
    #    print (controllers_list)#for testign
        HW_Objects_list = self.get_Hardware_parameters()
    #    print(HW_Objects_list)#fro testing
        x.Add_CanGeneral(general_list)

        for i in range(0, len(controllers_list)):
            x.Add_CanController(controllers_list[i])
        for j in range(0, len(HW_Objects_list)):
            x.Add_CanHWObject(HW_Objects_list[j])



if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    CanTool = QtGui.QMainWindow()
    CanTool.setWindowIcon(QIcon('icon-2.png'))
    splash_pix = QtGui.QPixmap('back.png')
    splash = QtGui.QSplashScreen(splash_pix, Qt.WindowStaysOnTopHint)
    progressBar = QtGui.QProgressBar(splash)
    progressBar.setGeometry(0, splash_pix.height() - 50, splash_pix.width(), 20)
    splash.setMask(splash_pix.mask())
    splash.show()
    splash.showMessage("<h1><font color='black'>Can Configuration Tool</font></h1>", Qt.AlignTop | Qt.AlignCenter, Qt.black)
    for i in range(0, 100):
        progressBar.setValue(i)
        t = time.time()
        while time.time() < t + 0.01:
            app.processEvents()
    time.sleep(1)


    ui = Ui_CanTool()
    ui.setupUi(CanTool)
    CanTool.show()
    splash.finish(CanTool)
    # ui.display_error("err0r")
    sys.exit(app.exec_())
