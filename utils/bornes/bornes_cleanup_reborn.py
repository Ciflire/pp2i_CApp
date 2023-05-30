import sys


def main():
    csv_source = 'data/schema_edited.csv'
    csv_dest = 'data/schema_clean.csv'
    process_csv(csv_source, csv_dest)

def process_csv(csv_source, csv_dest):
    csv_source = open(csv_source, 'r')
    csv_dest = open(csv_dest, 'w')
    line = csv_source.readline()
    line = csv_source.readline()
    while line:
        x,y, power = get_x_y(line)
        count = 1
        line = csv_source.readline()
        if line:
            x2,y2, power2 = get_x_y(line)
        while line and x == x2 and y == y2:
            x2,y2, power2 = get_x_y(line)
            if x == x2 and y == y2:
                count += 1
            line = csv_source.readline()
        power = power.replace("\n", "")
        csv_dest.write(f"[{x},{y}];{power};{count}\n")


def get_x_y(line):
    coords, power = line.split(";")
    coords = coords.replace("[", "")
    coords = coords.replace("]", "")
    x,y = coords.split(",")
    x,y = float(x), float(y)
    x,y = round(x, 3), round(y, 3)
    return x,y, power


if __name__ == '__main__':
    main()