function createDocumentCard(data) {
    let newCard = $($("#document-card-template").html().trim())
    newCard.find('.document-title').text(data.title)
    newCard.find('.document-author').text(data.author)
    newCard.find('.document-type').text(data.type)
    newCard.find('.document-format').text(data.extension)
    newCard.find('.document-delete').click(
        () => deleteDocument(newCard, data.id)
    )
    newCard.find('.document-edit').click(() => {
        $('#input-edit-document-id').val(data.id)
        $('#input-edit-document-author').val(data.author)
        $('#input-edit-document-type').val(data.type)
    })
    newCard.find('.document-download').click(() => {
        $.get(
            `php/download_document_handler.php?id=${data.id}`,
            null,
            (data) => console.log(data)
        )
    })
    $('body').append(newCard)
}

function deleteDocument(cardRef, id) {
    $.get(`php/delete_document_handler.php?id=${id}`)
    cardRef.remove()
}

function filterDocuments() {
    if (typeof filterDocuments.selectedType === 'undefined') {
        filterDocuments.selectedType = 'All'
        filterDocuments.selectedFormat = 'ALL'
    }
    console.log(filterDocuments.selectedType, filterDocuments.selectedFormat)
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
    $.get(
        'php/get_document_extensions_handler.php',
        data => {
            $('#extension-dropdown > div > a').each((_, e) => $(e).remove())

            filterDocuments.selectedFormat = 'ALL'
            all_option = '<a class=\"dropdown-item bg-primary\" href=\"#\">ALL</a>'
            $(all_option).appendTo($('#extension-dropdown > div'))

            JSON.parse(data).forEach(extension => {
                html = `<a class=\"dropdown-item\" href=\"#\">${extension}</a>`
                $(html).appendTo($('#extension-dropdown > div'))
            })

            $('#extension-dropdown a').click((e) => {
                console.log(e.target.innerText)
                filterDocuments.selectedFormat = e.target.innerText;
                filterDocuments()
                $('#extension-dropdown a').each(function () { $(this).removeClass('bg-primary') })
                $(e.target).addClass('bg-primary')
            })
        }
    )
}

function getAllDocumentTypes() {
    $.get(
        'php/get_document_types_handler.php',
        data => {
            $('#type-dropdown > div > a').each((_, e) => $(e).remove())

            filterDocuments.selectedType = 'All'
            all_option = '<a class=\"dropdown-item bg-primary\" href=\"#\">All</a>'
            $(all_option).appendTo($('#type-dropdown > div'))

            JSON.parse(data).forEach(type => {
                html = `<a class=\"dropdown-item\" href=\"#\">${type}</a>`
                $(html).appendTo($('#type-dropdown > div'))
            })

            $('#type-dropdown a').click((e) => {
                filterDocuments.selectedType = e.target.innerText;
                filterDocuments()
                $('#type-dropdown a').each(function () { $(this).removeClass('bg-primary') })
                $(e.target).addClass('bg-primary')
            })
        }
    )
}

function getAllDocuments() {
    $('.document-card').each(function () { $(this).remove() })
    $.get(
        'php/get_documents_handler.php',
        data => JSON.parse(data).forEach(doc => createDocumentCard(doc))
    );
    $('#document-edit-submit-button').click(e => {
        e.preventDefault()
        $.ajax({
            url: 'php/update_document_handler.php',
            type: 'POST',
            data: new FormData(document.getElementById('edit-document-form')),
            processData: false,
            contentType: false,
            success: response => {
                $('#editDocumentModal .close').click()
                getAllDocuments()
                getAllDocumentExtensions()
                getAllDocumentTypes()
                filterDocuments()
                console.log(response)
            }
        })
    });
}

$(document).ready(() => {
    getAllDocuments()
    getAllDocumentExtensions()
    getAllDocumentTypes()

    $('#new-document-form').submit(function (e) {
        e.preventDefault()
        $.ajax({
            url: 'php/new_document_handler.php',
            type: 'POST',
            data: new FormData(this),
            processData: false,
            contentType: false,
            success: (response) => {
                getAllDocuments()
                getAllDocumentExtensions()
                getAllDocumentTypes()
                filterDocuments()
                console.log(response)
            }
        })
    });
})