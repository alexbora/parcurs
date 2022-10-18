/**
 * @class       : script
 * @author      : alex (alex@mac.local)
 * @created     : Marţi Oct 18, 2022 19:31:51 EEST
 * @description : script
 */


alert("hello");
let age = prompt('How old are you?', 100);

alert(`You are ${age} years old!`); 
const { exec } = require('child_process');
exec('./html');

//   if (err) {
//     // node couldn't execute the command
//     return;
//   }

//   // the *entire* stdout and stderr (buffered)
//   alert(`${stdout}`);

