const https = require('https');
const fs = require('fs');

const options = {
    key : fs.readFileSync('key.pem'),
    cert : fs.readFileSync('cert.pem')
};

console.log('Started on localhost:443!');
https
    .createServer(options,
                  function(req, res) {
                      res.writeHead(200);
                      res.end(fs.readFileSync('index.html').toString());

                      let now = new Date();
                      console.log(`[${now.getHours()}:${now.getMinutes()}] ${req.headers['user-agent']}`);
                  })
    .listen(443, 'localhost');
