<?php
    $conn = new mysqli("localhost", "root", "supercool", "default");

    $author = $_POST['input-edit-document-author'];
    $type = $_POST['input-edit-document-type'];
    $id = $_POST['input-edit-document-id'];
    $file = $_FILES['input-edit-document-file'];

    $sstr = explode('.', $file['name']); 
    $name = implode(array_slice($sstr, 0, -1));
    $extension = strtoupper(end($sstr));

    $file_content = file_get_contents($file['tmp_name']);
    $file_content = $conn->real_escape_string($file_content);

    $sql = "UPDATE documents SET author = '$author', title = '$name', extension = '$extension', doc_type = '$type', document = '$file_content' WHERE id = '$id'";
    $conn->query($sql);
    
    $response->result = $conn->error;
    $response->content = $file_content;
    $conn->close();

    echo json_encode($response);
?>