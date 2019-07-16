/**
 * Copyright (C) 1998-2018 by Northwoods Software Corporation
 * All Rights Reserved.
 *
 * Go Cloud Storage Manager
*/

import * as go from "../../release/go";
import * as gcs from "./GoCloudStorage";
import * as GoGoogleDrive from "./GoGoogleDrive";
import {Promise} from "es6-promise";

/**
 * Class for easily saving / loading <a href="https://gojs.net/latest/api/symbols/Diagram.html">Diagram</a>
 * <a href="https://gojs.net/latest/api/symbols/Model.html">models</a> to / from a user-defined set of Cloud  Storage Services with a pre-defined UI.
 * <p>GoCloudStorageManager holds a set of {@link GoCloudStorage} subclass instances ({@link storages}) to manage. When one is selected from the
 * storage selection {@link menu}, it becomes the {@link currentStorage} property, which is used to save / load / delete / create files.</p>
 * @category Storage
 */
export class GoCloudStorageManager {

    private _storages: go.Set<gcs.GoCloudStorage>
    private _currentStorage: gcs.GoCloudStorage
    private _menu: HTMLElement;
    private _deferredPromise: gcs.DeferredPromise;
    private _iconsRelativeDirectory: string;

    /**
     * @constructor
     * @param {go.Set<gcs.GoCloudStorage>} storages Contains valid instances of {@link GoCloudStorage} subclasses. Use at most one instance of each subclass.
     * @param {string} iconsRelativeDirectory The directory path relative to the page in which this instance of GoCloudStorageManager exists, in which
     * the storage service brand icons can be found. The default value is "../goCloudStorageIcons/".
     * <strong>Note:</strong> If this parameter is supplied, it is used as for the "iconsRelativeDirectory" constructor parameter for each instance
     * this instance of GoCloudStorageManager manages in {@link storages}.
     */
    constructor(storages: go.Set<gcs.GoCloudStorage>|gcs.GoCloudStorage[], iconsRelativeDirectory?: string) {
        if (storages instanceof Array) {
            let storagesSet = new go.Set<gcs.GoCloudStorage>();
            for (var i = 0; i < storages.length; i++) {
                if (!(storages[i] instanceof gcs.GoCloudStorage)) {
                    throw Error("Cannot create GoCloudStorageManager; provided 'storages' parameter elements are not all of type GoCloudStorage");
                } else {
                    storagesSet.add(storages[i]);
                }
            }
            storages = storagesSet;
        }
        if (!(storages instanceof go.Set) || !storages) throw Error ("Cannot create GoCloudStorageManager with provided 'storages' parameter");
        const storageManager = this;
        storageManager._storages = storages;
        storageManager._currentStorage = storages.first();
        var menu = document.createElement('div');
        menu.id = 'goCloudStorageManagerMenu';
        storageManager._menu = menu;
        storageManager._deferredPromise = { promise: gcs.GoCloudStorage.prototype.makeDeferredPromise() };
        storageManager._iconsRelativeDirectory = (!!iconsRelativeDirectory) ? iconsRelativeDirectory : "../goCloudStorageIcons/";
        if (iconsRelativeDirectory) {
            storageManager._storages.iterator.each(function(storage){
                storage.iconsRelativeDirectory = iconsRelativeDirectory;
            });
        }
        // if href includes a certain string, we just authenticated DropBox, so use GoDropBox as "currentStorage"
        if (window.location.href.indexOf("account_id=dbid") !== -1) {
            storages.iterator.each(function(storage){
                if (storage.className === "GoDropBox") {
                    storageManager._currentStorage = storage;
                    // this will force a load of the diagram data that existed before the Dropbox auth flow
                    //setTimeout( function () {
                    //    alert("REE");
                        storageManager.currentStorage.authorize(); 
                    //},
                    //100);
                }
            });
        }
    }

    /**
     * Get storages ({@link GoCloudStorage} subclass instances) managed by an instance of GoCloudStorageManager. At most, there should be only one instance of each subclass.
     * This is set with a parameter during construction.
     * @function.
     * @return {go.Set<gcs.GoCloudStorage>}
     */
    get storages(): go.Set<gcs.GoCloudStorage> { return this._storages }

    /**
     * Get / set iconsRelativeDirectory, the directory path relative to the page in which this instance of GoCloudStorageManager exists, in which
     * the storage service brand icons can be found. The default value is "../goCloudStorageIcons/".
     * @function.
     * @return {string}
     */
    get iconsRelativeDirectory(): string { return this._iconsRelativeDirectory }
    set iconsRelativeDirectory(value: string) { this._iconsRelativeDirectory = value }

    /**
     * Get GoCloudStorageManager menu, from which a user chooses which storage service for this instance of GoCloudStorageManager to actively manage (see {@link currentStorage}).
     * This is created (as a blank div) during construction. Its contents are populated during {@link selectStorageService}.
     * @function.
     * @return {HTMLElement}
     */
    get menu(): HTMLElement { return this._menu }

    /**
     * Get / set the {@link GoCloudStorage} subclass this instance of GoCloudStorageManager is actively managing.
     * @function.
     * @return {gcs.GoCloudStorage}
     */
    get currentStorage() { return this._currentStorage }
    set currentStorage(value: gcs.GoCloudStorage) { this._currentStorage = value }

    /**
     * Creates a new diagram with {@link currentStorage}'s default model data (see {@link GoCloudStorage.defaultModel}.
     * If currentStorage.isAutoSaving is true, prompt to save it to to currentStorage's storage service.
     * if {@link currentStorage}'s {@link GoCloudStorage.isAutoSaving} is true).
     * @return {Promise} Returns a Promise that resolves a {@link DiagramFile} representing the newly created file (if file was saved).
     */
    public create() {
        const storageManager = this;
        return new Promise(function(resolve: Function, reject: Function){
            resolve(storageManager.handleAction("Create"));
        });
    }

    /**
     * Launches the load interface for {@link currentStorage}.
     * @return {Promise} Returns a Promise that resolves with a {@link DiagramFile} representing the loaded file.
     */
    public load() {
        const storageManager = this;
        return new Promise(function (resolve: Function, reject: Function) {
            resolve(storageManager.handleAction("Load"));
        });
    }

    /**
     * Launches the remove interface for {@link currentStorage}.
     * @return {Promise} Returns a Promise that resolves with a {@link DiagramFile} representing the deleted file.
     */
    public remove() {
        const storageManager = this;
        return new Promise(function (resolve: Function, reject: Function) {
            resolve(storageManager.handleAction("Remove"));
        });
    }

    /**
     * Either launches the save interface for {@link currentStorage} or just saves the {@link GoCloudStorage.managedDiagrams}' model data  to
     * storage at the path supplied in currentStorage's {@link GoCloudStorage.currentDiagramFile}.path value, depending on a parameter.
     * @param {boolean} isSaveAs If true, show the save interface for currentStorage. If false, save currentStorage's managedDiagrams' model data to storage.
     * Default value is true.
     * @return {Promise} Returns a Promise that resolves with a {@link DiagramFile} representing the saved file.
     */
    public save(isSaveAs: boolean = true) {
        const storageManager = this;
        return new Promise(function (resolve: Function, reject: Function) {
            if (isSaveAs) resolve(storageManager.handleAction("SaveAs"));
            else resolve(storageManager.handleAction("Save"));
        });
    }

    /**
     * Display a message on the screen for a given number of seconds. Can be used for a variety of purposes, but a common one is to
     * notify users when a file has been loaded / saved / deleted / created by handling the {@link DiagramFile} argument in the
     * "then" function of returned Promises (from functions {@link load}, {@link create}, {@link save},
     * {@link remove}) by displaying it as a message.
     * @param msg Message to display
     * @param seconds Number of seconds to display the message for. If no value is provided, the message will display for two seconds.
     */
    public showMessage(msg: string, seconds?: number) {
        if (!seconds) seconds = 2;
        let messageBox = document.createElement("div");
        messageBox.id = "goCloudStorageManagerMessageBox";
        messageBox.innerHTML = "<p>" + msg + "</p>";
        document.body.appendChild(messageBox);
        setTimeout(function() {
            messageBox.style.opacity = '0';
            setTimeout(function() {messageBox.parentNode.removeChild(messageBox)}, 1000);
        }, 1000*seconds);
    }

    /**
     * Get the path to the icon for a given {@link GoCloudStorage.className}
     * @param className 
    */
    public getStorageIconPath(className: string) {
        var storageManager = this;
        if (storageManager.iconsRelativeDirectory == null || storageManager.iconsRelativeDirectory == undefined) return null;
        var src: string = storageManager.iconsRelativeDirectory;
        switch (className) {
            case 'GoGoogleDrive': {
                src += 'googleDrive.jpg'; 
                break;
            }
            case 'GoOneDrive': {
                src += 'oneDrive.png'; 
                break;
            }
            case 'GoLocalStorage': {
                src += 'localStorage.png'; 
                break;
            }
            case 'GoDropBox': {
                src += 'dropBox.png'; 
                break;
            }
        } 
        return src;
    }

    /**
     * Display options ({@link storages}) supported by this instance of GoCloudStorageManager.
     * Sets {@link currentStorage} to user's choice.
     * @return {Promise} Returns a Promise that resolves with the new {@link currentStorage} instance
     */
    public selectStorageService() {
        const storageManager = this;
        const storages = this.storages;

        return new Promise(function(resolve: Function, reject: Function){
            const menu = storageManager.menu;
            let title: string = 'Select Storage Service';
            menu.innerHTML = "<strong>" + title + "</strong><hr></hr>";

            let selectedStorage: HTMLElement = document.createElement("p");
            selectedStorage.id = "gcsmSelectedStorage"; // Go Cloud Storage Manager selected storage
            selectedStorage.innerHTML = storageManager.currentStorage.serviceName;
            menu.appendChild(selectedStorage);

            // display the name of the currently selected radio button's storage service
            menu.onchange = function () {
                let radios: NodeListOf<HTMLInputElement> = <NodeListOf<HTMLInputElement>>document.getElementsByName('storageSelection');
                let selectedStorageClassName: string = null;
                for (let i = 0; i < radios.length; i++) {
                    if (radios[i].checked) {
                        selectedStorageClassName = radios[i].id;
                    }
                }
                let serviceNameStr: string = "";
                storages.iterator.each(function(s){
                    if (s.className == selectedStorageClassName) {
                        serviceNameStr = s.serviceName;
                    }
                });
                document.getElementById("gcsmSelectedStorage").innerHTML = serviceNameStr;
            }

            document.getElementsByTagName('body')[0].appendChild(storageManager.menu);
            storageManager.menu.style.visibility = 'visible';
            let optionsDiv: HTMLElement = document.createElement('div');
            optionsDiv.id = 'storageOptions';

            let it = storages.iterator;
            it.each(function(storage) {
                // create a radio input box for each service managed by this instace of GoCloudStorageManager
                let type: string = storage.className;
                let src: string = storageManager.getStorageIconPath(type);
                let isChecked: boolean = storage.className == storageManager.currentStorage.className;
                let checkedStr: string = "";
                if (isChecked) checkedStr = "checked";

                optionsDiv.innerHTML +=
                    "<label>" +
                        "<input id=" + type + " type='radio' name='storageSelection' " + checkedStr + " />" +
                        "<img class='storageLogo' src=" + src + " >";
            });

            menu.appendChild(optionsDiv);

            let description: string = 'This will be where you save / load diagram model data to / from. You will need to grant GoCloudStorage permission to access your files on the selected storage service.'
            menu.innerHTML += "<p class='description'>" + description + "</p>";

            let submitDiv: HTMLElement = document.createElement('div');
            let actionButton = document.createElement("button");
            actionButton.id = "actionButton";
            actionButton.textContent = "Select";
            actionButton.onclick = function() {
                // set currentStorage
                let radios: NodeListOf<HTMLInputElement> = <NodeListOf<HTMLInputElement>>document.getElementsByName('storageSelection');
                let selectedStorage: string = null;
                for (let i = 0; i < radios.length; i++) {
                    if (radios[i].checked) {
                        selectedStorage = radios[i].id;
                    }
                }
                storageManager.storages.each(function(storage){
                    if (storage.className == selectedStorage) storageManager.currentStorage = storage;
                });
                if (storageManager.currentStorageNeedsAuth()) {
                    storageManager.currentStorage.authorize().then(function (resp) {
                        /*if (storageManager.currentStorage.className == "GoDropBox") {
                            storageManager.currentStorage.authorize(); // forces GoDropBox to load previous app state (before the auth flow redirects)
                        }*/
                    });
                }
                resolve(storageManager.currentStorage);
                storageManager.hideMenu();
            }
            submitDiv.appendChild(actionButton);
            menu.appendChild(submitDiv);

            let cancelDiv: HTMLElement = document.createElement('div');
            let cancelButton = document.createElement("button");
            cancelButton.id = "cancelButton";
            cancelButton.textContent = "Cancel";
            cancelButton.onclick = function() {
                storageManager.hideMenu();
            }
            cancelDiv.appendChild(cancelButton);
            menu.appendChild(cancelDiv);
        });

    }

    /**
     * Hide the storage selection {@link menu}
     */
    public hideMenu() {
        const storageManager = this;
        storageManager.menu.style.visibility = 'hidden';
    }

    /**
     * @private
     * Some classes need to be explicitly authorized (get a user-specific auth token) for use with GoCloudStorageManager. Some do not.
     * This function simply examines the currently active storage and determines whether or not this explicit authorization is needed.
     * @return {boolean}
     */
    private currentStorageNeedsAuth() {
        const storageManager = this;
        let currentStorageClass: string = storageManager.currentStorage.className;
        if (currentStorageClass ===  "GoGoogleDrive" || currentStorageClass === "GoDropBox") return true;
        return false;
    }

    /**
     * Handle an action with the current {@link currentStorage}. Possible values for <code>action</code> can be:
     * <code>
     *  <ul>
     *      <li>Load</li>
     *      <li>Save</li>
     *      <li>Save As</li>
     *      <li>Create</li>
     *      <li>Remove</li>
     *  </ul>
     * </code>
     * @param action
     */
    public handleAction(action: string) {
        const storageManager = this;
        let storage: gcs.GoCloudStorage = storageManager.currentStorage;
        return new Promise(function(resolve: Function, reject: Function){
            function doAction() {
                switch(action) {
                    case "Load": {
                        resolve(storage.loadWithUI());
                        break;
                    }
                    case "SaveAs": {
                        resolve(storage.saveWithUI());
                        break;
                    }
                    case "Save": {
                        resolve(storage.save());
                        break;
                    }
                    case "Remove": {
                        resolve(storage.removeWithUI());
                        break;
                    }
                    case "Create": {
                        resolve(storage.create());
                        break;
                    }
                }
                storageManager.hideMenu();
            }
            if (storageManager.currentStorageNeedsAuth()) storage.authorize().then(function() {
                doAction();
            }); else doAction();
        });
    }
}