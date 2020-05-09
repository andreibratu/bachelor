// Global variables, hate me
let global_username = ''
let global_id = ''


function create_post_node(post) {
    let delete_button = `
        <div class="post-delete">
            <button type="button" class="btn btn-danger btn-sm post-delete-button">
                <svg class="bi bi-trash" width="2em" height="2em" viewBox="0 0 16 16" fill="currentColor" xmlns="http://www.w3.org/2000/svg">
                    <path d="M5.5 5.5A.5.5 0 016 6v6a.5.5 0 01-1 0V6a.5.5 0 01.5-.5zm2.5 0a.5.5 0 01.5.5v6a.5.5 0 01-1 0V6a.5.5 0 01.5-.5zm3 .5a.5.5 0 00-1 0v6a.5.5 0 001 0V6z" />
                    <path fill-rule="evenodd" d="M14.5 3a1 1 0 01-1 1H13v9a2 2 0 01-2 2H5a2 2 0 01-2-2V4h-.5a1 1 0 01-1-1V2a1 1 0 011-1H6a1 1 0 011-1h2a1 1 0 011 1h3.5a1 1 0 011 1v1zM4.118 4L4 4.059V13a1 1 0 001 1h6a1 1 0 001-1V4.059L11.882 4H4.118zM2.5 3V2h11v1h-11z" clip-rule="evenodd" />
                </svg> Delete
            </button>
        </div>`

    let html = `    
        <div class="card post">
            <p class="post-id" hidden>${post.post_id}</p>
            <div class="card-body d-flex flex-row">
                <div class="post-content">
                    <h6 class="card-subtitle mb-2 text-muted">${post.author.username}</h6>
                    <p class="card-subtitle mb-2 text-muted">${post.create}</p>
                    <p class="card-text post-content post-title">
                        <u>${post.content}</u>
                    </p>
                </div>
                ${(global_id === post.author.user_id) ? (delete_button) : ('')}
            </div>
        </div>`

    

    $('.post-container').append(html);
}

$(document).ready(() => {
    // var urlParams = new URLSearchParams(window.location.search)
    // console.log(urlParams.get('wow'));

    $.ajax({
        url: 'http://localhost:8080/users',
        type: 'GET',
        statusCode: {
            200: function (response) {
                global_username = response.username;
                global_id = response.user_id;
                $('#logged-username').text(global_username);
            },
            401: function () {
                window.location = '../login/login.html'
            }
        }
    });

    $.ajax({
        url: 'http://localhost:8080/posts',
        type: 'GET',
        statusCode: {
            200: function (response) {
                response.sort((a, b) => {
                    date_a = new Date(a.create);
                    date_b = new Date(b.create);
                    return date_b.getTime() - date_a.getTime()
                });
                response.forEach(post => {
                    create_post_node(post)
                });

                $('.post-content').click(function () {
                    id = $(this).parent().siblings('.post-id').text();
                    id = id === '' ? null : id;
                    if (id != null)
                    {
                        window.location = `../topic/topic.html?id=${id}`;
                    }
                });
            
                $('.post-delete').click(function () {
                    id = $(this).parent().siblings('.post-id').text();
                    id = id === '' ? null : id;
                    if (id != null)
                    {
                        $.ajax({
                            url: `http://localhost:8080/posts?id=${id}`,
                            type: 'DELETE',
                            statusCode: {
                                200: function() { window.location.reload(); },
                                401: function() {window.location = '../login/login.html';}
                            }
                        });
                    }
                });
            },
            401: function () {window.location = '../login/login.html';}
        }
    });

    $('#log-out').click(() => {
        $.ajax({
            url: 'http://localhost:8080/logout',
            type: 'GET',
            statusCode: {
                200: function () {
                    window.location = '../login/login.html'
                },
                401: function () {
                    window.location = '../login/login.html'
                }
            }
        })
    });

    $('#home-anchor').click(function () {
        window.location = '../main/main.html';
    })

    $('#submit-new-topic').click(() => {
        let input_val = $('#topic-input').val();
        if (input_val === '') return;
        $.ajax({
            url: 'http://localhost:8080/posts',
            type: 'POST',
            data: JSON.stringify({ content: input_val }),
            dataType: 'json',
            statusCode: {
                200: function () {
                },
                401: function () {
                    window.location = '../login/login.html'
                }
            }
        })
        window.location.reload();
    });
});