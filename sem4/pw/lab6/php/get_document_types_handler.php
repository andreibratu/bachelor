<?php
    $conn = new mysqli("localhost", "root", "supercool", "default");
    $sql = "SELECT doc_type FROM documents";
    $rows = $conn->query($sql);
    $response = array();
    while($row = $rows->fetch_assoc())
    {
        array_push($response, $row['doc_type']);
    }
    $conn->close();
    echo(json_encode($response));
?>