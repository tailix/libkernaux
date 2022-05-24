from jinja2 import Environment, FileSystemLoader
from os import path
from yaml import SafeLoader, safe_load

CASES_ORIG_FILENAME = 'printf_orig.yml'
TEMPLATE_FILENAME   = 'printf_gen.jinja'
TEST_FILENAME       = 'test_printf_gen.c'

TESTS_DIRPATH = path.dirname(path.abspath(__file__))

CASES_ORIG_FILEPATH = path.join(TESTS_DIRPATH, CASES_ORIG_FILENAME)
TEST_FILEPATH       = path.join(TESTS_DIRPATH, TEST_FILENAME)

def main():
    cases_orig = safe_load(open(CASES_ORIG_FILEPATH))
    cases = cases_orig

    jinja_env = Environment(
        keep_trailing_newline=True,
        loader=FileSystemLoader(TESTS_DIRPATH),
    )
    jinja_template = jinja_env.get_template(TEMPLATE_FILENAME)

    result = jinja_template.render(
        cases=cases,
        escape_str=escape_str,
        fmt=fmt,
        values=values,
    )

    with open(TEST_FILEPATH, 'w') as f:
        f.write(result)

def escape_char(c):
    return "'" + c + "'"

def escape_str(s):
    return '"' + s + '"'

def fmt(args):
    fmt = ''
    for arg in args:
        if type(arg) is list:
            fmt += arg[0]
        else:
            fmt += arg
    return fmt

def values(args):
    values = ''

    for arg in args:
        if type(arg) is list and len(arg) >= 2:
            if len(arg) >= 3:
                values += ', ' + str(arg[1])
                arg[1] = arg[2]

            if type(arg[1]) is str:
                values += ', ' + escape_str(arg[1])
            elif type(arg[1]) is list:
                values += ', ' + escape_char(arg[1][0])
            else:
                values += ', ' + str(arg[1])

    return values

if __name__ == '__main__':
    main()
