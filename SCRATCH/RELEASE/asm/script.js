/**
 * @class       : script
 * @author      : alex (alex@mac.local)
 * @created     : Marţi Oct 18, 2022 19:31:51 EEST
 * @description : script
 */


// alert("hello");
let age = prompt('How old are you?', 100);

alert(`You are ${age} years old!`); 

const data = {name: 'Ronn', age: 27};              //sample json
const a = document.createElement('a');
const blob = new Blob([JSON.stringify(data)]);
a.href = URL.createObjectURL(blob);
a.download = 'sample-profile';                     //filename to download
a.click();

const fs = require('fs').promises;
fs.writeFile('y.txt', "csvLine");

const { exec } = require('child_process');
function large (){
exec('./html');}
//   if (err) {
//     // node couldn't execute the command
//     return;
//   }

//   // the *entire* stdout and stderr (buffered)
//   alert(`${stdout}`);

