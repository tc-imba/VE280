import click
import subprocess
import os
import difflib
import json

args_dir = os.path.join(os.getcwd(), 'args')
answer_dir = os.path.join(os.getcwd(), 'ans')


def filter_empty_lines(arr):
    return list(filter(lambda x: len(x) > 0, arr))


def print_diff(diff, max_lines=20):
    for i in range(min(max_lines, len(diff))):
        print(diff[i])


def run_test_case(program, name, args, is_answer):
    answer_file = os.path.join(answer_dir, name)
    args = [program] + args

    if is_answer:
        with open(answer_file, 'w') as f:
            subprocess.run(args, stdout=f)
        print('%s: generated' % name)
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
            print('%s: error' % name)
            print_diff(list(diff))
            print('')
            return False
        else:
            print('%s: pass' % name)
            return True


@click.command()
@click.option('-a', '--answer', is_flag=True)
@click.argument('program')
def main(answer, program):
    # print(answer)
    # print(program)

    cases = json.load(open('args.json'))
    for name, args in cases.items():
        run_test_case(program, name, args, answer)


if __name__ == '__main__':
    main()
