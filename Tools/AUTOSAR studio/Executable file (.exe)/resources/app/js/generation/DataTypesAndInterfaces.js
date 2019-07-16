$(document).ready(function(){
	var btn_id = "generate_DataTypesAndInterfaces_arxml";
	$('body').delegate(`#${btn_id}`, 'click', function(){
		save(); // save actions in connection area to json textarea
			    var queryString = decodeURIComponent(window.location.search);
         queryString = queryString.substring(1);
         var queries = queryString.split("&");
         var Projectname=queries.toString().trim();	
		var CSlength=CSInterfacesarr.length;
		var SRlength=SRInterfacesarr.length;
		var datatypeslength=datatypesselected.length;
		// create the XML structure recursively
		var XML = new XMLWriter();
			XML.BeginNode("AUTOSAR");
				XML.Attrib("xsi:schemaLocation", "http://autosar.org/schema/r4.0 AUTOSAR_4-3-0.xsd");
				XML.Attrib("xmlns", "http://autosar.org/schema/r4.0");
				XML.Attrib("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
				// Your structure DataTypesAndInterfaces.xml file here...
			    XML.BeginNode("AR-PACKAGES");
						XML.BeginNode("AR-PACKAGE");
							XML.Node("SHORT-NAME", Projectname);
                                XML.BeginNode("AR-PACKAGES");
									    if(datatypeslength!=0)
										{	
								        XML.BeginNode("AR-PACKAGE");
							                  XML.Node("SHORT-NAME", "DataTypes");
											  XML.BeginNode("ELEMENTS");											    
												  for(i=0;i<datatypeslength;i++)
												  {
														XML.BeginNode("APPLICATION-PRIMITIVE-DATA-TYPE");
																  XML.Node("SHORT-NAME", datatypesselected[i]);	
														XML.EndNode();
												  }
											  
											  XML.EndNode();
										XML.EndNode();
										}
									    if(CSlength!=0 || SRlength!=0)	
										{	
											XML.BeginNode("AR-PACKAGE");
												  XML.Node("SHORT-NAME","PortInterfaces");
												  XML.BeginNode("ELEMENTS");	
												  for(i=0;i<SRlength;i++)
												  {
														XML.BeginNode("SENDER-RECEIVER-INTERFACE");
																  XML.Node("SHORT-NAME", SRInterfacesarr[i].name);	
																  XML.BeginNode("DATA-ELEMENTS");																  
																  for(j=0;j<SRInterfacesarr[i].dataelements.length;j++)
																  {
																	   XML.BeginNode("VARIABLE-DATA-PROTOTYPE");
																			   XML.Node("SHORT-NAME",SRInterfacesarr[i].dataelements[j].name);
																			   XML.BeginNode("TYPE-TREF");
																					XML.Attrib("DEST", "APPLICATION-PRIMITIVE-DATA-TYPE");
																					XML.WriteString(`/${Projectname}/DataTypes/${SRInterfacesarr[i].dataelements[j].type}${window.closer}`);
																			   XML.EndNode();
																	   XML.EndNode();
																  }
																  XML.EndNode();
														XML.EndNode();
												  }	
												  
												  for(i=0;i<CSlength;i++)
												  {
														XML.BeginNode("CLIENT-SERVER-INTERFACE");
																  XML.Node("SHORT-NAME", CSInterfacesarr[i].name);	
																  XML.BeginNode("OPERATIONS");															  
																  for(j=0;j<CSInterfacesarr[i].operations.length;j++)
																  {
																	    XML.BeginNode("CLIENT-SERVER-OPERATION");
																			   XML.Node("SHORT-NAME",CSInterfacesarr[i].operations[j].name);
																			   XML.BeginNode("ARGUMENTS");																			   
																			  for(k=0;k<CSInterfacesarr[i].operations[j].arguments.length;k++)
																			  {
																				   XML.BeginNode("ARGUMENT-DATA-PROTOTYPE");
																						   XML.Node("SHORT-NAME",CSInterfacesarr[i].operations[j].arguments[k].name);
																						   XML.BeginNode("TYPE-TREF");
																								XML.Attrib("DEST", "APPLICATION-PRIMITIVE-DATA-TYPE");
																								XML.WriteString(`/${Projectname}/DataTypes/${CSInterfacesarr[i].operations[j].arguments[k].datatype}${window.closer}`);
																						   XML.EndNode();
																						   XML.BeginNode("DIRECTION");
																								 XML.Node("DIRECTION", CSInterfacesarr[i].operations[j].arguments[k].argumenttype);
																						   XML.EndNode();																		   
																				   XML.EndNode();
																			  }																		   
																						   XML.EndNode();
																        if(CSInterfacesarr[i].operations[j].errors.length==0)
																		{				   
																			 XML.BeginNode("POSSIBLE-ERROR-REFS");
																																			   
																			 for(k=0;k<CSInterfacesarr[i].operations[j].errors.length;k++)
																					{

																						XML.BeginNode("POSSIBLE-ERROR-REF");
																								XML.Attrib("DEST", "APPLICATION-ERROR");
																								XML.WriteString(`/${Projectname}/Interfaces/${CSInterfacesarr[i].name}/${CSInterfacesarr[i].operations[j].errors[k].name}${window.closer}`);																		
																						XML.EndNode();
																					}	
																			 XML.EndNode();	
																		}
																        XML.EndNode();	
																	
																		
										
																  }
																  XML.EndNode();
																  if(CSInterfacesarr[i].possibleerrors.length==0)
																  {
																	  XML.BeginNode("POSSIBLE-ERRORS");
																			XML.WriteString(`${window.closer}`);																  
																		 for(j=0;j<CSInterfacesarr[i].possibleerrors.length;j++)
																		 {   
																			 XML.BeginNode("APPLICATION-ERROR");
																			 XML.Node("SHORT-NAME", CSInterfacesarr[i].possibleerrors[j].name);
																			 XML.Node("ERROR-CODE", CSInterfacesarr[i].possibleerrors[j].code);
																			 XML.EndNode();
																		 } 
																	  XML.EndNode();
																  }
														XML.EndNode();
												  }													  
												  XML.EndNode();
											XML.EndNode();	
										}										
                                XML.EndNode();								 
						XML.EndNode();	
				XML.EndNode();			
			XML.EndNode();
		XML.Close();

		// init xml export data
		var header_tag = `<?xml version="1.0" encoding="UTF-8"?>`; // header
		var xml_result = header_tag + XML.ToString(); // append internal contect with header
		save_arxml_file(btn_id, formatXml(xml_result, '  '), 'DataTypesAndInterfaces.arxml', 'text/plain'); // save & download file

	})
});
