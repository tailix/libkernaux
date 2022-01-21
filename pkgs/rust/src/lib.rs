#[cfg(test)]
use libc::c_char;

#[link(name = "kernaux")]
extern "C" {
    #[cfg(test)]
    fn kernaux_utoa10(value: u64, buffer: *mut c_char);
}

#[cfg(test)]
mod tests {
    use super::*;

    use std::ffi::CStr;

    #[test]
    fn utoa10() {
        let mut buffer: [i8; 1000] = [0; 1000];
        unsafe { kernaux_utoa10(123, buffer.as_mut_ptr()) };
        let result =
            unsafe { CStr::from_ptr(buffer.as_ptr()) }.to_str().unwrap();
        assert_eq!(result, "123");
    }
}
