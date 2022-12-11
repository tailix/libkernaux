from jinja2 import Environment, FileSystemLoader
from os import path
from sys import argv
from yaml import safe_load

def main(test_filepath, template_filepath, cases_filepath):
    cases = safe_load(open(cases_filepath))

    jinja_env = Environment(
        keep_trailing_newline=True,
        loader=FileSystemLoader(path.dirname(template_filepath)),
    )
    jinja_template = jinja_env.get_template(path.basename(template_filepath))

    result = jinja_template.render(
        cases=cases,
        escape_str=escape_str,
        escape_int=escape_int,
        len=len,
    )

    with open(test_filepath, 'w') as f:
        f.write(result)

def escape_int(n):
    return str(n)

def escape_str(s):
    return '"' + s + '"'

if __name__ == '__main__':
    print(argv)

    template_filepath = argv[1]
    cases_filepath    = argv[2]
    test_filepath     = argv[3]

    print('test_filepath:     %s' % test_filepath)
    print('template_filepath: %s' % template_filepath)
    print('cases_filepath:    %s' % cases_filepath)

    if path.exists(test_filepath) and not path.isfile(test_filepath):
        raise RuntimeError('invalid test file path')
    if not path.isfile(template_filepath):
        raise RuntimeError('invalid template file path')
    if not path.isfile(cases_filepath):
        raise RuntimeError('invalid cases file path')

    main(test_filepath, template_filepath, cases_filepath)
