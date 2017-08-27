var ws = require('nodejs-websocket');

var server = ws.createServer(function (conn) {
    console.log('New connection: ' + conn);

    conn.on('text', function (data) {
        data = JSON.parse(data);

        broadcast(server, JSON.stringify({'message': 'hello broad'}));
    });

    conn.on('close', function (code, reason) {
        console.log('Connection closed (' + reason + ')');
    });

}).listen(8001);

function broadcast(server, msg) {
    server.connections.forEach(function (conn) {
        conn.sendText(msg);
    });
}