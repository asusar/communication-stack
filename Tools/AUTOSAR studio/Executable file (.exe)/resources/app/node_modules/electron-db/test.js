const db = require('./index');

db.getAll('test', (succ, data) => {
  if (succ) {
    console.log(data);
  } else {
    console.log('The table test does not exist!');
  }
});