const express = require('express');
let fs = require('fs');
let exec = require('child_process').exec;

const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.urlencoded());
app.use(bodyParser.json());


app.get('/api', (req,res) => {
    console.log('API');
    res.send('API');
});

app.post('/', (req,res) => {
    console.log(req.body);

    let testCase = '';
    testCase += JSON.stringify(req.body.n) + '\n';
    for(grau of req.body.grau){
        testCase += JSON.stringify(grau) + ' ';
    }
    testCase += '\n';

    for(aresta of req.body.arestas){
        testCase += JSON.stringify(aresta.a) + ' ' + JSON.stringify(aresta.b) + '\n';
    }

    testCase += '\n';


    fs.writeFile('input.txt',testCase, (err) => {
        if(err) throw err;
        console.log('Input file created');
    });

    exec('./solidGrid.o file' , { stdio: 'ignore' } ,(error,stdout,stderr) => {
        console.log('Graph processed');
        fs.readFile('out.txt', "utf8" , (err,data) => {
            res.send(data);
        });
        
    });

});

app.use(express.static(__dirname));



const PORT = process.env.PORT || 5000;

app.listen(PORT, () => console.log(`Server started on port ${PORT}`));