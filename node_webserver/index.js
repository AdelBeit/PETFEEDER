var http = require('http');
var url = require('url');


// create a server object:
http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/html'}); // display html content, send as header
  var q = url.parse(req.url, true).query;
  var txt = q.year + " " + q.month;
  res.write("Node server is online! <br>"); // write response to the client
  res.write(req.url +"<br>");
  res.end(txt); // end the response
}).listen(1337); // the server object listens on port 1337