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
        escape_flags=escape_flags,
        escape_str=escape_str,
        escape_type=escape_type,
        none_to_zero=none_to_zero,
    )

    with open(test_filepath, 'w') as f:
        f.write(result)

def escape_flag(flag):
    return 'KERNAUX_PRINTF_FMT_FLAGS_' + flag.upper()

def escape_flags(flags):
    if len(flags) == 0:
        return '0'

    return '(' + ' | '.join(map(escape_flag, flags)) + ')'

def escape_str(s):
    return '"' + s + '"'

def escape_type(type_):
    return 'KERNAUX_PRINTF_FMT_TYPE_' + type_.upper()

def none_to_zero(num):
    if num is None:
        return '0'
    else:
        return str(num)

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
