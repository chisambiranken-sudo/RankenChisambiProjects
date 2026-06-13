<?php

header("Content-Type: application/json");

$patients = [
    ["name" => "John Doe", "condition" => "Flu"],
    ["name" => "Mary Jane", "condition" => "Diabetes"]
];

if ($_GET['action'] == "patients") {
    echo json_encode($patients);
}

if ($_GET['action'] == "count") {

    echo json_encode([
        "total" => count($patients),
        "active" => count($patients)
    ]);
}

?>
