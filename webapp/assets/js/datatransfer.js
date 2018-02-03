var socketConnected = false;

$(document).ready(function() {

	var socket = connectToSocket();

	var retryWrapper = $('#retry-wrapper');
	var retryButton = $('#retry-connection');
	var doorButton = $('.door-button');

	retryButton.click(connectToSocket);

	function connectToSocket(){
		var retryButton = $('#retry-connection');
		retryButton.addClass('rotating');

		var serverAddress = location.host;
		var socket = new WebSocket('ws://' + serverAddress + ':8001');
	
		socket.onopen = function() {
			retryButton.removeClass('rotating');
			console.log('WebSocket opened');
			socket.send(JSON.stringify({ 'message': 'hi' }));
			socketConnected = true;
			retryWrapper.hide();

			doorButton.click(function () {
				var id = $(this).attr('data-id');
				var command = $(this).attr('data-command');
				var msg = "door|" + id + "|" + command;
				console.log(msg);
				socket.send(msg);
			});
		};
	
		socket.onclose = function() {
			retryButton.removeClass('rotating');
			console.log('WebSocket closed');
			socketConnected = false;
			retryWrapper.show();
		};
	
		socket.onmessage = function (event) {
			var data = JSON.parse(event.data);
			console.log(data);
		};

		return socket;
	}

});

$(document).on('submit', 'form', function(e) {
	e.preventDefault();
});