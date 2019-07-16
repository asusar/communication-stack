// Properties Modal
var propertiesModal = $('#PropModal');
// Runnable Modal
var newRunnableModal = $('#newRunnableModal');
// Data Access Modal
var newDataAccessModal = $('#newDataAccessModal');
// Delete Runnable Modal
var deleteRunnableModal= $('#deleteRunnableModal');
// Set Triggered Event Modal
var setTriggeredEventModal=$('#setTriggeredEventModal');
// A runnable properties form
var Runnable_form  = document.getElementById("Runnable_form");
// A Sender revicever options form
var SR_form  = document.getElementById("SR-options");
// A Client Server options form
var CS_form  = document.getElementById("CS-options");
// Ports Array containing all ports
var ports_arr=[];
// Ports Array containing all server ports indices
var server_ports_indices_arr=[];
// Ports Array containing all reciever ports indices
var reciever_ports_indices_arr=[];
// Port Interface name
var port_interface_name;
// Port Data Elements
var port_data_elements=[];
// Port Operations
var port_operations=[];
// Data Write Access ()
var Explicit_Data_write_access=[];
// Data read access
var Explicit_Data_read_access=[];
// Data Write Access
var Implicit_Data_write_access=[];
// Data read access
var Implicit_Data_read_access=[];
// Server Call Points
var Server_Call_points=[];
// Data Access names Array
var AccessNamesArr=[];
// RunnableEventObject
var CurrentRunnableEventObject;
//Port Names Select
var PortNamesSelect=document.getElementById("PortNameSelect");
//Data Elements Select
var DataElementsSelect=document.getElementById("DataElementsSelect");
// Communication Type
var CommunicationTypeSelect=document.getElementById("CommunicationType");
//Operations Select
var OperationsSelect=document.getElementById("OperationsSelect");
//Event Types Select
var EventTypesSelect=document.getElementById("InputEventType");
//Event Rports Select
var EventRportsSelect=document.getElementById("InputEventRport");
//Event Pports Select
var EventPportsSelect=document.getElementById("InputEventPport");
//Event Datelements Select
var EventDatelementsSelect=document.getElementById("InputEventDataElement");
//Event Operations Select
var EventOperationsSelect=document.getElementById("InputEventOperation");
// Timing Event div
var TimingEventForm=document.getElementById("Timing_Event_Form");
// Timing Event div
var DataRecievedEventForm=document.getElementById("Data_Received_Form");
// Timing Event div
var OperationInvokedEventForm=document.getElementById("Operation_Invoked_Form");
// Runnables Button
var Runnables_Button=document.getElementById("Runnables_Button");
//Runnables Array 
var RunnablesArray=[];
//Current Edited Runnable
var CurrentRunnableName;
// Runnable unique names 
function isRunnableNameUnique(Rname)
{
	 jsonobject=JSON.parse(myDiagram.model.toJson());  //TODO
	 allSwcs=jsonobject.nodeDataArray
	 for(var i=0;i<allSwcs.length;i++)
	 {
		 iteratorArray=allSwcs[i].Runnables
		 console.log(iteratorArray)
		 if(iteratorArray==undefined)iteratorArray=[];
		 for(var k=0;k<iteratorArray.length;k++)
		 {
		 	if(iteratorArray[k].runnableName==Rname) 	return false 
 
		 }
	 }
	 return true;	
}
function check_Port_Relationto_Runnable(PortName,SWC)
{
    runnables=SWC.Runnables;
    if(runnables!=undefined){
	   for(i=0;i<runnables.length;i++)
	   {
            if(runnables[i].Event.Pport==PortName)
            {
                     return(runnables[i].runnableName)
            }
            else if(runnables[i].Event.Rport==PortName)
            {
                     return(runnables[i].runnableName)
            }
	  		for(k=0;k<runnables[i].Explicit_Data_write_access.length ;k++)
			{
				portpath=runnables[i].Explicit_Data_write_access[k].port;
				index=portpath.lastIndexOf("\/");
				port=portpath.substring(index+1);
                if(port==PortName)
                {
                	return(runnables[i].runnableName);
                }				
			}
	  		for(k=0;k<runnables[i].Explicit_Data_read_access.length ;k++)
			{
				portpath=runnables[i].Explicit_Data_read_access[k].port;
				index=portpath.lastIndexOf("\/");
				port=portpath.substring(index+1);
                if(port==PortName)
                {
                	return(runnables[i].runnableName);
                }						
			}
	  		for(k=0;k<runnables[i].Implicit_Data_write_access.length ;k++)
			{
				portpath=runnables[i].Implicit_Data_write_access[k].port;
				index=portpath.lastIndexOf("\/");
				port=portpath.substring(index+1);
                if(port==PortName)
                {
                	return(runnables[i].runnableName);
                }						
			}
	  		for(k=0;k<runnables[i].Implicit_Data_read_access.length ;k++)
			{
				portpath=runnables[i].Implicit_Data_read_access[k].port;
				index=portpath.lastIndexOf("\/");
				port=portpath.substring(index+1);
                if(port==PortName)
                {
                	return(runnables[i].runnableName);
                }						
			}
	  		for(k=0;k<runnables[i].Server_Call_points.length ;k++)
			{
				portpath=runnables[i].Server_Call_points[k].port;
				index=portpath.lastIndexOf("\/");
				port=portpath.substring(index+1);
                if(port==PortName)
                {
                	return(runnables[i].runnableName);
                }						
			}	




	   }
	}
	   return null;

}
function getRunnableWithoutTriggiredEvent()
{
	for(i=0;i<RunnablesArray.length;i++)
	{
		if(RunnablesArray[i].Event==null)
			return RunnablesArray[i].runnableName;
	}
	return null;
}
function isEventNameUnique(eventname)
{
	softwareComponentName=""
    myDiagram.selection.each(function (part) {
    if (part instanceof go.Node) {
        softwareComponentName = part.data.name;
    }
    })
 	jsonobject=JSON.parse(myDiagram.model.toJson());  //TODO
	allSwcs=jsonobject.nodeDataArray
	for(var i=0;i<allSwcs.length;i++)
	 {
		 iteratorArray=allSwcs[i].Runnables
		 console.log(iteratorArray)
		 if(iteratorArray==undefined)iteratorArray=[];
		 for(var k=0;k<iteratorArray.length;k++)
		 {
		 	if(!(k==getCurrentRunnableIndex() && allSwcs[i].name==softwareComponentName) &&iteratorArray[k].Event!=null &&iteratorArray[k].Event.name==eventname ) 	return false 
 
		 }
	 }
	 return true;	
}
function EventRportSelectChange()
{
	var Rport=EventRportsSelect.options[EventRportsSelect.selectedIndex].text;
	$('#InputEventDataElement').empty();
	Get_Data_Element_Names(Rport);
	for(var i=0;i<port_data_elements.length ;i++)
		{
			var option = document.createElement("option"); 
			option.text = port_data_elements[i].name;
			EventDatelementsSelect.appendChild(option); 
		}	
}
function EventPportSelectChange()
{
	var Pport=EventPportsSelect.options[EventPportsSelect.selectedIndex].text;
	$('#InputEventOperation').empty();
	Get_Operations(Pport)
	for(var i=0;i<port_operations.length;i++)
		{
			var option = document.createElement("option");
			option.text = port_operations[i].name;
			EventOperationsSelect.appendChild(option); 
		}		
}
function EventSelectChange()
{
	var eventType=EventTypesSelect.options[EventTypesSelect.selectedIndex].text;
	if (eventType=="Init-Event")
	{
		TimingEventForm.style.display="none";
		DataRecievedEventForm.style.display="none";
		OperationInvokedEventForm.style.display="none";

	}
	else if (eventType=="Timing-Event")
	{
		TimingEventForm.style.display="block";
		DataRecievedEventForm.style.display="none";
		OperationInvokedEventForm.style.display="none";		
	}
	else if (eventType=="Data-Recieved-Event" || eventType=="Data-Recieve-Error-Event")
	{
		TimingEventForm.style.display="none";
		DataRecievedEventForm.style.display="block";
		OperationInvokedEventForm.style.display="none";	
		$('#InputEventRport').empty();
        for(var i=0;i<reciever_ports_indices_arr.length ;i++)
		{
			var option = document.createElement("option"); 
			option.text = ports_arr[reciever_ports_indices_arr[i]].portId;
			option.type=reciever_ports_indices_arr[i];
			EventRportsSelect.appendChild(option); 
		}
	EventRportSelectChange();		
	}
	else if (eventType=="Operation-Invoked-Event")
	{
		TimingEventForm.style.display="none";
		DataRecievedEventForm.style.display="none";
		OperationInvokedEventForm.style.display="block";
		$('#InputEventPport').empty();
        for(var i=0;i<server_ports_indices_arr.length ;i++)
		{
			var option = document.createElement("option"); 
			option.text = ports_arr[server_ports_indices_arr[i]].portId;
			option.type=server_ports_indices_arr[i];
			EventPportsSelect.appendChild(option); 
		}		
	EventPportSelectChange();

	}
	
	
}
function fill_Event_Types_Select()
{
	$('#InputEventType').empty();
	var option = document.createElement("option"); 
	option.text = "Init-Event";
	EventTypesSelect.appendChild(option);     
	var option = document.createElement("option"); 
	option.text = "Timing-Event";
	EventTypesSelect.appendChild(option);     	
	if(reciever_ports_indices_arr.length!=0)
	{
		var option = document.createElement("option"); 
		option.text = "Data-Recieved-Event";
		EventTypesSelect.appendChild(option);     
		var option = document.createElement("option"); 
		option.text = "Data-Recieve-Error-Event";
		EventTypesSelect.appendChild(option);    		
		
	}
	if(server_ports_indices_arr.length!=0)
	{
		var option = document.createElement("option"); 
		option.text = "Operation-Invoked-Event";
		EventTypesSelect.appendChild(option);       				
	}	
}
function get_DataAccessArr_index(dataaccessname,arr)
{
	for(i=0;i<arr.length;i++)
	{
		if(arr[i].name==dataaccessname)
		{
			return i ;
		}
	}
}
function get_Runnable_index(runnablename)
{
	for(i=0;i<RunnablesArray.length;i++)
	{

		if(RunnablesArray[i].runnableName==runnablename)
		{

			return i ;
		}
	}
	return null ;
}
function Empty_DataAccess_div()
{
	$("#showDAccessName").html("");
	$("#showDAccessType").html("");
	$("#showDAccessComType").html("");
	$("#showDAccessInterfaceType").html("");
	$("#deleteDAccess").html("");			
}
function Fill_DataAccess_div(Runnable)
{

						
			$( "#showDAccessName" ).append( "<strong>Name</strong>" );
			$( "#showDAccessName" ).append( document.createElement("br") );
            $( "#showDAccessType" ).append( "<strong>Send/Recieve</strong>");
			$( "#showDAccessType" ).append( document.createElement("br") );
            $( "#showDAccessComType" ).append( "<strong>Implicit/Explicit</strong>");
			$( "#showDAccessComType" ).append( document.createElement("br") );
            $( "#showDAccessInterfaceType" ).append("<strong>DE/Operation</strong>");
			$( "#showDAccessInterfaceType" ).append( document.createElement("br") );
			$( "#deleteDAccess" ).append( document.createElement("br") );
  		for(i=0;i<Runnable.Explicit_Data_write_access.length ;i++)
		{
			$( "#showDAccessName" ).append( document.createTextNode(Runnable.Explicit_Data_write_access[i].name ) );
			$( "#showDAccessName" ).append( document.createElement("br") );
            $( "#showDAccessType" ).append( document.createTextNode( "Send" ));
			$( "#showDAccessType" ).append( document.createElement("br") );
            $( "#showDAccessComType" ).append( document.createTextNode( "Explicit" ) );
			$( "#showDAccessComType" ).append( document.createElement("br") );
			DE=Runnable.Explicit_Data_write_access[i].data;
			stopper=DE.lastIndexOf("\/");
			DE=DE.substring(stopper+1)
            $( "#showDAccessInterfaceType" ).append( document.createTextNode("DE : "+DE));
			$( "#showDAccessInterfaceType" ).append( document.createElement("br") );
		    var delete_btn1=document.createElement("input");
		    delete_btn1.type="button";
		    delete_btn1.setAttribute("class","btn btn-danger");	
		    delete_btn1.value="Delete  "+Runnable.Explicit_Data_write_access[i].name ;	
			delete_btn1.style.height = '20px'; 
			delete_btn1.style.fontSize = '12px';
			delete_btn1.style.lineHeight = '5px'; 
            delete_btn1.id=Runnable.Explicit_Data_write_access[i].name;
		    delete_btn1.addEventListener("click", function(event) 
			{
				    index=get_DataAccessArr_index(event.currentTarget.id,Runnable.Explicit_Data_write_access)
					nameindex=Runnable.AccessNamesArr.indexOf(event.currentTarget.id);
					Runnable.Explicit_Data_write_access.splice(index,1) ;
					Runnable.AccessNamesArr.splice(nameindex,1);
					Save_Runnables_Array();
					addDataAccessButton.click();
			});	
		    $( "#deleteDAccess" ).append(delete_btn1);
		    $( "#deleteDAccess" ).append( document.createElement("br"));			
		}
  		for(i=0;i<Runnable.Explicit_Data_read_access.length ;i++)
		{
			$( "#showDAccessName" ).append( document.createTextNode(Runnable.Explicit_Data_read_access[i].name ) );
			$( "#showDAccessName" ).append( document.createElement("br") );
            $( "#showDAccessType" ).append( document.createTextNode( "Recieve" ));
			$( "#showDAccessType" ).append( document.createElement("br") );
            $( "#showDAccessComType" ).append( document.createTextNode( "Explicit" ) );
			$( "#showDAccessComType" ).append( document.createElement("br") );
			DE=Runnable.Explicit_Data_read_access[i].data;
			stopper=DE.lastIndexOf("\/");
			DE=DE.substring(stopper+1)			
            $( "#showDAccessInterfaceType" ).append( document.createTextNode("DE : "+DE));
			$( "#showDAccessInterfaceType" ).append( document.createElement("br") );
		    var delete_btn2=document.createElement("input");
		    delete_btn2.type="button";
		    delete_btn2.setAttribute("class","btn btn-danger");	
		    delete_btn2.value="Delete  "+Runnable.Explicit_Data_read_access[i].name;	
			delete_btn2.style.height = '20px'; 
			delete_btn2.style.fontSize = '12px';
			delete_btn2.style.lineHeight = '5px'; 
            delete_btn2.id=Runnable.Explicit_Data_read_access[i].name;
		    delete_btn2.addEventListener("click", function(event) 
			{
					index=get_DataAccessArr_index(event.currentTarget.id,Runnable.Explicit_Data_read_access);
					nameindex=Runnable.AccessNamesArr.indexOf(event.currentTarget.id);
					Runnable.Explicit_Data_read_access.splice(index,1) ;
					Runnable.AccessNamesArr.splice(nameindex,1);
					Save_Runnables_Array();
					addDataAccessButton.click();
			});	
		    $( "#deleteDAccess" ).append(delete_btn2);
		    $( "#deleteDAccess" ).append( document.createElement("br"));				
		}
  		for(i=0;i<Runnable.Implicit_Data_write_access.length ;i++)
		{
			$( "#showDAccessName" ).append( document.createTextNode(Runnable.Implicit_Data_write_access[i].name ) );
			$( "#showDAccessName" ).append( document.createElement("br") );
            $( "#showDAccessType" ).append( document.createTextNode( "Send" ));
			$( "#showDAccessType" ).append( document.createElement("br") );
            $( "#showDAccessComType" ).append( document.createTextNode( "Implicit" ) );
			$( "#showDAccessComType" ).append( document.createElement("br") );
			DE=Runnable.Implicit_Data_write_access[i].data;
			stopper=DE.lastIndexOf("\/");
			DE=DE.substring(stopper+1)				
            $( "#showDAccessInterfaceType" ).append( document.createTextNode("DE : "+DE));
			$( "#showDAccessInterfaceType" ).append( document.createElement("br") );
		    var delete_btn3=document.createElement("input");
		    delete_btn3.type="button";
		    delete_btn3.setAttribute("class","btn btn-danger");	
		    delete_btn3.value="Delete  "+Runnable.Implicit_Data_write_access[i].name;	
			delete_btn3.style.height = '20px'; 
			delete_btn3.style.fontSize = '12px';	
			delete_btn3.style.lineHeight = '5px'; 			
            delete_btn3.id=Runnable.Implicit_Data_write_access[i].name;
		    delete_btn3.addEventListener("click", function(event) 
			{
					index=get_DataAccessArr_index(event.currentTarget.id,Runnable.Implicit_Data_write_access);
					nameindex=Runnable.AccessNamesArr.indexOf(event.currentTarget.id);
					Runnable.Implicit_Data_write_access.splice(index,1) ;
					Runnable.AccessNamesArr.splice(nameindex,1);
					Save_Runnables_Array();
					addDataAccessButton.click();
			});	
		    $( "#deleteDAccess" ).append(delete_btn3);
		    $( "#deleteDAccess" ).append( document.createElement("br"));				
		}
  		for(i=0;i<Runnable.Implicit_Data_read_access.length ;i++)
		{
			$( "#showDAccessName" ).append( document.createTextNode(Runnable.Implicit_Data_read_access[i].name ) );
			$( "#showDAccessName" ).append( document.createElement("br") );
            $( "#showDAccessType" ).append( document.createTextNode( "Recieve" ));
			$( "#showDAccessType" ).append( document.createElement("br") );
            $( "#showDAccessComType" ).append( document.createTextNode( "Implicit" ) );
			$( "#showDAccessComType" ).append( document.createElement("br") );
			DE=Runnable.Implicit_Data_read_access[i].data;
			stopper=DE.lastIndexOf("\/");
			DE=DE.substring(stopper+1)				
            $( "#showDAccessInterfaceType" ).append( document.createTextNode("DE : "+DE));
			$( "#showDAccessInterfaceType" ).append( document.createElement("br") );
		    var delete_btn4=document.createElement("input");
		    delete_btn4.type="button";
		    delete_btn4.setAttribute("class","btn btn-danger");	
		    delete_btn4.value="Delete  "+Runnable.Implicit_Data_read_access[i].name;	
			delete_btn4.style.height = '20px'; 
		    delete_btn4.style.fontSize = '12px';
			delete_btn4.style.lineHeight = '5px'; 
            delete_btn4.id=Runnable.Implicit_Data_read_access[i].name;
		    delete_btn4.addEventListener("click", function(event) 
			{
					index=get_DataAccessArr_index(event.currentTarget.id,Runnable.Implicit_Data_read_access);
					nameindex=Runnable.AccessNamesArr.indexOf(event.currentTarget.id);
					Runnable.Implicit_Data_read_access.splice(index,1) ;
					Runnable.AccessNamesArr.splice(nameindex,1);
					Save_Runnables_Array();
					addDataAccessButton.click();
			});	
		    $( "#deleteDAccess" ).append(delete_btn4);
		    $( "#deleteDAccess" ).append( document.createElement("br"));				
		}
  		for(i=0;i<Runnable.Server_Call_points.length ;i++)
		{
			$( "#showDAccessName" ).append( document.createTextNode(Runnable.Server_Call_points[i].name ) );
			$( "#showDAccessName" ).append( document.createElement("br") );
            $( "#showDAccessType" ).append( document.createTextNode( "Recieve" ));
			$( "#showDAccessType" ).append( document.createElement("br") );
            $( "#showDAccessComType" ).append( document.createTextNode( "---" ) );
			$( "#showDAccessComType" ).append( document.createElement("br") );
			OP=Runnable.Server_Call_points[i].data;
			stopper=OP.lastIndexOf("\/");
			OP=OP.substring(stopper+1)				
            $( "#showDAccessInterfaceType" ).append( document.createTextNode("OP : "+OP));
			$( "#showDAccessInterfaceType" ).append( document.createElement("br") );	
		    var delete_btn5=document.createElement("input");
		    delete_btn5.type="button";
		    delete_btn5.setAttribute("class","btn btn-danger");	
		    delete_btn5.value="Delete "+Runnable.Server_Call_points[i].name ;	
			delete_btn5.style.height = '20px'; 
		    delete_btn5.style.fontSize = '12px';
            delete_btn5.style.lineHeight = '5px'; 
            delete_btn5.id=Runnable.Server_Call_points[i].name;
		    delete_btn5.addEventListener("click", function(event) 
			{
					index=get_DataAccessArr_index(event.currentTarget.id,Runnable.Server_Call_points);
					nameindex=Runnable.AccessNamesArr.indexOf(event.currentTarget.id);
					Runnable.Server_Call_points.splice(index,1) ;
					Runnable.AccessNamesArr.splice(nameindex,1);
					Save_Runnables_Array();
					addDataAccessButton.click();
			});		
		    $( "#deleteDAccess" ).append(delete_btn5);
		    $( "#deleteDAccess" ).append( document.createElement("br"));				
		}		
}
function getCurrentRunnableIndex()
{
			for(var i=0;i<RunnablesArray.length;i++)
		   {
			   if(RunnablesArray[i].runnableName==CurrentRunnableName)
			   {

                  return i ;
			   }
		   }

}
function Load_Runnables_Array()
{
	  Runnable_form.style.display = "none";
	  myDiagram.selection.each(function(node) {
      // skip any selected Links
      if (!(node instanceof go.Node)) return;
      // get the Array of runnables to be modified
      RunnablesArray = node.data["Runnables"];
	  if(RunnablesArray==undefined)RunnablesArray=[];
	  $("#createdRunnables").empty();
	  for(i=0;i<RunnablesArray.length;i++)
	    {
			Create_Runnable (RunnablesArray[i].runnableName) ;

	    }
    });
	
}
function Save_Runnables_Array()
{   
    var current_SWC_index;
    var softwareComponentName;
    myDiagram.selection.each(function (part) {
        if (part instanceof go.Node) {
            softwareComponentName = part.data.name;
        }
    });
    Object.keys(myDiagram.model.nodeDataArray).forEach(function(index) {
        if(myDiagram.model.nodeDataArray[index].name == softwareComponentName) {
            current_SWC_index = index
        }
    })
    var current_runnables_place = myDiagram.model.nodeDataArray[current_SWC_index];
    myDiagram.model.setDataProperty(current_runnables_place, 'Runnables', RunnablesArray);
}
propertiesModal.undelegate('.create-runnable','click').delegate('.create-runnable', 'click', function()
{
    // show runnable modal when create runnable is cliked
    newRunnableModal.modal('show');
    // remove any pervious input text
    document.getElementById('new_runnable_name').value = '';
});



newRunnableModal.undelegate('.save-runnable','click').delegate('.save-runnable', 'click', function()
{
    // get runnable attributes when save runnable button is pressed
    var runnable_name = newRunnableModal.find('[name="runnable_name"]').val();
	if(runnable_name.length==0) {
			alert('please enter runnable name ');
			}
	else if (/^[A-Za-z0-9_]+$/.test(runnable_name)==false)
			{
			alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
			}
    else if (/^[A-Za-z]+$/.test(runnable_name[0])==false)
			{
				alert('please enter name start with letter');
			}
	else if(isRunnableNameUnique(runnable_name)==false)
		   {
		   alert('Runnable name already exist ');
		   }
    else 
	{
		// create runnable button	
		Create_Runnable(runnable_name);

		var new_Runnable =
		{
			runnableName : runnable_name ,
			Event :null,
			minimumStartInterval : 0,
			invoked:false,
			Explicit_Data_write_access:[],
			Explicit_Data_read_access:[],
			Implicit_Data_write_access:[],
			Implicit_Data_read_access:[],
			Server_Call_points:[],
			AccessNamesArr:[]
		}
		RunnablesArray.push(new_Runnable);
		Save_Runnables_Array();
		newRunnableModal.modal('hide');	
	}
});

Runnables_Button.addEventListener("click" , Load_Runnables_Array);
/* Create Runnable button */
function Create_Runnable (RName) 
{
    // create runnable button & add it's attributes
    let runnable = document.createElement("button");
    runnable.setAttribute("class" , "btn btn-outline-success runnable Port_S");
    runnable.setAttribute("type" , "button");
    let runnableName = document.createTextNode(RName);
    // add runnable text to runnable
    runnable.appendChild(runnableName);
    // add runnable to runnables list
    $("#createdRunnables").append(runnable);
		runnable.addEventListener("click" , function(){
		index=get_Runnable_index(RName);
		let Minimum=null;
		let invoked=null;
		if(index != null)
		{
			Minimum=RunnablesArray[index].minimumStartInterval;
			invoked=RunnablesArray[index].invoked;						
		}
		CurrentRunnableName=RName;
        Runnable_form.style.display = "block";
        $("#RunnableUpdateName").text($(this).text());
        document.getElementById("runnable-short-name-input").value=$(this).text();
		if(Minimum!=null)document.getElementById("Minimum_start_interval").value=Minimum;
		else document.getElementById("Minimum_start_interval").value=Minimum;
		if(invoked!=null)document.getElementById("invoked").checked=invoked;
		else document.getElementById("invoked").checked=false;
        Get_Port_Arr(); 
        var PortNamesSelect=document.getElementById("PortNameSelect");
        $('#PortNameSelect').empty();
        for ( var i=0 ; i<ports_arr.length;i++)
        {
             var option = document.createElement("option"); 
             option.text = ports_arr[i].portId;
             option.type = ports_arr[i].portType;
             PortNamesSelect.appendChild(option);          
        }
			i=getCurrentRunnableIndex();
			Explicit_Data_write_access  =  RunnablesArray[i].Explicit_Data_write_access;
			Explicit_Data_read_access  =  RunnablesArray[i].Explicit_Data_read_access;
			Implicit_Data_write_access  =  RunnablesArray[i].Implicit_Data_write_access;
			Implicit_Data_read_access  =  RunnablesArray[i].Implicit_Data_read_access;
			Server_Call_points  =  RunnablesArray[i].Server_Call_points;
			CurrentRunnableEventObject=RunnablesArray[i].Event;
			AccessNamesArr= RunnablesArray[i].AccessNamesArr;	

        
    });
}

function portSelectChange()
{

    var portName = PortNamesSelect.options[PortNamesSelect.selectedIndex].text;
    var portType =PortNamesSelect.options[PortNamesSelect.selectedIndex].type;
    
    Get_Data_Element_Names(portName);
    Get_Operations(portName);
    if(portType=="sender")
    {
        SR_form.style.display = "block";
        CS_form.style.display = "none";
        Fill_Data_Element_select();


    }
    else if(portType=="reciever")
    {
        SR_form.style.display = "block";
        CS_form.style.display = "none";
        Fill_Data_Element_select();

    }
    else if(portType=="client"||portType=="server")
    {
        SR_form.style.display = "none";
        CS_form.style.display = "block";
        Fill_Operation_select();
    }
    else{
        SR_form.style.display = "none";
        CS_form.style.display = "none";
    }

} 

propertiesModal.delegate('.save-runnable-changes', 'click', function(){

    var runnable_name=propertiesModal.find('[id="runnable-short-name-input"]').val();
    var minimum_start_interval = propertiesModal.find('[id="Minimum_start_interval"]').val();
    var invoked=document.getElementById('invoked').checked;
	if(runnable_name.length==0) {
			alert('please enter runnable name ');
			}
	else if (/^[A-Za-z0-9_]+$/.test(runnable_name)==false)
			{
			alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
			}
    else if (/^[A-Za-z]+$/.test(runnable_name[0])==false)
	{
		alert('please enter name start with letter');
	}
	else if(isRunnableNameUnique(runnable_name)==false && CurrentRunnableName!=runnable_name)
		   {
		   alert('Runnable name already exist ');
		   }
    else if (CurrentRunnableEventObject==null)
		   {
			alert('please set event trigger to the runnable ');
		   }
    else 
	{
		var softwareComponentName="";
		var queryString = decodeURIComponent(window.location.search);
		queryString = queryString.substring(1);
		var queries = queryString.split("&");
		var projectName=queries.toString().trim();  
			// get software component name
		myDiagram.selection.each(function (part) {
			if (part instanceof go.Node) {
				softwareComponentName = part.data.name;
			}
		});	
		eventtype=setTriggeredEventModal.find('[id="InputEventType"]').val();
		runnablepath=projectName+"\/"+softwareComponentName+"\/"+softwareComponentName+"_InternalBehavior"+"\/"+runnable_name;		
		CurrentRunnableEventObject.runnablepath=runnablepath;
		var Edited_Runnable =
			{
				runnableName : runnable_name ,
				Event :CurrentRunnableEventObject,   
				minimumStartInterval : minimum_start_interval,
				invoked:invoked,
				Explicit_Data_write_access:Explicit_Data_write_access,
				Explicit_Data_read_access:Explicit_Data_read_access,
				Implicit_Data_write_access:Implicit_Data_write_access,
				Implicit_Data_read_access:Implicit_Data_read_access,
				Server_Call_points:Server_Call_points,
				AccessNamesArr:AccessNamesArr


			}
			i=getCurrentRunnableIndex();
			RunnablesArray[i]=Edited_Runnable;
			Save_Runnables_Array();
            Load_Runnables_Array();			

	}

});


propertiesModal.delegate('.delete-runnable','click',function(){
$('#delete_runnable_select').empty();	
for ( var i=0 ; i<RunnablesArray.length;i++)
    {
         var option = document.createElement("option"); 
         option.text = RunnablesArray[i].runnableName;
		 option.id=i;
         $('#delete_runnable_select').append(option);          
    }
	deleteRunnableModal.modal('show');
	
});
deleteRunnableModal.delegate('.delete_runnable','click',function(){
         runnableName=$('#delete_runnable_select :selected').text();
		 runnableIndex=$('#delete_runnable_select :selected').attr("id");
		 RunnablesArray.splice(runnableIndex,1);
         Save_Runnables_Array();
		 Load_Runnables_Array();
         $('.delete-runnable').click();	
		 alert("Runnable  :  "+runnableName+"  is successfully deleted");
		 deleteRunnableModal.modal('hide');
		 
});

propertiesModal.delegate('.addDataAccessButton', 'click', function(){
	if(ports_arr.length==0)
	{
		alert("Please add ports first to the Software Component")
	}
	else if (getPortWithoutInterfaceSwc()!=null)
	{
    	alert("Please Add Interface to Port : "+getPortWithoutInterfaceSwc());

	}
	else{	
	    document.getElementById("InputAccessName").value="";	
		portSelectChange()
		Empty_DataAccess_div();
	    Fill_DataAccess_div(RunnablesArray[getCurrentRunnableIndex()]);
	    newDataAccessModal.modal('show');
    

      }
});

newDataAccessModal.delegate('.saveDataAccess','click',function()
{
    var softwareComponentName="";
    var queryString = decodeURIComponent(window.location.search);
    queryString = queryString.substring(1);
    var queries = queryString.split("&");
    var projectName=queries.toString().trim();    
        // get software component name
    myDiagram.selection.each(function (part) {
        if (part instanceof go.Node) {
            softwareComponentName = part.data.name;
        }
    });
    var accessname = newDataAccessModal.find('[id="InputAccessName"]').val();
    var portName = PortNamesSelect.options[PortNamesSelect.selectedIndex].text;
    var portType =PortNamesSelect.options[PortNamesSelect.selectedIndex].type;
    var portpath=projectName+"\/"+softwareComponentName+"\/"+portName;
	if(accessname.length==0) {
			alert('please enter access name ');
			}
	else if (/^[A-Za-z0-9_]+$/.test(accessname)==false)
			{
			alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
			}
    else if (/^[A-Za-z]+$/.test(accessname[0])==false)
	{
		alert('please enter name start with letter');
	}
	else if(AccessNamesArr.includes(accessname)==true)
		   {
		   alert('access name already exist ');
		   }
    else 
	{
		AccessNamesArr.push(accessname);
		if(portType=="sender" )
		{
			var dataelementname=DataElementsSelect.options[DataElementsSelect.selectedIndex].text;   
			var datapath=projectName+"\/"+"PortInterfaces"+"\/"+Get_Port_Interface_Name(portName)+"\/"+dataelementname;
			var comtype=CommunicationTypeSelect.options[CommunicationTypeSelect.selectedIndex].text; 
			if(comtype=="Implicit")
				 {
					var dataaccesspoint={name:accessname,port:portpath,data:datapath}
					Implicit_Data_write_access.push(dataaccesspoint);

				 }
			else 
				 {
					var dataaccesspoint={name:accessname,port:portpath,data:datapath}
					Explicit_Data_write_access.push(dataaccesspoint);
				 }
		}
		else if(portType=="reciever")
		{
			var dataelementname=DataElementsSelect.options[DataElementsSelect.selectedIndex].text;   
			var datapath=projectName+"\/"+"PortInterfaces"+"\/"+Get_Port_Interface_Name(portName)+"\/"+dataelementname;
			var comtype=CommunicationTypeSelect.options[CommunicationTypeSelect.selectedIndex].text; 
			if(comtype=="Implicit")
				  {
					var dataaccesspoint={name:accessname,port:portpath,data:datapath}
					Implicit_Data_read_access.push(dataaccesspoint);
				  }
			else 
				  {
					var dataaccesspoint={name:accessname,port:portpath,data:datapath}
					Explicit_Data_read_access.push(dataaccesspoint);        
				  }
		}
		else 
		{
			var operationname=OperationsSelect.options[OperationsSelect.selectedIndex].text;   
			var datapath=projectName+"\/"+"PortInterfaces"+"\/"+Get_Port_Interface_Name(portName)+"\/"+operationname;
			var dataaccesspoint={name:accessname,port:portpath,data:datapath}
			Server_Call_points.push(dataaccesspoint);
		}    
		 newDataAccessModal.modal('hide');
    }  
});

propertiesModal.delegate('#Events_Button','click',function()
{	
	fill_Event_Types_Select();	
	EventSelectChange();
	if(CurrentRunnableEventObject!=null)
	{ 
		document.getElementById("InputEventName").value=CurrentRunnableEventObject.name;
		fill_Event_Types_Select();	
		$('#InputEventType').val(CurrentRunnableEventObject.type);
		EventSelectChange();
		if(CurrentRunnableEventObject.type=="Timing-Event")
			{
		        document.getElementById("InputTimingEventPeriod").value=CurrentRunnableEventObject.period;
			    EventSelectChange();	
			}
		else if(CurrentRunnableEventObject.type=="Data-Recieved-Event" ||CurrentRunnableEventObject.type=="Data-Recieve-Error-Event")
			{
				$('#InputEventRport').val(CurrentRunnableEventObject.Rport);
				$('#InputEventDataElement').val(CurrentRunnableEventObject.dataelement);
			    EventSelectChange();	
				
			}
		else if(CurrentRunnableEventObject.type=="Operation-Invoked-Event")
			{
				$('#InputEventPport').val(CurrentRunnableEventObject.Pport);
				$('#InputEventOperation').val(CurrentRunnableEventObject.operation);
			    EventSelectChange();	
				
			}	
     
	}
	else
	{
		document.getElementById("InputEventName").value="";
	}
	setTriggeredEventModal.modal('show');
	

});
setTriggeredEventModal.delegate('.event-save-changes','click',function()
{
	eventname=setTriggeredEventModal.find('[id="InputEventName"]').val();
	if(eventname.length==0)
		{
		alert('please enter event name ');
		}
	else if (/^[A-Za-z0-9_]+$/.test(eventname)==false)
		{
		alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
		}
	else if (/^[A-Za-z]+$/.test(eventname[0])==false)
		{
			alert('please enter name start with letter');
		}
	else if(isEventNameUnique(eventname)==false)
	   {
	   alert('event name already exist ');
	   } 
	else 
	{		
		var softwareComponentName="";
		var queryString = decodeURIComponent(window.location.search);
		queryString = queryString.substring(1);
		var queries = queryString.split("&");
		var projectName=queries.toString().trim();  
			// get software component name
		myDiagram.selection.each(function (part) {
			if (part instanceof go.Node) {
				softwareComponentName = part.data.name;
			}
		});	
		eventtype=setTriggeredEventModal.find('[id="InputEventType"]').val();
		period=null;
		dataelement=null;
		Pport=null;
		Rport=null;
		operation=null;
		datapath=null;
		portpath=null;
		
		if(eventtype=="Timing-Event")
			{
			period=setTriggeredEventModal.find('[id="InputTimingEventPeriod"]').val();

			}
		else if(eventtype=="Data-Recieved-Event" ||eventtype=="Data-Recieve-Error-Event")
			{
			dataelement=setTriggeredEventModal.find('[id="InputEventDataElement"]').val();
			Rport=setTriggeredEventModal.find('[id="InputEventRport"]').val();
			datapath=projectName+"\/"+"PortInterfaces"+"\/"+Get_Port_Interface_Name(Rport)+"\/"+dataelement;
			portpath=projectName+"\/"+softwareComponentName+"\/"+Rport;
			}
		else if(eventtype=="Operation-Invoked-Event")
			{
			operation=setTriggeredEventModal.find('[id="InputEventOperation"]').val();
			Pport=setTriggeredEventModal.find('[id="InputEventPport"]').val();
			datapath=projectName+"\/"+"PortInterfaces"+"\/"+Get_Port_Interface_Name(Pport)+"\/"+operation;
			portpath=projectName+"\/"+softwareComponentName+"\/"+Pport;
			}	
		CurrentRunnableEventObject=
		{name :eventname,
		 type: eventtype,
		 period:period,
		 dataelement:dataelement,
		 operation:operation,
		 Rport:Rport,
		 Pport:Pport,
		 portpath:portpath,
		 datapath:datapath,
		 runnablepath:null	
		} ;
				setTriggeredEventModal.modal('hide');

		}
});
	
  // Add a port to the specified side of the selected nodes.
function Get_Port_Arr() {
	var softwareComponentName  
    myDiagram.selection.each(function(part) {
      // skip any selected Links
      if (part instanceof go.Node) 
          softwareComponentName=part.data.name;
      	return;
          });
      // get the Array of port data to be modified
    Object.keys(myDiagram.model.nodeDataArray).forEach(function(index) {
        if(myDiagram.model.nodeDataArray[index].name == softwareComponentName) {
		 	left=myDiagram.model.nodeDataArray[index].leftArray;
			right=myDiagram.model.nodeDataArray[index].rightArray;
			ports_arr=left.concat(right);
			server_ports_indices_arr=[];
			reciever_ports_indices_arr=[];
		  	for(var i=0 ;i<ports_arr.length;i++)
			{
				if(ports_arr[i].portType=="server")
					server_ports_indices_arr.push(i);
				else if (ports_arr[i].portType=="reciever")
					reciever_ports_indices_arr.push(i);
			}
				

			        
	  }
    })	      
     

  } 

function Get_Port_Interface_Name(port_name) {
    for ( var i=0 ; i<ports_arr.length;i++)
    {
        if(ports_arr[i].portId == port_name)
            return ports_arr[i].interface_name;
    }    
} 
// TODO : Change 
// return ports_arr[i].data_elements[0].dataElements;  TO
// return ports_arr[i].data_elements;
function Get_Data_Element_Names(port_name) {
    for ( var i=0 ; i<ports_arr.length;i++)
    {
        if(ports_arr[i].portId == port_name)
            port_data_elements=ports_arr[i].data_elements[0].dataElements;
    }    
} 

function Get_Operations(port_name) {
    for ( var i=0 ; i<ports_arr.length;i++)
    {
        if(ports_arr[i].portId == port_name)
             port_operations= ports_arr[i].data_elements[0].operations;
    } 

} 

function Fill_Data_Element_select()
{
    var DataElementSelect=document.getElementById("DataElementsSelect");
    $('#DataElementsSelect').empty();
    for ( var i=0 ; i<port_data_elements.length;i++)
    {
         var option = document.createElement("option"); 
         option.text = port_data_elements[i].name;
         DataElementSelect.appendChild(option);          
    }
}
function Fill_Operation_select()
{
    var OperationSelect=document.getElementById("OperationsSelect");
    $('#OperationsSelect').empty();
    for ( var i=0 ; i<port_operations.length;i++)
    {
         var option = document.createElement("option"); 
         option.text = port_operations[i].name;
         OperationSelect.appendChild(option);          
    }
}
