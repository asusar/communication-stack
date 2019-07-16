const electron = require("electron")
const app = electron.app|| electron.remote.app
const BrowserWindow = electron.BrowserWindow
const path = require('path')
const url = require('url')

// Database
const db = require('electron-db');
db.createTable('project', (succ, msg) => {
            // succ - boolean, tells if the call is successful
  console.log("Success: " + succ);
  console.log("Message: " + msg);
})

let win;

function createWindow () {
  win = new BrowserWindow({width: 1200, height: 800, icon: path.join(__dirname, '../images/smallLogo.png')})
  //win.maximize();
  win.loadURL(url.format({
    pathname: path.join(__dirname, '../index.html'),
    protocol: 'file:',
    slashes: true,
    webPreferences: {
    	nodeIntegration: false,
    }
  }));
  win.on('closed', () => {
    win = null
  });
}

app.on('ready', createWindow);

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  if (win === null) {
    createWindow();
  }
});