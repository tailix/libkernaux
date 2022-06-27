use libc::{c_char, size_t};

pub const ERROR_MSG_SIZE_MAX: usize = 256;
pub const ERROR_MSG_SLEN_MAX: usize = ERROR_MSG_SIZE_MAX - 1;

#[link(name = "kernaux")]
extern "C" {
    #[link_name = "kernaux_cmdline"]
    // TODO: Rust's "bool" is not guaranteed to be compatible with C's one
    pub fn cmdline(
        cmdline: *const c_char,
        error_msg: *mut c_char,
        argc: *mut size_t,
        argv: *mut *mut c_char,
        buffer: *mut c_char,
        arg_count_max: size_t,
        buffer_size: size_t,
    ) -> bool;
}

#[cfg(test)]
mod tests {
    use super::*;

    use std::ffi::{CStr, CString};

    const ARG_COUNT_MAX: usize = 100;
    const BUFFER_SIZE: usize = 4096;

    #[test]
    fn default() {
        let cmdline = CString::new("foo bar\\ baz \"car cdr\"").unwrap();

        let mut error_msg: [c_char; ERROR_MSG_SIZE_MAX] =
            [0; ERROR_MSG_SIZE_MAX];
        let mut argc: size_t = 0;
        let mut argv: [*mut c_char; ARG_COUNT_MAX] =
            [0 as *mut c_char; ARG_COUNT_MAX];
        let mut buffer: [c_char; BUFFER_SIZE] = [0; BUFFER_SIZE];

        unsafe {
            assert!(super::cmdline(
                cmdline.as_ptr(),
                error_msg.as_mut_ptr(),
                &mut argc,
                argv.as_mut_ptr(),
                buffer.as_mut_ptr(),
                ARG_COUNT_MAX,
                BUFFER_SIZE,
            ));
        }

        assert_eq!(
            unsafe { CStr::from_ptr(error_msg.as_ptr()) }
                .to_str()
                .unwrap(),
            "",
        );
        assert_eq!(argc, 3);
        assert_eq!(unsafe { CStr::from_ptr(argv[0]) }.to_str().unwrap(), "foo");
        assert_eq!(
            unsafe { CStr::from_ptr(argv[1]) }.to_str().unwrap(),
            "bar baz",
        );
        assert_eq!(
            unsafe { CStr::from_ptr(argv[2]) }.to_str().unwrap(),
            "car cdr",
        );
    }
}
