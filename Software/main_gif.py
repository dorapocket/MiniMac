n = 40
filename = 'sleep'
with open(filename+'.h', 'w') as d:
    d.write('#include <pgmspace.h>\n')
    #
    t = 1
    while t <= n:
        columnum = 25
        all_lines = ""
        #
        with open('sleep/sleep'+str(t).zfill(4)+'.jpg', "rb") as imageFile:
            f = imageFile.read()
            b = bytearray(f)
        print(len(b))
        for i in range(int(len(b) / columnum + 1)):
            b_line = ""
            for j in range(min(len(b) - i * columnum, columnum)):
                b_line += '0x{:02X},'.format(int(b[i * columnum + j]))
            print(b_line)
            all_lines += b_line + "\n"
            #
        d.write('const uint8_t '+filename+str(t-1)+'[] PROGMEM = {')
        d.write(all_lines)
        d.write('};')
        print(t)
        t+=1