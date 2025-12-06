import os

os.environ["OPENBLAS_NUM_THREADS"] = "1"

def get_grade(points):
    if points <= 50: return 5
    if points == 100: return 10
    return int((points-1) / 10 + 1)


if __name__ == "__main__":
    students = {}
    while True:
        line = input()
        if line == 'end': break
        parts = line.split(',')
        student_data = {
            "name" : parts[0],
            "surname" : parts[1],
            "index": parts[2],
            "subject": parts[3],
            "theory": int(parts[4]),
            "practical": int(parts[5]),
            "labs": int(parts[6])
        }

        students.setdefault(parts[2], []).append(student_data)


    for student in students:
        student_data = students[student]
        print(f"Student: {student_data[0]['name']} {student_data[0]['surname']}")
        for subject in student_data:
            total_points = subject['theory'] + subject['practical'] + subject['labs']
            print(f"----{subject['subject']}: {get_grade(total_points)}")
        print()