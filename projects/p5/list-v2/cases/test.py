import argparse
import os
import subprocess
import difflib

parser = argparse.ArgumentParser(description='project 5 test cases')
parser.add_argument('program_dir', type=str, help='your program')
parser.add_argument('--answer', action='store_true')

args = parser.parse_args()
program_dir = args.program_dir
is_answer = args.answer


def filter_empty_lines(arr):
    return list(filter(lambda x: len(x) > 0, arr))


def print_diff(diff, max_lines=20):
    for i in range(min(max_lines, len(diff))):
        print(diff[i])


def run_test_case(program, name):
    input_file = '%s.in' % name
    output_file = '%s.out' % name

    if is_answer:
        with open(input_file) as fin, open(output_file, 'w') as fout:
            subprocess.run([program], stdout=fout, stdin=fin)
        print('%s: generated' % output_file)
        return True
    else:
        with open(output_file, 'rb') as f:
            answer = f.read().decode('utf-8').splitlines()
        with open(input_file) as fin:
            p = subprocess.run([program], stdout=subprocess.PIPE, stdin=fin)
        output = p.stdout.decode('utf-8').splitlines()

        output = filter_empty_lines(output)
        answer = filter_empty_lines(answer)
        diff = list(difflib.context_diff(output, answer, lineterm=''))

        if len(diff):
            print('')
            print('%s: error' % name)
            print_diff(list(diff))
            print('')
            return False
        else:
            print('%s: pass' % name)
            return True


rpn_executable = os.path.join(program_dir, 'rpn')
cache_executable = os.path.join(program_dir, 'cache')

for f in os.listdir('.'):
    if not f.endswith('.in'):
        continue
    if f.startswith('rpn'):
        run_test_case(rpn_executable, f[:-3])
    elif f.startswith('cache'):
        run_test_case(cache_executable, f[:-3])
