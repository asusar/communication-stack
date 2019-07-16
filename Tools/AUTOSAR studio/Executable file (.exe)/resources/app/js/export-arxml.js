function save_arxml_file(btn_id, text, name, type) {
  var dlbtn = document.getElementById(btn_id);
  var file = new Blob([text], {type: type});
  dlbtn.href = URL.createObjectURL(file);
  dlbtn.download = name;
}

function save_file(text, name, type) {
  var file = new Blob([text], {type: type});
  dlbtn.download = name;
}

function GenerateArxml(object)
{
    var softwareComponentName;
  
    myDiagram.selection.each(function (part) {
    if (part instanceof go.Node) {
        softwareComponentName=part.data.name;
       }
    });

    download(object,softwareComponentName+".arxml",'text/plain');
}


// Function to download data to a file
function download(data, filename, type) {
    var file = new Blob([data], {type: type});
    if (window.navigator.msSaveOrOpenBlob) // IE10+
        window.navigator.msSaveOrOpenBlob(file, filename);
    else { // Others
        var a = document.createElement("a"),
                url = URL.createObjectURL(file);
        a.href = url;
        a.download = filename;
        document.body.appendChild(a);
        a.click();
        setTimeout(function() {
            document.body.removeChild(a);
            window.URL.revokeObjectURL(url);  
        }, 0); 
    }
}

/**/
