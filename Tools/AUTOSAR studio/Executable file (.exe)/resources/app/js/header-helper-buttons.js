function getPortWithoutInterfaceSwc()
{
    var softwareComponentName;
    myDiagram.selection.each(function (part) {
        if (part instanceof go.Node) {
            softwareComponentName = part.data.name;
        }
    });	
	ports=[]
	Object.keys(myDiagram.model.nodeDataArray).forEach(function(index) {
		        if(myDiagram.model.nodeDataArray[index].name == softwareComponentName) {
				 	ports=myDiagram.model.nodeDataArray[index].leftArray;
					ports=ports.concat(myDiagram.model.nodeDataArray[index].rightArray);
				}

    })		
	for(var k=0;k<ports.length;k++)
	{
	 	if(ports[k].interface_name==null) return ports[k].portId;
	}
	 
	 return null;
}
function check_Interface_Relationto_Port(Iname)
{
	 jsonobject=JSON.parse(myDiagram.model.toJson());  //TODO
	 allSwcs=jsonobject.nodeDataArray
	 for(var i=0;i<allSwcs.length;i++)
	 {
		 left=allSwcs[i].leftArray
		 right=allSwcs[i].rightArray
		 ports=left.concat(right);
		 for(var k=0;k<ports.length;k++)
		 {
		 	if(ports[k].interface_name==Iname) return {port:ports[k].portId,swc:allSwcs[i].name} ;
		 }
	 }
	 return null;		 
}
function getPortWithoutInterface()
{
	ports=[]
	Object.keys(myDiagram.model.nodeDataArray).forEach(function(index) {
 	ports=ports.concat(myDiagram.model.nodeDataArray[index].leftArray);
	ports=ports.concat(myDiagram.model.nodeDataArray[index].rightArray);
    })		
		for(var k=0;k<ports.length;k++)
		{
		 	if(ports[k].interface_name==null) return ports[k].portId;
		}
	 
	 return null;		
}
function isInterfaceNameUnique(Iname)
{
	for(var i=0;i<SRInterfacesarr.length;i++)
	{

		if(SRInterfacesarr[i].name==Iname) return false;
		
	}
	for(i=0;i<CSInterfacesarr.length;i++)
	{


		if(CSInterfacesarr[i].name==Iname) return false;
			
			
	}	
	return true;
}
function check_Datatype_Relationto_Interface(Dtype)
{
	for(var i=0;i<SRInterfacesarr.length;i++)
	{
		for (var k = 0; k < SRInterfacesarr[i].dataelements.length; k++)
		{
			if(SRInterfacesarr[i].dataelements[k].type==Dtype) return true;
		}

	}
	for(i=0;i<CSInterfacesarr.length;i++)
	{
		for (var k = 0; k < CSInterfacesarr[i].operations.length; k++)
		{
			for (var j = 0; j < CSInterfacesarr[i].operations[k].arguments.length; j++) 
			{
			if(CSInterfacesarr[i].operations[k].arguments[j].datatype==Dtype) return true;
			}
		}		
	}
	return false ;
}		

function get_InterfacesArray_index(Iname,arr)
{
	for(i=0;i<arr.length;i++)
	{
		if(arr[i].name==Iname)
		{
			return i ;
		}
	}
}
function showAllDataElements()
{
   $("#allDataElementsNames").empty();
   $("#allDataElementsDtypes").empty();
   $("#allDataElementsNames").append("<strong>DE_Name</strong>" );
   $("#allDataElementsDtypes").append("<strong>DE_Dtype</strong>" );
   $("#allDataElementsNames").append(document.createElement("br") );
   $("#allDataElementsDtypes").append(document.createElement("br") );
	for(var i=0;i<SRInterfacesarr.length;i++)
	{
		for (var k = 0; k < SRInterfacesarr[i].dataelements.length; k++)
		{
		   $("#allDataElementsNames").append(document.createTextNode(SRInterfacesarr[i].dataelements[k].name));
		   $("#allDataElementsDtypes").append(document.createTextNode(SRInterfacesarr[i].dataelements[k].type));
		   $("#allDataElementsNames").append(document.createElement("br") );
		   $("#allDataElementsDtypes").append(document.createElement("br") );
		}

	}
	for(i=0;i<CSInterfacesarr.length;i++)
	{
		for (var k = 0; k < CSInterfacesarr[i].operations.length; k++)
		{
			for (var j = 0; j < CSInterfacesarr[i].operations[k].arguments.length; j++) 
			{
			   $("#allDataElementsNames").append(document.createTextNode(CSInterfacesarr[i].operations[k].arguments[j].name));
			   $("#allDataElementsDtypes").append(document.createTextNode(CSInterfacesarr[i].operations[k].arguments[j].datatype));
			   $("#allDataElementsNames").append(document.createElement("br") );
			   $("#allDataElementsDtypes").append(document.createElement("br") );
			}
		}		
	}   
}
function isDataElementNameUnique(DEName)
{
	for(var i=0;i<SRInterfacesarr.length;i++)
	{
		for (var k = 0; k < SRInterfacesarr[i].dataelements.length; k++)
		{
			if(SRInterfacesarr[i].dataelements[k].name==DEName) return false;
		}

	}
	for(i=0;i<CSInterfacesarr.length;i++)
	{
		for (var k = 0; k < CSInterfacesarr[i].operations.length; k++)
		{
			for (var j = 0; j < CSInterfacesarr[i].operations[k].arguments.length; j++) 
			{
			if(CSInterfacesarr[i].operations[k].arguments[j].name==DEName) return false;
			}
		}		
	}
	return true ;

}
function isOperationNameUnique(DEName)
{

	for(i=0;i<CSInterfacesarr.length;i++)
	{
		for (var k = 0; k < CSInterfacesarr[i].operations.length; k++)
		{

			if(CSInterfacesarr[i].operations[k].name==DEName) return false;
			
		}		
	}
	return true ;

}
function Show_Load_DataTypesandDataElements_Modal()
{
	availabledatatypes=["Boolean","Float","UnsignedInteger_8","SignedInteger_8","UnsignedInteger_16","SignedInteger_16","UnsignedInteger_32","SignedInteger_32","UnsignedInteger_64","SignedInteger_64"];//array contain all datatypes
	var DataTypesWindowModal = $('#DataTypesWindowModal');
	var showDataTypesWindowBtn = $('#showDataTypesWindowid');
	var AddClientServerInterfacesWindowsModal = $('#AddClientServerInterfacesWindowsModal');
	var ShowInterfacesWindowsModal = $('#ShowInterfacesWindowsModal');
	showDataTypesWindowBtn.click(function(){
	showAllDataElements();
    for(var i=0;i<availabledatatypes.length;i++)
    {
		if(datatypesselected.includes(availabledatatypes[i])==false)
	  	{
	   		document.getElementById(availabledatatypes[i]).checked = false;
	  	}
	    else 
	  	{
			document.getElementById(availabledatatypes[i]).checked = true;
      		if(check_Datatype_Relationto_Interface(availabledatatypes[i])==true)$("#"+availabledatatypes[i]).attr("disabled", true);
       		else $("#"+availabledatatypes[i]).attr("disabled", false);		   
	  	}
    }
			DataTypesWindowModal.delegate('.save-datatypes', 'click', function(){ //saving selected datatypes
				isAnySelected=false; //to make sure 1 datatype at least selected
				changes=false ;
				temp=datatypesselected;
				datatypesselected=[];
                for(var i=0;i<8;i++)
				{
					if(document.getElementById(availabledatatypes[i]).checked==true)// check for each datatype checkbox if its checked
					{
						isAnySelected=true;
						if(temp.includes(availabledatatypes[i])==false )
						{
							
							console.log(availabledatatypes[i]);
							console.log(availabledatatypes);
							console.log(datatypesselected.includes(availabledatatypes[i]));							
							changes=true;						
						}
						datatypesselected.push(availabledatatypes[i]); //if its checked add it to the selected datatypes array						
						
					}

				}
				if(isAnySelected==false) 
				{
					alert('choose at least 1 data type ');  // if none selected alert to choose one at least
					datatypesselected=temp;
				}
				else if (changes==true)
				{
					
					   for(var i=0;i<datatypesselected.length;i++)
						{
						 if(check_Datatype_Relationto_Interface(availabledatatypes[i])==true)$("#"+datatypesselected[i]).attr("disabled", true);
						 else $("#"+availabledatatypes[i]).attr("disabled", false);		   
						}					
					DataTypesWindowModal.modal('hide');    //if all good hide the datatypes modal										    
				}
				else 
				{
					DataTypesWindowModal.modal('hide');    //if all good hide the datatypes modal
				}
			    var queryString = decodeURIComponent(window.location.search);
		    	queryString = queryString.substring(1);
		    	var queries = queryString.split("&");
		    	var projectName=queries.toString().trim();
				let where = 
				{
		            name:projectName
		        };

                let set = 
                {
		            "datatypesselected":datatypesselected
		        };
		        db.updateRow('project', where, set, (succ, msg) => {
		        // succ - boolean, tells if the call is successful
		        console.log("datatypesselected: " +succ+"  "+msg);
		        });
			});    			
		DataTypesWindowModal.modal('show');
	});	
}
function AddSenderReceiver_Modal()
{
	var addNewSenderReceiverInterfacesWindowBtn= $('#addNewSenderReceiverInterfacesWindowid');
	var AddSenderReceiverInterfacesWindowsModal = $('#AddSenderReceiverInterfacesWindowsModal');
    var dataelementform=document.getElementById("dataelementform");
    var dataelementformsaveclose=document.getElementById("dataelementformsaveclose");
    var closedataelementBtn=$('#closedataelement');
    var savedataelementBtn=$('#savedataelement');
    var addDataElementBtn = $('#addDataElementid');
	var myDiv = document.getElementById("wholesenderreceiverwindow");
	var dataelementdiv=document.createElement("div");// adding div which will contain div for  each dataelement and dropbox of its type
	dataelementdiv.id="dataelementdiv";
	myDiv.appendChild(dataelementdiv);
	dataelementsarr=new Array ();// contain all dataelements object of current SRInterface
	dataelementnamesarr=[];
	addNewSenderReceiverInterfacesWindowBtn.click(function(){
		document.getElementById("senderreceiver_name").value="";
		dataelementsarr=[];				//adding new Sender-Reciever modal
		dataelementnamesarr=[];
		dataelementform.style.display="none"; //hiding the form of creating newdataelement
		dataelementformsaveclose.style.display="none";//hiding the form of saving new dataelement
		myDiv.removeChild(dataelementdiv);    //remove rubbish from last time making a senderreciever
		dataelementdiv=document.createElement("div");
		dataelementdiv.id="dataelementdiv";
	 	myDiv.appendChild(dataelementdiv);
		AddSenderReceiverInterfacesWindowsModal.modal('show');  //show the senderreceiver modal
    });
		addDataElementBtn.click(function(){ 		   //adding new data element
		document.getElementById("dataelement_name").value="";
      	dataelementform.style.display="inline";       //showing the form of creating newdataelement
	    dataelementformsaveclose.style.display="inline";//showing the form of saving new dataelement
	});
    closedataelementBtn.click(function(){
		dataelementform.style.display="none";//hiding the form of creating newdataelement
		dataelementformsaveclose.style.display="none";//hiding the form of saving new dataelement
	 });
    savedataelementBtn.click(function(){         // saving dataelement
		var dataelementname=AddSenderReceiverInterfacesWindowsModal.find('[name="dataelement_name"]').val(); //getting name of dataelement
		if(dataelementname.length==0)
		{
			alert('Please enter dataelement name');
		}//assure the user enter name
        else if (/^[A-Za-z0-9_]+$/.test(dataelementname)==false)
	    {
			alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
		}
        else if (/^[A-Za-z]+$/.test(dataelementname[0])==false)
		{
			alert('please enter name start with letter');
		}
		else if(isDataElementNameUnique(dataelementname)==false ||dataelementnamesarr.includes(dataelementname)==true)
		{
			alert('dataelement name already exist ');
		}
		else if(datatypesselected.length==0) 
		{
			alert('Please choose datatypes first');
			dataelementform.style.display="none";
			dataelementformsaveclose.style.display="none";
		}
		else 
		{
			var dataelement={name:dataelementname,type:null}; //making object dataelement
			dataelementsarr.push(dataelement);// adding it to the dataelementsarr
			dataelementnamesarr.push(dataelementname);
			var selectList = document.createElement("select");//making dropdown list of datatypes for eachelement
			for(i=0 ;i< datatypesselected.length;i++)
			{

 				var option = document.createElement("option"); // adding option for each selected datatype
                option.value = i;
                option.text = datatypesselected[i];
                selectList.appendChild(option);    //append options to the dropdownlist
		 	}
		 	var newDiv = document.createElement("div");   //making a div containg name of dataelement and droplist of types
          	var node = document.createTextNode(dataelement.name+"\xa0\xa0\xa0");//name of dataelement
		 	newDiv.appendChild(node);
		  	selectList.id=(dataelement.name + "1234") ;// giving eacht dropdownlist id
		  	newDiv.appendChild(selectList); //appending name and dropdownlist in 1 div
		  	dataelementdiv.appendChild(newDiv);//appending the div to the dataelementdiv that contain all the elements
		 	dataelementform.style.display="none";//hiding the form of creating newdataelement
		 	dataelementformsaveclose.style.display="none";//hiding the form of saving new dataelement
        }
	});

    var mySRinterface;// making object of SRInterface
	AddSenderReceiverInterfacesWindowsModal.delegate('.save-senderreceiver', 'click', function(){//save the senderrecieverinterface
		var SRinterfacename= AddSenderReceiverInterfacesWindowsModal.find('[name="senderreceiver_name"]').val();//getting interface name
		if(SRinterfacename.length==0) { //assure the user enter name
			alert('please enter interface name ');
		}
        else if (/^[A-Za-z0-9_]+$/.test(SRinterfacename)==false)
		{
			alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
		}
        else if (/^[A-Za-z]+$/.test(SRinterfacename[0])==false)
		{
			alert('please enter name start with letter');
		}
        else if(isInterfaceNameUnique(SRinterfacename)==false) //assure there is no duplicate name in SR or CS Interfaces
        {
		   alert('Interface name already exist ');
        }
		else if(dataelementsarr.length==0 )
        {
		    alert('Please add one data element at least');
        }						
		else 
		{
			for(i=0;i<dataelementsarr.length;i++) // get the selecteddatatype from the dropdownlist of each element and
			{
			    e = document.getElementById((dataelementsarr[i].name+"1234"));
                strUser = e.options[e.selectedIndex].text;
				dataelementsarr[i].type=strUser ;
				e.parentNode.removeChild(e);
			}
			mySRinterface={name:SRinterfacename ,dataelements:dataelementsarr}; //making the SRinterface object
			SRInterfacesarr.push(mySRinterface); //adding the interface object to SRinterfaces array
			dataelementsarr=[];
			dataelementnamesarr=[];
			var queryString = decodeURIComponent(window.location.search);
			queryString = queryString.substring(1);
			var queries = queryString.split("&");
			var projectName=queries.toString().trim();
		 	let where = 
		 	{
			 	name:projectName
		    };
			let set = 
			{
			  "SRInterfacesarr":SRInterfacesarr
		    };
			db.updateRow('project', where, set, (succ, msg) => {
			// succ - boolean, tells if the call is successful
			console.log("SR: " +succ+"  "+msg);
			});				
			AddSenderReceiverInterfacesWindowsModal.modal('hide'); //hiding the modal
		}
	});

}
function Show_AddClientServerInterface_Modal()
{
  	var addNewClientServerInterfacesWindowBtn= $('#addNewClientServerInterfacesWindowid');
	var NewOperationWindowsModal=$('#NewOperationWindowsModal');
	var AddClientServerInterfacesWindowsModal = $('#AddClientServerInterfacesWindowsModal');
    var operationform=document.getElementById("operationform");
    var argumentformsaveclose=document.getElementById("argumentformsaveclose");
    var errorformsaveclose=document.getElementById("errorformsaveclose");
    var possibleerrorformsaveclose=document.getElementById("possibleerrorformsaveclose");
	var argumentform=document.getElementById("argumentform");
	var errorform=document.getElementById("errorform");
	var possibleerrorform=document.getElementById("possibleerrorform");
	var wholeargumentform=document.getElementById("wholeargumentform");
	var saveargumentBtn=$('#saveargument');
	var closeargumentBtn=$('#closeargument');
	var saveerrorBtn=$('#saveerror');
	var closeerrorBtn=$('#closeerror');
	var savepossibleerrorBtn=$('#savepossibleerror');
	var closepossibleerrorBtn=$('#closepossibleerror');
    var saveoperationBtn=$('#saveoperation');
    var addOperationBtn = $('#addOperationid');
    var addArgumentBtn = $('#addArgumentid');
	var addErrorBtn=$('#addErrorid');
	var myDiv2 = document.getElementById("wholeclientserverwindow");
	var argumentdiv=document.createElement("div");
	var errordiv=document.createElement("div");
	var operationdiv=document.createElement("div");
	var possibleerrordiv=document.createElement("div");
	var addPossibleErrorBtn=$('#addPossibleErrorid');
	wholeargumentform.appendChild(argumentdiv);
	wholeargumentform.appendChild(errordiv);
	operationdiv.class='form-group';
	myDiv2.appendChild(operationdiv);
	myDiv2.appendChild(possibleerrordiv);
	operationdiv.id="operationdiv";
	myDiv2.appendChild(operationdiv);
	myDiv2.appendChild(possibleerrordiv);
	operationsarr=new Array ();
	argumentnamesarr=[];			
	possibleerrorsarr=new Array ();
    operationnamesarr=[];
	possibleerrornamesarr=[];
	possibleerrorcodesarr=[];
	addNewClientServerInterfacesWindowBtn.click(function(){
		document.getElementById("clientserver_name").value = "";
		errordiv.innerHTML="";
		errorform.innerHTML="";
		operationnamesarr=[];
		operationsarr=[];
		argumentnamesarr=[];			
		possibleerrordiv.innerHTML="";
		var n = document.createTextNode("Operations :");
		operationdiv.appendChild(n);
		var n1 = document.createTextNode("Possible Errors :");
		possibleerrordiv.appendChild(n1);
		possibleerrornamesarr=[];
		possibleerrorcodesarr=[];
		possibleerrorsarr=[];
	    operationform.style.display="none";
		possibleerrorform.style.display="none";
		possibleerrorformsaveclose.style.display="none";
		argumentformsaveclose.style.display="none";
		errorformsaveclose.style.display="none";
		myDiv2.removeChild(operationdiv);
		myDiv2.removeChild(possibleerrordiv);
		operationdiv=document.createElement("div");
        operationdiv.class='form-group';
		operationdiv.id="operationdiv";
		myDiv2.appendChild(operationdiv);
		myDiv2.appendChild(possibleerrordiv);
	 	argumentsarr=new Array ();			
		errorsarr=new Array();
		AddClientServerInterfacesWindowsModal.modal('show');
    });
	addOperationBtn.click(function(){
		document.getElementById("operation_name").value="";
	  	wholeargumentform.removeChild(argumentdiv);
		wholeargumentform.removeChild(errordiv);
		argumentdiv=document.createElement("div");
 		errordiv=document.createElement("div");
		var node = document.createTextNode("Arguments :");
		argumentdiv.appendChild(node);
	    wholeargumentform.appendChild(argumentdiv);
		wholeargumentform.appendChild(errordiv);
	    argumentform.style.display="none";
	    argumentformsaveclose.style.display="none";
		errorform.style.display="none";
	    errorformsaveclose.style.display="none";
	    NewOperationWindowsModal.modal('show');
		argumentsarr=[];
		errorcodesarr=[];
		errorarr=[];
    });
	addPossibleErrorBtn.click(function(){
		document.getElementById("error_name").value="";
		document.getElementById("error_code").value="";
		myDiv2.removeChild(possibleerrordiv);
		myDiv2.appendChild(possibleerrordiv);
	    possibleerrorform.style.display="inline";
		possibleerrorformsaveclose.style.display="inline";
    });
    closepossibleerrorBtn.click(function(){
		possibleerrorform.style.display="none";
	    possibleerrorformsaveclose.style.display="none";
    })
    addArgumentBtn.click(function(){
	    document.getElementById("argument_name").value="";
  		wholeargumentform.removeChild(argumentdiv);
		wholeargumentform.appendChild(argumentdiv);
	    argumentform.style.display="inline";
		argumentformsaveclose.style.display="inline";
	});
		addErrorBtn.click(function(){
	  	wholeargumentform.removeChild(argumentdiv);
		wholeargumentform.appendChild(argumentdiv);
	    errorform.style.display="inline";
		errorformsaveclose.style.display="inline";
		});
	closeargumentBtn.click(function(){
	        argumentform.style.display="none";
	    argumentformsaveclose.style.display="none";
	});
	closeerrorBtn.click(function(){
			errorform.style.display="none";
	    errorformsaveclose.style.display="none";
	});
	saveargumentBtn.click(function(){
	 	var argumentname=NewOperationWindowsModal.find('[name="argument_name"]').val();
	 	if(argumentname.length==0)
	 	{
	 		alert('Please enter argument name');
	 	}
	  	else if (/^[A-Za-z0-9_]+$/.test(argumentname)==false)
		{
			alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
		}
        else if (/^[A-Za-z]+$/.test(argumentname[0])==false)
		{
			alert('please enter name start with letter');
		}
		else if(isDataElementNameUnique(argumentname)==false ||argumentnamesarr.includes(argumentname)==true)
		{
			alert('Argument name already exist ');
		}
	 	else if(datatypesselected.length==0) 
 		{
 			alert('Please choose datatypes first');
 		}
			else 
			{
			var argument={name:argumentname,datatype:null,argumenttype:null};
			argumentsarr.push(argument);
			argumentnamesarr.push(argumentname);			
			var selectListdatatypes = document.createElement("select");
			var selectListargumenttypes=document.createElement("select");
			for(i=0 ;i< datatypesselected.length;i++)
	 		{

	 				var option = document.createElement("option");
                    option.value = i;
                    option.text = datatypesselected[i];
                    selectListdatatypes.appendChild(option);
	 		}
			var option0 = document.createElement("option");
            option0.value = 0;
            option0.text = "input";
			var option1 = document.createElement("option");
            option1.value = 1;
            option1.text = "input/output";
			var option2 = document.createElement("option");
            option2.value = 2;
            option2.text = "output";
            selectListargumenttypes.appendChild(option0);
			selectListargumenttypes.appendChild(option1);
			selectListargumenttypes.appendChild(option2);
			var newDiv = document.createElement("div");
            var node = document.createTextNode("\xa0\xa0\xa0"+argument.name+"\xa0\xa0\xa0");
			selectListargumenttypes.id=(argument.name+"argumenttype" + "1234") ;
			selectListdatatypes.id=(argument.name+"datatype" + "1234") ;
			newDiv.appendChild(selectListargumenttypes);
			newDiv.appendChild(node);
			newDiv.appendChild(selectListdatatypes);
			argumentdiv.appendChild(newDiv);
			argumentform.style.display="none";
			argumentformsaveclose.style.display="none";
        }
	});
	savepossibleerrorBtn.click(function(){
 		var errorname=AddClientServerInterfacesWindowsModal.find('[name="error_name"]').val();
 		var errorcode=AddClientServerInterfacesWindowsModal.find('[name="error_code"]').val();
		if(errorname.length==0)
		{
			alert('Please enter error name');
		}
	    else if (/^[A-Za-z0-9_]+$/.test(errorname)==false)
		{
			alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
		}
        else if (/^[A-Za-z]+$/.test(errorname[0])==false)
		{
			alert('please enter name start with letter');
		}
	 	else if(errorcode.length==0)
 		{
 			alert('Please enter error code');
 		}
	 	else if (/^[0-9-]+$/.test(errorcode)==false)
		{
			alert('please enter code as number');
		}
	 	else if(possibleerrorcodesarr.includes(errorcode)==true)
	 	{
 			alert('error code already exist ');
	 	}
	 	else if(possibleerrornamesarr.includes(errorname)==true)
 		{
 			alert('error name already exist ');
 		}
	 	else 
	 	{
			var error={name:errorname,code:errorcode};
			var newCheckbox = document.createElement("input");
            newCheckbox.type = "checkbox";
            newCheckbox.name = errorname+"\xa0 \xa0code :"+errorcode;
			newCheckbox.id = possibleerrorsarr.length;
			possibleerrorsarr.push(error);
			possibleerrorcodesarr.push(errorcode);
			possibleerrornamesarr.push(errorname);
			var label=document.createElement("label");
			var x = document.createTextNode(errorname+"\xa0 \xa0code :"+errorcode+"\xa0 \xa0");
			label.appendChild(x);
			label.appendChild(newCheckbox);
            errorform.appendChild(label);
			br=document.createElement("br");
			errorform.appendChild(br);
			var newDiv = document.createElement("div");
            var node1 = document.createTextNode("\xa0\xa0\xa0 error name :"+error.name+"\xa0\xa0\xa0");
            var node2 = document.createTextNode("\xa0\xa0\xa0 code :"+error.code+"\xa0\xa0\xa0");
			newDiv.appendChild(node1);
			newDiv.appendChild(node2);
			possibleerrordiv.appendChild(newDiv);
			possibleerrorform.style.display="none";
			possibleerrorformsaveclose.style.display="none";
        }
	});
	saveerrorBtn.click(function(){
     	errorsarr=[];
		for(var i=0;i<possibleerrorsarr.length;i++)
		{
			if(document.getElementById(i).checked==true)// check for each datatype checkbox if its checked
			{    
				console.log("checked");
				e={name:possibleerrornamesarr[i],code:possibleerrorcodesarr[i]};
				errorsarr.push(e); //if its checked add it to the selected datatypes array
			}
	 		errorform.style.display="none";
	 		errorformsaveclose.style.display="none";
		}
	});
	NewOperationWindowsModal.delegate('.save-operation', 'click', function(){
		var operationsname= NewOperationWindowsModal.find('[name="operation_name"]').val();
		if(operationsname.length==0) 
		{
			alert('please enter operation name ');
		}
	  else if (/^[A-Za-z0-9_]+$/.test(operationsname)==false)
		{
			alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
		}
        else if (/^[A-Za-z]+$/.test(operationsname[0])==false)
		{
			alert('please enter name start with letter');
		}
        else if(isOperationNameUnique(operationsname)==false || operationnamesarr.includes(operationsname)==true )
        {
		    alert('operation name already exist ');
        }
		else if(argumentsarr.length==0 )
        {
		    alert('Please add one argument at least');
        }				   
		else 
		{
			for(i=0;i<argumentsarr.length;i++)
			{
			    e1 = document.getElementById((argumentsarr[i].name+"argumenttype"+"1234"));
			    e2 = document.getElementById((argumentsarr[i].name+"datatype"+"1234"));
                strUser1 = e1.options[e1.selectedIndex].text;
				strUser2 = e2.options[e2.selectedIndex].text;
				argumentsarr[i].datatype=strUser2 ;
				argumentsarr[i].argumenttype=strUser1;
				e1.parentNode.removeChild(e1);
				e2.parentNode.removeChild(e2);

			}
			myoperation={name:operationsname ,arguments:argumentsarr , errors:errorsarr};
			operationnamesarr.push(operationsname);
			operationsarr.push(myoperation);
			x="\xa0Operation Name \xa0\xa0:\xa0\xa0"+operationsname+"\xa0";
			node=document.createTextNode(x);
			operationdiv.appendChild(node);
			var br = document.createElement("br");
			operationdiv.appendChild(br);
			l=myoperation.arguments.length-1;
			for(i=0;i<=l;i++)
			{
			    x="\xa0\xa0\xa0"+"\xa0\xa0Argument name\xa0:\xa0"+myoperation.arguments[i].name+"\xa0\xa0"+myoperation.arguments[i].argumenttype+"\xa0\xa0"+myoperation.arguments[i].datatype;
				node=document.createTextNode(x);
				operationdiv.appendChild(node);
				var br = document.createElement("br");
				operationdiv.appendChild(br);
			}
			argumentsarr=[];
			l=myoperation.errors.length-1;
			for(i=0;i<=l;i++)
			{
			    x="\xa0\xa0\xa0"+"\xa0\xa0Error name\xa0:\xa0"+myoperation.errors[i].name+"\xa0\xa0Error code :"+myoperation.errors[i].code+"\xa0,";
				node=document.createTextNode(x);
				operationdiv.appendChild(node);
				var br = document.createElement("br");
				operationdiv.appendChild(br);
			}
			errorsarr=[];
			NewOperationWindowsModal.modal('hide');
		}
	});
    var myCRinterface;
	AddClientServerInterfacesWindowsModal.delegate('.save-clientserver', 'click', function(){
		var CRinterfacename= AddClientServerInterfacesWindowsModal.find('[name="clientserver_name"]').val();
		if(CRinterfacename.length==0) 
		{
			alert('please enter interface name ');
		}
	    else if (/^[A-Za-z0-9_]+$/.test(CRinterfacename)==false)
		{
			alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
		}
        else if (/^[A-Za-z]+$/.test(CRinterfacename[0])==false)
		{
			alert('please enter name start with letter');
		}
        else if(isInterfaceNameUnique(CRinterfacename)==false)
        {
		    alert('Interface name already exist ');
        }
		else if(operationsarr.length==0 )
        {
		   alert('Please add one operation at least');
        }						   					   
		else 
		{
			myCRinterface={name:CRinterfacename ,operations:operationsarr,possibleerrors:possibleerrorsarr};
			CSInterfacesarr.push(myCRinterface);
			AddClientServerInterfacesWindowsModal.modal('hide');
			operationnamesarr=[];
			operationsarr=[];
			argumentnamesarr=[];
			possibleerrorsarr=[];
			possibleerrornamesarr=[];
			possibleerrorcodesarr=[];
		    var queryString = decodeURIComponent(window.location.search);
            queryString = queryString.substring(1);
            var queries = queryString.split("&");
            var projectName=queries.toString().trim();
			let where = 
			{
				name:projectName
			};
			let set = 
			{
			  "CSInterfacesarr":CSInterfacesarr
		    };
			db.updateRow('project', where, set, (succ, msg) => {
			// succ - boolean, tells if the call is successful
			console.log("CS: " +succ+"  "+msg);
			});				
		}

	});	

}
function Show_Load_Interfaces_Modal()
{
			var showInterfacesWindowBtn= $('#showInterfacesWindowid');
			var ShowInterfacesWindowsModal = $('#ShowInterfacesWindowsModal');
			var showinterfaces = document.getElementById("showinterfaces");
			var interfacesdiv=document.createElement("div"); //making a div to show all interfaces
		   	showinterfaces.appendChild(interfacesdiv);			
			showInterfacesWindowBtn.click(function(){  // when clicking showInterfacesBtn
				ShowInterfacesWindowsModal.modal('show');// show the modal
				showinterfaces.removeChild(interfacesdiv); // clearing rubbish from before
				interfacesdiv=document.createElement("div");
				interfacesdiv.id="interfacesdiv";
				var COUNT=-1;
				for(i=0;i<SRInterfacesarr.length;i++)//adding each SRinterface with its dataelements info
			    {
			        var irr=document.createElement("div");
			        node = document.createTextNode(Number(i+1)+"-InterfaceName : "+SRInterfacesarr[i].name+"\xa0\xa0InterfaceType: S/R ");
				    irr.appendChild(node);
				    irr.appendChild(document.createElement("br"));
				    for(j=0;j<SRInterfacesarr[i].dataelements.length;j++)
					{
				        node=document.createTextNode("\xa0\xa0\xa0 Dataelement"+Number(j+1)+"\xa0\xa0 Name: "+SRInterfacesarr[i].dataelements[j].name+"\xa0\xa0\xa0Type: "+SRInterfacesarr[i].dataelements[j].type);
				        irr.appendChild(node);
						irr.appendChild(document.createElement("br"));
					}
				    interfacesdiv.appendChild(irr);
					var delete_btn=document.createElement("input");
					delete_btn.type="button";
				    delete_btn.setAttribute("class","btn btn-danger");
				    delete_btn.style.margin = "5px 5px 20px 5px";

	                delete_btn.value="Delete Interface";
	                delete_btn.id=SRInterfacesarr[i].name;
					delete_btn.addEventListener("click", function(event) {
		  	        	try
			  	        {
			  	         	portname=check_Interface_Relationto_Port(event.currentTarget.id).port;
				  	        swc=check_Interface_Relationto_Port(event.currentTarget.id).swc;
			  	        } 
			  	        catch(d)
			  	        {
			  	        	portname=null;
			  	        }
			  	        if(portname!=null)
			  	        {
			  	         	alert("Interface : "+event.currentTarget.id+"  is used in Port : "+portname+" in Software Component : " +swc+" you can't delete it!!")
			  	        }
			  	        else
			  	        {
			  	         	index=get_InterfacesArray_index(event.currentTarget.id,SRInterfacesarr);
	                        SRInterfacesarr.splice(index,1) ;
				            var queryString = decodeURIComponent(window.location.search);
	                        queryString = queryString.substring(1);
	                        var queries = queryString.split("&");
	                        var projectName=queries.toString().trim();
	      	                let where = 
	      	                {
	                         	name:projectName
	                        };

	                        let set =
	                        {
	                           "SRInterfacesarr":SRInterfacesarr,
	                        };
	                        db.updateRow('project', where, set, (succ, msg) => {
	                        // succ - boolean, tells if the call is successful
	                        console.log("CS: " +succ+"  "+msg);
	                               });
							showInterfacesWindowBtn.click();
					  	}
	                });

	                interfacesdiv.appendChild(delete_btn);
				    COUNT=i;
			    }
			  	COUNT+=2;
			  	for(i=0;i<CSInterfacesarr.length;i++)//adding eacht CSinterface with its operations info
			 	{
			       	var irr=document.createElement("div");
			       	node = document.createTextNode(Number(COUNT)+"-InterfaceName : "+CSInterfacesarr[i].name+"\xa0\xa0InterfaceType: C/S ");
				   	irr.appendChild(node);
				  	irr.appendChild(document.createElement("br"));
				  	for(j=0;j<CSInterfacesarr[i].operations.length;j++)
				    {
				        node=document.createTextNode("\xa0\xa0\xa0\xa0\xa0\xa0 Operation"+Number(j+1)+"\xa0\xa0 "+CSInterfacesarr[i].operations[j].name);
						node2=document.createTextNode("\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0 Args:");
				        irr.appendChild(node);
						irr.appendChild(document.createElement("br"));
						irr.appendChild(node2);
						irr.appendChild(document.createElement("br"));
				        for(k=0;k<CSInterfacesarr[i].operations[j].arguments.length;k++)
				        {
					        node=document.createTextNode("\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0 arg\xa0"+Number(k+1)+"\xa0\xa0 "+CSInterfacesarr[i].operations[j].arguments[k].name+"\xa0\xa0"+CSInterfacesarr[i].operations[j].arguments[k].datatype+"\xa0\xa0"+CSInterfacesarr[i].operations[j].arguments[k].argumenttype);
					        irr.appendChild(node);
							irr.appendChild(document.createElement("br"));
				        }
						node2=document.createTextNode("\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0 Errors:");
						irr.appendChild(node2);
						irr.appendChild(document.createElement("br"));
				        for(k=0;k<CSInterfacesarr[i].operations[j].errors.length;k++)
				        {
					        node=document.createTextNode("\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0error\xa0"+Number(k+1)+"\xa0\xa0 name:\xa0 "+CSInterfacesarr[i].operations[j].errors[k].name+"\xa0\xa0 code:\xa0"+CSInterfacesarr[i].operations[j].errors[k].code);
					        irr.appendChild(node);
							irr.appendChild(document.createElement("br"));
				        }
				    }
				    for(j=0;j<CSInterfacesarr[i].possibleerrors.length;j++)
				    {
				        node=document.createTextNode("\xa0\xa0\xa0\xa0\xa0\xa0Possible Error"+Number(j+1)+"\xa0 name:\xa0 "+CSInterfacesarr[i].possibleerrors[j].name+"\xa0 code:\xa0 "+CSInterfacesarr[i].possibleerrors[j].code);
				        irr.appendChild(node);
						irr.appendChild(document.createElement("br"));
				    }
			        interfacesdiv.appendChild(irr);
				    var delete_btn=document.createElement("input");
				    delete_btn.type="button";
				 	delete_btn.setAttribute("class","btn btn-danger");	
				 	delete_btn.style.margin = "5px 5px 20px 5px";
                  	delete_btn.value="Delete Interface";
                  	delete_btn.id=CSInterfacesarr[i].name;
				  	console.log(i);
				  	delete_btn.addEventListener("click", function() {
			  	        try
			  	        {
				  	        portname=check_Interface_Relationto_Port(event.currentTarget.id).port;
				  	        swc=check_Interface_Relationto_Port(event.currentTarget.id).swc;
			  	        } 
			  	        catch(d)
			  	        {	
			  	        	portname=null;
			  	        }
			  	        if(portname!=null)
			  	        {
			  	         	alert("Interface : "+event.currentTarget.id+"  is used in Port : "+portname+" in Software Component : " +swc+ " you can't delete it!!")
			  	        }
			  	        else 
			  	        {
			  	         	index=get_InterfacesArray_index(event.currentTarget.id,CSInterfacesarr)
	                        CSInterfacesarr.splice(index,1) ;
				            var queryString = decodeURIComponent(window.location.search);
	                        queryString = queryString.substring(1);
	                        var queries = queryString.split("&");
	                        var projectName=queries.toString().trim();
	      	                let where =
	      	                {
	                         index: "0"
	                        };
	                        let set = 
	                        {
	                           "CSInterfacesarr":CSInterfacesarr,
	                        };
	                        db.updateRow(projectName, where, set, (succ, msg) => {
	                        // succ - boolean, tells if the call is successful
	                        console.log("CS: " +succ+"  "+msg);
	                               });
							showInterfacesWindowBtn.click();
			  	        }

                    });
                    interfacesdiv.appendChild(delete_btn);
			 		COUNT++;
			    }
			    showinterfaces.appendChild(interfacesdiv);
			});
}
$(document).ready(function(){

	setTimeout(function(){
		/****Show Data Types and Data Elements Window Modal****/
		Show_Load_DataTypesandDataElements_Modal()
		/****Show Add Sender-Reciever Interface Modal****/
	    AddSenderReceiver_Modal()
		/****Show Add Client-Server Interface Modal****/
	    Show_AddClientServerInterface_Modal()
		/****Show Interfaces Modal****/
		Show_Load_Interfaces_Modal()
	}, 350);
});
