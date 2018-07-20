var http = require('http');

// create a server object:
http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/html'}); // display html content, send as header
  res.write('Node server is online!'); // write response to the client
  res.end(); // end the response
}).listen(1337); // the server object listens on port 1337