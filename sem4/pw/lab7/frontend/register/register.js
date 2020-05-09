function show_alerts(invalid, used)
{
    $('#invalid-credentials-alert').css('display', (invalid ? 'block' : 'none'));
    $('#credentials-used-alert').css('display', (used ? 'block' : 'none'));
}

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

    show_alerts(false, false);

    $('#register-submit-button').click(e => {
        e.preventDefault();

        let usrn = $('#username').val();
        let paswd =  $('#password').val();

        $.ajax({
            url: 'http://localhost:8080/register',
            type: 'POST',
            data: JSON.stringify({username: usrn, password: paswd}),
            dataType: 'json',
            statusCode: {
                400: function() { 
                    show_alerts(true, false);
                },
                200: function() { 
                    show_alerts(false, false);
                    window.location = '../main/main.html';
                },
                409: function() {
                    show_alerts(false, true);
                }
            }
        })
    })
});