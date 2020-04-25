<?php
    $id = $_GET['id'];
    
    $conn = new mysqli("localhost", "root", "supercool", "default");
    $sql = "DELETE FROM documents WHERE id='$id'";
    $conn->query($sql);
    $conn->close;
?>