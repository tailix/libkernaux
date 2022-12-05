from jinja2 import Environment, FileSystemLoader
from os import path
from sys import argv
from yaml import safe_load

def main(test_filepath, template_filepath, cases_reg_filepath, cases_orig_filepath):
    cases_reg  = safe_load(open(cases_reg_filepath))
    cases_orig = safe_load(open(cases_orig_filepath))

    cases = cases_reg + cases_orig

    jinja_env = Environment(
        keep_trailing_newline=True,
        loader=FileSystemLoader(path.dirname(template_filepath)),
    )
    jinja_template = jinja_env.get_template(path.basename(template_filepath))

    result = jinja_template.render(
        cases=cases,
        escape_str=escape_str,
        fmt=fmt,
        values=values,
    )

    with open(test_filepath, 'w') as f:
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
                if len(arg[1]) == 1:
                    values += ', ' + escape_char(arg[1][0])
                elif arg[1][0] == 'long long':
                    values += ', (long long)' + str(arg[1][1])
                else:
                    raise RuntimeError('unknown format: ' + str(args))
            else:
                values += ', ' + str(arg[1])

    return values

if __name__ == '__main__':
    print(argv)

    template_filepath   = argv[1]
    cases_reg_filepath  = argv[2]
    cases_orig_filepath = argv[3]
    test_filepath       = argv[4]

    print('test_filepath:       %s' % test_filepath)
    print('template_filepath:   %s' % template_filepath)
    print('cases_reg_filepath:  %s' % cases_reg_filepath)
    print('cases_orig_filepath: %s' % cases_orig_filepath)

    if path.exists(test_filepath) and not path.isfile(test_filepath):
        raise RuntimeError('invalid test file path')
    if not path.isfile(template_filepath):
        raise RuntimeError('invalid template file path')
    if not path.isfile(cases_reg_filepath):
        raise RuntimeError('invalid regular cases file path')
    if not path.isfile(cases_orig_filepath):
        raise RuntimeError('invalid original cases file path')

    main(test_filepath, template_filepath, cases_reg_filepath, cases_orig_filepath)
