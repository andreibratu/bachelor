$(document).ready(() => {
    $.ajax({
        url: 'http://localhost:8080/users',
        type: 'GET',
        statusCode: {
            200: function(response)
            {
                window.location = '../main/main.html'
            },
            401: function() {}
        }
    })
    
    $('#invalid-credentials-alert').css('display', 'none');


    $('#login-submit-button').click(e => {
        e.preventDefault();

        let usrn = $('#username').val();
        let paswd =  $('#password').val();

        $.ajax({
            url: 'http://localhost:8080/login',
            type: 'POST',
            data: JSON.stringify({username: usrn, password: paswd}),
            dataType: 'json',
            statusCode: {
                400: function() { 
                    $('#invalid-credentials-alert').css('display', 'block');
                    console.log($('#invalid-credentials-alert'));
                },
                200: function() { 
                    $('#invalid-credentials-alert').css('display', 'none');
                    window.location = '../main/main.html';
                 }
            }
        })
    })
})