var socketConnected = false;

$(document).ready(function() {

	connectToSocket();

	var retryWrapper = $('#retry-wrapper');
	var retryButton = $('#retry-connection');

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
	}

});

$(document).on('submit', 'form', function(e) {
	e.preventDefault();
});