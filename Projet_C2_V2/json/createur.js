function getRandomIntInclusive(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min +1)) + min;
}

var fs = require('fs');

var courreurs = {}
courreurs.table = []
for (i=0; i <200 ; i++){
   var obj = {
   	   nom: "Jack",
       dossard: i,
       masse: getRandomIntInclusive(45,120),
       taille: getRandomIntInclusive(130,200),
       chaussure: getRandomIntInclusive(100,300),
       vmoyenne:  getRandomIntInclusive(7,20),
       sprep:  getRandomIntInclusive(8,16)
   }
   courreurs.table.push(obj)
}
fs.writeFile ("coureurs.json", JSON.stringify(courreurs), function(err) {
    if (err) throw err;
    console.log('complete');
    }
);