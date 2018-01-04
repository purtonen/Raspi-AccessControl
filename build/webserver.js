const util = require('util');
var net = require('net');
var ws = require('nodejs-websocket');

const socketPath = '/tmp/ipc-test';

var unixSocketServer = net.createConnection(socketPath, function(){
	console.log('connected');
	unixSocketServer.write('HELLO!');
});

var webSocketServer = ws.createServer(function (conn) {
	console.log('New connection: ');
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