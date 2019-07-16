function init() {
    if (window.goSamples) goSamples();  // init for these samples -- you don't need to call this
    var $ = go.GraphObject.make;  //for conciseness in defining node templates

    myDiagram =
      $(go.Diagram, "myDiagramDiv",  //Diagram refers to its DIV HTML element by id
        {
        	initialContentAlignment: go.Spot.Center,
        	"textEditingTool.textValidation": isValidScore,
        	"undoManager.isEnabled": true
        });

    // validation function for editing text
    function isValidScore(textblock, oldstr, newstr) {
    	// It has any kind of whitespace
    	if (/\s/.test(newstr) || newstr.length <= 0) {
    		alert('can\'t set whitespace with SWC name or leave it empty.');
    		return false;
			}
			return true;
    }

    myDiagram.addDiagramListener("BackgroundDoubleClicked",
      function(e) {
        showNewSoftwareComponentModal(e);
       });
    // when the document is modified, add a "*" to the title and enable the "Save" button
    myDiagram.addDiagramListener("Modified", function(e) {
      var button = document.getElementById("SaveButton");
      if (button) button.disabled != myDiagram.isModified;
      var idx = document.title.indexOf("*");
      if (myDiagram.isModified) {
        if (idx < 0) document.title += "*";
      } else {
        if (idx >= 0) document.title = document.title.substr(0, idx);
      }
    });

    // To simplify this code we define a function for creating a context menu button:
    function makeButton(text, action, visiblePredicate) {
      return $("ContextMenuButton",
               $(go.TextBlock, text),
               {
              	click: action
               },
               // don't bother with binding GraphObject.visible if there's no predicate
               visiblePredicate ? new go.Binding("visible", "", function(o, e) { return o.diagram ? visiblePredicate(o, e) : false; }).ofObject() : {});
    }


    var nodeMenu =  // context menu for each Node
      $(go.Adornment, "Vertical",
        makeButton("Copy",
                   function(e, obj) { e.diagram.commandHandler.copySelection(); }),
        makeButton("Delete",
                   function(e, obj) { e.diagram.commandHandler.deleteSelection(); }),
        $(go.Shape, "LineH", { strokeWidth: 2, height: 1, stretch: go.GraphObject.Horizontal }),
        makeButton("Add new port",
                   function (e, obj) {
                    showNewPortModal();
                    //addPort("left");
                     }),/*
        makeButton("Add right port",
                   function (e, obj) {
                    showNewPortModal();
                    //addPort("right");
                     }),*/
        makeButton("properties",
                   function (e, obj) {
/*                    var msg = "";
                  		e.diagram.selection.each(function(n) {
	                   	 	if (!n instanceof go.Node) return;
	                    	if (msg.length > 0) msg += ", ";
	                    	msg += n.data.name;
                    	})*/
                      showPropertiesModal();
                    }),
        makeButton("Generate ARXML",
                   function (e, obj) {
                    Generate_Swc_Arxml();
                     })
      );

    var portSize = new go.Size(10, 10);

    var portMenu =  // context menu for each port
      $(go.Adornment, "Vertical",
        makeButton("Remove port",
                   // in the click event handler, the obj.part is the Adornment;
                   // its adornedObject is the port
                   function (e, obj)
                   {
                      var swc;
                      var portname=obj.part.adornedObject.ie.portId;
                      e.diagram.selection.each(function(n) {
                        if (!n instanceof go.Node) return;
                        swc=n.data;
                      })
                      runnablename=check_Port_Relationto_Runnable(portname,swc);

                      if(!confirm('Are you sure to delect ' + portname + ' port?')) {
                      	return;
                      }

                      if(runnablename!=null)
                      {
                      alert("Port : "+portname+"  is used by Runnable : "+runnablename+" you can't delete it!!")
                      }
                      else
                      {
                       removePort(obj.part.adornedObject);
                      }
                   }

                  )
      );

    // the node template
    // includes a panel on each side with an itemArray of panels containing ports
    myDiagram.nodeTemplate =
      $(go.Node, "Table",
        { locationObjectName: "BODY",
          locationSpot: go.Spot.Center,
          selectionObjectName: "BODY",
          contextMenu: nodeMenu,
        },
        new go.Binding("location", "loc", go.Point.parse).makeTwoWay(go.Point.stringify),

        // the body
        $(go.Panel, "Auto",
          { row: 1, column: 1, name: "BODY", },
          $(go.Shape, "Rectangle",
            {
            	fill: "#FFFFFF",
            	stroke: "#2d2d2d",
            	strokeWidth: 3,
            	cursor: "pointer",
            	minSize: new go.Size(80, 56)
            }),
          $(go.TextBlock, {
          	margin: 10,
          	textAlign: "center",
          	font: "14px  Segoe UI,sans-serif",
          	stroke: "black",
          	editable: true
          },
          new go.Binding("text", "name").makeTwoWay())
        ),  // end Auto Panel body

        // the Panel holding the left port elements, which are themselves Panels,
        // created for each item in the itemArray, bound to data.leftArray
        $(go.Panel, "Vertical",
          new go.Binding("itemArray", "leftArray"),
          { row: 1, column: 0,
            itemTemplate:
              $(go.Panel,
                {
                	name: 'PORT',
                	_side: "left",  // internal property to make it easier to tell which side it's on
                  fromSpot: go.Spot.Left,
                  toSpot: go.Spot.Left,
                  fromLinkable: true,
                  toLinkable: true,
                  cursor: "pointer",
                  contextMenu: portMenu,
                  fromLinkableDuplicates: false, toLinkableDuplicates: false,
                  fromLinkableSelfNode: false, toLinkableSelfNode: false
                },
                new go.Binding("portId", "portId"),
                $(go.Shape, "Rectangle",
                  { stroke: null,
                  	strokeWidth: 0,
                    desiredSize: portSize,
                    margin: new go.Margin(1,0)
                  },
                  new go.Binding("fill", "portColor")),
	                {
			          	mouseEnter: function(e, obj, prev) {  // change group's background brush
			            	// console.log(obj.part.adornedObject);
			            	e.diagram.selection.each(function(n) {
		                       	// console.log(n);
		                    })
			          	}
			        }
              )  // end itemTemplate
          },
        ),  // end Vertical Panel

        // the Panel holding the right port elements, which are themselves Panels,
        // created for each item in the itemArray, bound to data.rightArray
        $(go.Panel, "Vertical",
          new go.Binding("itemArray", "rightArray"),
          { row: 1, column: 2,
            itemTemplate:
              $(go.Panel,
                { _side: "right",
                  fromSpot: go.Spot.Right, toSpot: go.Spot.Right,
                  fromLinkable: true, toLinkable: true, cursor: "pointer",
                  contextMenu: portMenu ,
                  fromLinkableDuplicates: false, toLinkableDuplicates: false,
                  fromLinkableSelfNode: false, toLinkableSelfNode: false
                },
                new go.Binding("portId", "portId"),
                $(go.Shape, "Rectangle",
                  { stroke: null,
                  	strokeWidth: 0,
                    desiredSize: portSize,
                    margin: new go.Margin(1, 0)
                  },
                  new go.Binding("fill", "portColor"))
              )  // end itemTemplate
          }
        ),  // end Vertical Panel





      );  // end Node

    // an orthogonal link template, reshapable and relinkable
    myDiagram.linkTemplate =
      $(CustomLink,  // defined below
        {
          routing: go.Link.Orthogonal,
          corner: 5,
          curve: go.Link.JumpGap,
          reshapable: true,
          resegmentable: true,
          relinkableFrom: true,
          relinkableTo: true
        },
        new go.Binding("points").makeTwoWay(),
        $(go.Shape, { stroke: "#2F4F4F", strokeWidth: 2}),
        $(go.Shape, { stroke: "2F4F4F", fill: "gray", toArrow: "Standard" })
      );

    // support double-clicking in the background to add a copy of this data as a node
    // left required(r) ----  Right provide (p)
    //myDiagram.BackgroundDoubleClicked =
    /*
    myDiagram.toolManager.clickCreatingTool.archetypeNodeData =
      name:"",
      leftArray: [],
      rightArray: [],
    };*/
   // myDiagram.toolManager.linkingTool.linkValidation = performLinkValidation;
    myDiagram.contextMenu =
      $(go.Adornment, "Vertical",
          makeButton("Paste",
                     function(e, obj) { e.diagram.commandHandler.pasteSelection(e.diagram.lastInput.documentPoint); },
                     function(o) { return o.diagram.commandHandler.canPasteSelection(); }),
          makeButton("Undo",
                     function(e, obj) { e.diagram.commandHandler.undo(); },
                     function(o) { return o.diagram.commandHandler.canUndo(); }),
          makeButton("Redo",
                     function(e, obj) { e.diagram.commandHandler.redo(); },
                     function(o) { return o.diagram.commandHandler.canRedo(); })
      );

    // load the diagram from JSON data
    load();
  }


  // This custom-routing Link class tries to separate parallel links from each other.
  // This assumes that ports are lined up in a row/column on a side of the node.
  function CustomLink() {
    go.Link.call(this);
  };
  go.Diagram.inherit(CustomLink, go.Link);

  CustomLink.prototype.findSidePortIndexAndCount = function(node, port) {
    var nodedata = node.data;
    if (nodedata !== null) {
      var portdata = port.data;
      var side = port._side;
      var arr = nodedata[side + "Array"];
      var len = arr.length;
      for (var i = 0; i < len; i++) {
        if (arr[i] === portdata) return [i, len];
      }
    }
    return [-1, len];
  };

  /** @override */
  CustomLink.prototype.computeEndSegmentLength = function(node, port, spot, from) {
    var esl = go.Link.prototype.computeEndSegmentLength.call(this, node, port, spot, from);
    var other = this.getOtherPort(port);
    if (port !== null && other !== null) {
      var thispt = port.getDocumentPoint(this.computeSpot(from));
      var otherpt = other.getDocumentPoint(this.computeSpot(!from));
      if (Math.abs(thispt.x - otherpt.x) > 20 || Math.abs(thispt.y - otherpt.y) > 20) {
        var info = this.findSidePortIndexAndCount(node, port);
        var idx = info[0];
        var count = info[1];
        if (port._side == "top" || port._side == "bottom") {
          if (otherpt.x < thispt.x) {
            return esl + 4 + idx * 8;
          } else {
            return esl + (count - idx - 1) * 8;
          }
        } else {  // left or right
          if (otherpt.y < thispt.y) {
            return esl + 4 + idx * 8;
          } else {
            return esl + (count - idx - 1) * 8;
          }
        }
      }
    }
    return esl;
  };

  /** @override */
  CustomLink.prototype.hasCurviness = function() {
    if (isNaN(this.curviness)) return true;
    return go.Link.prototype.hasCurviness.call(this);
  };

  /** @override */
  CustomLink.prototype.computeCurviness = function() {
    if (isNaN(this.curviness)) {
      var fromnode = this.fromNode;
      var fromport = this.fromPort;
      var fromspot = this.computeSpot(true);
      var frompt = fromport.getDocumentPoint(fromspot);
      var tonode = this.toNode;
      var toport = this.toPort;
      var tospot = this.computeSpot(false);
      var topt = toport.getDocumentPoint(tospot);
      if (Math.abs(frompt.x - topt.x) > 20 || Math.abs(frompt.y - topt.y) > 20) {
        if ((fromspot.equals(go.Spot.Left) || fromspot.equals(go.Spot.Right)) &&
            (tospot.equals(go.Spot.Left) || tospot.equals(go.Spot.Right))) {
          var fromseglen = this.computeEndSegmentLength(fromnode, fromport, fromspot, true);
          var toseglen = this.computeEndSegmentLength(tonode, toport, tospot, false);
          var c = (fromseglen - toseglen) / 2;
          if (frompt.x + fromseglen >= topt.x - toseglen) {
            if (frompt.y < topt.y) return c;
            if (frompt.y > topt.y) return -c;
          }
        } else if ((fromspot.equals(go.Spot.Top) || fromspot.equals(go.Spot.Bottom)) &&
                   (tospot.equals(go.Spot.Top) || tospot.equals(go.Spot.Bottom))) {
          var fromseglen = this.computeEndSegmentLength(fromnode, fromport, fromspot, true);
          var toseglen = this.computeEndSegmentLength(tonode, toport, tospot, false);
          var c = (fromseglen - toseglen) / 2;
          if (frompt.x + fromseglen >= topt.x - toseglen) {
            if (frompt.y < topt.y) return c;
            if (frompt.y > topt.y) return -c;
          }
        }
      }
    }
    return go.Link.prototype.computeCurviness.call(this);
  };
  // end CustomLink class


  // Add a port to the specified side of the selected nodes.
  function addPort(side) {
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
      if (arr) {
        // create a new port data object
        var newportdata = {
          portId: name,
          //portColor: go.Brush.randomColor()
          // if you add port data properties here, you should copy them in copyPortData above
        };
        // and add it to the Array of port data
        myDiagram.model.insertArrayItem(arr, -1, newportdata);
      }
    });
    myDiagram.commitTransaction("addPort");
  }

  // Exchange the position/order of the given port with the next one.
  // If it's the last one, swap with the previous one.
  function swapOrder(port) {
    var arr = port.panel.itemArray;
    if (arr.length >= 2) {  // only if there are at least two ports!
      for (var i = 0; i < arr.length; i++) {
        if (arr[i].portId === port.portId) {
          myDiagram.startTransaction("swap ports");
          if (i >= arr.length - 1) i--;  // now can swap I and I+1, even if it's the last port
          var newarr = arr.slice(0);  // copy Array
          newarr[i] = arr[i + 1];  // swap items
          newarr[i + 1] = arr[i];
          // remember the new Array in the model
          myDiagram.model.setDataProperty(port.part.data, port._side + "Array", newarr);
          myDiagram.commitTransaction("swap ports");
          break;
        }
      }
    }
  }

  // Remove the clicked port from the node.
  // Links to the port will be redrawn to the node's shape.
  function removePort(port) {
    myDiagram.startTransaction("removePort");
    var pid = port.portId;
    var arr = port.panel.itemArray;
    for (var i = 0; i < arr.length; i++) {
      if (arr[i].portId === pid) {
        myDiagram.model.removeArrayItem(arr, i);
        break;
      }
    }
    myDiagram.commitTransaction("removePort");
  }

  // Remove all ports from the same side of the node as the clicked port.
  function removeAll(port) {
    myDiagram.startTransaction("removePorts");
    var nodedata = port.part.data;
    var side = port._side;  // there are four property names, all ending in "Array"
    myDiagram.model.setDataProperty(nodedata, side + "Array", []);  // an empty Array
    myDiagram.commitTransaction("removePorts");
  }
  // Change the color of the clicked port.
  function changeColor(port) {
    myDiagram.startTransaction("colorPort");
    var data = port.data;
    myDiagram.model.setDataProperty(data, "portColor", go.Brush.randomColor());
    myDiagram.commitTransaction("colorPort");
  }


    var myDbSavedModal;

      var db = nodeRequire('electron-db');
  // Save the model to / load it from JSON text shown on the page itself, not in a database.
  function save() {
    //document.getElementById("mySavedModel").value = myDiagram.model.toJson();
    var diagramObject = myDiagram.model.toJson()
    var data = JSON.parse(diagramObject).nodeDataArray;


    //console.log("Welcome "+projectName);
    //saveDataLink(diagramObject);
    //myDiagram.isModified = false;
    // Variables
    var queryString = decodeURIComponent(window.location.search);
    queryString = queryString.substring(1);
    var queries = queryString.split("&");
    var projectName=queries.toString().trim();

    console.log(diagramObject);
    console.log(projectName)

    /*data.forEach(function(element) {
        set[element.name]=[];
        set[element.name].push({"ports":"","runnables":"","events":""})
      });
    */

     db.updateRow('project', {'name':projectName}, {"Diagram": diagramObject}, (succ, msg) => {
      // succ - boolean, tells if the call is successful
      console.log("Success: " + succ);
      console.log("Message: " + msg);

    });



/*const arr = ['class', 'copiesArrays', 'copiesArrayObjects', 'linkFromPortIdProperty', 'linkToPortIdProperty','nodeDataArray','linkDataArray'];
  const m = arr.map((product, id) => {
  const obj = {}
  obj.image_name = product;
  obj.index = id;
  return obj;
  });
  db.insertTableContents('records', m, (isSuccess, message) => {
  console.log(isSuccess);
  console.log(message);
  });*/

  }

var datatypesselected = new Array();   //// array contain selected datatypes
var SRInterfacesarr   = new Array();// array contain all SRInterfaces objects
var CSInterfacesarr   = new Array();// array contain all CSInterfaces objects

  function load() {
    // get row of index 0
       // Variables
    var queryString = decodeURIComponent(window.location.search);
    queryString = queryString.substring(1);
    var queries = queryString.split("&");
    var projectName=queries.toString().trim();
    db.getRows('project', {name:projectName}, (succ, result) => {
    console.log("Success: " + succ);
    console.log(result);
        if(succ == true) {
   datatypesselected=result[0]["datatypesselected"];
    SRInterfacesarr=result[0]["SRInterfacesarr"];
    CSInterfacesarr=result[0]["CSInterfacesarr"];
     myDbSavedModal = result[0]["Diagram"]
  }
    })


	// loading databases and interfaces from database
    if(datatypesselected=="" || datatypesselected==undefined)datatypesselected=[];
    if(SRInterfacesarr=="" || SRInterfacesarr==undefined)SRInterfacesarr=[];
    if(CSInterfacesarr=="" || CSInterfacesarr==undefined)CSInterfacesarr=[];
    // get 'Diagram' attribute & change it to string

    console.log(myDbSavedModal);
    if(isEmpty(myDbSavedModal))
    {
      myDiagram.model = go.Model.fromJson(document.getElementById("mySavedModel").value);
    }
    // show the diagram model
    else{
    myDiagram.model = go.Model.fromJson(myDbSavedModal);}
    // When copying a node, we need to copy the data that the node is bound to.
    // This JavaScript object includes properties for the node as a whole, and
    // four properties that are Arrays holding data for each port.
    // Those arrays and port data objects need to be copied too.
    // Thus Model.copiesArrays and Model.copiesArrayObjects both need to be true.

    // Link data includes the names of the to- and from- ports;
    // so the GraphLinksModel needs to set these property names:
    // linkFromPortIdProperty and linkToPortIdProperty.
  }

  function returnToMainWindow()
  {
    //
    let myDbSavedModal2 ;
    db.getRows('project', {projectName:projectName}, (succ, result) => {
    console.log("Success: " + succ);
    console.log(result);
    myDbSavedModal2=result;
    })
    // get 'Diagram' attribute & change it to string
    myDbSavedModal2 = myDbSavedModal2.map(a => a.Diagram).toString();
    console.log("Saved"+myDbSavedModal2);
    if(myDbSavedModal2==myDiagram.model.toJson()){
      console.log("The same");
      // The diagram model is already saved in database
      window.location="index.html";
    }
    else
    {
      // the diagre=am is not saved in database
      // ask if you want to save your work Model
      var returnToMainWindowModal = $('#returnToMainWindowModal');
      returnToMainWindowModal.modal('show');
      // check yes or no
      returnToMainWindowModal.delegate('.save-project', 'click', function(){
        save();
        returnToMainWindowModal.modal('hide');
        window.location="index.html";
       });
      returnToMainWindowModal.delegate('.dont-save-project', 'click', function(){
        returnToMainWindowModal.modal('hide');
        window.location="index.html";
       });
      //console.log("Different");

    }
    var href = "index.html";

  }

   function checkLinks(node, link, port) {
    console.log(link.count);
        return (link.count > 0) ? 0 :1;
    }
