$(document).ready(function(){
	var btn_id = "generate_Composition_arxml";
	$('body').delegate(`#${btn_id}`, 'click', function(){
		save(); // save actions in connection area to json textarea

		// create the XML structure recursively
		var XML = new XMLWriter();
			XML.BeginNode("AUTOSAR");
				XML.Attrib("xsi:schemaLocation", "http://autosar.org/schema/r4.0 AUTOSAR_4-3-0.xsd");
				XML.Attrib("xmlns", "http://autosar.org/schema/r4.0");
				XML.Attrib("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
				// Your structure Composition.xml file here...
			XML.EndNode();
		XML.Close();

		// init xml export data
		var header_tag = `<?xml version="1.0" encoding="UTF-8"?>`; // header
		var xml_result = header_tag + XML.ToString(); // append internal contect with header
		save_arxml_file(btn_id, formatXml(xml_result, '  '), 'Composition.arxml', 'text/plain'); // save & download file

	})
});