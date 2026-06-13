<?php

header("Content-Type: application/json");

// Simulated hospital equipment data
$equipment = [
    ["name" => "X-Ray Machine", "status" => "Active"],
    ["name" => "ECG Monitor", "status" => "Maintenance"],
    ["name" => "Ventilator", "status" => "Active"]
];

// Simple API routing
if (isset($_GET['action'])) {

    if ($_GET['action'] == "getEquipment") {
        echo json_encode($equipment);
    }

    if ($_GET['action'] == "stats") {
        $active = 0;
        $maintenance = 0;

        foreach ($equipment as $item) {
            if ($item['status'] == "Active") $active++;
            if ($item['status'] == "Maintenance") $maintenance++;
        }

        echo json_encode([
            "total" => count($equipment),
            "active" => $active,
            "maintenance" => $maintenance
        ]);
    }
}

?>
