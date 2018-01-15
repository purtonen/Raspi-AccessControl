const util = require('util');
var net = require('net');
var ws = require('nodejs-websocket');

var reconnectTimeout = 0;

const socketPath = '/tmp/ipc-test';

console.log(" ");

connectToSocket();

var webSocketServer = ws.createServer(function (conn) {
	console.log('webserver.js: New websocket connection');
	//console.log(util.inspect(conn, false, null))

	conn.on('text', function (data) {
		data = JSON.parse(data);
		messageHandler(data);
		broadcast(webSocketServer, JSON.stringify({'message': 'hello broadcast'}));
	});

	conn.on('close', function (code, reason) {
		console.log('webserver.js: Client disconnected (' + reason + ')');
	});

	process.on('uncaughtException', function (e) {
		console.error(e.stack);
		console.log("webserver.js: Node NOT Exiting...");
	});

}).listen(8001);

function broadcast(webSocketServer, msg) {
	webSocketServer.connections.forEach(function (conn) {
		conn.sendText(msg);
	});
}

function messageHandler(msg){

}

function connectToSocket(){
	
	var unixSocket = net.createConnection(socketPath, function(){
		console.log('webserver.js: Connected to Unix socket');
		unixSocket.write('HELLO!');
	});
	unixSocket.on('error', function(e){
		reconnectTimeout += 100;
		if(reconnectTimeout > 10000){
			console.log('webserver.js: socket connection timeout, exiting...');
			process.exit();
		} else {
			console.log('webserver.js: error connecting, retrying in '+reconnectTimeout+'ms...');
			setTimeout(connectToSocket, reconnectTimeout);
		}
		
	})
	unixSocket.on('data', function(data){
		data = data.toString();
		broadcast(webSocketServer, data);
	});

}