<?php
    $conn = new mysqli("localhost", "root", "supercool", "default");
    $sql = "SELECT extension FROM documents";
    $rows = $conn->query($sql);
    $response = array();
    while($row = $rows->fetch_assoc())
    {
        array_push($response, $row['extension']);
    }
    $conn->close();
    echo(json_encode($response));
?>