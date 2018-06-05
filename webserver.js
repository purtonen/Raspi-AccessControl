/*	This is the Node.js intermediate between the frontend and the sensorapp.
 *	Main purpose of this app is to deliver messages between frontend
 *	and backend. 
 *	This app connects to a Unix socket created by the sensorapp, creates
 *	its own websocket for the frontend to connect to, and passes data
 *	along these pipelines. All data is transferred via JSON strings. 
 */


const util = require('util');
var net = require('net');
var ws = require('nodejs-websocket');

var reconnectTimeout = 0;

const socketPath = '/tmp/ipc-test';

console.log(" ");

var unixSocket = connectToSocket();

var webSocketServer = ws.createServer(function (conn) {
	console.log('webserver.js: New websocket connection');
	//console.log(util.inspect(conn, false, null))

	conn.on('text', function (data) {
		clientMessageHandler(data);
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

// Broadcast a message to all connected clients (frontend)
function broadcast(webSocketServer, msg) {
	webSocketServer.connections.forEach(function (conn) {
		conn.sendText(msg);
	});
}

// Handle all incoming messages from client (front end)
function clientMessageHandler(msg) {
	unixSocket.write(msg);
}

// Connect to the Unix socket created by the sensorapp
function connectToSocket() {

	var unixSocket = net.createConnection(socketPath, function () {
		console.log('webserver.js: Connected to Unix socket');
		unixSocket.write('HELLO!');
	});

	// Catch all connection errors and recursively try again in intervals
	unixSocket.on('error', function (e) {
		// Make each reconnect timeout 100ms longer than the previous one
		reconnectTimeout += 100;
		// If timeout grovs beyond a threshold, stop trying and exit
		if (reconnectTimeout > 10000) {
			console.log('webserver.js: socket connection timeout, exiting...');
			process.exit();
		} else {
			console.log('webserver.js: error connecting, retrying in ' + reconnectTimeout + 'ms...');
			setTimeout(connectToSocket, reconnectTimeout);
		}

	});

	// Event for catching incoming data from sensorapp
	unixSocket.on('data', function (data) {
		data = data.toString();
		broadcast(webSocketServer, data);
	});

	return unixSocket;

}