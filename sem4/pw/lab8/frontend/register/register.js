function setJwtHeader(xhr) {
    xhr.setRequestHeader("Authorization", 'Bearer '+ sessionStorage.getItem('jwt'));
}


function show_alerts(invalid, used)
{
    $('#invalid-credentials-alert').css('display', (invalid ? 'block' : 'none'));
    $('#credentials-used-alert').css('display', (used ? 'block' : 'none'));
}

$(document).ready(() => {
    $.ajax({
        url: 'https://localhost:44377/api/documents/',
        type: 'GET',
        beforeSend: setJwtHeader,
        statusCode: {
            200: function() { window.location = '../index/index.html' },
            401: function() {}
        }
    })

    show_alerts(false, false);

    $('#register-submit-button').click(e => {
        e.preventDefault();

        let usrn = $('#username').val();
        let paswd =  $('#password').val();

        $.ajax({
            url: 'https://localhost:44377/api/register',
            type: 'POST',
            data: JSON.stringify({username: usrn, password: paswd}),
            dataType: 'json',
            contentType: 'application/json; charset=utf-8',
            statusCode: {
                400: function () {  show_alerts(true, false); },
                200: function (response) { 
                    console.log(response);
                    show_alerts(false, false);
                    sessionStorage.setItem('jwt', response);
                    window.location = '../login/login.html';
                },
                409: function () { show_alerts(false, true); },
                415: function (response) { console.log(response); }
            }
        })
    })
});