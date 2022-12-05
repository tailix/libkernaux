use kernaux_sys::cmdline::*;

use libc::{c_char, c_int, size_t};
use serde::{Deserialize, Serialize};
use std::ffi::{CStr, CString};

static CASES: &'static str = include_str!("../../../../common/cmdline.yml");

#[derive(Debug, Deserialize, Serialize)]
struct TestCase {
    pub cmdline: String,
    pub result: Option<Vec<String>>,
    pub error: Option<String>,
    pub arg_count_max: Option<size_t>,
    pub buffer_size: Option<size_t>,
}

unsafe extern "C" fn assert_cb(
    file: *const c_char,
    line: c_int,
    msg: *const c_char,
) {
    let file = CStr::from_ptr(file).to_str().unwrap();
    let msg = CStr::from_ptr(msg).to_str().unwrap();
    panic!("{}:{}: {}", file, line, msg);
}

fn setup() {
    unsafe { kernaux_sys::assert_cb = Some(assert_cb) }
}

fn cases() -> Vec<TestCase> {
    serde_yaml::from_str(&CASES).unwrap()
}

const ARG_COUNT_MAX: usize = 100;
const BUFFER_SIZE: usize = 4096;

#[test]
fn default() {
    setup();
    for case in cases() {
        if case.error.is_none()
            && case.arg_count_max.is_none()
            && case.buffer_size.is_none()
        {
            if let Some(_) = case.result {
                let case_cmdline = CString::new(case.cmdline).unwrap();
                let mut error_msg: [c_char; ERROR_MSG_SIZE_MAX] =
                    [0; ERROR_MSG_SIZE_MAX];
                let mut argc: size_t = 0;
                let mut argv: [*mut c_char; ARG_COUNT_MAX] =
                    [0 as *mut c_char; ARG_COUNT_MAX];
                let mut buffer: [c_char; BUFFER_SIZE] = [0; BUFFER_SIZE];

                unsafe {
                    assert!(cmdline(
                        case_cmdline.as_ptr(),
                        error_msg.as_mut_ptr(),
                        &mut argc,
                        argv.as_mut_ptr(),
                        buffer.as_mut_ptr(),
                        ARG_COUNT_MAX,
                        BUFFER_SIZE,
                    ));
                }
            }
        }
    }
}
