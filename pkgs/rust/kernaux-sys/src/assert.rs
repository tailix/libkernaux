use libc::{c_char, c_int};

pub type AssertCB = unsafe extern "C" fn(*const c_char, c_int, *const c_char);

#[link(name = "kernaux")]
extern "C" {
    #[link_name = "kernaux_assert_do"]
    pub fn assert_do(file: *const c_char, line: c_int, msg: *const c_char);

    #[link_name = "kernaux_assert_cb"]
    pub static mut assert_cb: Option<AssertCB>;
}

#[cfg(test)]
mod tests {
    use super::*;

    use std::ffi::{CStr, CString};
    use std::ptr::null;

    static mut LAST_FILE: *const c_char = null();
    static mut LAST_LINE: c_int = 0;
    static mut LAST_MSG: *const c_char = null();

    unsafe extern "C" fn some_assert_cb(
        file: *const c_char,
        line: c_int,
        msg: *const c_char,
    ) {
        LAST_FILE = file;
        LAST_LINE = line;
        LAST_MSG = msg;
    }

    #[test]
    fn default() {
        unsafe {
            assert_cb = None;
            assert!(assert_cb.is_none());

            assert_cb = Some(some_assert_cb);
            match assert_cb {
                None => panic!(),
                Some(actual_assert_cb) => {
                    assert!(actual_assert_cb == some_assert_cb)
                }
            }

            let file_cstr = CString::new("foo.rs").unwrap();
            let msg_cstr = CString::new("bar").unwrap();

            assert_do(
                file_cstr.as_ptr() as *const c_char,
                123,
                msg_cstr.as_ptr() as *const c_char,
            );

            let file = CStr::from_ptr(LAST_FILE).to_str().unwrap();
            let line = LAST_LINE;
            let msg = CStr::from_ptr(LAST_MSG).to_str().unwrap();

            assert_eq!(file, "foo.rs");
            assert_eq!(line, 123);
            assert_eq!(msg, "bar");
        }
    }
}
