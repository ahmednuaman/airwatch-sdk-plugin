/*
 Based on https://github.com/Microsoft/cordova-docs/blob/master/articles/tips-and-workarounds/ios/ios-plugin-symlink-fix/hook-symlink-fix.js , to which the following declaration applies:
 Copyright (c) Microsoft. All rights reserved.
 Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */
var fs = require("fs");
var path = require("path");
var Q;
var glob;

module.exports = function(context) {

    var makeLink = function(basedir, target, link) {

        // Change dir to link location
        var startDir = process.cwd();
        process.chdir(basedir);

        // Create symlink, if possible
        if (!fs.existsSync(target)) {
            console.log("Link target does not exist: " + target);
        } else if (fs.existsSync(link)) {
            console.log("Symlink already exists: " + link);
        } else {
            fs.symlinkSync(target, link);
        }

        // Restore directory
        process.chdir(startDir);
    };

    // Grab the Q, glob node modules from cordova
    Q = context.requireCordovaModule("q");
    glob = context.requireCordovaModule("glob");

    // Need to return a promise since glob is async
    var deferred = Q.defer();

    // Find all custom framework files within plugin source code for the iOS platform
    glob("plugins/**/AWSDK.framework", function(err, awFrameworks) {
        if (err) {
            deferred.reject(err);
        } else {
            awFrameworks.forEach(function(fwk) {
                fwk = path.join(context.opts.projectRoot, fwk);
                makeLink(path.join(fwk, "Versions"), "A", "Current");
                makeLink(fwk, "Versions/Current/Headers", "Headers");
                makeLink(fwk, "Versions/Current/AWSDK", "AWSDK");
                makeLink(fwk, "Versions/Current/AWKit.bundle", "AWKit.bundle");
            });
            deferred.resolve();
        }
    });
    
    return deferred.promise;
}

