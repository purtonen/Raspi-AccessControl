var socketConnected = false;

$(document).ready(function () {

	var socket = connectToSocket();

	var retryWrapper = $('#retry-wrapper');
	var retryButton = $('#retry-connection');
	var doorButton = $('.door-button');

	retryButton.click(connectToSocket);

	function connectToSocket() {
		var retryButton = $('#retry-connection');
		retryButton.addClass('rotating');

		var serverAddress = location.host;
		var socket = new WebSocket('ws://' + serverAddress + ':8001');

		socket.onopen = function () {
			retryButton.removeClass('rotating');
			console.log('WebSocket opened');
			socket.send(JSON.stringify({'message': 'hi'}));
			socketConnected = true;
			retryWrapper.hide();

			doorButton.click(function () {
				var id = $(this).data('id');
				var command = $(this).data('command');
				var msg = "door|" + id + "|" + command;
				console.log(msg);
				socket.send(msg);
				$(this).toggleClass('fa-door-open fa-door-closed');
				if(command == 'open'){
					$(this).data('command', 'close');
				} else if(command == 'close'){
					$(this).data('command', 'open');
				}
			});
		};

		socket.onclose = function () {
			retryButton.removeClass('rotating');
			console.log('WebSocket closed');
			socketConnected = false;
			retryWrapper.show();
		};

		socket.onmessage = function (event) {
			var data = JSON.parse(event.data);
			console.log(data);
			interpretMessage(data);
		};

		return socket;
	}

});

function interpretMessage(msg){
	if(msg.logEntry.eventType == 'sensor_triggered' && msg.logEntry.sensorValue == 1){
		var id = msg.logEntry.sensorId;
		$('node[data-id="'+id+'"]').addClass('alarm');
	} else if(msg.logEntry.eventType == 'sensor_triggered' && msg.logEntry.sensorValue == 0){
		var id = msg.logEntry.sensorId;
		$('node[data-id="'+id+'"]').removeClass('alarm');
	}
}

$(document).on('submit', 'form', function (e) {
	e.preventDefault();
});