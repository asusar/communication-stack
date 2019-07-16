// Properties Modal
var propertiesModal = $('#PropModal');
// Save Properties Work Modal
var closePropertiesModal = $('#closePropertiesModal');
/* [Runnables , Ports] main Divs */
    Runnable_Properties             = document.getElementById("Runnable_Properties"),
    Ports_Properties                = document.getElementById("Ports_Properties");
    /* [Runnables , Ports] Navigation Buttons */
var Ports_Button                    = document.getElementById("Ports_Button"),
    Runnables_Button                = document.getElementById("Runnables_Button");

/* Main Properties of SWc [Runnables , Ports] */
function show_Ports_Properties(){
    Runnable_Properties.style.display  = "none";
    Ports_Properties.style.display     = "block";
}
function show_Runnables_Properties(){
    Ports_Properties.style.display     = "none";
    Runnable_Properties.style.display  = "block";
}
function saveConfirm()
{
	
	if(confirm("are you sure you want to save changes?"))save()


}
Ports_Button.addEventListener("click" , show_Ports_Properties);
Runnables_Button.addEventListener("click" , show_Runnables_Properties);
propertiesModal.delegate('.properties-save-button','click',function(){
	if(getRunnableWithoutTriggiredEvent()!=null)
	{
		alert("please set Event to runnable : "+getRunnableWithoutTriggiredEvent());
	}
    // save to database
	else 
	{
		if(confirm("are you sure you want to save changes?"))
		{
			save();
			alert("your work saved successfully");
		}

	}
});

    // Variables
    var queryString = decodeURIComponent(window.location.search);
    queryString = queryString.substring(1);
    var queries = queryString.split("&");
    var projectName=queries.toString().trim();

propertiesModal.on('hide.bs.modal', function (e) {

    let myDbSavedModal2 ;
   /* db.getRows(projectName, {index:"0"}, (succ, result) => {
    console.log("Success: " + succ);
    console.log(result);
    myDbSavedModal2=result;
    })*/
 
    db.getRows('project',{name: projectName}, (succ, result) => {
    console.log("Success: " + succ);
    console.log(result);
    myDbSavedModal2=result;
    })

    // get 'Diagram' attribute & change it to string
	show=false;
	console.log(myDbSavedModal2);
    myDbSavedModal2 = myDbSavedModal2[0]["Diagram"];
   
    

    if(myDbSavedModal2!=myDiagram.model.toJson())
    {
       if (confirm("Do you want to save your work ?")) 
       	{
        	runnableCheck=getRunnableWithoutTriggiredEvent()
        	portcheck=getPortWithoutInterface();
			if(runnableCheck!=null)
		    {   
                e.preventDefault();
				e.stopImmediatePropagation();
				alert("please set Event to runnable : "+runnableCheck);
				return false ;				
			}
            else 
			{
				save();
			}
       	}
		else 
		{
			load();
        }
    }
});
