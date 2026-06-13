let equipmentList = [
    { name: "X-Ray Machine", department: "Radiology", status: "Active" },
    { name: "ECG Monitor", department: "Cardiology", status: "Maintenance" },
    { name: "Ventilator", department: "ICU", status: "Active" }
];

// Load data when page opens
window.onload = function () {
    updateDashboard();
    loadInventory();
    loadMaintenance();
};

// Add new equipment
function addEquipment() {
    let name = document.getElementById("name").value;
    let department = document.getElementById("department").value;
    let status = document.getElementById("status").value;

    if (name && department) {
        equipmentList.push({ name, department, status });
        alert("Equipment added successfully!");
        loadInventory();
        updateDashboard();
    }
}

// Inventory table
function loadInventory() {
    let table = document.getElementById("equipmentTable");
    if (!table) return;

    table.innerHTML = "";

    equipmentList.forEach(item => {
        table.innerHTML += `
            <tr>
                <td>${item.name}</td>
                <td>${item.department}</td>
                <td>${item.status}</td>
            </tr>
        `;
    });
}

// Dashboard stats
function updateDashboard() {
    let total = equipmentList.length;
    let active = equipmentList.filter(e => e.status === "Active").length;
    let maintenance = equipmentList.filter(e => e.status === "Maintenance").length;

    if (document.getElementById("totalEquipment")) {
        document.getElementById("totalEquipment").innerText = total;
        document.getElementById("activeEquipment").innerText = active;
        document.getElementById("maintenanceEquipment").innerText = maintenance;
    }
}

// Maintenance page
function loadMaintenance() {
    let table = document.getElementById("maintenanceTable");
    if (!table) return;

    table.innerHTML = "";

    equipmentList
        .filter(item => item.status === "Maintenance")
        .forEach(item => {
            table.innerHTML += `
                <tr>
                    <td>${item.name}</td>
                    <td>${item.department}</td>
                    <td><button onclick="markActive('${item.name}')">Mark Active</button></td>
                </tr>
            `;
        });
}

// Change status
function markActive(name) {
    equipmentList = equipmentList.map(item => {
        if (item.name === name) {
            item.status = "Active";
        }
        return item;
    });

    loadMaintenance();
    loadInventory();
    updateDashboard();
}
