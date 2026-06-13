# Smart Clinic Analytics Report

patients = [
    {"name": "John Doe", "condition": "Flu"},
    {"name": "Mary Jane", "condition": "Diabetes"},
    {"name": "Peter Smith", "condition": "Malaria"}
]

print("=== Clinic Analytics Report ===")

print("Total Patients:", len(patients))

conditions = {}
for p in patients:
    c = p["condition"]
    conditions[c] = conditions.get(c, 0) + 1

print("\nCondition Distribution:")
for k, v in conditions.items():
    print(k, ":", v)
