// GLOBAL VARIABLES
var content;
var subPage;
var margin;
var contentWidth;
var contentSlider;
var indicatorPos;

$(document).ready(function () {
	subPage = $('.sub-page');
	content = $('#content');
	contentSlider = $('.content-slider');
	subPage.css('width', $('#content').width());
	contentWidth = content.width();
	margin = content.outerWidth(true) - contentWidth / 2;
	subPage.css('margin-right', margin);

	// Move the current nav menu indicator
	indicatorPos = $('.selected').position().left;
	var offset = $('.selected').width() / 2 - 25;
	$('nav #nav-indicator').css('left', indicatorPos + offset);

	// Move the selected page to view
	var destination = $('.active');
	var destinationPos = destination.position().left;
	contentSlider.css('left', -destinationPos);

	// Window resize function
	var id;
	$(window).resize(function () {
		// Delay the handler
		clearTimeout(id);
		id = setTimeout(function () {
			// Set sub-page lengths and margins to match content
			contentWidth = content.width();
			margin = content.outerWidth(true) - contentWidth / 2;

			subPage.css('width', contentWidth);
			subPage.css('margin-right', margin);

			// Move the current nav menu indicator
			indicatorPos = $('.selected').position().left;
			var offset = $('.selected').width() / 2 - 25;
			$('nav #nav-indicator').css('left', indicatorPos + offset);

			// Move the slider to correct position
			var destination = $('.active');
			var destinationPos = destination.position().left;
			contentSlider.css('left', -destinationPos);

		}, 200);
	});

	// Scrollable sub-page links on nav
	$('.main-navigation a[href*="#"]').click(function (e) {
		e.preventDefault();

		var destination = $($(this).attr('href'));
		var destinationPos = destination.position().left;

		$('.active').removeClass('active');
		destination.addClass('active');

		// Slide slider negative left the amount of the destination position
		contentSlider.css('left', -destinationPos);

		// Give parent (li) class selected and remove from others
		$('.selected').removeClass('selected');
		$(this).parent().addClass('selected');

		// Move the current nav menu indicator
		indicatorPos = $('.selected').position().left;
		var offset = $('.selected').width() / 2 - 25;
		$('nav #nav-indicator').css('left', indicatorPos + offset);
	});

	// Open settings
	$('aside a[href*="#"]').click(function (e) {
		e.preventDefault();
		var destination = $(this).attr('href');
		$('.overlay-wrapper' + destination).css('top', 0);
	});

	// Close settings
	$('.close-overlay').click(function () {
		var parent = $(this).closest('.overlay-wrapper');
		parent.css('top', -2000);
	});

	// Color change
	$('footer a').click(function (e) {
		e.preventDefault();
		var color = $(this).attr('href').replace('#', '');

		// Check if page has the color laready, run if not
		if (!$('#page').hasClass(color)) {
			// Use transition layer for smooth bg swap, wait until done
			$('#transition-layer').toggleClass('transitioning');
			setTimeout(function () {
				$('#page').removeClass('red yellow green');
				$('#page').addClass(color);
				$('#transition-layer').toggleClass('transitioning');
			}, 500);
		}
	});
});