$(document).ready(() => {
    $.ajax({
        url: 'https://localhost:44377/api/documents/',
        type: 'GET',
        beforeSend: function (xhr) {   //Include the bearer token in header
            xhr.setRequestHeader("Authorization", 'Bearer '+ sessionStorage.getItem('jwt'));
        },
        statusCode: {
            200: function() { window.location = '../main/main.html' },
            401: function() { },
        }
    })
    
    $('#invalid-credentials-alert').css('display', 'none');

    $('#login-submit-button').click(e => {
        e.preventDefault();

        let usrn = $('#username').val();
        let paswd =  $('#password').val();
        
        $.ajax({
            url: 'https://localhost:44377/api/login',
            type: 'POST',
            data: JSON.stringify({username: usrn, password: paswd}),
            dataType: 'text',
            contentType: 'application/json; charset=utf-8',
            statusCode: {
                400: function() { 
                    $('#invalid-credentials-alert').css('display', 'block');
                },
                200: function(response) { 
                    $('#invalid-credentials-alert').css('display', 'none');
                    sessionStorage.setItem('jwt', response);
                    sessionStorage.setItem('username', usrn);
                    window.location = '../index/index.html';
                },
            }
        })
    })
})