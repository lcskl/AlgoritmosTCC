const express = require('express');
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
    res.send('POST response');
});

app.use(express.static(__dirname));



const PORT = process.env.PORT || 5000;

app.listen(PORT, () => console.log(`Server started on port ${PORT}`));