m1, m2 = map(int, input().split())
t1, t2 = map(int, input().split())
p1, p2 = map(int, input().split())
mp1 = m1 if m1 < p1 else p1
mp2 = m2 if m2 < p2 else p2
r1 = mp1 if mp1 < t2 else t2
r2 = mp2 if mp2 < t1 else t1
r3 = r1 * 2 if r1 < r2 else r2 * 2
r3 = r3 + 1 if not r1 == r2 else r3
print(r3)