function TestCase68() {
  let n = Math.floor(Math.random() * (100 - 10)) + 10;
  let values = "";
  let weigths = "";
  let intValues = [];
  let intWeights = [];

  while (n > 0) {
    let v = Math.floor(Math.random() * (100 - 1)) + 1;
    let w = Math.floor(Math.random() * (100 - 1)) + 1;
    values += v.toString() + " ";
    weigths += w.toString() + " ";
    intValues.push(v);
    intWeights.push(w);
    n--;
  }

  let collc = [values, intValues, weigths, intWeights];
  return collc;
}

export default TestCase68;
