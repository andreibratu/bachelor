function setJwtHeader(xhr) {
    xhr.setRequestHeader("Authorization", 'Bearer '+ sessionStorage.getItem('jwt'));
}

function prependDownloadRequest(xhr) {
    xhr.setRequestHeader("Authorization", 'Bearer '+ sessionStorage.getItem('jwt'));
    xhr.setRequestHeader('Accept', 'application/octet-stream');
}

function createDocumentCard(data) {
    let username = sessionStorage.getItem('username');
    let newCard = $($("#document-card-template").html().trim())
    newCard.find('.document-title').text(data.title)
    newCard.find('.document-author').text(data.author.username)
    newCard.find('.document-type').text(data.type)
    newCard.find('.document-format').text(data.extension)
    newCard.find('.document-delete').click(function() {
        $("#deleteDocumentHiddenInput").val(data.id)
    });
    newCard.find('.document-edit').click(() => {
        $('#input-edit-document-id').val(data.id)
        $('#input-edit-document-author').val(data.author)
        $('#input-edit-document-type').val(data.type)
    })
    newCard.find('.document-download').click(() => {
        $.ajax({
            url: `https://localhost:44377/api/download/?id=${data.id}`,
            type: 'GET',
            beforeSend: prependDownloadRequest,
            statusCode: {
                200: function(response) 
                {
                    var headers = response.headers;
                    var blob = new Blob(
                        [response.body], 
                        { type: headers['application/octet-stream'] }
                    );
                    var link = document.createElement('a');
                    link.href = window.URL.createObjectURL(blob);
                    link.download = data.fileUrl.substring(7);
                    link.click();
                },
                401: function() { window.location = '../login/login.html' },
                500: function(response) { console.log(response.responseText); }
            }
        })
    })
    if(username !== data.author.username)
    {
        // newCard.find('.document-delete').remove();
        // newCard.find('.document-edit').remove();
    }
    $('.content').append(newCard)
}

function deleteDocument(id) {
    $.ajax({
        url: `https://localhost:44377/api/documents/${id}`,
        type: 'DELETE',
        beforeSend: setJwtHeader,
        statusCode: {
            200: function() { window.location = 'index.html' },
            401: function() { window.location = '../login/login.html' },
            403: function() { alert('Forbidden action!') },
            500: function(response) { console.log(response.responseText); }
        }
    });
}

function filterDocuments() {
    if (typeof filterDocuments.selectedType === 'undefined') {
        filterDocuments.selectedType = 'All'
        filterDocuments.selectedFormat = 'ALL'
    }
    $('.document-card').each(function () {
        let selectedType = filterDocuments.selectedType
        let selectedFormat = filterDocuments.selectedFormat

        let type = $(this).find('.document-type').text()
        let format = $(this).find('.document-format').text()

        if (selectedType !== 'All' && selectedType !== type) $(this).hide()
        else if (selectedFormat !== 'ALL' && selectedFormat !== format) $(this).hide()
        else $(this).show()
    })
}

function getAllDocumentExtensions() {
    $.ajax({
        url: `https://localhost:44377/api/documents`,
        type: 'GET',
        dataType: 'json',
        beforeSend: setJwtHeader,
        statusCode: {
            200: function(data) {
                $('#extension-dropdown > div > a').each((_, e) => $(e).remove())

                filterDocuments.selectedFormat = 'ALL'
                all_option = '<a class=\"dropdown-item bg-primary\" href=\"#\">ALL</a>'
                $(all_option).appendTo($('#extension-dropdown > div'))
    
                data.forEach(doc => {
                    html = `<a class=\"dropdown-item\" href=\"#\">${doc.extension}</a>`
                    $(html).appendTo($('#extension-dropdown > div'))
                })
    
                $('#extension-dropdown a').click((e) => {
                    console.log(e.target.innerText)
                    filterDocuments.selectedFormat = e.target.innerText;
                    filterDocuments()
                    $('#extension-dropdown a').each(function () { $(this).removeClass('bg-primary') })
                    $(e.target).addClass('bg-primary')
                })
            },
            401: function() { window.location = '../login/login.html' },
            500: function(response) { console.log(response.responseText); }
        }
    });
}

function getAllDocumentTypes() {
    $.ajax({
        url: `https://localhost:44377/api/documents`,
        beforeSend: setJwtHeader,
        type: 'GET',
        dataType: 'json',
        statusCode: {
            200: function(data) {
                $('#type-dropdown > div > a').each((_, e) => $(e).remove())

                filterDocuments.selectedType = 'All'
                all_option = '<a class=\"dropdown-item bg-primary\" href=\"#\">All</a>'
                $(all_option).appendTo($('#type-dropdown > div'))
    
                data.forEach(doc => {
                    html = `<a class=\"dropdown-item\" href=\"#\">${doc.type}</a>`
                    $(html).appendTo($('#type-dropdown > div'))
                })
    
                $('#type-dropdown a').click((e) => {
                    filterDocuments.selectedType = e.target.innerText;
                    filterDocuments()
                    $('#type-dropdown a').each(function () { $(this).removeClass('bg-primary') })
                    $(e.target).addClass('bg-primary')
                })
            },
            401: function() { window.location = '../login/login.html'; },
            500: function(response) { console.log(response.responseText); }
        }
    });
}

function getAllDocuments() {
    $('.document-card').each(function () { $(this).remove() })
    $.ajax({
        url: `https://localhost:44377/api/documents`,
        beforeSend: setJwtHeader,
        dataType: 'json',
        contentType: 'application/json; charset=utf-8',
        type: 'GET',
        statusCode: {
            200: function(data) { data.forEach(doc => createDocumentCard(doc)); },
            401: function() { window.location = '../login/login.html'; },
            500: function(response) { console.log(response.responseText); }
        }
    });
    $('#document-edit-submit-button').click(e => {
        e.preventDefault();

        let f = document.getElementById('input-edit-document-file').files[0];
        let type = $('#input-edit-document-type').val();

        if (!f || type === '') 
        {
            alert('Fill out the form please :3')
            return;
        }

        let docId = $('#input-edit-document-id').val();
        let extension = f.name.split('.').slice(-1).pop().toUpperCase();
        let title = f.name.split('.').slice(0, -1).join('');

        var reader = new FileReader();
        reader.onload = function() {
            let content = reader.result.slice(37);
            $.ajax({
                url: `https://localhost:44377/api/documents/${docId}`,
                type: 'PUT',
                beforeSend: setJwtHeader,
                data: JSON.stringify({
                    title: title,
                    extension: extension,
                    file: content,
                    type: type,
                }),
                dataType: 'json',
                contentType: 'application/json; charset=utf-8',
                statusCode: {
                    204: function() { 
                        getAllDocuments()
                        getAllDocumentExtensions()
                        getAllDocumentTypes()
                        filterDocuments()
                    },
                    400: function(response) { console.log(response); },
                    401: function() { window.location = '../login/login.html' },
                    500: function(response) { console.log(response.responseText); } 
                }
            })
        };
        reader.readAsDataURL(f);
    });
}

$(document).ready(() => {
    getAllDocuments()
    getAllDocumentExtensions()
    getAllDocumentTypes()

    $('#log-out').click(function () {
        sessionStorage.removeItem('jwt');
        window.location = '../login/login.html';
    })

    $('#submitDeleteButton').click(function () {
        let deleteId = $("#deleteDocumentHiddenInput").val();
        deleteDocument(deleteId);
    })

    $('#new-document-form').submit(function (e) {
        e.preventDefault()
        let f = document.getElementById('input-document-file').files[0]; 
        let docType = $('#input-document-type').val();
        console.log(docType);

        if (f) {
            var reader = new FileReader();
            let extension = f.name.split('.').slice(-1).pop().toUpperCase();
            let title = f.name.split('.').slice(0, -1).join('');
            reader.onload = function() {
                let content = reader.result.slice(37);
                $.ajax({
                    url: 'https://localhost:44377/api/documents',
                    type: 'POST',
                    beforeSend: setJwtHeader,
                    data: JSON.stringify({
                        title: title,
                        extension: extension,
                        file: content,
                        type: docType,
                    }),
                    dataType: 'json',
                    contentType: 'application/json; charset=utf-8',
                    statusCode: {
                        200: function() { 
                            getAllDocuments()
                            getAllDocumentExtensions()
                            getAllDocumentTypes()
                            filterDocuments()
                        },
                        401: function() { window.location = '../login/login.html' },
                        500: function(response) { console.log(response.responseText); } 
                    }
                })
            };
            reader.readAsDataURL(f);
        }
    });
})