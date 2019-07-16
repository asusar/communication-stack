function showNewSoftwareComponentModal(e)
{
	var SoftwareComponentModal = $('#newSoftwareComponentModal');
	position=e.diagram.lastInput.documentPoint;
	var error=false;
	var location = position.x+" "+position.y;
	SoftwareComponentModal.modal('show');
	document.getElementById('component_name').value = '';
	SoftwareComponentModal.undelegate('.save-software-component','click').delegate('.save-software-component', 'click', function(){
		var software_component_name = SoftwareComponentModal.find('[name="component_name"]').val();
		//console.log(software_component_name);
		// check if there is another software component with the same name
		myDiagram.nodes.each(function(n) {
			if (n.data.name === software_component_name){
				alert('Please enter a unique software component name');
				error=true;
			}
			else
				error=false;
		})
		if(false==error)
		// if ther is no error
			if(software_component_name.length == 0) {
				alert('Please enter the software name');
			}
			else
			{
				SoftwareComponentModal.modal('hide');
				myDiagram.model.addNodeData(
				{
					name: software_component_name,
					leftArray: [],
					rightArray: [],
					"loc":location,
				});
				software_component_name="";
				location="";

			}
	});

}


function isEmpty(obj) {
    for(var key in obj) {
        if(obj.hasOwnProperty(key))
            return false;
    }
    return true;
}


function showNewPortModal ()
{
	var newPortModal = $('#newPortModal');
    newPortModal.modal('show');
    document.getElementById('port_name').value = '';
    fill_Port_Interfaces_Select();
    newPortModal.undelegate('.save-port','click').delegate('.save-port', 'click', function()
    {
    	// get port name
    	var port_name = newPortModal.find('[name="port_name"]').val();

    	// port type
    	var port_type;
    	var p_port =document.getElementById("p_port").checked;
    	var r_port =document.getElementById("r_port").checked;
    	console.log(p_port);
    	console.log(r_port);
    	//port interface
    	var selected_interface = $('#newPortModal select option:selected').text();
    	console.log(selected_interface);
    	// position
    	var position;
    	var position_left =document.getElementById("left").checked;

    	// port color
    	var port_color ;
    	myDiagram.selection.each(function(node) {
			if(node.findPort(port_name)!==node){
				alert("Please enter a unique port name");
				error=true;
			}
			else
				error=false;
		});

    	// check for port interfaces arrays
    	if(SRInterfacesarr.length <= 0&&CSInterfacesarr.length <= 0) {			
    		error = true ;
			alert("Please add interface first");
    	}

    	// check port type
		if(true==p_port)
		{
			if (SRInterfacesarr.filter(e => e.name === selected_interface).length > 0) {
				port_type="sender"
				port_color="#66bb6a"
			}
			else
			{
				port_type="server"
				port_color="#f44336"
			}
			
		}
		else
		{
			//R port
			if (SRInterfacesarr.filter(e => e.name === selected_interface).length > 0) 
			{
				port_type="reciever"
				port_color="#90caf9"
			}
			else
			{
				port_type="client"
				port_color="#d4e157"
			}
		}
		console.log(port_type);

		if(false==error){
			if(port_name.length == 0) {
				alert('Please enter the port name');
			}
			else
			{
				// check port position
				if(true==position_left)
					position = "left";
					//add_Port("left",port_name);
				else
					position="right";
					//add_Port("right",port_name);

				add_Port(position,port_name,port_type,port_color,selected_interface);
					newPortModal.modal('hide');
			}
		}
	});
}



function fill_Port_Interfaces_Select()
{
	$('#newPortInterfaceSelect').empty();
	var option = document.createElement("option");
	console.log($("p_port").is(':checked'))
	for(var i=0;i<SRInterfacesarr.length;i++)
   	{
   		if(0==i)
   		{
   			senderRecieverGroup = document.createElement("OPTGROUP");
			senderRecieverGroup.setAttribute("label", "Sender Reciever Interfaces");
			$('#newPortInterfaceSelect').append(senderRecieverGroup);
   		}
   		var option = document.createElement("option");
   		option.text = SRInterfacesarr[i].name;
  		$('#newPortInterfaceSelect').append(option); 
   	}	
   	for(var i=0;i<CSInterfacesarr.length;i++)
   	{
   		if(0==i)
   		{
   			clientServerGroup = document.createElement("OPTGROUP");
			clientServerGroup.setAttribute("label", "Client Server Interfaces");
			$('#newPortInterfaceSelect').append(clientServerGroup);
   		}
   		var option = document.createElement("option");
   		option.text = CSInterfacesarr[i].name;
  		$('#newPortInterfaceSelect').append(option); 
   	}

}



  // Add a port to the specified side of the selected nodes.
function add_Port(side,port_name,port_type,port_color,interfaceName) {
    myDiagram.startTransaction("addPort");
    myDiagram.selection.each(function(node) {
      // skip any selected Links
      if (!(node instanceof go.Node)) return;
      // compute the next available index number for the side
      var i = 0;
      while (node.findPort(side + i.toString()) !== node) i++;
      // now this new port name is unique within the whole Node because of the side prefix
      var name = side + i.toString();
      // get the Array of port data to be modified
      var arr = node.data[side + "Array"];
      // data elements
      let dataElements = [];
      // data element type 
      let type;
      if (arr) {
        // create a new port data object
        var newportdata = {
          portId: port_name,
          portType:port_type,
          portColor: port_color,
          interface_name:interfaceName
          // if you add port data properties here, you should copy them in copyPortData above
        };
        var interfaceObject;
        switch(port_type) {
	 		case 'sender' :
	 		case 'reciever':
	 			type = 'S_R';
	 			interfaceObject =SRInterfacesarr.filter(e => e.name === interfaceName);
	 			dataElements.push({
	 				type: type,
	 				dataElements: interfaceObject[0].dataelements
	 			})
	 			break;
	 		case 'server':
	 		case 'client':
	 			type = 'C_S';
	 			console.log(CSInterfacesarr.filter(e => e.name === interfaceName))
	 			interfaceObject =CSInterfacesarr.filter(e => e.name === interfaceName);
	 			dataElements.push({
	 				type: type,
	 				operations: interfaceObject[0].operations
	 			})
	 		break;
	 	}
	 	newportdata['data_elements']=dataElements;
        // and add it to the Array of port data
        myDiagram.model.insertArrayItem(arr, -1, newportdata);    
      }
    });
    myDiagram.commitTransaction("addPort");
  }



function showPropertiesModal ()
{
	let Runnable_form  = document.getElementById("Runnable_form");
	let Port_form  = document.getElementById("Ports_Info_Form_SenderServer");
	Port_form.style.display="none";
	let Port_form2  = document.getElementById("Ports_Info_Form_ReceiverClient");
	Port_form2.style.display="none";	
	Runnable_form.style.display = "none";
	Load_Runnables_Array();
	jQuery('#PropModal').modal('show');

}
