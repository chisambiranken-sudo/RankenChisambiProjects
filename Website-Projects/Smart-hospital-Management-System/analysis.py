# Hospital Equipment Data Analysis Script

equipment = [
    {"name": "X-Ray Machine", "status": "Active", "hours": 120},
    {"name": "ECG Monitor", "status": "Maintenance", "hours": 80},
    {"name": "Ventilator", "status": "Active", "hours": 200}
]

# Calculate stats
total = len(equipment)
active = len([e for e in equipment if e["status"] == "Active"])
maintenance = len([e for e in equipment if e["status"] == "Maintenance"])

most_used = max(equipment, key=lambda x: x["hours"])

print("=== Hospital Equipment Report ===")
print("Total Equipment:", total)
print("Active:", active)
print("Under Maintenance:", maintenance)
print("\nMost Used Equipment:")
print(most_used["name"], "-", most_used["hours"], "hours")
