$(document).on('submit', 'form', function(e){
    e.preventDefault();
    scrolling = true;
    console.log("posting AJAX");
    $.ajax({
        url : 'open_door',
        type : 'POST',
        data : $(this).serialize(),

        success : function(json){
            console.log("successful post");
            scrolling = false;
            updateDoors();
        }
    });
});

function updateDoors(){
    if (!scrolling) {
        console.log("update");
        $.get('update_doors', function(doors){
            $('#doors').empty().append(doors);
        });
    }
    scrolling = false;
}

var scrolling = false;
$(function(){
    $('#home-container').on('scroll', function(){
        scrolling = true;
    });
    var refreshTimer = setInterval(updateDoors, 800);
});
