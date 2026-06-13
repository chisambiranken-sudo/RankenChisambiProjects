let patients = [
    { name: "John Doe", condition: "Flu" },
    { name: "Mary Jane", condition: "Diabetes" }
];

// LOGIN
function login() {
    let u = document.getElementById("username").value;
    let p = document.getElementById("password").value;

    if (u === "admin" && p === "1234") {
        window.location.href = "dashboard.html";
    } else {
        document.getElementById("msg").innerText = "Invalid login";
    }
}

// ADD PATIENT
function addPatient() {
    let name = document.getElementById("name").value;
    let condition = document.getElementById("condition").value;

    patients.push({ name, condition });
    loadPatients();
}

// LOAD TABLE
function loadPatients() {
    let table = document.getElementById("patientTable");
    if (!table) return;

    table.innerHTML = "";

    patients.forEach(p => {
        table.innerHTML += `
            <tr>
                <td>${p.name}</td>
                <td>${p.condition}</td>
            </tr>
        `;
    });

    updateStats();
}

// DASHBOARD STATS
function updateStats() {
    let total = patients.length;
    let active = patients.filter(p => p.condition !== "").length;

    if (document.getElementById("total")) {
        document.getElementById("total").innerText = total;
        document.getElementById("active").innerText = active;
    }
}

window.onload = loadPatients;
