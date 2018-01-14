const util = require('util');
var net = require('net');
var ws = require('nodejs-websocket');

const socketPath = '/tmp/ipc-test';

var unixSocket = net.createConnection(socketPath, function(){
	console.log('webserver.js connected to Unix socket');
	unixSocket.write('HELLO!');
});
unixSocket.on('data', function(data){
	data = data.toString();
	broadcast(webSocketServer, data);
});

var webSocketServer = ws.createServer(function (conn) {
	console.log('webserver.js New websocket connection');
	broadcast(webSocketServer, JSON.stringify(conn));
	//console.log(util.inspect(conn, false, null))

	conn.on('text', function (data) {
		data = JSON.parse(data);
		broadcast(webSocketServer, JSON.stringify({'message': 'hello broadcast'}));
	});

	conn.on('end', function (code, reason) {
		console.log('Client disconnected (' + reason + ')');
	});

	process.on('uncaughtException', function (err) {
		console.error(err.stack);
		console.log("Node NOT Exiting...");
	});

}).listen(8001);

function broadcast(webSocketServer, msg) {
	webSocketServer.connections.forEach(function (conn) {
		conn.sendText(msg);
	});
}