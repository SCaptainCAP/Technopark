'use strict';

const http = require('http');
const fs = require('fs');

const server = http.createServer(function(req, resp){

    const url = req.url;
    console.log(url);

    const text = fs.readFileSync('./static/index.html', 'utf8');
    resp.write(text);
    resp.end();
});

const PORT = process.env.PORT || 3000;


server.listen(PORT);
console.log(PORT);