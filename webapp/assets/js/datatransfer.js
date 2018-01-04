$(document).ready(function () {
	var serverAddress = location.host;
	var socket = new WebSocket('ws://' + serverAddress + ':8001');

	socket.onopen = function () {
		console.log('WebSocket opened');
		socket.send(JSON.stringify({ 'message': 'hi' }));
	};

	socket.onclose = function () {
		console.log('WebSocket closed');
	};

	socket.onmessage = function (event) {
		var data = JSON.parse(event.data);
		console.log(data);
	};

});

$(document).on('submit', 'form', function (e) {
	e.preventDefault();
});
