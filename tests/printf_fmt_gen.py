from jinja2 import Environment, FileSystemLoader
from os import path
from yaml import SafeLoader, safe_load

CASES_FILENAME    = 'printf_fmt.yml'
TEMPLATE_FILENAME = 'printf_fmt_gen.jinja'
TEST_FILENAME     = 'test_printf_fmt_gen.c'

ROOT_DIRPATH = path.dirname(path.dirname(path.join(path.abspath(__file__))))

COMMON_DIRPATH = path.join(ROOT_DIRPATH, 'common')
TESTS_DIRPATH  = path.join(ROOT_DIRPATH, 'tests')

CASES_FILEPATH = path.join(COMMON_DIRPATH, CASES_FILENAME)
TEST_FILEPATH  = path.join(TESTS_DIRPATH, TEST_FILENAME)

def main():
    cases = safe_load(open(CASES_FILEPATH))

    jinja_env = Environment(
        keep_trailing_newline=True,
        loader=FileSystemLoader(TESTS_DIRPATH),
    )
    jinja_template = jinja_env.get_template(TEMPLATE_FILENAME)

    result = jinja_template.render(
        cases=cases,
        escape_flags=escape_flags,
        escape_str=escape_str,
        escape_type=escape_type,
        none_to_zero=none_to_zero,
    )

    with open(TEST_FILEPATH, 'w') as f:
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
    main()
