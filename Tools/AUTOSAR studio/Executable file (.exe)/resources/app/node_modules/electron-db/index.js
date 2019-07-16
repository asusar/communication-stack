// Load required modules
const jsonfile = require('jsonfile');
// const electron = require('electron');
const path = require('path');
const fs = require('fs');
const os = require('os');

// const app = electron.app || electron.remote.app;
// const userData = app.getPath('userData');

const platform = os.platform();

let appName = '';
if (JSON.parse(fs.readFileSync('package.json', 'utf-8')).productName) {
  appName = JSON.parse(fs.readFileSync('package.json', 'utf-8')).productName;
}else{
  appName = JSON.parse(fs.readFileSync('package.json', 'utf-8')).name;
}

let userData = '';

if (platform === 'win32') {
  userData = path.join(process.env.APPDATA, appName);
} else if (platform === 'darwin') {
  userData = path.join(process.env.HOME, 'Library', 'Application Support', appName);
} else {
  userData = path.join('var', 'local', appName);
}

/**
 * Create a table | a json file
 * @param  {[string]} tableName [Table name]
 */
function createTable(tableName, callback) {
  // Define the filename
  let fname = path.join(userData, tableName + '.json');

  // Check if the file with the tablename.json exists
  let exists = fs.existsSync(fname);

  if (exists) {
    // The file exists, do not recreate the table/json file
    callback(false, tableName + '.json already exists!');
    return;
  } else {
    // Create an empty object and pass an empty array as value
    let obj = new Object();
    obj[tableName] = [];

    // Write the object to json file
    try {
      jsonfile.writeFile(fname, obj, {spaces: 2}, function (err){
        // console.log(err);
      });
      callback(true, "Success!");
      return;
    } catch (e) {
      callback(false, e.toString());
    }

  }
}


/**
 * Insert object to table. The object will be appended with the property, id
 * which uses timestamp as value.
 * @param  {string} tableName  [Table name]
 * @param  {string} tableField [Field name]
 * @param  {value} fieldValue [Value (string, number, list, etc.)]
 * @param {Function} callback [Callback function]
 */
function insertTableContent(tableName, tableRow, callback) {
  let fname = path.join(userData, tableName + '.json');
  let exists = fs.existsSync(fname);

  if (exists) {
    // Table | json parsed
    let table = JSON.parse(fs.readFileSync(fname));

    let date = new Date();
    let id = date.getTime();
    tableRow['id'] = id;

    table[tableName].push(tableRow);

    try {
      jsonfile.writeFile(fname, table, {spaces: 2}, function (err){
        console.log(err);
      });
      callback(true, "Object written successfully!");
      return;
    } catch (e) {
      callback(false, "Error writing object.");
      return;
    }
  }
  callback(false, "Table/json file doesn't exist!");
  return;

}

function insertTableContents(tableName, tableRows, callback) {
  let fname = path.join(userData, tableName + '.json');
  let exists = fs.existsSync(fname);

  if (exists) {
    if (tableRows.length === 0) {
      callback(false, "Empty array of rows. Please provide minimum of one record (object).");
      return ;
    } else {
      // Delay function
      function delay() {
        return new Promise(resolve => setTimeout(resolve, 10));
      }

      // Async function
      async function delayedAction(item) {
        await delay();

        // Insert the data/object
        // Table | json parsed
        let table = JSON.parse(fs.readFileSync(fname));

        let date = new Date();
        let id = date.getTime();
        item['id'] = id;

        table[tableName].push(item);
        try {
          jsonfile.writeFile(fname, table, {spaces: 2}, function (err){
            //console.log(err);
          });
          callback(true, "Object written successfully!");
          return;
        } catch (e) {
          callback(false, "Error writing object.");
          return;
        }
      }

      async function insertData(rows) {
        for (const row of rows) {
          await delayedAction(row);
        }
      }

      insertData(tableRows);
    }
  } else {
    callback(false, "Table/json file doesn't exist!");
    return;
  }
}

/**
 * Get all contents of the table/json file object
 * @param  {[string]}   tableName [Table name]
 * @param  {Function} callback  [callback]
 */
function getAll(tableName, callback) {
  let fname = path.join(userData, tableName + '.json');
  let exists = fs.existsSync(fname);

  if (exists) {
    try {
      let table = JSON.parse(fs.readFileSync(fname));
      callback(true, table[tableName]);
      return;
    } catch (e) {
      callback(false, []);
      return;
    }
  } else {
    callback(false, []);
    return;
  }
}

/**
 * Get row or rows that matched the given condition(s) in WHERE argument
 * @param {string} tableName Table name
 * @param {object} where Collection of conditions to be met
 * @param {callback} callback Function callback
 */
function getRows(tableName, where, callback) {
  let fname = path.join(userData, tableName + '.json');
  let exists = fs.existsSync(fname);
  let whereKeys;

  // Check if where is an object
  if (Object.prototype.toString.call(where) === "[object Object]" ) {
    // Check for number of keys
    whereKeys = Object.keys(where);
    if (whereKeys === 0) {
      callback(false, "There are no conditions passed to the WHERE clause.");
      return;
    }
  } else {
    callback(false, "WHERE clause should be an object.");
    return;
  }

  // Check if the json file exists, if it is, parse it.
  if (exists) {
    try {
      let table = JSON.parse(fs.readFileSync(fname));
      let rows = table[tableName];

      let objs = [];

      for (let i = 0; i < rows.length; i++) {
        let matched = 0;    // Number of matched complete where clause
        for (var j = 0; j < whereKeys.length; j++) {
          // Test if there is a matched key with where clause
          if (rows[i].hasOwnProperty(whereKeys[j])) {
            if (rows[i][whereKeys[j]] === where[whereKeys[j]]) {
              matched++;
            }
          }
        }

        // Check if all conditions in the WHERE clause are matched
        if (matched === whereKeys.length) {
          objs.push(rows[i])
        }
      }

      callback(true, objs);
      return;
    }catch (e) {
      callback(false, e.toString());
      return;
    }
  } else {
    callback(false, "JSON file does not exist.");
    return;
  }
}

/**
 * Update a row or record which satisfies the where clause
 * @param  {[string]}   tableName [Table name]
 * @param  {[object]}   where     [Objet for WHERE clause]
 * @param  {[object]}   set       [Object for SET clause]
 * @param  {Function} callback  [Callback function]
 */
function updateRow(tableName, where, set, callback) {
  let fname = path.join(userData, tableName + '.json');
  let exists = fs.existsSync(fname);

  let whereKeys = Object.keys(where);
  let setKeys = Object.keys(set);

  if (exists) {
    let table = JSON.parse(fs.readFileSync(fname));
    let rows = table[tableName];

    for (var i = 0; i < rows.length; i++) {
      let matched = 0;    // Number of matched complete where clause
      for (var j = 0; j < whereKeys.length; j++) {
        // Test if there is a matched key with where clause and single row of table
        if (rows[i].hasOwnProperty(whereKeys[j])) {
          if (rows[i][whereKeys[j]] === where[whereKeys]) {
            matched++;
          }
        }
      }

      if (matched === whereKeys.length) {
        // All field from where clause are present in this particular
        // row of the database table
        try {
          for (var k = 0; k < setKeys.length; k++) {
            rows[i][setKeys[k]] = set[setKeys[k]];
          }

          // Create a new object and pass the rows
          let obj = new Object();
          obj[tableName] = rows;

          // Write the object to json file
          try {
            jsonfile.writeFile(fname, obj, {spaces: 2}, function (err){
              console.log(err);
            });
            callback(true, "Success!")
            return;
          } catch (e) {
            callback(false, e.toString());
            return;
          }

          callback(true, rows);
        } catch (e) {
          callback(false, e.toString());
          return;
        }
      } else {
        callback(false, "Cannot find the specified record.");
        return;
      }

    }
  } else {
    callback(false, "JSON file does not exist.");
    return;
  }
}

/**
 *
 * @param {*} tableName Name of the table to search for
 * @param {*} field Name of the column/key to match
 * @param {*} keyword The part of the value of the key that is being lookup
 * @param {*} callback Callback function
 */
function search(tableName, field, keyword, callback) {
  let fname = path.join(userData, tableName + '.json');
  let exists = fs.existsSync(fname);

  if (exists) {
    let table = JSON.parse(fs.readFileSync(fname));
    let rows = table[tableName];

    if (rows.length > 0) {

      // Declare an empty list
      let foundRows = [];

      for (var i = 0; i < rows.length; i++) {
        // Check if key exists
        if (rows[i].hasOwnProperty(field)) {
          // Get the index of the search term
          let value = rows[i][field].toLowerCase();
          let n = value.search(keyword.toLowerCase());

          if (n !== -1) {
            // The substring is found, add object to the list.
            foundRows.push(rows[i]);
          }

        }else{
          callback(false, 2);
          return;
        }
      }

      callback(true, foundRows);
      return;

    } else {
      callback(false, 1);
      return;
    }
  } else {
    callback(false, 0);
    return;
  }
}

function deleteRow(tableName, where, callback) {
  let fname = path.join(userData, tableName + '.json');
  let exists = fs.existsSync(fname);

  let whereKeys = Object.keys(where);

  if (exists) {
    let table = JSON.parse(fs.readFileSync(fname));
    let rows = table[tableName];

    if (rows.length > 0) {
      for (let i = 0; i < rows.length; i++) {
        // Iterate throught the rows
        let matched = 0;
        let matchedIndices = [];

        for (var j = 0; j < whereKeys.length; j++) {
          // Test if there is a matched key with where clause and single row of table
          if (rows[i].hasOwnProperty(whereKeys[j])) {
            if (rows[i][whereKeys[j]] === where[whereKeys]) {
              matched++;
              matchedIndices.push(i);
            }
          }
        }

        for (let i = 0; i < matchedIndices.length; i++) {
          rows.splice(matchedIndices[i], 1);
        }

      }

      // Create a new object and pass the rows
      let obj = new Object();
      obj[tableName] = rows;

      // Write the object to json file
      try {
        jsonfile.writeFile(fname, obj, {spaces: 2}, function (err){

        });
        callback(true, "Row(s) deleted successfully!")
        return;
      } catch (e) {
        callback(false, e.toString());
        return;
      }

    } else {
      callback(false, 'Table is empty!');
      return;
    }
  } else {
    callback(false, "JSON file does not exist.");
    return;
  }

}

// Export the public available functions
module.exports = {
  createTable,
  insertTableContent,
  insertTableContents,
  getAll,
  getRows,
  updateRow,
  search,
  deleteRow
};
