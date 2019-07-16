function fetchPortsXML(XML) {
	let softwareComponentName;
	let callback_string;
	let ports = [];
	// get software component name
	myDiagram.selection.each(function (part) {
		if (part instanceof go.Node) {
        	softwareComponentName = part.data.name;
       	}
    });

	// filter current needed ports
	$.each(myDiagram.model.nodeDataArray, function(i, v){
		if(v.name == softwareComponentName) {
			$.each(myDiagram.model.nodeDataArray[i].leftArray, function(i1, v1){
				ports.push(v1)
			});
			$.each(myDiagram.model.nodeDataArray[i].rightArray, function(i1, v1){
				ports.push(v1)
			});
		}
	})
	function P_PORT_PROTOTYPE_generation(port, XML) {
		XML.BeginNode("P-PORT-PROTOTYPE");
			XML.Node("SHORT-NAME", port.portId);
			senderbool=false;
			XML.BeginNode("PROVIDED-COM-SPECS");
				$.each(port.data_elements, function(i2, dataElement) {
					switch(dataElement.type) {
						case 'S_R':
						    senderbool=true;
							$.each(dataElement.dataElements, function(i3, element){
		 						XML.BeginNode("NONQUEUED-SENDER-COM-SPEC");
		 							XML.BeginNode("DATA-ELEMENT-REF");
		 								XML.Attrib("DEST", "VARIABLE-DATA-PROTOTYPE");
		 								XML.WriteString(`/PortInterfaces/${port.interface_name}/${element.name}${window.closer}`);
		 							XML.EndNode();
		 						XML.EndNode();								
							});
						
						break;
						case 'C_S':
							$.each(dataElement.operations, function(i3, element){
		 						XML.BeginNode("SERVER-COM-SPEC");
		 							XML.BeginNode("OPERATION-REF");
		 								XML.Attrib("DEST", "CLIENT-SERVER-OPERATION");
		 								XML.WriteString(`/PortInterfaces/${port.interface_name}/${element.name}${window.closer}`);
		 							XML.EndNode();
		 						XML.EndNode();
							
							});
							
						break;
					}
				})
			XML.EndNode();
			if(senderbool)
			{
			XML.BeginNode("PROVIDED-INTERFACE-TREF");
				XML.Attrib("DEST", "SENDER-RECEIVER-INTERFACE");
				XML.WriteString(`/PortInterfaces/${port.interface_name}${window.closer}`);
			XML.EndNode();					
			}
			else
			{
			XML.BeginNode("PROVIDED-INTERFACE-TREF");
				XML.Attrib("DEST", "CLIENT-SERVER-INTERFACE");
				XML.WriteString(`/PortInterfaces/${port.interface_name}${window.closer}`);
			XML.EndNode();					
			}
		XML.EndNode();

		return XML;
	}

	function R_PORT_PROTOTYPE_generation(port, XML) {
		XML.BeginNode("R-PORT-PROTOTYPE");
			XML.Node("SHORT-NAME", port.portId);
			receiverbool=false;
			XML.BeginNode("REQUIRED-COM-SPECS");
				$.each(port.data_elements, function(i2, dataElement) {
					switch(dataElement.type) {
						case 'S_R':
						    receiverbool=true;
							$.each(dataElement.dataElements, function(i3, element){
		 						XML.BeginNode("NONQUEUED-RECEIVER-COM-SPEC");
		 							XML.BeginNode("DATA-ELEMENT-REF");
		 								XML.Attrib("DEST", "VARIABLE-DATA-PROTOTYPE");
		 								XML.WriteString(`/PortInterfaces/${port.interface_name}/${element.name}${window.closer}`);
		 							XML.EndNode();
		 						XML.EndNode();								
							});

						break;
						case 'C_S':
							$.each(dataElement.operations, function(i3, element){
		 						XML.BeginNode("CLIENT-COM-SPEC");
		 							XML.BeginNode("OPERATION-REF");
		 								XML.Attrib("DEST", "CLIENT-SERVER-OPERATION");
		 								XML.WriteString(`/PortInterfaces/${port.interface_name}/${element.name}${window.closer}`);
		 							XML.EndNode();
		 						XML.EndNode();
									
							});
						
						break;
					}
				})
			XML.EndNode();
			if(receiverbool)
			{
			XML.BeginNode("REQUIRED-INTERFACE-TREF");
				XML.Attrib("DEST", "SENDER-RECEIVER-INTERFACE");
				XML.WriteString(`/PortInterfaces/${port.interface_name}${window.closer}`);
			XML.EndNode();					
			}
			else
			{
			XML.BeginNode("REQUIRED-INTERFACE-TREF");
				XML.Attrib("DEST", "CLIENT-SERVER-INTERFACE");
				XML.WriteString(`/PortInterfaces/${port.interface_name}${window.closer}`);
			XML.EndNode();					
			}			
		XML.EndNode();

		return XML;
	}

	$.each(ports, function(i, port) {
		switch(port.portType) {
	 		case 'sender':
	 			XML = P_PORT_PROTOTYPE_generation(port, XML);
	 		break;
	 		case 'server':
	 			XML = P_PORT_PROTOTYPE_generation(port, XML);
	 		break;
	 		case 'reciever':
	 			XML = R_PORT_PROTOTYPE_generation(port, XML);
	 		break;
	 		case 'client':
	 			XML = R_PORT_PROTOTYPE_generation(port, XML);
	 		break;
	 	}
	})
}

function Generate_Swc_Arxml(){

		save(); // save actions in connection area to json textarea

		var jsonDataString = myDiagram.model.toJson();
		var jsonData = JSON.parse(jsonDataString);
	//	var testUUID = "C6D70561-A98B-4387-A0EB-6C661B3FC005";
		var softwareComponentName;
		var SWC_INTERNAL_BEHAVIOR_2nd_path = softwareComponentName+"_InternalBehavior";
		// get project Name
	    var queryString = decodeURIComponent(window.location.search);
	    queryString = queryString.substring(1);
	    var queries = queryString.split("&");
	    var projectName = queries.toString().trim();

		// get software component name
		myDiagram.selection.each(function (part) {
			if (part instanceof go.Node) {
	        	softwareComponentName = part.data.name;
	       	}
	    });
		var InternalBehviorName = softwareComponentName+"_InternalBehavior";
		var SwcImplementationName=softwareComponentName+"_Implementation";
		// create the XML structure recursively
		var XML = new XMLWriter();
			XML.BeginNode("AUTOSAR");
				XML.Attrib("xsi:schemaLocation", "http://autosar.org/schema/r4.0 AUTOSAR_4-3-0.xsd");
				XML.Attrib("xmlns", "http://autosar.org/schema/r4.0");
				XML.Attrib("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
				XML.BeginNode("AR-PACKAGES");
						XML.BeginNode("AR-PACKAGE");
						//	XML.Attrib("UUID", testUUID);
							XML.Node("SHORT-NAME", projectName);
							XML.BeginNode("ELEMENTS");
								XML.BeginNode("APPLICATION-SW-COMPONENT-TYPE");
							//		XML.Attrib("UUID", testUUID);
									XML.Node("SHORT-NAME", softwareComponentName);
									XML.BeginNode("PORTS");
										fetchPortsXML(XML);
									XML.EndNode();
									XML.BeginNode("INTERNAL-BEHAVIORS");
									  // Generate Internal Behavior
                                      Generate_Internal_Behavior(XML,softwareComponentName);
									XML.EndNode();
								XML.EndNode();
								XML.BeginNode("SWC-IMPLEMENTATION");
								//	XML.Attrib("UUID", testUUID);
									XML.Node("SHORT-NAME", SwcImplementationName);
									XML.BeginNode("BEHAVIOR-REF");
										XML.Attrib("DEST", "SWC-INTERNAL-BEHAVIOR");
										XML.WriteString(`/${projectName}/${softwareComponentName}/${InternalBehviorName}${window.closer}`);
									XML.EndNode();
								XML.EndNode();
							XML.EndNode();
						XML.EndNode();
				XML.EndNode();
			XML.EndNode();
		XML.Close();

		// init xml export data
		var header_tag = `<?xml version="1.0" encoding="UTF-8"?>`; // header
		var xml_result = header_tag + XML.ToString(); // append internal contect with header
		//save_arxml_file(btn_id, formatXml(xml_result, '  '), 'SWCApplication.arxml', 'text/plain'); // save & download file
		GenerateArxml(formatXml(xml_result, '  '),'SWCApplication');
}
