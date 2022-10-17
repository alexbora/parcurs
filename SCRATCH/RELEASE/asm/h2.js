/**
 * @class       : h2
 * @author      : alex (alex@mac.local)
 * @created     : Luni Oct 17, 2022 15:58:36 EEST
 * @description : h2
 */



const execSync = require('child_process').execSync;
// import { execSync } from 'child_process';  // replace ^ if using ES modules

const output = execSync('./gtk4', { encoding: 'utf-8' });  // the default is 'buffer'
console.log('Output was:\n', output);
