import click
import subprocess
import os
import difflib

args_dir = os.path.join(os.getcwd(), 'args')
answer_dir = os.path.join(os.getcwd(), 'ans')


def filter_empty_lines(arr):
    return list(filter(lambda x: len(x) > 0, arr))


def print_diff(diff, max_lines=10):
    for i in range(min(max_lines, len(diff))):
        print(diff[i])


def run_test_case(program, filename, is_answer):
    args_file = os.path.join(args_dir, filename)
    answer_file = os.path.join(answer_dir, filename)
    args = [program]
    with open(args_file) as f:
        line = f.readline().strip()
        if line:
            args += line.split(' ')

    if is_answer:
        with open(answer_file, 'w') as f:
            subprocess.run(args, stdout=f)
        print('%s: generated' % filename)
        return True
    else:
        with open(answer_file, 'rb') as f:
            answer = f.read().decode('utf-8').splitlines()
        p = subprocess.run(args, stdout=subprocess.PIPE)
        output = p.stdout.decode('utf-8').splitlines()

        output = filter_empty_lines(output)
        answer = filter_empty_lines(answer)
        diff = list(difflib.context_diff(output, answer, lineterm=''))

        if len(diff):
            print('')
            print('%s: error' % filename)
            print_diff(list(diff))
            print('')
            return False
        else:
            print('%s: pass' % filename)
            return True


@click.command()
@click.option('-a', '--answer', is_flag=True)
@click.argument('program')
def main(answer, program):
    # print(answer)
    # print(program)

    for f in os.listdir(args_dir):
        run_test_case(program, f, answer)


if __name__ == '__main__':
    main()
