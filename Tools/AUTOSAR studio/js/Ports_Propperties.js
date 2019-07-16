var Ports_Container = document.getElementById("chPorts");
let selected_P_interface_name;
let selected_P_interface_index;
let selected_R_interface_name;
let selected_R_interface_index;

var Port_Name = [];

let Global_op_arg_DE_name = 0,
    Global_op_arg_DE_type = 0;

/* Generate P-Ports */
let Create_P_Port = (_index, port, ArrayPosition) => {
	let css_style = `background: ${port.portColor}; color: #FFF; text-shadow: 1px 1px 1px #2d2d2d; box-shadow: 1px 1px 1px #EEE`;

    $('#chPorts').append(`
    	<button class="btn Port_S P_Port btn-block"
    	type="button"
    	style="${css_style}"
    	data-port-index="${_index}"
    	data-port-interface-name="${port.interface_name}"
    	data-port-name="${port.portId}"
    	data-port-type="${port.portType}"
    	data-array-position="${ArrayPosition}" >
    		<span class="current">${port.portId}</span> <br> <small>(type: ${port.portType})</small>
    	</button>
    `);
}

/* Generate R-Ports */
let Create_R_Port = (_index, port, ArrayPosition) => {
	let css_style = `background: ${port.portColor}; color: #FFF; text-shadow: 1px 1px 1px #2d2d2d; box-shadow: 1px 1px 1px #EEE`;

	$('#chPorts').append(`
    	<button class="btn Port_S R_Port btn-block"
    	type="button"
    	style="${css_style}"
    	data-port-index="${_index}"
    	data-port-interface-name="${port.interface_name}"
    	data-port-name="${port.portId}"
    	data-port-type="${port.portType}"
    	data-array-position="${ArrayPosition}" >
    		<span class="current">${port.portId}</span> <br> <small>(type: ${port.portType})</small>
    	</button>
    `);
}

let Create_Data_Element = (DE_Name , DE_Type) =>{
    let DEname         = document.getElementById("DEname"),
        DEvalue        = document.getElementById("DEvalue"),
        newDEname      = document.createElement("a"),
        newDEnameValue = document.createTextNode(DE_Name),
        newDEtype      = document.createElement("a"),
        newDEtypeValue = document.createTextNode(DE_Type);

    newDEname.classList.add("list-group-item" , "list-group-item-action" , "DE_name");
    newDEname.appendChild(newDEnameValue);

    newDEtype.classList.add("list-group-item" , "list-group-item-action" , "DE_type");
    newDEtype.appendChild(newDEtypeValue);

    DEname.appendChild(newDEname);
    DEvalue.appendChild(newDEtype);
}

let Create_Arg_Data_Element = (DE_Name , DE_Type , DE_name_ID , DE_type_ID) =>{
    let DEname         = document.getElementById(DE_name_ID),
        DEvalue        = document.getElementById(DE_type_ID),

        newDEname      = document.createElement("a"),
        newDEnameValue = document.createTextNode(DE_Name),
        newDEtype      = document.createElement("a"),
        newDEtypeValue = document.createTextNode(DE_Type);

    newDEname.classList.add("list-group-item" , "list-group-item-action" , "DE_name");
    newDEname.appendChild(newDEnameValue);

    newDEtype.classList.add("list-group-item" , "list-group-item-action" , "DE_type");
    newDEtype.appendChild(newDEtypeValue);

    DEname.appendChild(newDEname);
    DEvalue.appendChild(newDEtype);
}

let Create_Single_Operation = (op_name , op_arg) =>{
    let OperationElement = document.getElementById("OperationElement"),
        single_op   = document.createElement("div"),
        Row_Elment  = document.createElement("div"),
        op_name_col  = document.createElement("div"),
        arg_name_col  = document.createElement("div"),
        arg_type_col  = document.createElement("div")
        op_name_list_group = document.createElement("div"),
        op_name_list_group_item = document.createElement("a"),
        arg_name_list_group = document.createElement("div"),
        arg_type_list_group = document.createElement("div"),
        break_tag           = document.createElement("br"),
        single_op_name = document.createTextNode(op_name);

        break_tag.classList.add("breaker");
        single_op.classList.add("single_op");
        Row_Elment.classList.add("row");

        op_name_col.classList.add("col-lg-4");
        op_name_list_group.classList.add("list-group");
        op_name_list_group_item.classList.add("list-group-item" , "list-group-item-action" , "op_name");
        op_name_list_group_item.appendChild(single_op_name);
        op_name_list_group.appendChild(op_name_list_group_item);
        op_name_col.appendChild(op_name_list_group);

        arg_name_col.classList.add("col-lg-4");
        arg_name_list_group.classList.add("list-group");
        let local_op_arg_DE_name = 'op_arg_DE_name' + Global_op_arg_DE_name;
        arg_name_list_group.setAttribute("id" , local_op_arg_DE_name);
        arg_name_col.appendChild(arg_name_list_group);

        arg_type_col.classList.add("col-lg-4");
        arg_type_list_group.classList.add("list-group");
        let local_op_arg_DE_type = 'op_arg_DE_type' + Global_op_arg_DE_type;
        arg_type_list_group.setAttribute("id" , local_op_arg_DE_type);
        arg_type_col.appendChild(arg_type_list_group);



        Row_Elment.appendChild(op_name_col);
        Row_Elment.appendChild(arg_name_col);
        Row_Elment.appendChild(arg_type_col);
        single_op.appendChild(Row_Elment);
        OperationElement.appendChild(single_op);
        OperationElement.appendChild(break_tag);


        for(let k = 0 ; k < op_arg.length ; k++){
            Create_Arg_Data_Element(op_arg[k].name , op_arg[k].datatype , local_op_arg_DE_name , local_op_arg_DE_type);
        }

        Global_op_arg_DE_name++;
        Global_op_arg_DE_type++;
}

let Remove_Data_Elements = () => {
	// $('#DEname, #DEvalue').text('');
    let DE_Name_List = document.getElementsByClassName("DE_name"),
        DE_Type_List = document.getElementsByClassName("DE_type"),
        DE__Name     = document.getElementById("DEname"),
        DE__Type     = document.getElementById("DEvalue");
        while (DE__Name.childNodes[1] && DE__Type.childNodes[1]) {
            DE__Name.removeChild(DE__Name.childNodes[1]);
            DE__Type.removeChild(DE__Type.childNodes[1]);
        }
}
let Remove_Operations=()=>{
        $(".single_op").parent().children().not(':first-child').remove();
}

let Remove_Single_Operation = (ClassName) => {
    let Elements = document.getElementsByClassName(ClassName),
        Element_Breaker = document.getElementsByClassName("breaker");
    while (Elements.length > 0) {
        Elements[0].parentNode.removeChild(Elements[0]);
        Element_Breaker[0].parentNode.removeChild(Element_Breaker[0]);
    }
}

let Create_SR_Port_Interface = (PIname) =>{
    let PortInterFaceSelect = document.getElementById("PortInterFaceSelect"),
        PIOption            = document.createElement("option"),
        PIOptionValue       = document.createTextNode(PIname);
        PIOption.classList.add("PI_Options" , "PortInterface");
        PIOption.appendChild(PIOptionValue);
        PIOption.setAttribute("value" , PIname);
        PortInterFaceSelect.appendChild(PIOption);
}

let Create_CS_Port_Interface = (PIname) =>{
    let PortInterFaceSelect = document.getElementById("CSPortInterFaceSelect"),
        PIOption            = document.createElement("option"),
        PIOptionValue       = document.createTextNode(PIname);
        PIOption.classList.add("PI_Options" , "PortInterface");
        PIOption.appendChild(PIOptionValue);
        PIOption.setAttribute("value" , PIname);
        PortInterFaceSelect.appendChild(PIOption);
}

let Create_DE_Header = () =>{
    let DEname         = document.getElementById("DEname"),
        DEvalue        = document.getElementById("DEvalue"),
        newDEname      = document.createElement("a"),
        newDEnameValue = document.createTextNode("Date Element Name"),
        newDEtype      = document.createElement("a"),
        newDEtypeValue = document.createTextNode("Date Element Type");

    newDEname.classList.add("list-group-item" , "list-group-item-action" , "active" , "active_color");
    newDEname.appendChild(newDEnameValue);

    newDEtype.classList.add("list-group-item" , "list-group-item-action" , "active" , "active_color");
    newDEtype.appendChild(newDEtypeValue);

    DEname.appendChild(newDEname);
    DEvalue.appendChild(newDEtype);
}

let Create_OP_Header = () =>{
    let OP_name        = document.getElementById("OP_name"),
        OP_DE_name     = document.getElementById("OP_DE_name"),
        OP_DE_value    = document.getElementById("OP_DE_value"),
        newOPname      = document.createElement("a"),
        newOPnameValue = document.createTextNode("OP Name"),
        newDEname      = document.createElement("a"),
        newDEnameValue = document.createTextNode("ARG Name"),
        newDEtype      = document.createElement("a"),
        newDEtypeValue = document.createTextNode("ARG Type");

    newOPname.classList.add("list-group-item" , "list-group-item-action" , "active" , "active_color");
    newOPname.appendChild(newOPnameValue);

    newDEname.classList.add("list-group-item" , "list-group-item-action" , "active" , "active_color");
    newDEname.appendChild(newDEnameValue);

    newDEtype.classList.add("list-group-item" , "list-group-item-action" , "active" , "active_color");
    newDEtype.appendChild(newDEtypeValue);

    OP_name.appendChild(newOPname);
    OP_DE_name.appendChild(newDEname);
    OP_DE_value.appendChild(newDEtype);
}

/* Show and Handle Ports oparations */
let Single_Port1_Submittion          = document.getElementById("Single_Port1_Submittion"),
 	Single_Port2_Submittion          = document.getElementById("Single_Port2_Submittion"),
    Ports_Info_Form_SenderServer    = document.getElementById("Ports_Info_Form_SenderServer"),
    Ports_Info_Form_ReceiverClient  = document.getElementById("Ports_Info_Form_ReceiverClient");

let AppendPortNamesToLeftSection = () => {
	var softwareComponentName = '';

	myDiagram.selection.each(function (part) {
    	if (part instanceof go.Node) {
        	softwareComponentName = part.data.name;
       	}
    });

	// Empty old ports name in appended elements
	$('#Ports_Properties #ports_main_details #chPorts').text('');
    $.each(JSON.parse(myDiagram.model.toJson()).nodeDataArray, function(i, SWC){
		if(SWC.name == softwareComponentName) {
			$.each(SWC.leftArray, function(i, v){
				switch(v.portType) {
			 		case 'sender':
			 		case 'reciever':
			 			Create_P_Port(i, v, 'leftArray');
            			Port_Name.push(v.portId);
			 		break;
			 		case 'server':
			 		case 'client':
		                // Create_R_Port(i, v.portId, v.portType, v.portColor, 'leftArray');
		                Create_R_Port(i, v, 'leftArray');
		                Port_Name.push(v.portId);
			 		break;
			 	}
			});
			$.each(SWC.rightArray, function(i, v){
				switch(v.portType) {
					case 'sender':
			 		case 'reciever':
			 			Create_P_Port(i, v, 'rightArray');
            			Port_Name.push(v.portId);
			 		break;
			 		case 'server':
			 		case 'client':
		                Create_R_Port(i, v, 'rightArray');
		                Port_Name.push(v.portId);
			 		break;
			 	}
			});
		}
    })
}

let Remove_OP_header = () => {
    $('#OP_name').text('');
    $('#OP_DE_name').text('');
    $('#OP_DE_value').text('');
}

let At_PPort_InterfaceChange = () => {
	let DataElement = document.getElementById("DataElement");

	Create_DE_Header();
	$('#PortInterFaceSelect').change(function(){
        Remove_Data_Elements();
        DataElement.style.display = "block";

    	let current_index = $(this)[0].selectedIndex;
    	selected_P_interface_name = $(`#PortInterFaceSelect :eq(${current_index})`).val();
    	selected_P_interface_index = current_index;

        for(let i = 0; i < SRInterfacesarr[current_index].dataelements.length; i++){
        	let current_item = SRInterfacesarr[current_index].dataelements[i];
            Create_Data_Element(current_item.name , current_item.type);
        }
	}).change()
}

let At_RPort_InterfaceChange = () => {
    let DataElement = document.getElementById("DataElement");

	$('#CSPortInterFaceSelect').change(function(){
        // Remove_Single_Operation("single_op");
        // Remove_OP_header();
        // Create_OP_Header();
        DataElement.style.display = "block";

        let current_index = $(this)[0].selectedIndex;
        selected_R_interface_name = $(`#CSPortInterFaceSelect :eq(${current_index})`).val();
    	selected_R_interface_index = current_index;
        Remove_Operations();
        for(let s = 0 ; s < CSInterfacesarr[current_index].operations.length ; s++){
            Create_Single_Operation(CSInterfacesarr[current_index].operations[s].name , CSInterfacesarr[current_index].operations[s].arguments);
        }
	}).change()
}

let P_Ports_Configurations = () => {
    let P_Ports      = document.getElementsByClassName("P_Port");

    for(let i = 0 ; i<P_Ports.length; i++){
        P_Ports[i].addEventListener('click' , function(){
        	// empty PortInterFaceSelect
    		$('#PortInterFaceSelect').text('');

            let current_port_name = P_Ports[i].firstChild.nextSibling.innerText;
            PortUpdateName.innerText = current_port_name + " ";
            $('#Ports_Info_Form_SenderServer .InputPortShortName').val(current_port_name);

            for(let z = 0 ; z<SRInterfacesarr.length; z++){
                Create_SR_Port_Interface(SRInterfacesarr[z].name);
            }

           	$('#Single_Port1_Submittion').attr('data-port-name', current_port_name);

			let current_port = $(`#chPorts > button[data-port-name="${current_port_name}"]`);
			let current_interface_name = current_port.data('port-interface-name');

			$(`#PortInterFaceSelect option`).each(function(i, v){
				if($(this).text() == current_interface_name) {
					$('#PortInterFaceSelect').val(current_interface_name).trigger('change');
				}
			});

            Ports_Info_Form_SenderServer.style.display = "block";
            Ports_Info_Form_ReceiverClient.style.display = "none";
    		At_PPort_InterfaceChange()
        });


        // Ports_Info_Form_SenderServer.style.display = "block";
    }
}

let R_Ports_Configurations = () => {
    let R_Ports  = document.getElementsByClassName("R_Port");
    for(let i = 0 ; i<R_Ports.length; i++){
        R_Ports[i].addEventListener('click' , function(){
        	// empty PortInterFaceSelect
    		$('#CSPortInterFaceSelect').text('');

    		let current_port_name = R_Ports[i].firstChild.nextSibling.innerText;
            PortUpdateName.innerText = current_port_name + " ";
            $('#Ports_Info_Form_ReceiverClient .InputPortShortName').val(current_port_name);

            for(let z = 0 ; z<CSInterfacesarr.length; z++){
                Create_CS_Port_Interface(CSInterfacesarr[z].name);
            }

            $('#Single_Port2_Submittion').attr('data-port-name', current_port_name);

            let current_port = $(`#chPorts > button[data-port-name="${current_port_name}"]`);
			let current_interface_name = current_port.data('port-interface-name');

			$(`#CSPortInterFaceSelect option`).each(function(i, v){
				if($(this).text() == current_interface_name) {
					$('#CSPortInterFaceSelect').val(current_interface_name).trigger('change');
				}
			});

            Ports_Info_Form_SenderServer.style.display = "none";
            Ports_Info_Form_ReceiverClient.style.display = "block";
    		At_RPort_InterfaceChange();
        });
    }
}

let saveChangesToMainObject__PPorts = () => {
    let current_port_name = $('#Single_Port1_Submittion').attr('data-port-name');
	let new_port_name = $('#Single_Port1_Submittion').parent().find('.InputPortShortName').val()
    var error = false;
    if (current_port_name!=new_port_name)
    {
	jsonobject=JSON.parse(myDiagram.model.toJson());  //TODO
	allSwcs=jsonobject.nodeDataArray
	for(var i=0;i<allSwcs.length;i++)
	{
		iteratorArray=allSwcs[i].leftArray
		if(allSwcs[i].rightArray!=undefined) iteratorArray=iteratorArray.concat(allSwcs[i].rightArray)
		if(iteratorArray==undefined)iteratorArray=[];
		for(var k=0;k<iteratorArray.length;k++)
		{
		 	if(iteratorArray[k].portId==new_port_name) 	error=true

		}
	 }
	}
    if(error){
        alert("Please enter a unique port name");
    } 	
    else if(new_port_name.length==0) {
            alert('please enter port name ');
            }
    else if (/^[A-Za-z0-9_]+$/.test(new_port_name)==false)
            {
            alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
            }
    else if (/^[A-Za-z]+$/.test(new_port_name[0])==false)
            {
                alert('please enter name start with letter');
            }
	else {
        var softwareComponentName = '';
        myDiagram.selection.each(function (part) {
            if (part instanceof go.Node) {
                softwareComponentName = part.data.name;
            }
        });

        let cuurent_SWC_index;
        Object.keys(myDiagram.model.nodeDataArray).forEach(function(index) {
            if(myDiagram.model.nodeDataArray[index].name == softwareComponentName) {
                cuurent_SWC_index = index
            }
        })        
        let current_port = $(`#chPorts > button[data-port-name="${current_port_name}"]`);
        let port_index = current_port.data('port-index');
        let port_type = current_port.data('port-type');
        let array_position = current_port.data('array-position');
	 	let current_port_place = myDiagram.model.nodeDataArray[cuurent_SWC_index][array_position][port_index]
	 	myDiagram.model.setDataProperty(current_port_place, 'portId', new_port_name);

	 	let dataElements = [];
	 	let type;

	 	switch(port_type) {
	 		case 'sender' :
	 		case 'reciever':
	 			type = 'S_R';
	 			interface_name = selected_P_interface_name;
	 			dataElements.push({
	 				type: type,
	 				dataElements: SRInterfacesarr[selected_P_interface_index].dataelements
	 			})
	 		break;
	 	}

	 	myDiagram.model.setDataProperty(current_port_place, 'interface_name', interface_name);
		myDiagram.model.setDataProperty(current_port_place, 'data_elements', dataElements);
        let Port_form  = document.getElementById("Ports_Info_Form_SenderServer");
        Port_form.style.display="none";
        Ports_Handler_Refresh();	}

}

let saveChangesToMainObject__RPorts = () => {
    let current_port_name = $('#Single_Port2_Submittion').attr('data-port-name');
	let new_port_name = $('#Single_Port2_Submittion').parent().find('.InputPortShortName').val()
    var error = false;
    if (current_port_name!=new_port_name)
    {
	jsonobject=JSON.parse(myDiagram.model.toJson());  //TODO
	allSwcs=jsonobject.nodeDataArray
	for(var i=0;i<allSwcs.length;i++)
	{
		iteratorArray=allSwcs[i].leftArray
		if(allSwcs[i].rightArray!=undefined) iteratorArray=iteratorArray.concat(allSwcs[i].rightArray)
		if(iteratorArray==undefined)iteratorArray=[];
		for(var k=0;k<iteratorArray.length;k++)
		{
		 	if(iteratorArray[k].portId==new_port_name) 	error=true

		}
	 }
	}
    if(error){
        alert("Please enter a unique port name");
    }   
    else if(new_port_name.length==0) {
            alert('please enter port name ');
            }
    else if (/^[A-Za-z0-9_]+$/.test(new_port_name)==false)
            {
            alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
            }
    else if (/^[A-Za-z]+$/.test(new_port_name[0])==false)
            {
                alert('please enter name start with letter');
            }

	else {
        var softwareComponentName = '';
        myDiagram.selection.each(function (part) {
            if (part instanceof go.Node) {
                softwareComponentName = part.data.name;
            }
        });

        let cuurent_SWC_index;
        Object.keys(myDiagram.model.nodeDataArray).forEach(function(index) {
            if(myDiagram.model.nodeDataArray[index].name == softwareComponentName) {
                cuurent_SWC_index = index
            }
        })       
        let current_port = $(`#chPorts > button[data-port-name="${current_port_name}"]`);
        let port_index = current_port.data('port-index');
        let port_type = current_port.data('port-type');
        let array_position = current_port.data('array-position');
	 	let current_port_place = myDiagram.model.nodeDataArray[cuurent_SWC_index][array_position][port_index]
	 	myDiagram.model.setDataProperty(current_port_place, 'portId', new_port_name);

	 	let dataElements = [];
	 	let type;

	 	switch(port_type) {
	 		case 'server':
	 		case 'client':
	 			type = 'C_S';
	 			interface_name = selected_R_interface_name
	 			dataElements.push({
	 				type: type,
	 				operations: CSInterfacesarr[selected_R_interface_index].operations
	 			})
	 		break;
	 	}

	 	myDiagram.model.setDataProperty(current_port_place, 'interface_name', interface_name);
		myDiagram.model.setDataProperty(current_port_place, 'data_elements', dataElements);
        let Port_form  = document.getElementById("Ports_Info_Form_ReceiverClient");
        Port_form.style.display="none";
        Ports_Handler_Refresh();
	}

}

let Ports_Handler = () => {
    let PortUpdateName = document.getElementById("PortUpdateName");

    // Add all actions after props modal shown
    $('#PropModal').on('show.bs.modal', function (e) {
    	AppendPortNamesToLeftSection();

        P_Ports_Configurations();
        R_Ports_Configurations();

	    /* save ports changes button */
	    $('body').delegate('#Single_Port1_Submittion', 'click', function(){
	    	saveChangesToMainObject__PPorts();
	    });

	    $('body').delegate('#Single_Port2_Submittion', 'click', function(){
	        saveChangesToMainObject__RPorts();
	    });
    })
}
let Ports_Handler_Refresh = () => {
    // Add all actions after props modal shown
    AppendPortNamesToLeftSection();
    P_Ports_Configurations();
    R_Ports_Configurations();
}
Ports_Handler();

// console.log(datatypesselected);
// console.log(SRInterfacesarr);
// console.log(CSInterfacesarr);
// console.log(InterfacesNames);
