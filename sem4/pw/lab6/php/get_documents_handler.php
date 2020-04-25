<?php
    $conn = new mysqli("localhost", "root", "supercool", "default");
    $rows = $conn->query("SELECT * FROM documents");
    $response = array();
    while($row = $rows->fetch_assoc())
    {   
        $result = new stdClass();
        $result->id = $row['id'];
        $result->author = $row['author'];
        $result->title = $row['title'];
        $result->extension = $row['extension'];
        $result->type = $row['doc_type'];
        array_push($response, $result);
    }
    $conn->close();

    echo(json_encode($response));
