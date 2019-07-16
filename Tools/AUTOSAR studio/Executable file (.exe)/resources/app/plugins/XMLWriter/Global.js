function JSettings()
{
	this.IE=document.all?true:false;
	this.MouseX=_JSettings_MouseX;
	this.MouseY=_JSettings_MouseY;
	this.SrcElement=_JSettings_SrcElement;
	this.Parent=_JSettings_Parent;
	this.RunOnLoad=_JSettings_RunOnLoad;
	this.FindParent=_JSettings_FindParent;
	this.FindChild=_JSettings_FindChild;
	this.FindSibling=_JSettings_FindSibling;
	this.FindParentTag=_JSettings_FindParentTag;
}
function _JSettings_MouseX(e)
{return this.IE?event.clientX:e.clientX;}
function _JSettings_MouseY(e)
{return this.IE?event.clientY:e.clientY;}
function _JSettings_SrcElement(e)
{return this.IE?event.srcElement:e.target;}
function _JSettings_Parent(Node)
{return this.IE?Node.parentNode:Node.parentElement;}
function _JSettings_RunOnLoad(Meth){var Prev=(window.onload)?window.onload:function(){};window.onload=function(){Prev();Meth();};}
function _JSettings_FindParent(Node, Attrib, Value)
{var Root = document.getElementsByTagName("BODY")[0];
Node = Node.parentNode;	while (Node != Root && Node.getAttribute(Attrib) != Value){Node=Node.parentNode;}
if (Node.getAttribute(Attrib) == Value)	{return Node;} else	{return null;}}
function _JSettings_FindParentTag(Node, TagName)
{var Root = document.getElementsByTagName("BODY")[0];
TagName=TagName.toLowerCase();
Node = Node.parentNode;	while (Node != Root && Node.tagName.toLowerCase() != TagName){Node=Node.parentNode;}
if (Node.tagName.toLowerCase() == TagName) {return Node;} else {return null;}}
function _JSettings_FindChild(Node, Attrib, Value)
{
	if (Node.getAttribute)
		if (Node.getAttribute(Attrib) == Value) return Node;

	var I=0;
	var Ret = null;
	for (I=0;I<Node.childNodes.length;I++)
	{
		Ret = FindChildByAttrib(Node.childNodes[I]);
		if (Ret) return Ret;
	}
	return null;
}
function _JSettings_FindSibling(Node, Attrib, Value)
{
	var Nodes=Node.parentNode.childNodes;
	var I=0;
	for (I=0;I<Nodes.length;I++)
	{
		if (Nodes[I].getAttribute)
		{
			if (Nodes[I].getAttribute(Attrib) == Value)
			{return Nodes[I];}
		}
	}
	return null;
}

var Settings = new JSettings();