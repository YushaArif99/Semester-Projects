// var fs = require("browserify-fs");

// function saveTestCase(data, name) {
//   fs.mkdir("desktop", function () {
//     fs.writeFile(`desktop/${name}`, data, function () {
//       fs.readFile(`desktop/${name}`, "utf-8", function (err, data) {
//         console.log(data);
//       });
//     });
//   });
// }

const saveTestCase = (content, filename, contentType) => {
  const a = document.createElement("a");
  const file = new Blob([content], { type: contentType });

  a.href = URL.createObjectURL(file);
  a.download = filename;
  a.click();

  URL.revokeObjectURL(a.href);
};

export default saveTestCase;
