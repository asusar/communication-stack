var db = require('electron-db');
global.sessionName;

function projectNameItemRepeater(project_name, project_id)
{
	return `
	<div class="col-md-12 col-md-12 col-lg-6" style="margin-bottom: 10px;" data-project-name="${project_name}">
      <button class="btn btn-light btn-block" style="border: 1px solid #ba68c8" data-project-name="${project_name}">
      	<div style="font-size: 26px" class="text-primary"><i class="fa fa-file"></i></div>
      	<div>ID: <b>${project_id}</b></div>
      	<div>Project name: <b class="current-p-name">${project_name}</b></div>
      	<a class="btn btn-link" href="#" style="font-size: 13px">click to edit...</a>
      </button>
  	</div>`;
}

function renderProjectsFromElectron()
{
	let project_counter = 0;

	db.getAll('project', function (succ, data){
        $('.wapper_projects').show(300, function(){
        	$.each(data, function(i, v){
        		project_counter = project_counter+1;
        		var repeater = projectNameItemRepeater(v.name, v.id);
        		$('.wapper_projects .row').append(repeater);
        	})
    		$('#projectNumbers').text(`Number of total projects: ${project_counter}`);
        });
	});
}

function loadProjectNamesIntoSelect()
{
	db.getAll('project', function (succ, data){
		var selector = $('#deleteProjectModal select');
		selector.text('');
		$.each(data, function(i, v){
			var repeater = `<option value="${v.id}">${v.name}</option>`;
			selector.append(repeater);
		})
	});
}

function deleteProjectFromElectron()
{
	var selector = $('#deleteProjectModal select');
	var selected_id = parseInt(selector.val());
	var selected_name = $('#deleteProjectModal select option:selected').text();
	console.log('deleteProjectModal1');

	db.deleteRow('project', {'id': selected_id}, (succ, msg) => {
		alert(`Project ${selected_name} is deleted successfully.`);
		$('#deleteProjectModal').modal('hide');
		console.log('deleteProjectModal2');
		$('.wapper_projects .row div[data-project-name="'+ selected_name +'"]').remove(); // remove button from project list
    });
    setTimeout(function(){
    	loadProjectNamesIntoSelect();
        disableDeleteProjectBtn();
    }, 50);
}

function renameProjectFromElectron()
{
	var selector = $('#renameProjectModal select');
	var selected_id = parseInt(selector.val());
	var selected_name = $('#renameProjectModal select option:selected').text();
	let where = {
		"id": selected_id
	};
	let set = {
		"name": rename_name
	}
	db.updateRow('project', where, set, (succ, msg) => {
		// succ - boolean, tells if the call is successful
		console.log("Success: " + succ);
		console.log("Message: " + msg);
	});
	db.deleteRow('project', {'id': selected_id}, (succ, msg) => {
		alert(`Project ${selected_name} is renamed successfully.`);
		$('#deleteProjectModal').modal('hide');
		$('.wapper_projects .row div[data-project-name="'+ selected_name +'"]').remove(); // remove button from project list
    });
   
    setTimeout(function(){
    	loadProjectNamesIntoSelect();
        disableDeleteProjectBtn();
    }, 50);
}

function addProjectToList(project_name)
{
  var repeater = projectNameItemRepeater(project_name, '-');
  $('.wapper_projects .row').append(repeater);
}

function addProjectToProjectDatabase(project_name)
{
	// Add project name to project database
	let obj = new Object();
	obj.name = project_name;
	obj.Diagram="";

	//create a json file for every project
	db.createTable('project', (succ, msg) => {
      	// succ - boolean, tells if the call is successful
        console.log("Success: " + succ);
        console.log("Message: " + msg);
      });
	//insert index
	/*
	setTimeout(function(){
        	//insert index
	let obj2 = new Object();
	obj2.index = "0";
	db.insertTableContent(project_name, obj2, (succ, msg) => {
		// succ - boolean, tells if the call is successful
		console.log("Success: " + succ);
		console.log("Message: " + msg);
	});
    }, 500);*/

	//add project row in a project database
	db.insertTableContent('project', obj, (succ, msg) => {
		console.log("Success: " + succ);
        console.log("Message: " + msg);
    });
setTimeout(function(){
      	loadProjectNamesIntoSelect();
        disableDeleteProjectBtn();
}, 1000);
}


function disableDeleteProjectBtn()
{
    db.getAll('project', function (succ, data){
        var count = data.length;
        console.log(count);
        if(count <= 0){
            $('#deleteProjectBtn').prop("disabled", true);
        } else {
            $('#deleteProjectBtn').prop("disabled", false);
        }
    })
}



$(document).ready(function()
{
	includeHTML();
	setTimeout(function(){
		var newProjectModal = $('#newProjectModal');
		var newProjectBtn = $('#newProjectBtn');

		var delectProjectModal = $('#deleteProjectModal');
		var deleteProjectBtn = $('#deleteProjectBtn');

		var renameProjectModal = $('#renameProjectModal');
		var renameProjectBtn = $('#renameProjectBtn');

		var addComponentBtn = $('#add-component');
		var newComponentModal = $('#newComponentModal');

		var accountDataBtn = $('#AccountDataBtn');
		var accountDataModal = $('#AccountDataModal');

		renderProjectsFromElectron();
		loadProjectNamesIntoSelect();
        disableDeleteProjectBtn();

		newProjectBtn.click(function(){

			newProjectModal.modal('show');
			document.getElementById('create_project_name').value = '';
		});

		newProjectModal.delegate('.save-project', 'click', function(){
			var project_name = newProjectModal.find('[name="project_name"]').val();
			if(project_name.length == 0) {
				alert('Please enter the project name');
			} 
	        else if (/^[A-Za-z0-9_]+$/.test(project_name)==false)
		    {
				alert('please enter name start with letter and consists of letters ,numbers and underscores only ');
			}
	        else if (/^[A-Za-z]+$/.test(project_name[0])==false)
			{
				alert('please enter name start with letter');
			}
			else if ($('.wapper_projects .row div[data-project-name="'+ project_name +'"]').length)
			{
				alert('Please enter unique project name');
			}
			else {
				newProjectModal.modal('hide');
				addProjectToProjectDatabase(project_name);
				addProjectToList(project_name);
				setTimeout(function(){
					loadProjectNamesIntoSelect();
					disableDeleteProjectBtn();
				}, 500);
				
			}
		});

		addComponentBtn.click(function(){
			newComponentModal.modal('show');
		});

		deleteProjectBtn.click(function(){
			delectProjectModal.modal('show');
		});

		renameProjectBtn.click(function(){
			renameProjectModal.modal('show');
		});

		accountDataBtn.click(function(){
			accountDataModal.modal('show');
		});

		// submit button of delete modal
		$('#deleteProjectModal').delegate('.delete_project', 'click', function(){
			setTimeout(function(){
				deleteProjectFromElectron();
			}, 50);
		});

		// submit button of rename modal
		$('#deleteProjectModal').delegate('.rename_project', 'click', function(){
			renameProjectFromElectron();
		});

		$('.wapper_projects .row').on("click", "div", function(){
			// create a special database for the project
			// get current project name when click on it
			sessionName = $(this).find('.current-p-name').text();
			var queryString = "?" + sessionName;
			window.location.href = 'dataFlow.html' + queryString;
		});
	}, 500);


});