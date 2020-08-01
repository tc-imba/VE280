import random
from collections import deque
import string

random.seed(280)


def generate_rpn_i():
    return str(random.randint(1, 9)) + ' '


def generate_rpn_add_minus():
    return random.randint(0, 1) == 0 and '- ' or '+ '


def generate_rpn_multi_div():
    return random.randint(0, 1) == 0 and '* ' or '/ '


def generate_rpn_m():
    a = random.randint(1, 7)
    if a == 1:
        return '( ' + generate_rpn_e() + generate_rpn_add_minus() + generate_rpn_e() + ') '
    elif a == 2:
        return generate_rpn_m() + generate_rpn_multi_div() + generate_rpn_m()
    else:
        return generate_rpn_i()


def generate_rpn_e():
    a = random.randint(1, 3)
    if a == 1:
        return generate_rpn_e() + generate_rpn_add_minus() + generate_rpn_e()
    elif a == 2:
        return generate_rpn_m() + generate_rpn_multi_div() + generate_rpn_m()
    else:
        return generate_rpn_i()


def generate_rpn(index):
    while True:
        try:
            expression = generate_rpn_e()
            if len(expression) > 10:
                generate_rpn_expression(index, expression)
                return
        except:
            continue


def generate_rpn_expression(index, expression):
    filename = 'rpn.%s.in' % index
    with open(filename, 'w') as f:
        f.write('%s\n' % expression)


def random_string(min_length=8, max_length=8):
    length = random.randint(min_length, max_length)
    letters = string.ascii_lowercase + string.ascii_uppercase + string.digits
    return ''.join(random.choice(letters) for i in range(length))


def generate_cache(index, cache_size, memory_size, operations):
    filename = 'cache.%s.in' % index
    used_address = deque([random.randint(0, memory_size - 1) for i in range(5)])
    with open(filename, 'w') as f:
        f.write('%d %d\n' % (cache_size, memory_size))
        for i in range(operations):
            if random.randint(0, 3):
                address = random.randint(0, memory_size - 1)
            else:
                address = used_address[random.randint(0, 4)]
            used_address.popleft()
            used_address.append(address)

            a = random.randint(0, 9)
            b = random.randint(0, 9)
            if 0 <= a <= 3:
                f.write('READ ')
                if b != 0:
                    f.write('%d' % address)
            elif 4 <= a <= 6:
                f.write('WRITE %d ' % address)
                if b != 0:
                    f.write('%d ' % random.randint(0, 10000))
            elif a == 7:
                f.write('PRINTCACHE ')
            elif a == 8:
                f.write('PRINTMEM ')
            elif a == 9:
                f.write('%s ' % random_string())
            if b == 0:
                if random.randint(0, 1) and 7 <= a <= 9:
                    f.write('%s ' % random_string())
                else:
                    f.write('%d ' % random.randint(0, 10000))
            f.write('\n')
            if i == operations - 2:
                f.write('PRINTCACHE\n')
                f.write('PRINTMEM\n')
                f.write('EXIT\n')


def main():
    for i in range(10):
        generate_rpn(i)
    generate_rpn_expression(10, '0 / 0')
    generate_rpn_expression(11, '( 0 + 0')
    generate_rpn_expression(12, '0 +')
    generate_rpn_expression(13, '0 0')
    generate_rpn_expression(14, '')

    generate_cache(0, 3, 8, 20)
    generate_cache(1, 3, 8, 1000)
    generate_cache(2, 10, 100, 1000)
    generate_cache(3, 100, 1000, 10000)


if __name__ == '__main__':
    main()
