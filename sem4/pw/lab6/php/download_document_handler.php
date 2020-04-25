<?php
    $conn = new mysqli("localhost", "root", "supercool", "default");

    $id = $_GET['id'];
    $sql = "SELECT * FROM documents WHERE id = '$id'";
    $rows = $conn->query($sql);
    while($row = $rows->fetch_assoc())
    {
        $filename = $row['title'] . '.' . $row['extension'];
        $doc_size = $row['document_size'];
        header("Content-length: $doc_size");
        header("Content-type: application/octet-stream");
        header("Content-Disposition: attachment; filename=$filename");
        ob_clean();
        flush();
        echo($row['document']);
    }
    $conn->close();
?>