from jinja2 import Environment, FileSystemLoader
from os import path
from yaml import SafeLoader, safe_load

CASES_FILENAME    = 'cmdline.yml'
TEMPLATE_FILENAME = 'cmdline_gen.jinja'
TEST_FILENAME     = 'test_cmdline_gen.c'

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
        escape_str=escape_str,
        escape_int=escape_int,
        len=len,
    )

    with open(TEST_FILEPATH, 'w') as f:
        f.write(result)

def escape_int(n):
    return str(n)

def escape_str(s):
    return '"' + s + '"'

if __name__ == '__main__':
    main()
