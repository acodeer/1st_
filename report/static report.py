import math as m
# 데이터
data = [41, 32, 30, 23, 24, 32, 11, 39, 24, 46,
        50, 18, 41, 14, 33, 50, 38, 25, 32, 16,
        43, 19, 35, 22, 46, 43, 10, 22, 17, 47,
        66, 48, 25, 43, 28, 31, 12, 25, 12, 48]
no_c = round(1 + m.log2(len(data)))  # 계급의 수
unit = 1;  # 계급 단위
gap = m.ceil((max(data)-min(data))/no_c)  # 계급폭
floor = min(data)-unit/2  # 계급의 하한
freq = [0] * no_c # 도수
# 도수분포표 생성
def draw_table(data, no_c, gap, floor):
    while True:
        freq = [0] * no_c
        c_freq = 0  # 누적도수
        
        for i in range(no_c):
            for j in data:
                if floor + gap * i <= j < floor + gap * (i + 1):
                    freq[i] += 1
            c_freq += freq[i]
        
        if c_freq == len(data):
            return freq, gap
        else:
            gap += 1
#출력
def print_table(freq, gap, floor):
    print(f"{'계급':<6} {'계급간격':<10} {'도수':<5} {'상대도수':<10} {'누적도수':<8} {'누적상대도수':<12} {'계급값':<5}")
    c_freq = 0 #누적도수
    for i in range(no_c):
        c_freq += freq[i]
        print('%-6s %-14s %-7d %-14.3f %-12d %-18.3f %-10.2f' % 
      (f"{i+1}계급", f"{floor+gap*i}~{floor+gap*(i+1)}", freq[i], freq[i]/len(data),c_freq, c_freq/len(data) , (floor + floor + gap*(i+1))/2))
    print(f"{'합계':<6} { ' ':<14} {sum(freq):<7} {c_freq/len(data):.3f} {' ':<12} {' ':<5}")
#히스토그램 생성
def draw_hist(freq):
    for level in range(max(freq), 0, -1): #최대도수부터 역순으로
        row = ''
        for count in freq:
            if count >= level:
                row += '*' + ' '*5
            else:
                row += ' '*6
        print((f"{1/len(data)*level:.3f}  ")+row)
    print(' '*4 + ' '.join(f"{floor + (gap * i) + (gap / 2):>5.1f}" for i in range(no_c)))

print('도수분포표 출력')
freq , gap = draw_table(data, no_c, gap, floor)
print_table(freq, gap, floor)
print('히스토그램 출력')
draw_hist(freq)
