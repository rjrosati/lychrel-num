# http://en.wikipedia.org/wiki/Lychrel_number

def Lychrel_num(x,print_steps=False):
    steps = 0
    while(x != int(str(x)[::-1])):
        x += int(str(x)[::-1])
        steps += 1
        if print_steps: print(steps, x)
        if steps > 300: return True, steps 
    return False,steps 

max_steps = 0
for x in range(int(5e5),int(1e6)):
    lychrel_q, steps = Lychrel_num(x)
    if not lychrel_q:
        if steps > max_steps:
            longest_num, max_steps = x, steps

print(max_steps, longest_num)
