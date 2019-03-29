converted = []
final = []

def add_if(n):
    converted.append("if(y + {} >= 0)".format(n))
    converted.append("{")

def ifinator(lin):
    last = -1
    for line in lin:
        index = line.find(" + y") - 1
        if int(line[index-1:index+1].strip()) != last:

            # end if condition
            if last!=-1:
                converted.append("}")

            add_if(int(line[index-1:index+1].strip()))
            converted.append(line)
            last = int(line[index-1:index+1].strip())
        else:
            converted.append(line)
    converted.append("}")

with open(r"C:\Users\targe\Downloads\Chili DirectX Framework\PutPixelImages\asteroid0.txt", "r") as f:
    lines = f.readlines()
    ifinator(lines)

for l in converted:
    try:
        final.append(l.encode('ascii'))
    except:
        final.append(l[3:].encode('ascii'))

with open(r"C:\Users\targe\Downloads\Chili DirectX Framework\PutPixelImages\asteroid0_converted.txt", "wb") as f:
    f.writelines(final)
