
from subprocess import run, PIPE
import os
import argparse

global args

parser = argparse.ArgumentParser(description='Test the implementation of Dijkstra’s algorithm against a few test graphs')
parser.add_argument("--input", help="Path to the folder with the TXT graphs", default=os.path.abspath(os.path.join(os.path.curdir, "inputs/")))
parser.add_argument("--output", help="Path to the folder with the TXT graphs", default=os.path.abspath(os.path.join(os.path.curdir, "outputs/")))

args = parser.parse_args()
print(args)

def main():
    path = args.input
    files_list = list(filter(lambda x: x.endswith(".txt"), os.listdir(path)))

    files_list.sort()

    if files_list == []:
        print("No TXT files found")
        exit(1)

    for f in files_list:
        f_path = os.path.join(path, f)
        c_path = os.path.join(args.output, f)
        print("Testing ", f_path, c_path)
        data = ""
        with open(f_path, 'r') as f:
                data = f.read() # .replace('\n', '')
        c_data = ""
        with open(c_path, 'r') as f:
                c_data = f.read() # .replace('\n', '')

        #print(data)


        p = run(['./a.out'], stdout=PIPE, stderr=PIPE,
                input=data, encoding="utf-8")

        # print("Ret", p.returncode)
        # -> 0
        # print("out", p.stdout)

        # print("expected", c_data)

        # print("err", p.stderr)

        if p.stdout == c_data:
            print("Success")
        else:
            print("Fail")
            #raise Exception("Failed for input : " + f_path)


if __name__ == '__main__':
    main()
