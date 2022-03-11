filename = 'mac_withouteye'
with open(filename+'.h', 'w') as d:
    d.write('#include <pgmspace.h>\n')
    columnum = 25
    all_lines = ""
    with open(filename+'.jpg', "rb") as imageFile:
        f = imageFile.read()
        b = bytearray(f)
    print(len(b))
    for i in range(int(len(b) / columnum + 1)):
        b_line = ""
        for j in range(min(len(b) - i * columnum, columnum)):
            b_line += '0x{:02X},'.format(int(b[i * columnum + j]))
        print(b_line)
        all_lines += b_line + "\n"
    d.write('const uint8_t '+filename+'[] PROGMEM = {')
    d.write(all_lines)
    d.write('};')
