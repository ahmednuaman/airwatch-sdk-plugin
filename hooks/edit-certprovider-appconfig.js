#!/usr/bin/env node

module.exports = function(context) {

    if (context.opts.plugins != undefined
       && context.opts.plugins.indexOf("com.airwatch.awfioriplugin") == -1)
        return;

    console.log('********** modify AppConfig.js ********');

    /** @external */
    var fs = context.requireCordovaModule('fs'),
    path = context.requireCordovaModule('path'),
    shell = context.requireCordovaModule('shelljs');

    // put certificate name in
    shell.sed('-i', /"certificate": ""/, '"certificate": "com.airwatch.x509provider"',
                    path.join(context.opts.projectRoot, 'www', 'appConfig.js'));

    console.log('********** modified AppConfig.js ********');

};
