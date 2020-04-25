<?php 
    $author = $_POST['input-document-author'];
    $type = $_POST['input-document-type'];
    $file = $_FILES['input-document-file'];

    $sstr = explode('.', $file['name']); 
    $name = implode(array_slice($sstr, 0, -1));
    $extension = strtoupper(end($sstr));

    $conn = new mysqli("localhost", "root", "supercool", "default");

    $file_content = file_get_contents($file['tmp_name']);
    $document_size = filesize($file['tmp_name']);
    $file_content = $conn->real_escape_string($file_content);

    $sql = "INSERT INTO documents (author, title, extension, doc_type, document, document_size) VALUES ('$author', '$name', '$extension', '$type', '$file_content', '$document_size')";
    $conn->query($sql);
    
    $response->result = $conn->error;
    $response->content = $file_content;
    $conn->close();

    echo json_encode($response);
?>