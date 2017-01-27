$('.like').click(function(){
    var qid;
    qid = $(this).attr("qid");
    $.get( "/like", {id: qid}, function( data ) {
        //alert(data.rating)
        $('#' + qid + 'rating').html(data.rating);
        $('#' + qid + 'like').css('background-color', '');
        $('#' + qid + 'dislike').css('background-color', '');
        if (data.myrate == 1) {
            $('#' + qid + 'like').css('background-color', 'green');
        }
        if (data.myrate == -1) {
            $('#' + qid + 'dislike').css('background-color', 'red');
        }
    }, "json" );})

$('.dislike').click(function(){
    var qid;
    qid = $(this).attr("qid");
    $.get( "/dislike", {id: qid}, function( data ) {
        //alert(data.rating)
        $('#' + qid + 'rating').html(data.rating);
        $('#' + qid + 'like').css('background-color', '');
        $('#' + qid + 'dislike').css('background-color', '');
        if (data.myrate == 1) {
            $('#' + qid + 'like').css('background-color', 'green');
        }
        if (data.myrate == -1) {
            $('#' + qid + 'dislike').css('background-color', 'red');
        }
    }, "json" );})

$('.rightbutton').click(function(){
    var qid;
    qid = $(this).attr("qid");
    $.get( "/setanswercorrect", {id: qid}, function( data ) {
        if (data.error == 0) {
           $('#' + data.lastid + 'anspanel').css('background-color', '');
           $('#' + data.newid + 'anspanel').css('background-color', 'GreenYellow');
        }
    }, "json" );})

$('.likeanswer').click(function(){
    var qid;
    qid = $(this).attr("qid");
    $.get( "/likeanswer", {id: qid}, function( data ) {
        //alert(JSON.stringify(data));
        $('#' + qid + 'ratinganswer').html(data.rating);
        $('#' + qid + 'likeanswer').css('background-color', '');
        $('#' + qid + 'dislikeanswer').css('background-color', '');
        if (data.myrate == 1) {
            $('#' + qid + 'likeanswer').css('background-color', 'green');
        }
        if (data.myrate == -1) {
            $('#' + qid + 'dislikeanswer').css('background-color', 'red');
        }
    }, "json" );})

$('.dislikeanswer').click(function(){
    var qid;
    qid = $(this).attr("qid");
    $.get( "/dislikeanswer", {id: qid}, function( data ) {
        //alert(data.rating)
        $('#' + qid + 'ratinganswer').html(data.rating);
        $('#' + qid + 'likeanswer').css('background-color', '');
        $('#' + qid + 'dislikeanswer').css('background-color', '');
        if (data.myrate == 1) {
            $('#' + qid + 'likeanswer').css('background-color', 'green');
        }
        if (data.myrate == -1) {
            $('#' + qid + 'dislikeanswer').css('background-color', 'red');
        }
    }, "json" );})