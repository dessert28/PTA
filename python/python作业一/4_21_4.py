def count_eligible_students(n, grades):
    eligible_count = 0
    
    for student_grades in grades:
        if all(grade >= 60 for grade in student_grades):
            eligible_count += 1
            
    return eligible_count

# 读取输入
n = int(input())
grades = []
for _ in range(n):
    grades.append(list(map(int, input().split())))

# 计算具有保研资格的学生人数
result = count_eligible_students(n, grades)
print(result)
