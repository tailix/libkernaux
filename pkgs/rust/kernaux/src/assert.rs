use ctor::ctor;
use libc::{c_char, c_int};
use std::ffi::CStr;

#[ctor]
unsafe fn ctor() {
    kernaux_sys::assert_cb = Some(assert_cb);
}

unsafe extern "C" fn assert_cb(
    file: *const c_char,
    line: c_int,
    msg: *const c_char,
) {
    let file = CStr::from_ptr(file).to_str().unwrap();
    let msg = CStr::from_ptr(msg).to_str().unwrap();

    panic!("{}:{}:{}", file, line, msg);
}

#[cfg(test)]
mod tests {
    use std::ffi::CString;

    #[test]
    #[should_panic(expected = "foo.rs:123:bar")]
    fn default() {
        let file = CString::new("foo.rs").unwrap();
        let msg = CString::new("bar").unwrap();

        unsafe { kernaux_sys::assert_do(file.as_ptr(), 123, msg.as_ptr()) }
    }
}
