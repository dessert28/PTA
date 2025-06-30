n = int(input())
scores = list(map(int, input().split()))
max_score = max(scores)
min_score = min(scores)
average_score = sum(scores) / n
fail_count = sum(1 for score in scores if score < 60)

print(f"Max: {max_score}")
print(f"Min: {min_score}")
print(f"Ave: {average_score:.1f}")
print(f"Fail: {fail_count}")