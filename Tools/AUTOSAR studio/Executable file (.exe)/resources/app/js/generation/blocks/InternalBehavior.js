function Generate_Internal_Behavior(x,swc)
{
  runnablearr=[];
  myDiagram.selection.each(function(node) {
  if (!(node instanceof go.Node)) return;
  runnablearr = node.data["Runnables"];
  })
  if(runnablearr==undefined)runnablearr=[];	
  x.BeginNode("SWC-INTERNAL-BEHAVIOR");  
    x.Node("SHORT-NAME",swc+"_InternalBehavior");	
    if (runnablearr.length!=0)
    {
		x.BeginNode("Events");  	
		for (i=0;i<runnablearr.length;i++)
		{
			if(runnablearr[i].Event.type=="Timing-Event")
				{
					x.BeginNode("TIMING-EVENT");
					    x.Node("SHORT-NAME",runnablearr[i].Event.name);	
						x.BeginNode("START-ON-EVENT-REF");
							x.Attrib("DEST", "RUNNABLE-ENTITY");
							x.WriteString(`/${runnablearr[i].Event.runnablepath}${window.closer}`);																		
						x.EndNode();
					    x.Node("PERIOD",runnablearr[i].Event.period);	
					x.EndNode();
				}
			else if(runnablearr[i].Event.type=="Data-Recieved-Event")
				{
					x.BeginNode("DATA-RECEIVED-EVENT");
					    x.Node("SHORT-NAME",runnablearr[i].Event.name);	
						x.BeginNode("START-ON-EVENT-REF");
							x.Attrib("DEST", "RUNNABLE-ENTITY");
							x.WriteString(`/${runnablearr[i].Event.runnablepath}${window.closer}`);																		
						x.EndNode();
						x.BeginNode("DATA-IREF");
							x.BeginNode("CONTEXT-R-PORT-REF");
								x.Attrib("DEST", "R-PORT-PROTOTYPE");
								x.WriteString(`/${runnablearr[i].Event.portpath}${window.closer}`);																		
							x.EndNode();	
							x.BeginNode("TARGET-DATA-ELEMENT-REF");
								x.Attrib("DEST", "VARIABLE-DATA-PROTOTYPE");
								x.WriteString(`/${runnablearr[i].Event.datapath}${window.closer}`);																		
							x.EndNode();								
						x.EndNode();					
					x.EndNode();				
				}
			else if(runnablearr[i].Event.type=="Operation-Invoked-Event")
				{
					x.BeginNode("OPERATION-INVOKED-EVENT");
					    x.Node("SHORT-NAME",runnablearr[i].Event.name);	
						x.BeginNode("START-ON-EVENT-REF");
							x.Attrib("DEST", "RUNNABLE-ENTITY");
							x.WriteString(`/${runnablearr[i].Event.runnablepath}${window.closer}`);																		
						x.EndNode();
						x.BeginNode("OPERATION-IREF");
							x.BeginNode("CONTEXT-P-PORT-REF");
								x.Attrib("DEST", "P-PORT-PROTOTYPE");
								x.WriteString(`/${runnablearr[i].Event.portpath}${window.closer}`);																		
							x.EndNode();	
							x.BeginNode("TARGET-PROVIDED-OPERATION-REF");
								x.Attrib("DEST", "CLIENT-SERVER-OPERATION");
								x.WriteString(`/${runnablearr[i].Event.datapath}${window.closer}`);																		
							x.EndNode();								
						x.EndNode();					
					x.EndNode();				
				}
	        else if(runnablearr[i].Event.type=="DATA-RECEIVE-ERROR-EVENT")
				{
					x.BeginNode("DATA-RECEIVE-ERROR-EVENT");
					    x.Node("SHORT-NAME",runnablearr[i].Event.name);	
						x.BeginNode("START-ON-EVENT-REF");
							x.Attrib("DEST", "RUNNABLE-ENTITY");
							x.WriteString(`/${runnablearr[i].Event.runnablepath}${window.closer}`);																		
						x.EndNode();
						x.BeginNode("DATA-IREF");
							x.BeginNode("CONTEXT-R-PORT-REF");
								x.Attrib("DEST", "R-PORT-PROTOTYPE");
								x.WriteString(`/${runnablearr[i].Event.portpath}${window.closer}`);																		
							x.EndNode();	
							x.BeginNode("TARGET-DATA-ELEMENT-REF");
								x.Attrib("DEST", "VARIABLE-DATA-PROTOTYPE");
								x.WriteString(`/${runnablearr[i].Event.datapath}${window.closer}`);																		
							x.EndNode();								
						x.EndNode();					
					x.EndNode();					
				}	
			else if(runnablearr[i].Event.type=="Init-Event")
				{
					x.BeginNode("INIT-EVENT");
					    x.Node("SHORT-NAME",runnablearr[i].Event.name);	
						x.BeginNode("START-ON-EVENT-REF");
							x.Attrib("DEST", "RUNNABLE-ENTITY");
							x.WriteString(`/${runnablearr[i].Event.runnablepath}${window.closer}`);																		
						x.EndNode();
					x.EndNode();
				}						
		}	
		x.EndNode();
	}
   if (runnablearr.length!=0)
   {
		  x.BeginNode("RUNNABLES");  
			for (k=0;k<runnablearr.length;k++)
			{
			    x.BeginNode("RUNNABLE-ENTITY");
			        x.Node("SHORT-NAME",runnablearr[k].runnableName);	
					x.Node("CAN-BE-INVOKED-CONCURRENTLY",runnablearr[k].invoked.toString());
					console.log(runnablearr[k].invoked)
					x.Node("MINIMUM-START-INTERVAL",runnablearr[k].minimumStartInterval.toString());	
		            console.log(runnablearr[k].minimumStartInterval)
					if(runnablearr[k].Explicit_Data_write_access.length!=0)
		            {
				        x.BeginNode("DATA-SEND-POINTS");			
			            for(i=0;i<runnablearr[k].Explicit_Data_write_access.length;i++)
						{
							x.BeginNode("VARIABLE-ACCESS");
			                    x.Node("SHORT-NAME",runnablearr[k].Explicit_Data_write_access[i].name);	
							    x.BeginNode("ACCESSED-VARIABLE");
							        x.BeginNode("AUTOSAR-VARIABLE-IREF");
										x.BeginNode("PORT-PROTOTYPE-REF");
											x.Attrib("DEST", "P-PORT-PROTOTYPE");
											x.WriteString(`/${runnablearr[k].Explicit_Data_write_access[i].port}${window.closer}`);																		
										x.EndNode();	
										x.BeginNode("TARGET-DATA-PROTOTYPE-REF");
											x.Attrib("DEST", "VARIABLE-DATA-PROTOTYPE");
								 		    x.WriteString(`/${runnablearr[k].Explicit_Data_write_access[i].data}${window.closer}`);																		
										x.EndNode();								
			                        x.EndNode();	                   
								x.EndNode();	
			                x.EndNode();				
						}
						x.EndNode();		            	
		            }
					if(runnablearr[k].Implicit_Data_write_access.length!=0)
					{
				        x.BeginNode("DATA-WRITE-ACCESSS");			
			            for(i=0;i<runnablearr[k].Implicit_Data_write_access.length;i++)
						{
							x.BeginNode("VARIABLE-ACCESS");
			                    x.Node("SHORT-NAME",runnablearr[k].Implicit_Data_write_access[i].name);	
							    x.BeginNode("ACCESSED-VARIABLE");
							        x.BeginNode("AUTOSAR-VARIABLE-IREF");
										x.BeginNode("PORT-PROTOTYPE-REF");
											x.Attrib("DEST", "P-PORT-PROTOTYPE");
											x.WriteString(`/${runnablearr[k].Implicit_Data_write_access[i].port}${window.closer}`);																		
										x.EndNode();	
										x.BeginNode("TARGET-DATA-PROTOTYPE-REF");
											x.Attrib("DEST", "VARIABLE-DATA-PROTOTYPE");
											x.WriteString(`/${runnablearr[k].Implicit_Data_write_access[i].data}${window.closer}`);																		
										x.EndNode();								
			                        x.EndNode();	                   
								x.EndNode();	
			                x.EndNode();				
						}
						x.EndNode();						
					}
					if(runnablearr[k].Explicit_Data_read_access.length!=0)
					{
				        x.BeginNode("DATA-RECEIVE-POINT-BY-VALUES");							
			            for(i=0;i<runnablearr[k].Explicit_Data_read_access.length;i++)
						{
							x.BeginNode("VARIABLE-ACCESS");
			                    x.Node("SHORT-NAME",runnablearr[k].Explicit_Data_read_access[i].name);	
							    x.BeginNode("ACCESSED-VARIABLE");
							        x.BeginNode("AUTOSAR-VARIABLE-IREF");
										x.BeginNode("PORT-PROTOTYPE-REF");
											x.Attrib("DEST", "R-PORT-PROTOTYPE");
											x.WriteString(`/${runnablearr[k].Explicit_Data_read_access[i].port}${window.closer}`);																		
										x.EndNode();	
										x.BeginNode("TARGET-DATA-PROTOTYPE-REF");
											x.Attrib("DEST", "VARIABLE-DATA-PROTOTYPE");
											x.WriteString(`/${runnablearr[k].Explicit_Data_read_access[i].data}${window.closer}`);																		
										x.EndNode();								
			                        x.EndNode();	                   
								x.EndNode();	
			                x.EndNode();					
						}
						x.EndNode(); 						
					}			
					if(runnablearr[k].Implicit_Data_read_access.length!=0)
					{
				        x.BeginNode("DATA-READ-ACCESSS");							
			            for(i=0;i<runnablearr[k].Implicit_Data_read_access.length;i++)
						{
							x.BeginNode("VARIABLE-ACCESS");
			                    x.Node("SHORT-NAME",runnablearr[k].Implicit_Data_read_access[i].name);	
							    x.BeginNode("ACCESSED-VARIABLE");
							        x.BeginNode("AUTOSAR-VARIABLE-IREF");
										x.BeginNode("PORT-PROTOTYPE-REF");
											x.Attrib("DEST", "R-PORT-PROTOTYPE");
											x.WriteString(`/${runnablearr[k].Implicit_Data_read_access[i].port}${window.closer}`);																		
										x.EndNode();	
										x.BeginNode("TARGET-DATA-PROTOTYPE-REF");
											x.Attrib("DEST", "VARIABLE-DATA-PROTOTYPE");
											x.WriteString(`/${runnablearr[k].Implicit_Data_read_access[i].data}${window.closer}`);																		
										x.EndNode();								
			                        x.EndNode();	                   
								x.EndNode();	
			                x.EndNode();					
						}
						x.EndNode(); 						
					}
					if(runnablearr[k].Server_Call_points.length!=0)
					{
				        x.BeginNode("SERVER-CALL-POINTS");			
			            for(i=0;i<runnablearr[k].Server_Call_points.length;i++)
						{
							x.BeginNode("SYNCHRONOUS-SERVER-CALL-POINT");
			                    x.Node("SHORT-NAME",runnablearr[k].Server_Call_points[i].name);	
							    x.BeginNode("OPERATION-IREF");
										x.BeginNode("CONTEXT-R-PORT-REF");
											x.Attrib("DEST", "R-PORT-PROTOTYPE");
											x.WriteString(`/${runnablearr[k].Server_Call_points[i].port}${window.closer}`);																		
										x.EndNode();	
										x.BeginNode("TARGET-REQUIRED-OPERATION-REF");
											x.Attrib("DEST", "CLIENT-SERVER-OPERATION");
											x.WriteString(`/${runnablearr[k].Server_Call_points[i].data}${window.closer}`);																		
										x.EndNode();								
								x.EndNode();
			                    x.Node("TIMEOUT","0");					
			                x.EndNode();	
						}
						x.EndNode();						
					}			

			        x.Node("SYMBOL",runnablearr[k].runnableName);				
			    x.EndNode();
			}
			x.EndNode();   	
   }
   

    
  x.EndNode();
	
}	
